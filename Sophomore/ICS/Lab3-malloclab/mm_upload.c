#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"
team_t team = {
    /* Team name */
    "MyGO",
    /* First member's full name */
    "",
    /* First member's email address */
    "",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

// #define DEBUG
// #define DEBUG2

#ifdef DEBUG
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

static void check_heap();

/* 16 bytes alignment */
#define ALIGNMENT 16

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#define SIZE_T_SIZE (ALIGN(sizeof(size_t))) // size_t 在 64 位系统下是 8 字节, 但此处对齐 16 字节

#define LIST_MAX 11 // 奇数

#define MAGIC 96 // 实验得到的数

#define WSIZE 8 // 64 位中 1 字 = 8 字节
#define DSIZE 16
#define CHUNKSIZE (1 << 12)
#define INIT_CHUNKSIZE (1 << 6) // 初始化时分配的空闲块的大小
#define UNIT_CHUNKSIZE (1 << 5) // 最小空闲块的大小

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define PACK(size, alloc) ((size) | (alloc))

#define GET(p)      (*(size_t *)(p))         // 读取 p 指向的 word
#define PUT(p, val) (*(size_t *)(p) = (val)) // 将 val 写入 p 指向的 word

#define GET_SIZE(p)  (GET(p) & ~0x7) // 读取 p 指向的 word 的 size
#define GET_ALLOC(p) (GET(p) & 0x1)  // 读取 p 指向的 word 的 alloc

#define HDRP(bp) ((char *)(bp) - WSIZE)                      // 返回 bp 指向的 block 的 header 的指针
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) // 返回 bp 指向的 block 的 footer 的指针

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) // 返回 bp 指向的 block 的下一个 block 的指针
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) // 返回 bp 指向的 block 的上一个 block 的指针

#define GET_SUCC(bp)      (GET(bp))              // 注意这里拿到的是后继对应块的开始 **地址**
#define SET_SUCC(bp, val) (PUT(bp, val))
#define GET_PRED(bp)      (GET(bp + WSIZE))
#define SET_PRED(bp, val) (PUT(bp + WSIZE, val))

static char *heap_listp, *seg_listp; // 初始化后分别指向序言块中间和链表头的第一个

static int get_class(size_t size) { // 根据 size 计算出对应的大小类
  // 大小类按照 2 的整数次幂进行划分, 最小的是 [16,32), 最大的是 [2^(LIST_MAX+3),inf)
  size_t class_index = LIST_MAX - 1;
  if (size < (1 << (LIST_MAX + 3))) {
    class_index = 0;
    size >>= 5; // 因为最小就是 [16,32)
    while (size) {
      size >>= 1;
      class_index++;
    }
  }
  return class_index;
}

static void add_to_class(void *bp) {
  DEBUG_PRINTF("start add_to_class(), bp = %p\n", bp);
  size_t size = GET_SIZE(HDRP(bp));
  size_t class_index = get_class(size);

  char *list = seg_listp + class_index * WSIZE;

  // Size Ordered
  list = GET_SUCC(list);
  char *last_p = NULL;
  while ((list != NULL) && (size > GET_SIZE(HDRP(list)))) { // 按照块大小从小到大的顺序查找待插入的位置
    last_p = list;
    list = GET_SUCC(list);
  }
  if (list == NULL && last_p == NULL) { // 链表为空时
    SET_SUCC(seg_listp + class_index * WSIZE, bp);
    SET_PRED(bp, seg_listp + class_index * WSIZE);
    SET_SUCC(bp, NULL);
  }
  else if (list == NULL && last_p != NULL) { // 放在链表尾部
    SET_SUCC(last_p, bp);
    SET_PRED(bp, last_p);
    SET_SUCC(bp, NULL);
  }
  else if (list != NULL && last_p == NULL) { // 放在链表开头
    SET_SUCC(seg_listp + class_index * WSIZE, bp);
    SET_PRED(bp, seg_listp + class_index * WSIZE);
    SET_SUCC(bp, list);
    SET_PRED(list, bp);
  }
  else { // 插在链表中间
    SET_PRED(bp, last_p);
    SET_SUCC(last_p, bp);
    SET_PRED(list, bp);
    SET_SUCC(bp, list);
  }

  DEBUG_PRINTF("finish add_to_class(), list = %p, GET_SUCC(list) = %p\n", list, GET_SUCC(list));
}

