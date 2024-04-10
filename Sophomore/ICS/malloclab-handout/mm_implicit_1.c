/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memlib.h"
#include "mm.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
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

#ifdef DEBUG
#define DEBUG_PRINTF(...) printf()
#else
#define DEBUG_PRINTF(...)
#endif

/* 16 bytes alignment */
#define ALIGNMENT 16

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#define SIZE_T_SIZE (ALIGN(sizeof(size_t))) // size_t 在 64 位系统下是 8 字节, 但此处对齐 16 字节

#define WSIZE 8 // 64 位中 1 字 = 8 字节
#define DSIZE 16
#define CHUNKSIZE (1 << 12)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define PACK(size, prev_alloc, alloc) ((size) | (((prev_alloc) == 0) ? 0 : 2 ) | (alloc)) // 将 size 和 alloc 合并为一个 word

#define GET(p)      (*(size_t *)(p))         // 读取 p 指向的 word
#define PUT(p, val) (*(size_t *)(p) = (val)) // 将 val 写入 p 指向的 word

#define GET_SIZE(p)  (GET(p) & ~0x7) // 读取 p 指向的 word 的 size
#define GET_ALLOC(p) (GET(p) & 0x1)  // 读取 p 指向的 word 的 alloc
#define GET_PREALLOC(p) (GET(p) & 0x2)

#define HDRP(bp) ((char *)(bp) - WSIZE)                      // 返回 bp 指向的 block 的 header 的指针
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) // 返回 bp 指向的 block 的 footer 的指针

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) // 返回 bp 指向的 block 的下一个 block 的指针
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) // 返回 bp 指向的 block 的上一个 block 的指针

static char *heap_listp, *last_listp;

static void *coalesce(void *bp) {
  size_t prev_alloc = GET_PREALLOC(HDRP(bp));
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
  size_t size = GET_SIZE(HDRP(bp));

  if (prev_alloc && next_alloc) { // 前后都已分配, 无需合并操作
    // 将 bp 的下一个块的 prev_alloc 设为 0
    PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 0, GET_ALLOC(HDRP(NEXT_BLKP(bp)))));
    last_listp = bp;
    return bp;
  }
  else if (prev_alloc && !next_alloc) { // 与下一个块合并
    size += GET_SIZE(HDRP(NEXT_BLKP(bp))); // 先计算出合并后块大小
    PUT(HDRP(bp), PACK(size, 1, 0)); // 写入新的 header, 标为未分配
    PUT(FTRP(bp), PACK(size, 1, 0)); // 写入新的 footer, 标为未分配
  }
  else if (!prev_alloc && next_alloc) { // 与上一个块合并
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    PUT(FTRP(bp), PACK(size, 1, 0));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 1, 0));
    bp = PREV_BLKP(bp); // 将指针移向原来的前一块, 即新块的开始位置
  }
  else {
    // 从前一个块的 header 和后一个块的 footer 计算新块大小
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 1, 0));
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 1, 0));
    bp = PREV_BLKP(bp);
  }
  // 将 bp 的下一个块的 prev_alloc 设为 0
  PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 0, GET_ALLOC(HDRP(NEXT_BLKP(bp)))));
  last_listp = bp;
  return bp;
}

static void *extend_heap(size_t words) {
  char *bp;
  size_t size;

  size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
  if ((long)(bp = mem_sbrk(size)) == -1)
    return NULL;

  // 这里操作时, 将扩展前的 epilogue block 直接覆盖成扩展后的新未分配块的 header
  PUT(HDRP(bp), PACK(size, GET_PREALLOC(HDRP(bp)), 0)); // free block header
  PUT(FTRP(bp), PACK(size, GET_PREALLOC(HDRP(bp)), 0)); // free block footer
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 0, 1)); // new epilogue header

  return coalesce(bp);
}

static void *find_fit(size_t asize) {
  // first fit
  /*char *bp = heap_listp; // 从头开始
  DEBUG_PRINTF("start find fit, bp = %p\n", bp);

  while (GET_SIZE(HDRP(NEXT_BLKP(bp))) > 0) { // 没到 epilogue 就一直遍历
    bp = NEXT_BLKP(bp);
    if (GET_ALLOC(HDRP(bp))) {
      DEBUG_PRINTF("  bp = %p is alloced! %ld\n", bp, GET_ALLOC(bp));
      continue;
    }
    if (GET_SIZE(HDRP(bp)) < asize) {
      DEBUG_PRINTF("  bp = %p's size is not enough, which is %ld. alloc? %ld\n", bp, GET_SIZE(bp), GET_ALLOC(bp));
      continue;
    }
    DEBUG_PRINTF("fit found! bp = %p, asize = %ld\n", bp, asize);
    return bp; // 如果上面两个if的条件都没达成, 自然就是合适的块, 直接 return 即可
  }
  return NULL;*/

  // next fit
  char *bp = last_listp; // 从上一次记录的位置开始
  while (GET_SIZE(HDRP(NEXT_BLKP(bp))) > 0) { // 没到 epilogue 就一直遍历
    bp = NEXT_BLKP(bp);
    if (GET_ALLOC(HDRP(bp))) continue;
    if (GET_SIZE(HDRP(bp)) < asize) continue;
    return bp;
  }
  // 如果到了 epilogue 还没找到, 那么只能从头再来, 一直找到上次记录的位置位置即可
  bp = heap_listp;
  while (bp != last_listp) { // 没到 epilogue 就一直遍历
    bp = NEXT_BLKP(bp);
    if (GET_ALLOC(HDRP(bp))) continue;
    if (GET_SIZE(HDRP(bp)) < asize) continue;
    return bp;
  }
  return NULL;
}

