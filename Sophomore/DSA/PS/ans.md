以下答案仅供参考, 有很多错误和不确定的地方

## PS-01
10. 正着可以, 反着不行: $\log(n^3)=O(\log(n^2))$ 显然推不出 $n^3=O(n^2)$

## PS-02
1. 好的.
2. 
   1. 已会;
   2. 先不测试了.
3. 
   1. 好的;
   2. 好的;
   3. 好的.
4. 可以, 反正都是等比数列求和到最后一项为 n .
5. 
   1. 理解了. 但讲义里也没分析啊...
   2. 进一步理解了.
   3. 取 $\frac{1}{2}$ 的话, `shrink` 之后的装填因子就变成 $1$ 了, 那就又得 `expand` 一次, 还不如等到装填因子 $<\frac{1}{4}$ 再 `shrink` .
6. 这样会让被删除区间后面那段被多次向左移动 $1$ 位, 反而使得时间复杂度退化至 $O(n^2)$ .
7. 特判也就是个 `if` , 不耽误功夫还能爽加 best case. 不特判还要把后面所有元素自己给自己赋值一遍, 太二了.
8. 
   1. 颠倒循环方向会出问题很显然;
   2. `memmove()` 用于拷贝字节, 如果目标区域和源区域有重叠的话, `memmove()` 能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中. —— 百度百科
9.  天才
10. 
    1. 最坏情况就是所有元素全相同;
    2. **F**类成本是 $O(1)$ 的情况就是 `find()` 的 best case(即目标元素是当前查找范围 `[0,i)` 的最后一个元素 `_elem[i-1]` ), 对应的**R**类成本是 $O(\text{\_size} - \text{i})$ ;
    3. 若**R**类成本为 $O(1)$ , 那么此时 `remove()` 没执行, 也就代表 `find()` 结果是没找到, 即 `find()` 的 worst case, 其对应的**F**类成本必然是线性的;
    4. 也许可以这样: 思路大致不变, 但每次 `find()` 的对象是 `_elem[_size-1]` , 如果 `remove()` , 单次时间复杂度只是 $O(1)$ , 否则就将其与 `_elem[i]` 交换. (我不确定这个思路是否可行, 因此这样会破坏向量去重前的顺序)
    5. 因为**R**类成本少了?
    6. 要不还是排序完去重吧... 不过用哈希表实现的 `set` 是不是可行?
11. 
    1. 上学期 OOP 的内容;
    2. 好的, 非常巧妙思路, 爱来自瓷器.
12. 
    1.  确认了, 确实如此;
    2.  加一个判断, 如果 `i+1==j` , 那么就代表这肯定是自己到自己的赋值, 跳过即可;
    3.  说不定编译器会优化? 如果没优化的话, 那么我认为这种改进是值得的, 因为赋值操作可能会很耗时(对于某些成员非常多的类或结构体).
13. 
    1. 已验证;
    2. 可以看成二叉树的样子, 有多少个叶子就多少种成功的可能, 而失败的可能就是叶子间隙的个数(算上最左和最右两边), 肯定是叶子个数+1;
    3. 已验证, 但注意, 往左走只需要比一次, 查找长度+1; 但因为代码实现顺序问题, 往右走需要先否定往左走, 所以需要比两次, 查找长度+2. 到判定相等的情况也是+2;
    4. 这个先不试了.
14. 
    1.  $\frac{10^6}{2^{32}}$ ?
    2.  原来是 $\frac{1-\frac{10^6}{2^{32}}}{2}\times1+\frac{10^6}{2^{32}}\times3+\frac{1-\frac{10^6}{2^{32}}}{2}\times2$, 改之后就变成了 $\frac{1-\frac{10^6}{2^{32}}}{2}\times2+\frac{10^6}{2^{32}}\times1+\frac{1-\frac{10^6}{2^{32}}}{2}\times3$ . 显然改之后的平均比较次数更多.
15. 
    1. 是这样的, 实际上二分查找的版本 A 也有一样的问题;
    2. 之后再说吧...
16. 
    1. 先不验证了;
    2. 显然;
    3. 需要再检查一下查找目标值和返回的下标对应的元素是否相等, 额外时间无非是常数.
17. 啊这, 我的脑子不够用啊啊啊啊啊啊啊.
18. 那就找一个某区间数值分布特别集中, 剩下的特别稀疏的分布即可.
19. 如果是正态分布, 那就得用概率密度函数的反函数(正态分布分位数), 计算插值下标, 感觉好费劲.
20. 
    1. 感觉这个实验有意思, 但我在期末复习啊;
    2. 不太可能捏.