static void remove_from_class(void *bp) { // 将 bp 从原本的大小类链表中移出
  DEBUG_PRINTF("start remove_from_class, bp = %p, GET_ALLOC(HDRP(bp)) = %d\n", bp, GET_ALLOC(HDRP(bp)));
  void *pred_block = GET_PRED(bp);
  void *succ_block = GET_SUCC(bp);
  SET_SUCC(pred_block, succ_block);
  if (succ_block != NULL) SET_PRED(succ_block, pred_block);
  DEBUG_PRINTF("finish remove_from_class!\n");
}

static void *coalesce(void *bp) { // 合并操作
  DEBUG_PRINTF("start coalesce, bp = %p\n", bp);
  void *prev_p = PREV_BLKP(bp);
  void *next_p = NEXT_BLKP(bp);
  size_t prev_alloc = GET_ALLOC(HDRP(prev_p));
  size_t next_alloc = GET_ALLOC(HDRP(next_p));
  size_t size = GET_SIZE(HDRP(bp));

  if (prev_alloc && next_alloc) { // 前后都已分配, 无需合并操作
    DEBUG_PRINTF("finish coalesce and no need to merge!\n");
    return bp;
  }
  else if (prev_alloc && !next_alloc) { // 与下一个块合并
    DEBUG_PRINTF("  case2\n");
    remove_from_class(NEXT_BLKP(bp));
    size += GET_SIZE(HDRP(NEXT_BLKP(bp))); // 先计算出合并后块大小
    PUT(HDRP(bp), PACK(size, 0)); // 写入新的 header, 标为未分配
    PUT(FTRP(bp), PACK(size, 0)); // 写入新的 footer, 标为未分配
  }
  else if (!prev_alloc && next_alloc) { // 与上一个块合并
    DEBUG_PRINTF("  case3\n");
    remove_from_class(PREV_BLKP(bp));
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp); // 将指针移向原来的前一块, 即新块的开始位置
  }
  else {
    DEBUG_PRINTF("  case4\n");
    remove_from_class(PREV_BLKP(bp));
    remove_from_class(NEXT_BLKP(bp));
    // 从前一个块的 header 和后一个块的 footer 计算新块大小
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
    bp = PREV_BLKP(bp);
  }
  DEBUG_PRINTF("finish coalesce!\n");
  return bp;
}

static void *realloc_coalesce(void *bp, size_t asize, int *next) { // 重分配时, 也可以进行合并
  // 通过 next 将合并的细节传出
  // 具体的, 如果当前块只与下一个空闲块合并了, next = 1, 否则为 0
  size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));

  *next = 0;

  if (prev_alloc && next_alloc) { // 前后都已分配, 无需合并操作
    DEBUG_PRINTF("finish realloc_coalesce and no need to merge!\n");
    return bp;
  }
  else if (prev_alloc && !next_alloc) { // 与下一个块合并
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
    if (size >= asize) { // 当可能合并后的大小大于需要的大小(asize), 合并才有意义, 才会去真正执行合并
      remove_from_class(NEXT_BLKP(bp));
      PUT(HDRP(bp), PACK(size, 1));
      PUT(FTRP(bp), PACK(size, 1));
      *next = 1;
    }
  }
  else if (!prev_alloc && next_alloc) { // 与上一个块合并
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    if (size >= asize) {
      remove_from_class(PREV_BLKP(bp));
      PUT(FTRP(bp), PACK(size, 1));
      PUT(HDRP(PREV_BLKP(bp)), PACK(size, 1));
      bp = PREV_BLKP(bp);
    }
  }
  else {
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
    if (size >= asize) {
      remove_from_class(PREV_BLKP(bp));
      remove_from_class(NEXT_BLKP(bp));
      PUT(HDRP(PREV_BLKP(bp)), PACK(size, 1));
      PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 1));
      bp = PREV_BLKP(bp);
    }
  }
  return bp;
}