static void place(void *bp, size_t asize) {
  size_t size = GET_SIZE(HDRP(bp)); // 当前未分配块的大小
  DEBUG_PRINTF("start place: bp = %p, asize = %ld, alloc? %ld, size = %ld\n", bp, asize, GET_ALLOC(bp), size);
  
  if ((size - asize) >= DSIZE) {
    DEBUG_PRINTF("  *HDRP(bp) = %d, PACK(asize, 1) = %ld\n", *(HDRP(bp)), PACK(asize, 1));
    PUT(HDRP(bp), PACK(asize, 1, 1)); // 必须先放 header , 不然没办法计算正确的 footer 的位置
    DEBUG_PRINTF("  *HDRP(bp) = %d\n", *(HDRP(bp)));
    // PUT(FTRP(bp), PACK(asize, 1)); // 此处不需要写入 footer
    DEBUG_PRINTF("  bp = %p, alloc? %ld\n", bp, GET_ALLOC(bp));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(size - asize, 1, 0)); // 分割后剩下的未分配块
    PUT(FTRP(NEXT_BLKP(bp)), PACK(size - asize, 1, 0));
    // 将 bp 的下一个块的 prev_alloc 设为 0
    PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 0, GET_ALLOC(HDRP(NEXT_BLKP(bp)))));
  }
  else { // 这种情况下, 如果还要分割, 反而得不偿失
    PUT(HDRP(bp), PACK(size, 1, 1));
    // PUT(FTRP(bp), PACK(size, 1)); // 此处不需要写入 footer
    // 将 bp 的下一个块的 prev_alloc 设为 1
    PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 1, GET_ALLOC(HDRP(NEXT_BLKP(bp)))));
  }
  last_listp = bp;
  DEBUG_PRINTF("finish place bp = %p, alloc? %ld\n", bp, GET_ALLOC(bp));
}

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void) {
  if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
    return -1;
  PUT(heap_listp, 0); // 对齐
  PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1, 1)); // prologue header
  PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1, 1)); // prologue footer
  PUT(heap_listp + (3 * WSIZE), PACK(0, 1, 1)); // epilogue header
  heap_listp += DSIZE;
  last_listp = heap_listp;
  if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
    return -1;
  return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
/*void *mm_malloc(size_t size) {
  int newsize = ALIGN(size + SIZE_T_SIZE);
  void *p = mem_sbrk(newsize);
  if (p == (void *)-1)
    return NULL;
  else {
    *(size_t *)p = size;
    return (void *)((char *)p + SIZE_T_SIZE);
  }
}*/
void *mm_malloc(size_t size) {
  size_t asize;
  size_t extendsize;
  char *bp;

  if (size == 0) return NULL;
  if (size <= DSIZE) asize = 2 * DSIZE; // 至少得是 16 字节
  else asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE); // 16 字节对齐

  if ((bp = find_fit(asize)) != NULL) {
    place(bp, asize);
    return bp;
  }
  DEBUG_PRINTF("fit not found! size = %ld, asize = %ld\n", size, asize);
  extendsize = MAX(asize, CHUNKSIZE);
  if ((bp = extend_heap(extendsize / WSIZE)) == NULL) return NULL;
  place(bp, asize);
  return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *bp) {
  DEBUG_PRINTF("free: bp = %p\n", bp);
  size_t size = GET_SIZE(HDRP(bp));

  PUT(HDRP(bp), PACK(size, GET_PREALLOC(HDRP(bp)), 0));
  PUT(FTRP(bp), PACK(size, GET_PREALLOC(HDRP(bp)), 0));

  coalesce(bp);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size) {
  if (ptr == NULL) return mm_malloc(size);
  if (size == 0) mm_free(ptr);

  char *bp = mm_malloc(size);
  if (bp == NULL) return NULL;
  size_t copySize = MIN(GET_SIZE(HDRP(ptr)), GET_SIZE(HDRP(bp)));
  memcpy(bp, ptr, copySize - SIZE_T_SIZE);
  mm_free(ptr);
  return bp;
}
/*void *mm_realloc(void *ptr, size_t size) {
  void *oldptr = ptr;
  void *newptr;
  size_t copySize;

  newptr = mm_malloc(size);
  if (newptr == NULL)
    return NULL;
  copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
  if (size < copySize)
    copySize = size;
  memcpy(newptr, oldptr, copySize);
  mm_free(oldptr);
  return newptr;
}*/