21. 
    1. 先不测了, 老师我对不起您 :(
    2. 先不测了...
22. 
    1. 先不测了...
    2. 先不测了...
23. 
    1. 那可以先开好一个数组, 稍微长一点, 然后一直复用这个数组;
    2. 先不测了捏;
    3. 就是跟我第 10 题最后一问的想法一样;
    4. 进一步优化? 那大概就是哈希表了吧...
24. 巧妙之处就是这里, 因此 `C` 实际上是就地的, 所以就算 `B` 先耗尽, `C` 压根就不用动.
25. 
    1. 那就先比一下两个待归并的序列的最大值最小值;
    2. 大概就是 $O(1)$ ;
    3. 应该是收益少吧, 因此两个序列恰好能直接拼起来而不需线性扫描的概率太低了.
26. https://www.cnblogs.com/shoulinjun/p/3815636.html
    1. 原理如上;
    2. 很明显, 代价就是切分数组所花费的查找时间;
    3. 我感觉是大的, 因为毕竟没有辅助空间比都比不了, 能这么实现很强.
27. 
    1. 以 `test(int k)` 举例: 其返回值为 `M[k >> 3] & (0x80 >> (k & 0x07))` . 首先 `M` 是个 `char` 数组, 因此取下标一次得到的是 $8$ 个比特, 所以下标需要先除 $8$ , 也就是右移 $3$ 位. 那么取好相应的 $8$ 个比特了, 接下来该取到底哪一个比特呢? 就看 `&` 后面的数, 相当于一个 mask. `0x80` 是 `1000 0000` , `(k & 0x07)` 相当于对 $8$ 取余. 这样就可以得到对应的比特位了;
    2. 理解了, 也是加倍扩容;
    3. 大概懂了;
    4. 想不出来;
    5. 无;
    6. 先不学.
28. 
    1. 先把向量中所有元素存到 bitmap, 然后再遍历 bitmap , 从而得到所有元素;
    2. 时间复杂度是 $O(n+m)$ , 空间复杂度是 $O(m)$ ;
    3. 确实, 因为 bitmap 就是按值的顺序存储的.
29. 
    1. 那就把 `T` 数组的后缀先前移过来, `top--` , 然后 shift 后的 `T` 中元素对应的 `F` 数组的元素都自减 1;
    2. 时间复杂度是线性的;
    3. 明显比 Hopcroft 的 $O(1)$ 差很多.
30. 
    1. 确实, 因此每次插入都还是 $O(1)$ , 然后拿到结果数组就直接拿 `T` 数组即可;
    2. 代价就是 `T` 数组不是排好序的.‘

## PS-03
1. 先不写了.
2. 
   1. 链表中秩是按照连接顺序决定的, 位置就是物理位置?
   2. 因为很慢, 没有利用链表挨个访问的优势.
3. 
   1. 不用对可能访问到头尾进行特殊判断;
   2. 时间复杂度肯定不变, 但得益于不用特判, 运行时间会有略微改进(没有仔细思考, 未必正确);
   3. 已验证.
4. 当然不能, 以 `insert()` 举例, 如果先 `pred=x;` 再 `pred->succ=x;` 就会让 `x` 这里形成一个环.
5. 
   1. ez, 略;
   2. 啊? 这还能变化?
6. 
   1. ez, 略;
   2. 啊? 这还能变化?
7. 
   1. 那就不断扫描 $[0,r)$ 中有无 `p->data` (`p` 从 `last()` 一直到 `header`);
   2. 那么 `r++` 的位置就需要换到与 `remove(p);` 同一分支下;
   3. 先不验证了;
   4. 先不设计实现了.
8. 
   1. 理解了;
   2. 好的(提醒一下, 这些源文件都在 `/_share` 文件夹下);
   3. 理解了;
   4. 理解了;
   5. 先不了.
9. 
   1. 原来如此;
   2. 了解了;
   3. 理解了;
   4. 理解了;
   5. 先不了.
10. 
    1. 方便直接返回?
    2. 我感觉不加 `_size < 2` 的特判, 剩下的逻辑也能正常运行;
    3. 先不了;
    4. 先不了.
11. 
    1. 确实可能返回 `header` (当 `n == rank(p)` 时), 从而造成误判(比如 `header` 的值是 $0$ 而要搜索的值 `e` 也是 $0$);
    2. 一个比较笨的方式: 加一个可修改的参数, 相当于把成功与否通过这个参数传出去, 具体实现可以是检查循环后的 `n` 的值.
12. 
    1. 确实;
    2. 因为链表不能随机访问, 而只能顺序访问.
13. 分析可得, 如果按照本题题干描述的那样去操作, 但凡 `p` 的值是最大的, 那么它将被移到最后, 而这样就会让循环后续的 `selectMax(p, n)` 实际查找范围出错.
14. 
    1. 因为 `selectMax()` 太慢了?
    2. 调用 `remove()` 和 `insert()` 就可以了;
    3. 待插入的节点, 待插入的位置;
    4. 先不实现了.
15. 略.
16. 
    1. 还真是, 想要证明的话, 可以先证明还没有有序区间的时候, 最后一个元素一定是和整体最大元素位于一个循环节的(循环节的定义使然), 然后再考虑数学归纳法;
    2. 如果 M 所属的循环节长度为 $1$ , 说明它的位置正好不再需要交换, 相当于在长度为 `r` 的无序前缀中排序, 让 M 这个元素恰好就位的概率, 结果是 $\frac{(r-1)!\times1}{r!}=\frac{1}{r}$ ;
    3. 啊啊啊啊啊啊真不会了.
17. 最特殊的, 1 个原本循环节长度为 $1$ , 交换后 M 原所属循环节消失, 但是新的循环节因为位置正确, 所以长度还是 $1$ ; 然后就是正常的情况, 交换后 M 原所属循环节长度 $-1$ , 新循环节长度仍为 $1$ .
18. 
    1. 参考 https://en.wikipedia.org/wiki/Online_algorithm
    2. 因为是实时抓牌并排序, 需要在线算法;
    3. 起泡算法;
    4. 稳定.
19. 插入排序适合链表, 选择排序适合向量.
20. 
    1. `insert()` 里套用 `search()` 然后再 `remove()`, 相当于重复操作, 不如直接写个 `move()` 让链表一步到位 ;
    2. 好的;
    3. 略;
    4. 略;
21. 
    1. $\frac{1}{n!}$ ;
    2. 1 次;
    3. $O(n^2)$ .
22. 
    1. 链表不能二分查找;
    2. 接口需要有下标访问, 至少是常数时间内完成.
23. 本题答案正确性不定
    1. 可以;
    2. 如果 $n\gg m$ , 那么时间复杂度应该是 $O(m)$ ; 如果 $n\ll m$ , 则是 $O(n+m)\approx O(m)$ .
24. 与第 20 题等题是一个问题, 略;
25. 向量需要辅助空间, 且剩余一路时需要整体 `move` ; 链表在二分的时候很慢.
26. 
    1. 比如 $\{5,4,3,2,1\}$ ;
    2. 参考 https://www.cnblogs.com/ydUESTC/p/16890713.html , 结论是 $\frac{\tbinom{n}{2}}{2}$ 个;
    3. 若逆序对数量为 $I$, 根据讲义, 运行时间应是 $O(n+I)=O(n+\frac{\tbinom{n}{2}}{2})=O(n^2)$ .
27. 
    1. 最少 $0$ 个, 最多 $0+1+\dots+2n-1=n(2n-1)$ 个;
    2. 最少就是全部有序, 最多就是全部倒序.
28. 
    1. 至少减少 $1$ 个, 即交换双方构成的记在后者的那个逆序对; 对于其他元素, 在交换区间前面的不受影响, 交换区间内的可能减少, 但不可能增加(因为换到前面的肯定更小), 交换区间后的不受影响;
    2. 因为这样让交换区间更大, 那么中间的元素更多, 可能减少更多的逆序对;
    3. 最差情况下, 即完全逆序, 也只需要交换大约 $\frac{n}{2}$ 次, 因此总体是 $O(n)$ .
    4. 插入排序具有上述特性, 而起泡排序明显就没有.
29. 
    1. 确实, 就按讲义图示的那样, 比较两个待归并序列的两个元素的时候, 逆序对总数直接加上前一个序列中剩余的元素个数;
    2. 参考 https://blog.csdn.net/zy_dreamer/article/details/130921131 ;
    3. 我感觉没有吧.
30. 
    1. 按讲义里写的, 某些没有指针的语言中需要;
    2. 理解了, 先不实现了.
31. 略.
32. 略.

## PS-04
1. 
   1. 略;
   2. 如果颠倒, 那么每次 `pop()` 后都需要将全栈的元素都向前移动一次, 从而使得单次 `pop()` 的时间复杂度变成 $O(\_size)$ .
2. 
   1. 略;
   2. 无变化.
3. `return` ?
4. 从 $n$ 扩大到 $n^2$ ; 从 $n$ 扩大到 $n^{10}$ .
5. 可以, 都转换成显式维护栈, 但对于算法优化帮助不大.
6. 我感觉不行, 因为每次二分递归的前一次都会往下产生后一次递归的尾递归链, 从而导致无法简单地转换为线性递归.
7. 粗略地看, 应该是得到尾递归的返回值(或者其他形式的计算结果)后, 对其进行简单的计算, 然后返回该值.
8. 额我还没想到...
9. 
   1. 略;
   2. 那么只要栈中出现一左一右且无法匹配的"括号", 那么这两个对应的位置就是错误的位置, 修正的建议可以是将两者其中一个改成另一个对应的"括号".
10. 
    1. 因为合法的括号表达式的匹配方式是对应栈的不断 `pop()` 和 `push()` , 而栈混洗也是对于栈 S 的不断 `pop()` 和 `push()` , 因此二者一一对应;
    2. 略.
11. 略(我还没找到 TAOCP 的资源...)
12. 
    1. $2^{3^4}=8^4$ ;
    2. 啊这, 数学课也不会写出来 "2^3^4" 这种表达式啊;
    3. 略;
    4. 空格对应的项实际上不会在合法的表达式中出现.
13. 
    1. 确实啊;
    2. 如果给定表达式长度的话那确实;
    3. "(1+(1+...1+(1+1))...))"
14. 逆波兰表达式中不需要括号，用户只需按照表达式顺序求值，让堆栈自动记录中间结果；同样的，也不需要指定操作符的优先级。——— 维基百科
15. 不能, 因为还需要执行操作符的优先级.
16. 可以, 但效率相对低, 因为每次队首出队, 不论是什么方式, 最终都需要将队中元素整体前移; 即使采用队尾达到向量尾再前移的方式, 均摊为 $O(1)$ , 其效率仍然低于列表.
17. dijkstra 算法的优先队列优化.
18. 
    1. 感觉是递增序列;
    2. 通过 `if (maxRect < mR)` 实现, 因为相等时不更新, 自然实现"最靠左".
19. 
    1. 比如辅助空间少?
    2. 可以看入栈总数(每个柱仅入栈 2 or 1 次), 因此总体就是 $O(n)$ ;
    3. Brute-Force: 无论什么情况, 空间复杂度都是 $O(1)$ ;
       2-Pass Scan: 矩形高度单增, 保证所有秩都入栈 2 次, 空间复杂度为 $O(n)$ ;
       1-Pass Scan: 矩形高度单增, 保证所有秩都入栈 1 次, 空间复杂度为 $O(n)$ ;
    4. Brute-Force: 无论什么情况, 空间复杂度都是 $O(1)$ ;
       2-Pass Scan: 矩形高度一高一低排列, 保证秩入栈后立刻出栈(较低的矩形的高度呈单减), 空间复杂度为 $O(1)$ ;
       1-Pass Scan: 矩形高度一高一低排列, 保证秩入栈后立刻出栈(较低的矩形的高度呈单减), 空间复杂度为 $O(1)$ ;
    5. Brute-Force: $O(1)$ ;
       2-Pass Scan: $O(n)$ ;
       1-Pass Scan: $O(n)$ .
20. 大致分析一下. 假设输入序列的取值区间相对于其数据类型的取值范围很小, 然后计算一个元素比上一个元素小的概率: $\frac{1}{n}\sum_{k=0}^{n-1}\frac{k}{n}=\frac{n-1}{2n}\rightarrow\frac{1}{2}$ . 然后不严谨地考虑一次 `enqueue()` 需要向前修改 `P` 中的元素个数的期望: $\mathbb{E}=\frac{1}{2}\times0+\frac{1}{2^2}\times1+\frac{1}{2^3}\times1+\dots\approx\frac{1}{2}$ . 因此 `enqueue()` 的均摊时间复杂度是 $O(1)$ . 而 `dequeue()` 的均摊时间复杂度是 $O(1)$ 是显然的.
21. 仅仅是常系数的放缩. 
    P.S. 这里讲义的实现真的没问题吗? 我感觉可以优化一点点, 就是当 `F` 为空的时候, 仍然是一直 `R.dequeue()` 并 `F.enqueue()` , 但 `R` 中最后一个元素 `dequeue()` 后没必要再进入 `F` , 导致多操作两次了. 这一改进会使得讲义中最后 Amortization By Potential 计算不再正确.
22. 
    1. 04Q : `x && (x->key <= e);` 避免了 `x` 为空指针的错误;
    2. 04J: `!S.empty() && ( H[S.top()] >= H[r] )` 避免了 `S` 空时调用 `S.top()` 的错误;
    3. 03D2: `while ( ( -1 != n ) && ( e < p->data ) ); ` 避免了 `n` 为负数时, `p` 指针指向超出范围从而导致错误使用哨兵的 `data` 进行比较的错误.

## PS-05
1. 考虑带自环的路径?
2. 
    1. `depth(v)+height(v)` 实际上是以 `v` 为根节点的子树中最深者的深度, 那么这个值自然不大于整棵树的高度, 即整棵树最深者的深度;
    2. 以 `v` 为根节点的子树包含整棵树最深的叶子.
3. 
    1. **父节点**表示法: `parent()` 可 $O(1)$ 获得, 查找后代需要遍历所有节点, 花费 $O(n)$;
       **孩子节点**表示法: `parent()` 需要遍历所有节点, 花费 $O(n)$ , 查找后代花费 $O(childNum)$ 获得;
       **父节点-孩子节点**表示法: 均为 $O(1)$ ;
    2. **父节点**表示法: 额外写入新节点的父亲的秩即可;
       **孩子节点**表示法: 插入到新节点父亲的孩子链表尾部即可;
       **父节点-孩子节点**表示法: 额外写入新节点父亲与孩子的秩;
    3. 略;
    4. **父节点**表示法: 两节点不断向上找父亲, 直至重合;
       **孩子节点**表示法: 若处于同一公共祖先则位于同一链表下, 不断向上找父亲直至满足上述条件;
       **父节点-孩子节点**表示法: 同上;
4. 
   1. 是;
   2. 按照讲义上的映射关系即可.
5. 真二叉树: 节点的度为 $0$ 或 $2$ . 反过来如果是指任一真二叉树通过引入外部节点转化为二叉树, 那么是可以的.
6. 
   1. 是;
   2. 未必;
   3. 是;
   4. 未必;
   5. 写两个更新高度的函数, 一个带 `break;` , 另一个不带;
   6. 随机测例+统计平均更新高度次数+统计无效更新次数.
7. 
   1. 略;
   2. 勤奋策略适用于需要频繁访问的信息, 懒惰策略适用于不需要频繁访问的信息.
8. 
   1. 略;
   2. 感觉没区别, 左右不是等价的吗?
9. 就按题干 tips 的思路来, 考查左侧路径末端节点刚被访问完的时刻, 此时原树遍历问题拆解成左侧路径上的每颗右子树的遍历问题, 从而实现归纳证明.
10. 
    1. 考察每次访问一个节点后栈的情况, 算法的操作是将右孩子入栈, 并且向左孩子走; 注意到入栈 1 个节点, 遍历深度+1 , 因此栈的深度不会超过最大遍历深度, 即树的高度;
    2. 因为入栈的时候, 只会把右孩子, 也就是右子树的根节点入栈, 再往左孩子走; 相当于每入栈一个节点, 实际上是走过 1 个左祖先, 因此栈的最大深度不会超过左祖先的总和的最大值;
    3. 每个节点只有右孩子的超超超高的树;
    4. 每个节点只有左孩子的超超超高的树;
    5. 粗略地考虑, 若树的节点数足够多, 期望, 也就是理想情况下, 输入的二叉树无限接近满二叉树, 那么这两种上界一致, 比值为 1.
11. 类似地, 每次沿左侧藤遍历后, 相当于把问题分解为访问完左子树后, 访问自身, 再处理右子树. 此时右子树就是更小规模的相同问题, 可以归纳证明.
12. 
    1. `first()` 只需要从根节点不断往左走, 最后一个非空节点即返回值;
    2. 略;
    3. 时间: $O(h)\approx O(\log n)$ , 空间: $O(1)$ ;
    4. `succ()` 思路: 如果有左孩子就返回左孩子, 不然有右孩子返回右孩子, 没孩子就找最低的有右孩子的祖先的右孩子, 并且这个右孩子不能是自己的祖先; `first()` 就直接返回根节点;
    5. `succ()` 思路: 如果自己是右孩子则返回父亲, 如果自己是左孩子且父亲有右孩子, 则返回父亲的右孩子对应子树的 `first()` , 如果自己是左孩子且父亲无右孩子则返回父亲; `first()` 思路是一直尽可能向左孩子走, 实在不行才往右孩子走, 直至叶子节点返回.
13. 好的, 谢谢提醒捏.
14. 添加特判 `! IsRoot(x)` , `#define IsRoot(x) ( ! ( (x).parent ) )` .
15. 注意到中序遍历的最终节点, 应当是无右孩子且任一祖先(除根节点外)均无左孩子, 那么根据示例代码, 算法会不断往上找, 直至根节点, 然后再往上找一次, 这时就是空指针, 然后返回, 从而落实题目所述功能.
16. 那么可以将原本 `if ( S.top() != x->parent )` 改成通过判断 `S.top()` 的左/右孩子是否为 `x` .
17. 使用 Amortization By Accounting , 每个节点都是 1 次 `visit()` 搭配 1 次 `pop()` 或者 1 次 `push()` , 因此每个节点相当于分配 2 个 "coin", 而总代价不会超过 $2n$ , 因此均摊时间复杂度为 $O(n)$ .
18. 这个问题的本质是后序遍历的结果是否保留了二叉树的全部信息, 而显然没有, 因此不行.
19. 
    1. 这证个什么, 代码就这么写的;
    2. 按深度单调排列是因为每次入队都是出队的孩子, 自然深度不断增加; 而深度相差不超过 $1$ 可以反证, 如果相差超过 $1$ , 那么这两个相差过大的节点的后者(深度大者)入队时必须是其父亲出队, 而队中不可能有其父亲深度的节点, 矛盾;
    3. 代码中入队次序如此;
    4. 代码就这么写的;
    5. True.
20. 
    1. 因为二叉树是树状的, 只能依照父子关系访问, 如果按照层级访问, 就需要一个缓存空间来实现;
    2. 最接近满树的.
21. 
    1. 略;
    2. 大部分情况无法利用系统缓存.
22. 略.
23. 略.
24. 略.
25. 
    1. 编码成本估计过程可以用频率代替概率进行计算, 因此交换子树后, 只要要能使频率高/低者更高/低, 那么对应的期望自然会减小, 从而使编码成本降低;
    2. 取决于交互两子树的高度差以及子树总频率的差.
26. 参考 https://blog.csdn.net/weixin_42881755/article/details/90714191 .
27. 示例代码通过构建好 Huffman 树之后, 将每个 `HuffChar` 及其编码放入哈希表中以供后续使用.
    1. `huffman_generateTree.cpp`
    2. 用一个`List` 保存所有 Huffman 树的指针;
    3. 通过 `HuffChar` 的封装;
    4. 参考 `Huffman_PQ.h` 中最后那些宏定义与头文件引入.
28. 思路可简单参考 https://codeleading.com/article/473650844/ .
29. 略.

## PS-06
1. `searchAll(e)` 采取类似区间查找的方式, 待查找区间为 $(e-\epsilon,e+\epsilon)$ , 其中 $\epsilon$ 为"极小真值"(针对关键码的数据类型而言), 参考教材习题解答, 本方法的时间复杂度为 $O(k+h)$ , 其中 $k$ 为查找到的关键码个数, $h$ 为 BST 的高度.
2. 先序相当于左右孩子的关键码都比自身的大, 且右边的更大, 那么搜索的时候就不能根据关键码的序进行二分查找, 而是需要逐个比较, 再决定往左 or 往右走, 比较次数明显增加; 后序同理. 对于层级遍历, 那信息量更少了, 只能保证上层比下层小, 也就是孩子比父亲大, 但是孩子之间的关系就不知道了, 因此也不能二分查找, 只能逐个比较.
3. 因为还有 `Splay` 这种非静态的 `search()` 方法.
4. 因为没得考虑? BST 就已经从数据结构上将二分的方式定死了. 而搜索失败时的返回值实际上也由一步一步的向下搜索决定好了.
5. 太巧妙了! 因为 `search()` 返回的是引用! 所以当没有树根的时候, `search()` 返回树根的引用, 后面直接给返回值赋值为 `new BinNode<T>` 的同时也相当于修改了树根这个指针, 从而正确处置首个节点插入这种情况.
6. 那么就在 `insert()` 等函数内部实现 `search()` 的逻辑, 或者直接将 `insert()` 等函数改为递归实现.
7. 
   1. 讲义写的, `u` 有可能就是 `x` ;
   2. `u==x` 的情况可能是待删除的节点(即 `x` )的直接后继就是它的右孩子.
8. 如果待删除节点有两个孩子, 则会进入最后一个分支, 其中会调用 `succ()` , 其时间复杂度为 $O(h)$ , 虽然不会影响整体的时间复杂度, 但会增加常系数, 从而增加运行时间.
9. 
   1. 不会;
   2. 好的.
10. 
    1. 采用加锁的方式;
    2. 受到其他线程的影响;
    3. 也许可以局部加锁.
11. 
    1. 因为可以将插入序列看成按照层级遍历得到的结果, 那么越平衡的 BST , 相对来说每层的节点数越多, 从而使得每层的可能的排列组合越多, 最终对应越多的插入序列;
    2. 略.
12. 可以将树的形成看成是一个节点和两个子树的拼合过程, 那么子树的节点数就分别是 $k-1$ 和 $n-k$ , 就自然可以得到递推式 $S(n)=\sum_{k=1}^{n}S(k-1)\cdot S(n-k)$ , 从而证明 BST 的数量是卡特兰数.
13. 局部性可以考虑成一堆值域很小的关键码和极少距离它们非常远的关键码, 这就导致可能某一侧的子树节点很多但另一侧几乎没有; 单调性就会使 BST 退化为单链; 周期性可以考虑一个特例作为思路: `3 2 1 6 5 4 9 8 7` .
14. 确实, 因为只是修改父亲和孩子们的指针而已, 常数个赋值操作.
15. 
    1. 只要中序遍历的结果一致, 那么任何两棵树都可以通过适当的 zig/zag 得到;
    2. 参考讲义习题 7-15, 应该是 $2n-2$ ;
    3. 参考讲义习题 7-15, 先找到树的最左侧通路, 然后从下往上依次遍历, 如果有右孩子则一直 zag, 这样将会使任意一颗树转化成左偏的单链;
    4. 略.
16. 
    1. 那么按照讲义一致的思路, 设 $S(h)$ 为高度 $h$ 下最少的节点数, 递推关系为 $S(h)=1+S(h-1)+S(h-3)$ ; 接下来令 $g(h)=S(h)-S(h-1)$ , 则有 $g(h)=g(h-1)+g(h-3)$ , 尝试幂函数的形式, 令 $g(h)=a^h$ , 那么可得 $a^3-a^2=1$ , 解出 $g(h)\approx1.4656^h$, 因此有 $S(h)-S(h-1)=1.4656^h$ , 从而 $S(h)\approx\sum_{k=1}^{h}1.4656^k$ , 从而 $S(h)\approx O(1.4656^h)$ ; 因此反过来, 高度不会超过 $O(\log n)$ ;
    2. 退让常数步仍然是渐进平衡的, 因为只是修改上一问递推式中的常数项, 从而不会影响最终函数为指数形式.
17. 
    1. 假设左子树比右子树高 1, 然后让左子树为满树, 右子树最少是单链, 设总树高度为 $h$ , 那么两子树规模之差为 $(2^{h-1}-1)-(h-2)$ ;
    2. 略.
18. 可以根据上一题得到思路, 如果使用规模平衡, 那么可能导致高度相差过大, 而树的各种操作的复杂度更多是与高度相关, 而非规模.
19. 
    1. 删除最右侧的(中序遍历最后一个)节点即可;
    2. 任意 $n$ 长度的插入序列, 都可以看成 $[0,n-1]$ 范围内的数; 之后只需要按照需要形成的树的层级遍历顺序依次插入即可;
    3. 参考教材习题解析 7-17 中的思路, 只需要将之前的 Fibonacci 树稍微修改一下, 使得每次需要重平衡的节点都需要进行双旋即可; 具体修改思路: 让除了一直往右侧那个支路上以外的内部节点的平衡因子为 $-1$ , 最右侧支路上的内部节点保持为 $1$ , 然后删除中序遍历最后一个节点, 就会保证每次都需要双旋解决当前失衡节点的同时失衡会一直向上传播至根节点;
    4. 仍然是按照层级遍历顺序依次插入, 但记得要按照修改后的 Fibonacci 树的层级遍历顺序.
20. 
    1. 根据平衡因子的定义, 其计算只依赖于孩子的高度, 那么插入后改变高度之后, 只会影响其祖先们的平衡因子;
    2. 因为 `_hot` 一定是至多只有一个孩子的节点, 且有孩子时只会插入到 `_hot` 的空孩子位置, 因此 `_hot` 的平衡因子的绝对值不可能增大, 从而不会失衡;
    3. 插入前祖先们平衡因子的绝对值均为 $1$ 且正负与插入路径的左右相对应(讲义该节的例子非常好);
    4. 必然.
21. 
    1. 同第 20 题第 1 问;
    2. 首先, 删除一节点有几率影响其父亲的高度, 若不影响, 则父亲可能失衡, 但更高的祖先们因为父亲高度不变而不受影响; 若影响, 说明删除的节点位于更长的子链上, 父亲高度减 $1$ , 但父亲不会失衡, 更高的祖先们平衡因子可能变化, 但变化者一定是因为其变化的孩子位于自己更长的子链上, 这样只会让自己的平衡因子绝对值减 $1$ , 反而更平衡, 直至碰到某个祖先, 其位于自己短链上的孩子高度减 $1$ , 自身高度不变但失衡; 综上, 至多一个祖先失衡;
    3. 见上一问的回答.
22. 
    1. 省略无需重平衡的情况, 剩下可能的组合为: `-2 -1` , `2 1` , `-2 1` , `2 -1` ;
    2. 不会, 因为没有失衡且有平衡因子为 $0$ 的情况;
    3. 示例代码的处理方式是选择与父亲同方向的孩子, 相当于优先 zig-zig/zag-zag 操作, 更为简便.
23. 
    1. 省略无需重平衡的情况, 剩下可能的组合为: `1 2` , `0 2` , `-1 -2` , `0 -2` , `-2 1` , `2 -1` ;
    2. 会;
    3. 同第 22 题第 3 问.
24. 
    1. 确实;
    2. 因为是在 `rotateAt()` 的参数中调用的 `tallerchild` , 所以会让 `rotateAt` 即进入 zig-zig/zag-zag 操作分支.

## PS-07
1. 这不是 07-E 节的内容吗... 非重点, 略.
2. 非重点, 略.
3. 非重点, 略.
4. byd就打不对小节号是吧, 这题对应的是 07-F 节的内容.
   额, 这结论真的对吗?
5. 反证, 假如存了三份及以上, 如果它们互不相邻, 则说明这条线段不连续, 显然不可能; 如果它们有两个相邻的, 那么按照贪心策略, 这两个的父节点应当存储, 而不是它们两个存储, 亦矛盾.
6. 什么玩意, 这题.
7. 本题对应的是 07-A[1-2] 节的内容.
   1. 预处理过程就是排序+记录小于等于当前点的总点数, 每次查询只需要二分查找即可;
   2. 有, 空间复杂度为 $O(n^2)$ , 见讲义 07-A2 节.
8. 本题对应的是 07-A[1-2] 节的内容.
   1. 类似第 7 题第 1 问, 只不过记录的是小于等于当前点的值的总和;
   2. 有.
9. 本题对应的是 07-A1 节的内容.
   首先先证明单次查询的下界: 先包括汇报总点数 $k$ , 有个 $O(k)$ ; 之后考虑查询区间的下界, 若采用基于比较的方法, 那么显然下界是 $O(\log n)$ ; 因此单次查询的下界是 $O(k+\log n)$ . 接着考虑实现此下界所需的预处理时间的下界, 因为要实现查询的下界必须要求有序, 那么自然有排序的时间, 其下界为 $O(n\log n)$ , 其次记录小于等于当前点的总点数, 那么自然需要遍历所有点, 其下界为 $O(n)$ , 因此预处理时间的下界为 $O(n\log n)$ . 而遍历所有点进行存储的空间复杂度自然为 $O(n)$ .
10. 
    1. $O(n^2)$ ;
    2. 确实;
    3. 确实;
    4. 确实;
    5. 需要稍加修改, 矩阵的每个点需要存储小于等于对应点的值的所有点的总数+所有点, 因此空间复杂度会升至 $O(n^3)$ .
11. 本题对应的是 07-B1 节的内容.
    1. 该版本的 BST 本质上就是允许关键码重复的 BST 的特殊情况;
    2. 因为命中的一定是不大于查找关键码的最大者, 返回值语义与版本 C 一致;
    3. $1\log1+2\log2+\dots+(n-1)\log(n-1)=O(n\log n)$ .
12. 本题对应的是 07-B1 节的内容.
    1. 因为 `x_1` 和 `x_2` 一定有个最低公共祖先(LCA), 那么之后二者的查找路径可能涉及的区间一定是被这个 LCA 一分为二的, 自然彼此无交; 剩下路径上分开的子树, 也可以用类似的想法证明;
    2. 确实;
    3. 考虑子树的个数小于等于搜索路径在 LCA 下的部分的拐点个数小于等于树高, 因此为 $O(\log n)$ .
13. 本题对应的是 07-B1 节的内容.
    1. 与第 12 题第 1 问同理;
    2. 确实.
14. 本题对应的是 07-B1 节的内容.
    1. 等同于 `search(e-epsilon)` , 其中 $\epsilon$ 为关键码的数据类型的最小"正"元;
    2. 先调用 `searchFirst(e)` , 然后再正常继续删除的逻辑;
    3. 等同于 `search(e+epsilon)` ;
    4. 先调用 `searchLast(e)` , 然后再正常继续删除的逻辑;
    5. 相当于使用区间查找 $(e-\epsilon,e+\epsilon)$ 的逻辑, 但是碰到讲义中说的拐点的子树时直接累计子树规模, 最后返回总和;
    6. 按照讲义上的区间查找逻辑就ok;
    7. 按照 `searchAll(e)` 的逻辑附加上依次删除的逻辑即可;
    8. `insert(e)` 需要记得按照插入先后决定顺序, 也就是说如果碰到相等的关键码自己需要往右走, 而不是往左走.
15. 本题对应的是 07-B1 节的内容.
    1. 确实;
    2. 因为区间查找在 LCA 前一直都是只有一条搜索路径, 所以一层只有 `Recursion` ; LCA 后将会二分递归一次, 之后都是线性递归, 二分递归后将产生两条搜索路径, 它们分别会在每层产生至多 2 个前三类节点; 综上, 任一深度上前三类节点不超过常数个;
    3. 与第 12 题第 1 问同理.
16. 本题对应的是 07-B2 节的内容.
    1. X-树依照所有点的 x 坐标正常构建; 然后每个X-树中的节点需要再构建其对应X-区间内所有点的Y-树;
    2. 正常构造X-树需要 $O(n\log n)$ , 而每个X-树中的节点需要再构建其对应X-区间内所有点的Y-树, 那么每个节点需要 $O(r_x\log r_x)$ , 其中 $r_x$ 为当前节点对应的X-区间的总点数, 因此构建Y-树导致的额外时间复杂度为 $O(n\log n+2\times\frac{n}{2}\log\frac{n}{2}+4\times\frac{n}{4}\log\frac{n}{4}+\dots+n\times\frac{n}{n}\log\frac{n}{n})=O(n\log(n+\frac{n}{2}+\frac{n}{4}+\dots))=O(n\log(2n-1))=O(n\log n)$ ; 综上, 总时间复杂度为 $O(n\log n)$ ;
    3. 法 1: 根据讲义的思路, 每个点至多存在 $O(\log n)$ 个Y-树上, 因此总空间复杂度为 $O(n\log n)$ ;
       法 2: 每颗Y-树的空间复杂度为 $O(r_x\log r_x)$ , 总和为 $O(n\log n+2\times\frac{n}{2}\log\frac{n}{2}+4\times\frac{n}{4}\log\frac{n}{4}+\dots+n\times\frac{n}{n}\log\frac{n}{n})=O(n\log n)$ .
17. 本题对应的是 07-B2 节的内容. (正确性待定)
    1. 最坏情况: 首先查询区间的 x 区间尽可能靠近树的 x 范围, 这样会使得在X-树中遍历找到的Y-树个数为 $\approx2\log n=\Theta(\log n)$ 个; 而在每个Y-树中都需要花费 $\Theta(\log r_x)=O(\log n)$ 的时间进行查找; 因此总时间复杂度为 $O(\log^2 n)$ ;
    2. 那么只要让查询区域每一个维度(除最后一个维度外)都接近树的每个维度的取值范围即可.
18. 本题对应的是 07-D 节的内容.
    1. 新插入的点插入后, 依照插入时的搜索路径依次更新 y-list, 同时更新 y-list 的指向, 使得搜索路径上的节点的新插入的 y-list 元素正确指向其他 child y-list (依照 y 区间左开右闭的原则); 而对于删除, 也是先搜索, 根据搜索路径依次删除 y-list 中的对应元素, child y-list 的删除也是按照路径顺序删除即可;
    2. 应该都是 $O(\log n)$ , 因为都需要顺着搜索路径建立/删除 y-list 及其指向连接.
19. 本题对应的是 07-B2 节的内容.
    1. 因为可以将 Quadtree 相邻两个节点"捏合"在一起, 便是 2d-Tree;
    2. 不需要记录划分维度; 构造直接四分, 缩短运行时间; 查询递归一次相当于原来 2d-Tree 的两次.
20. 本题对应的是 07-B3 节的内容.
    1. 我感觉不行...
    2. $O(n\log n+2\times\frac{n}{2}\log\frac{n}{2}+\dots)=O(n\log n)$ .
21. 本题对应的是 07-B3 节的内容.
    我感觉不行, 因为如果自底而上, 那么需要先知道划分后的结果再得到划分前的区域, 这明显是不可能的.
22. 本题对应的是 07-B3 节的内容.
    1. 这个策略与 PA3 的 CST 3-3-2 Nearest Neighbor 一题中使用的优化策略一致;
    2. 略.
23. 本题对应的是 07-B5 节的内容.
    1. 应该不需要;
    2. 因为内部节点只存储分割维度和分割值, 叶节点存储对应点, 那么总节点数不超过 $2n$ , 空间复杂度为 $O(n)$ .
24. 本题对应的是 07-B5 节的内容.
    wtf... 参考 https://zhuanlan.zhihu.com/p/629081049
25. 本题对应的是 07-B6 节的内容.
    确实, 思路巧妙.
26. 本题对应的是 07-B6 节的内容.
    1. 按照递推式, 那么需要构造一个输入, 使得每 4 个孙子里都有 2 个需要发生递归, 那可以构造一个恰好的情况, 就是查询区域为从左下角开始的, 然后正好使 4 个孙子的左上和右下发生递归, 每一次都恰好如此;
    2. 这是可能的, 只要让每 4 个孙子里左下角的区域尽可能小就可以.
27. 本题对应的是 07-B6 节的内容.
    1. 解 $\sqrt{n}=\log_2^2n$ , 得 $n=65536$ ;
    2. 解 $\sqrt{n}=10\log_2^2n$ , 得 $n>4\times10^7$ .

## PS-08
1. 以下摘抄自讲义:
   时间: 刚被访问过的节点, 极有可能很快地再次被访问
   空间: 下一将要访问的节点, 极有可能就在刚被访问过节点的附近
2. 仍然是 $\Omega(n)$ .
3. 
   1. 因为第 1 轮过后, 该子集的节点均曾依次被推送至根, 因此最靠近根的 $r$ 个节点均来自该子集, 后续周期访问时也只会涉及到这些节点;
   2. 由第 2 题结论知.
4. 确实.
5. 
   1. 可能性太多了, 可以参考讲义中旋转的 4 种可能进行讨论;
   2. 最大是减半吧;
   3. 考虑一条单链将最深节点伸展到根.
6. 可能不成立, 因为推导的时候是 $A_i^{(k)}\leq1+3\Delta rank(v)=O(1+\log n)=O(\log n)$ . 如果前面那个 $1$ 变成含 $n$ 的表达式, 时间复杂度自然无法保证还是 $O(\log n)$ .
7. 略.
8. 本题对应的是 08-B2 节的内容.
   略.
9. 本题对应的是 08-B1 节的内容.
   略.
10. 将每 $d$ 代合成为 $1$ 个超级节点, 那么超级节点内部的关键码个数为 $1+2+\dots+2^{d-1}=2^d-1$ , 其子超级节点个数应当为 $2^d$ , 所以关键码总是恰好比外部节点少 $1$ 个.
11. `BTNode` 里哪定义了向量的容量?
12. 略.
13. 
    1. $N\in[2\lceil\frac{m}{2}\rceil^{h-1}-1,m^h-1]$ ;
    2. 范围跨度为 $m^h-2\lceil\frac{m}{2}\rceil^{h-1}\approx m^{h-1}\left(m-\frac{1}{2^{h-2}}\right)=O(m^h)$ , 以指数速度增长;
    3. 意味着高度增高很少, 就能容纳额外巨量的关键码.
14. 
    1. 略;
    2. 略.
15. 讲义 08-B2 节"分裂"部分的示意图应该是 6 阶 B-树.
    1. 确实;
    2. 确实.
16. 
    1. 插入的节点的所有祖先都恰好有 $m-1$ 个关键码;
    2. 考虑每个节点恰好有 $m-1$ 个关键码的概率: $\frac{1}{m^h}$ , $h$ 为该节点的高度, 那么发生上述情况的概率应该是 $\frac{1}{m}\cdot\frac{1}{m^2}\cdot\dots\cdot\frac{1}{m^{\log n}}=\frac{1-\frac{1}{m^{\log n-1}}}{m-1}$ ;
    3. 分裂次数的期望大致为 $\frac{1}{m}\times1+\frac{1}{m^2}\times2+\dots+\frac{1}{m^h}\times h=\frac{1}{m-1}+\frac{m^h+h-hm-m}{(m-1)^2m^h}=O(1)$ .
17. 
    1. 略;
    2. 因为长期来看, 这样操作不会减小该层节点的关键码数量, 因此早晚会满, 还不如直接上溢, 扩充整棵树的关键码容量, 有些类似向量翻倍扩容的策略.
18. 略.
19. 确实, 内部节点的直接后驱确实只能位于叶子节点中, 否则还可以继续往下找, 直至叶子节点.
20. 
    1. 如果一味合并, 那很可能导致合并后的节点的关键码超过 $m-1$ 个, 之后还需要上溢处理, 效率太低;
    2. 不可以, 因为这样虽然避免了当前处理不会上溢, 但相当于提高了空间利用率, 从而使得后续发生上溢的概率增大, 效率仍会降低.
21. (正确性待定)
    1. 删除的叶节点的所有祖先恰好都只有 $\lfloor\frac{m}{2}\rfloor$ 个关键码, 且它们的相邻兄弟也只有 $\lfloor\frac{m}{2}\rfloor$ 个关键码;
    2. 考虑每个节点恰好有 $\lfloor\frac{m}{2}\rfloor$ 个关键码的概率: $\frac{1}{\lfloor\frac{m}{2}\rfloor^h}$ , 发生上述情况的概率为 $\frac{1}{\lfloor\frac{m}{2}\rfloor}\cdot\frac{1}{\lfloor\frac{m}{2}\rfloor^2}\cdot\dots\cdot\frac{1}{\lfloor\frac{m}{2}\rfloor^{\log n}}=\frac{1-\frac{1}{\lfloor\frac{m}{2}\rfloor^{\log n-1}}}{\lfloor\frac{m}{2}\rfloor-1}$ ;
    3. 合并次数的期望大致为 $\frac{1}{\lfloor\frac{m}{2}\rfloor}\times1+\frac{1}{\lfloor\frac{m}{2}\rfloor^2}\times2+\dots+\frac{1}{\lfloor\frac{m}{2}\rfloor^h}\times h=\frac{1}{\lfloor\frac{m}{2}\rfloor-1}+\frac{\lfloor\frac{m}{2}\rfloor^h+h-h\lfloor\frac{m}{2}\rfloor-\lfloor\frac{m}{2}\rfloor}{(\lfloor\frac{m}{2}\rfloor-1)^2\lfloor\frac{m}{2}\rfloor^h}=O(1)$ .
22. 图形渲染.
23. 除了版本控制我还真没想到别的.
24. 略.
25. 讲义的配图很细节, 注意边的确也上色了.
26. 好的.
27. 那就需要解决可能的双黑问题, 可以参考删除中解决双黑的策略.
28. 
    1. 如果叔叔有孩子, 那么新插入节点的父亲(原来的红的叶子节点)的另一孩子(外部节点)就和叔叔的孩子的孩子(外部节点)的黑深度不一致, 违反了红黑树的第 4 条规则;
    2. 如果叔叔有孩子(一定是黑节点), 那么新插入节点的父亲(原来的红的叶子节点)的另一孩子(外部节点)就和叔叔的孩子的孩子(外部节点)的黑深度不一致, 违反了红黑树的第 4 条规则;
    3. 因为 RR-2 情况会向上传递双红, 传递后的新 `v` 就不保证是新插入的节点了, 上述推理就不再成立, `u` 可能有非外部节点的孩子.
29. 
    1. 略;
    2. 略.
30. 不严谨假设, 每往上走一层, 每层的 `u` 的颜色都是 $50\%$ 概率红/黑, 那么重染色的期望为 $\frac{1}{2}\cdot0+\frac{1}{2^2}\cdot1+\frac{1}{2^3}\cdot2+\dots+\frac{1}{2^{\log n+1}}\cdot\log n=O(1)$ .
31. 因为分摊后是 $O(1)$ .
32. 
    1. 确实;
    2. 因为双黑处理的 BB-2B 情况会导致双黑向上传递, 后续双黑处理时 `k` 就有可能是常规子树了.
33. 
    1. 略;
    2. 略.
34. 可能会导致 BB-3 转化为 BB-2B, 之后又造成新的 BB-3, 导致最后运行时间增长.

## PS-09
1. 略.
2. 没有捏.
3. 点菜的时候找对应的价格?
4. 参考 https://blog.csdn.net/ii1245712564/article/details/47083025 .
5. 略.
6. 
   1. $p(x)=p(x-1)+\frac{\tbinom{N}{x}M\times(N-x)^M}{N^M}$ ;
   2. 确实.
7. 略.
8. 还没想到, 但对抗攻击这种思路很常用.
9. 大多数的分布式散列表使用某些稳定散列（consistent hashing）方法来将关键值对应到节点......稳定散列拥有一个基本的性质：增加或移除节点只改变邻近ID的节点所拥有的关键值集合，而其他节点的则不会被改变。对比于传统的散列表，若增加或移除一个位置，则整个关键值空间就必须重新对应。由于拥有数据的改变通常会导致数据从分布式散列表中的一个节点被搬到另一个节点，而这是非常浪费带宽的，因此若要有效率地支持大量密集的节点增加或离开的动作，这种重新配置的行为必须尽量减少。 —— 百度百科
10. 
    1. 根据讲义提示, `rand()` 生成的数组下标是均匀分布在 $[0,2^{64})$ 中的 , 但这个值介于 $20!$ 和 $21!$ 之间, 因此当 $n\geq21$ 时, 实际上的交换下标可能总数比实际能生成的总数多了, 那么就不可能等概率地生成所有 $n!$ 种排列;
    2. 还没.
11. 略.
12. 略.
13. 略.
14. 可以将试探链的最后一个挪到被摘除的词条的位置.
15. 举例: $N=51,M=100$ , $M^{'}=4N$ or $M^{'}=2M$ , 后者重散列后的装填因子可能大于 $\frac{1}{4}$ .
16. 不行, 因为 $M$ 变了, 每个词条对应的 Hash 值可能会变.
17. 略.
18. 参考 https://ah.nccu.edu.tw/bitstream/140.119/37089/8/101008.pdf
19. distribution: 按照原序依次处理, 同义词放到相应链表结尾; collection: 按照大小依次汇报, 同义词链表从头到尾汇报.
20. 不能, 因为最小间距不保证只出现在桶间/只出现在桶内.
21. 
    1. 理解了;
    2. 肯定不行, 后续位还没排序;
    3. 大概只能是剩下都已经有序或者每个数的剩下各位都对应一致才行吧;
    4. 确实;
    5. 略.
22. 
    1. 省去了进制转换的 $O(d\times n)$ , 但排序时间的常数项会增加;
    2. 利大于弊, 目前通用的系统架构都是二进制.
23. 
    1. 后续放置的时候直接能知道要放到哪个下标上;
    2. 确实;
    3. 调整: 统计出每个桶对应的秩区间后, 只记录秩区间的左端点, 而非原本的右端点, 然后放一个元素, 对应桶记录的值自增 1;
    4. 可以;
    5. 略.
24. $\text{Var}(h)=\frac{p+1}{(1-p)^2}=6$ , 求二阶矩就行.
25. 
    1. 假如横向跳转的目的地不是某座塔的顶部, 那么这座塔就存在一个比目的地更高的同样的元素, 并且还代表着在上一层进行比较的时候没有选择横向跳转而是向下跳转, 也就是说待查找元素比这座塔的元素更小, 那就不可能会再横向跳转了, 从而产生矛盾;
    2. 因为塔高符合几何分布, 那么横向跳转的步数就是取塔高对应的横向坐标, 那么自然就是符合几何分布的, 从而期望是 $O(1)$ .
26. 因为只是多一次而已, 常数项.
27. 不用特殊处理边界条件了.

## PS-10
1. 已了解.
2. 已了解.
3. 好的.
4. 
   1. 邻接表适合稀疏图(边相对节点多), 邻接矩阵适合稠密图(边相对节点少);
   2. 场合是指什么...
5. 
   1. `UNDISCOVERED` , `DISCOVERED` , `VISITED` ;
   2. 入队前是 `UNDISCOVERED` , 入队后是 `DISCOVERED` , 出队后是 `VISITED` ;
   3. 分为 `UNDETERMINED` , `TREE` , `CROSS` ;
   4. 最开始都是 `UNDETERMINED` , 在 BFS 的过程中, 如果找到新点, 那么这条边就可以看成树枝, 状态设为 `TREE` ; 如果是已经被发现的点, 那么这条边就不会成为树枝, 状态设为 `CROSS` ;
   5. 因为首先要每个点都入队一次, 有一个 $O(n)$ , 其次还要计算每个点的邻居, 总数与总边数相等, 因此还要加上 $O(e)$ .
6. 
   1. 遍历所有点, 如果是 `UNDISCOVERD` 状态则执行 BFS;
   2. 同上, 不可达的域将单独形成一颗 BFS 树;
   3. 因为直观地想, 所有遍历过程实际上遍历所有点仅一次, 不会重复, 同时遍历相邻节点时, 会将边进行标记, 也不会重复遍历, 故时间复杂度仍是 $O(n+e)$ .
7. 
   1. 只与连通域的情况有关;
   2. 显然?
   3. 想一个最简单的情况: $A\rightarrow B\leftarrow C$ , 那么从 $A$ 或 $C$ 开始的结果自然不同.
8. 
   1. BFS 着色;
   2. 只需要按照 BFS 中 `dTime` 对 $2$ 取余的结果进行划分即可;
   3. 参考 https://blog.csdn.net/Tyro_java/article/details/113548046 , 取 BFS 树中最大的 `dTime` 即可;
   4. 对每个点都 BFS?
   5. 参考上面链接;
   6. 参考上面链接;
   7. 参考上面链接, 两次 BFS 即可;
   8. 可能的思路: 从任意点开始, 在 BFS 判定 `CROSS` 边的时候, 将这条边头尾两点的 `dTime` 做差再加 $1$ , 得到该环路的长度, 然后取最小值即可;
   9. 参考上面链接.
9. 
   1. `UNDISCOVERED` , `DISCOVERED` , `VISITED` ;
   2. 在深探前是 `UNDISCOVERED` , 深探过程中是 `DISCOVERED` , 深探递归完成后是 `VISITED` ;
   3. 分为 `UNDETERMINED` , `TREE` , `BACKWARD` , `FORWARD` , `CROSS` ;
   4. 初始化为 `UNDETERMINED` , 在深探过程中, 如果找到新点, 那么这条边就可以看成树枝, 状态设为 `TREE` ; 如果是 `DISCOVERED` 的点, 那么这条边就不会成为树枝, 状态设为 `BACKWARD` ; 如果是 `VISITED` 的点, 那么需要根据该点和当前点的 `dTime` 的大小关系来判断, 如果当前点的 `dTime` 比该点的 `dTime` 小, 那么这条边就是 `FORWARD` , 否则就是 `CROSS` ;
   5. 跟 BFS 的原因类似, 也是每个点和每条边仅遍历一次;
10. 
    1. 同理 BFS;
    2. 同理 BFS;
    3. 同理 BFS.
11. 
    1. 仅与连通域的情况有关;
    2. 还是考虑这个最简单的例子: $A\rightarrow B\leftarrow C$ .
12. 注意, 本课程代码中 , BFS 和 DFS 中 `fTime` 的含义并不一致, 前者代表同一 `dTime` 下遍历的次序, 后者与 `dTime` 一起表示遍历的时间轴上的区间.
    1. 略;
    2. 略.

## PS-11
1. 