static void *extend_heap(size_t words) {
  char *bp;
  size_t size;

  size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
  if ((long)(bp = mem_sbrk(size)) == -1)
    return NULL;

  // 这里操作时, 将扩展前的 epilogue block 直接覆盖成扩展后的新未分配块的 header
  PUT(HDRP(bp), PACK(size, 0)); // free block header
  PUT(FTRP(bp), PACK(size, 0)); // free block footer
  SET_SUCC(bp, NULL);
  SET_PRED(bp, NULL);
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); // new epilogue header

  bp = coalesce(bp);
  add_to_class(bp);
  return bp;
}

static void *find_fit(size_t asize) {
  // first fit
  char *bp, *listp; // 从头开始
  int class_index = get_class(asize);
  
  while (class_index < LIST_MAX) {
    listp = seg_listp + class_index * WSIZE;
    bp = GET_SUCC(listp);
    while (bp) {
      if (GET_SIZE(HDRP(bp)) >= asize) return bp;
      bp = GET_SUCC(bp);
    }
    class_index++;
  }
  return NULL;
}

static void *place(void *bp, size_t asize) {
  size_t size = GET_SIZE(HDRP(bp)); // 当前未分配块的大小
  remove_from_class(bp);
  
  if (size < asize + 2 * DSIZE) { // 这时候就算要分割, 新的空闲块也不足 4 字, 没有必要进行分割
    PUT(HDRP(bp), PACK(size, 1));
    PUT(FTRP(bp), PACK(size, 1));
  }
  else if (asize >= MAGIC) { // 这样会让较大的已分配块放在后面, 对于某些情况的空间利用率会有极大的提升
    PUT(HDRP(bp), PACK(size - asize, 0));
    PUT(FTRP(bp), PACK(size - asize, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(asize, 1));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(asize, 1));
    add_to_class(bp);
    bp = NEXT_BLKP(bp);
  }
  else { // 正常分割
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(size - asize, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size - asize, 0));
    add_to_class(NEXT_BLKP(bp));
  }
  return bp;
}

int mm_init(void) {
  if ((heap_listp = mem_sbrk((LIST_MAX + 3) * WSIZE)) == (void *)-1) {
    return -1;
  }
  for (int i = 0; i < LIST_MAX; ++i) { // 初始化每个大小类链表的开头
    PUT(heap_listp + (i * WSIZE), NULL);
  }

  PUT(heap_listp + (LIST_MAX * WSIZE), PACK(DSIZE, 1)); // prologue header
  PUT(heap_listp + ((LIST_MAX + 1) * WSIZE), PACK(DSIZE, 1)); // prologue footer
  PUT(heap_listp + ((LIST_MAX + 2) * WSIZE), PACK(0, 1)); // epilogue header

  seg_listp = heap_listp;
  heap_listp += (LIST_MAX + 1) * WSIZE;
  if (extend_heap(INIT_CHUNKSIZE / WSIZE) == NULL)
    return -1;
  check_heap();
  return 0;
}

void *mm_malloc(size_t size) {
  DEBUG_PRINTF("start mm_malloc(), size = %ld\n", size);
  size_t asize;
  size_t extendsize;
  char *bp;

  if (size == 0) return NULL;
  if (size <= DSIZE) asize = 2 * DSIZE; // 至少得是 32 字节
  else asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE); // 16 字节对齐

  if ((bp = find_fit(asize)) != NULL) {
    bp = place(bp, asize);
    DEBUG_PRINTF("finish mm_malloc()!\n");
    check_heap();
    return bp;
  }
  DEBUG_PRINTF("fit not found! size = %ld, asize = %ld\n", size, asize);
  extendsize = MAX(asize, CHUNKSIZE);
  if ((bp = extend_heap(extendsize / WSIZE)) == NULL) return NULL;
  bp = place(bp, asize);
  DEBUG_PRINTF("finish mm_malloc()!\n");
  check_heap();
  return bp;
}

void mm_free(void *bp) {
  size_t size = GET_SIZE(HDRP(bp));

  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));

  bp = coalesce(bp);
  add_to_class(bp);
  check_heap();
}

void *mm_realloc(void *ptr, size_t size) {
  DEBUG_PRINTF("start mm_realloc, ptr = %p, size = %ld\n", ptr, size);
  char *bp = ptr;
  if (ptr == NULL) bp = mm_malloc(size);
  else if (size == 0) mm_free(ptr);
  else {
    size_t oldsize = GET_SIZE(HDRP(ptr)), asize = (size <= DSIZE) ? 2 * DSIZE : ALIGN(size + DSIZE);
    if (oldsize > asize) {
      // 经试验, 发现这种情况下不分割反而会减少外部碎片化, 从而提高内存利用率
    }
    else if (oldsize < asize) {
      int f;
      if (GET_SIZE(HDRP(NEXT_BLKP(bp))) == 0) { // 如果待扩展的块是最后一个块, 那么就特殊处理, 直接向后扩展需要大小的堆
          size_t temp = MAX((asize - oldsize), UNIT_CHUNKSIZE);
          remove_from_class(extend_heap(temp / WSIZE));
          PUT(HDRP(bp), PACK(oldsize + temp, 1));
          PUT(FTRP(bp), PACK(oldsize + temp, 1));
          return bp;
      }
      bp = realloc_coalesce(ptr, asize, &f); // 重分配的合并操作
      if (f) { // 如果只跟后面空闲块合并
        // 经实验发现不分割反而会减少外部碎片化, 从而提高内存利用率
        // if (GET_SIZE(HDRP(bp)) >= asize + 2 * DSIZE) {
        //   size_t temp = GET_SIZE(HDRP(bp));
        //   PUT(HDRP(bp), PACK(asize, 1));
        //   PUT(FTRP(bp), PACK(asize, 1));
        //   PUT(HDRP(NEXT_BLKP(bp)), PACK(temp - asize, 0));
        //   PUT(FTRP(NEXT_BLKP(bp)), PACK(temp - asize, 0));
        //   add_to_class(NEXT_BLKP(bp));
        // }
      }
      else if (bp != ptr && f == 0) { // 如果只跟前面空闲块合并
        memcpy(bp, ptr, oldsize - SIZE_T_SIZE);
        // 经实验发现不分割反而会减少外部碎片化, 从而提高内存利用率
        // if (GET_SIZE(HDRP(bp)) >= asize + 2 * DSIZE) {
        //   size_t temp = GET_SIZE(HDRP(bp));
        //   PUT(HDRP(bp), PACK(asize, 1));
        //   PUT(FTRP(bp), PACK(asize, 1));
        //   PUT(HDRP(NEXT_BLKP(bp)), PACK(temp - asize, 0));
        //   PUT(FTRP(NEXT_BLKP(bp)), PACK(temp - asize, 0));
        //   add_to_class(NEXT_BLKP(bp));
        // }
      }
      else { // 正常操作
        bp = mm_malloc(size);
        if (bp == NULL) return NULL;
        size_t copySize = MIN(GET_SIZE(HDRP(ptr)), GET_SIZE(HDRP(bp)));
        memcpy(bp, ptr, copySize - SIZE_T_SIZE);
        mm_free(ptr);
      }
    }
  }
  DEBUG_PRINTF("finish mm_realloc!\n");
  check_heap();
  return bp;
}

static void check_heap() {
  #ifdef DEBUG2
  char *bp = heap_listp;
  while (GET_SIZE(HDRP(bp)) > 0) {
    printf("%p: header: [%ld, %ld] footer: [%ld, %ld]\n", 
      bp, GET_SIZE(HDRP(bp)), GET_ALLOC(HDRP(bp)), 
      GET_SIZE(FTRP(bp)), GET_ALLOC(FTRP(bp)));
    bp = NEXT_BLKP(bp);
  }
  printf("-------------------------\n");
  sleep(1);
  #else
  return;
  #endif
}