# Bomb Lab Report

## Phase 1

在本函数可以看到, 调用了 `string_not_equal()` 函数, 同时调用之前修改了 `%rsi` , 可以判断它有两个参数. 

```asm
141d:	48 8d 35 2c 1d 00 00 	lea    0x1d2c(%rip),%rsi        # 3150 <_IO_stdin_used+0x150>
1424:	e8 53 04 00 00       	call   187c <strings_not_equal>
```

(注意上面的注释形式, 这相当于读取程序里面指令之后的部分, 里面是一些预置的数值或字符串, 后续phase会用到)

再结合函数名可以猜测, Phase 1 只需要输入于标准答案相一致的字符串即可.

那么只需要使用 GDB 进行断点调试, 在执行 `string_not_equal()` 函数之前查看 `%rsi` 指向的内存中的值即可, 得到答案 "I can see Russia from my house!" .

本函数对应的伪代码如下:

```c
void phase_1(char* input){
    char* answer;
    if (strings_not_equal(input, answer)) explode_bomb();
}
```

## Phase 2

首先先看到本函数调用了一个 `read_six_numbers()` 函数, 并且读取的六个数字顺序放入栈中, 也就是 `%rsp` ~ `%rsp+20` 这六个位置. 同时本函数根据返回值检查是否输入成功, 失败则直接爆炸. 对应的汇编代码如下:

```asm
1442:	e8 5b 05 00 00       	call   19a2 <read_six_numbers>
1447:	83 3c 24 00          	cmpl   $0x0,(%rsp)
144b:	78 0a                	js     1457 <phase_2+0x1e>
...
1457:	e8 20 05 00 00       	call   197c <explode_bomb>
```

我们暂且认为这个数组对应的变量为 `int x[6]` . 随后本函数检查 `x[0]` 是否小于 0 ,如是则会爆炸:

```asm
1447:	83 3c 24 00          	cmpl   $0x0,(%rsp)
144b:	78 0a                	js     1457 <phase_2+0x1e>
```

之后我们会看到一个经典的循环代码特征, 对应汇编代码如下:

```asm
1450:	bb 01 00 00 00       	mov    $0x1,%ebx
1455:	eb 13                	jmp    146a <phase_2+0x31>
...
1465:	83 fb 06             	cmp    $0x6,%ebx
1468:	74 11                	je     147b <phase_2+0x42>
...
147b:	48 83 c4 28          	add    $0x28,%rsp
1481:	c3                   	ret
```

这里就可以看成 `for(int i = 1; i < 6; i++)` 的循环结构, `%ebx` 就对应变量 `i` .
额外地, 可以确定这个函数在循环结束之后就直接返回了.
接下来只需要确定循环体內部的代码逻辑就可以了.

```asm
146c:	03 45 00             	add    0x0(%rbp),%eax          # %rbp has been set to %rsp before
146f:	39 45 04             	cmp    %eax,0x4(%rbp)
1472:	74 ea                	je     145e <phase_2+0x25>
1474:	e8 03 05 00 00       	call   197c <explode_bomb>
...
145e:	83 c3 01             	add    $0x1,%ebx
1461:	48 83 c5 04          	add    $0x4,%rbp
```

很明显, 这一段就是不断检查 `x[i-1]+i` 是否等于 `x[i]`, 如果有不等的情况就会爆炸. 现在, 我们就可以把本函数的伪代码写出来了:

```c
void phase_2(char* input){
    int* x; read_six_numbers(input, x);
    if (x[0] < 0) explode_bomb();
    for (int i = 1; i < 6; i++) {
        if (i + x[i-1] != x[i]) explode_bomb();
    }
}
```

由此可知phase2的答案是一个首项非负的数列, 差是一个从 1 开始的等差数列, 最简单的形式就是 `0 1 3 6 10 15` .

## Phase 3

本函数包含 `switch` 语句, 因此关键在于找出跳转计算目标地址的方式. 经分析我们可以看到, 本函数先是输入了两个数, 我们称它们为 `int x, y` , 然后根据 `x` 的值进行跳转.

具体跳转有些复杂, 实际是读取一个数组, 里面存储了后续跳转case需要的地址偏移量, 具体汇编代码如下:

```asm
14b1:	8b 44 24 0c          	mov    0xc(%rsp),%eax
14b5:	48 8d 15 e4 1c 00 00 	lea    0x1ce4(%rip),%rdx        # 31a0 <_IO_stdin_used+0x1a0>
14bc:	48 63 04 82          	movslq (%rdx,%rax,4),%rax
14c0:	48 01 d0             	add    %rdx,%rax
14c3:	ff e0                	jmp    *%rax
```

(注意到这里 GDB 再次给出了与 phase1 类似的注释, 说明这里的确是读取了一个数组)

这几行的操作就是, 先将 `x` 的值存入 `%eax` , 然后通过 `%rdx` 找到地址偏移量数组, 再利用 `%rax` 的值找到相应的偏移量, 存入 `%rax`, 最后跳转.

最后只需要分析每个case做了什么就可以了, 相对简单, 直接可以得到本函数的伪代码:

```c
void phase_3(char* input){
    int x, y; sscanf(input, "%d %d", &x, &y);
    if (x > 7 or x < 0) explode_bomb();
    switch (x) {
        case 0:
            int temp = 0xdb; break;
        case 1:
            int temp = -0x1a8; break;
        case 2:
            int temp = 0x2; break;
        case 3: // 没必要写 x == 5 和 7 的情况, 因为后面会爆炸
            int temp = -0x2fa; break;
        case 4: // 没必要写 x == 6 的情况, 因为后面会爆炸
            int temp = 0; break;
    }
    if (x > 5 or temp != y) explode_bomb();
}
```

由此可见phase3答案不唯一, 可以是 `0 219` , `1 -424` , `2 2` , `3 -762` , `4 0` , `5 -762` .

## Phase 4

本函数包含递归方法, 因此只要搞清楚递归的起始参数和递归公式, 就可以得到答案了.

函数主体的逻辑较为简单, 稍加分析就可以得到伪代码:

```c
void phase_4(char* input){
    int x, y;
    sscanf(input, "%d %d", &x, &y);
    if (y >= 4 or y < 2) explode_bomb();
    if (func4(9, y) != x) explode_bomb();
}
```

接下来分析 `func4(int arg1, int arg2)` , 先来找递归的结束条件:

```asm
1548:	b8 00 00 00 00       	mov    $0x0,%eax
154d:	85 ff                	test   %edi,%edi
154f:	7e 2d                	jle    157e <func4+0x36>
...
157e:	c3                   	ret
```

这代表当 `arg1 == 0` , 直接返回 0 . 继续阅读汇编代码, 我们会发现还有另一个结束条件:

```asm
1559:	89 f0                	mov    %esi,%eax
155b:	83 ff 01             	cmp    $0x1,%edi
155e:	74 19                	je     1579 <func4+0x31>
...
1579:	5b                   	pop    %rbx
157a:	5d                   	pop    %rbp
157b:	41 5c                	pop    %r12
157d:	c3                   	ret
```

也就是当 `arg1 == 1` , 返回 `%esi` 的值, 也就是 `arg2` . 之后来分析递归公式:

```asm
1557:	89 f5                	mov    %esi,%ebp
...
1560:	8d 7f ff             	lea    -0x1(%rdi),%edi
1563:	e8 e0 ff ff ff       	call   1548 <func4>
1568:	44 8d 24 28          	lea    (%rax,%rbp,1),%r12d
```

这里先拿到了 `func4(arg1-1, arg2)` 的值, 然后加上 `arg2` 的值, 存入 `%r12d` .

```asm
156c:	8d 7b fe             	lea    -0x2(%rbx),%edi
156f:	89 ee                	mov    %ebp,%esi
1571:	e8 d2 ff ff ff       	call   1548 <func4>
1576:	44 01 e0             	add    %r12d,%eax
1579:	5b                   	pop    %rbx
157a:	5d                   	pop    %rbp
157b:	41 5c                	pop    %r12
157d:	c3                   	ret
```

之后再计算出 `func4(arg1-2,arg2)` 的值, 加上原先 `%r12d` 的值作为返回值. 递归公式就是 $func4(arg1,arg2)=func4(arg1-1,arg2)+func4(arg1-2,arg2)+arg2$ . 结合本函数对于 `y` 的取值范围限定在了 $\{2,3\}$ 中, 因此正确答案只有 `264 3` 和 `176 2` .

## Phase 5

本函数主要是考察指针, 先分析出输入的内容:

```asm
15d9:	48 89 fb             	mov    %rdi,%rbx
15dc:	e8 7e 02 00 00       	call   185f <string_length>
15e1:	83 f8 06             	cmp    $0x6,%eax
15e4:	75 45                	jne    162b <phase_5+0x57>
...
162b:	e8 4c 03 00 00       	call   197c <explode_bomb>
```

字面理解, 应该是通过 `string_length()` 函数来检查输入的字符串长度是否为 6 , 若不是则爆炸.

接下来我们又会看到读取内置数组的操作:

```asm
15eb:	48 8d 0d ce 1b 00 00 	lea    0x1bce(%rip),%rcx        # 31c0 <array.0>
```

经过 GDB 检查, 发现 `%rcx` 指向的数组存储的是一个字符串, 内容为 `maduiersnfotvbyl` .

在后面我们又会看到调用了 `strings_not_equal()` 函数, 可以猜测是通过某种方式, 将输入的长度为 6 的字符串转为读取 `%rcx` 指向的字符串的下标, 从而拼出一个新的字符串, 与某一固定字符串对比.

再继续分析后续代码逻辑:

```asm
15f6:	83 e2 0f             	and    $0xf,%edx
```

这一行相当于对输入的字符串的每个字符的 ASCII 码对 16 取余, 这验证了上述猜想.

接下来通过 GDB 检查可以得知, 目标字符串为 `devils` , 这就意味着我们需要对 16 取余后为 `2 5 12 4 15 7` 的字符串. 这很容易联想到根据字符 `a` 进行偏移, 因为 `a` 的 ASCII 码恰好为 96, 于是我们得到答案的一种情况: `beldog` .

最后给出本函数对应的伪代码:

```c
void phase_5(char* input){
    if (string_length(input) != 6) explode_bomb();
    char arr[] = "maduiersnfotvbyl";
    char* result;
    for (int i = 0; i < 6; i++)
        result[i] = arr[input[i] % 16];
    if (result != "devils") explode_bomb();
}
```

## Phase 6

还是先判断输入, 发现是调用 `read_six_numbers` , 读取 6 个数, 存在 `%rsp+48` ~ `%rsp+68` . 之后是复杂的循环嵌套, 通过分析可以看出总共有三个循环 (因为编译器对循环的实现特征较为明显):

(由于篇幅限制我直接给出伪代码, 假设输入的 6 个数为 `int a[6]`)

1. 
    ```c
    int* t = a;
    for (int i = 1; i < 7; i++) {
        int temp = *t; temp --;
        if (temp > 5) explode_bomb();
        int i2 = i;
        while (i2 <= 5) {
            if (a[i2] == temp) explode_bomb();
            i2++;
        }
    }
    ```

    这个循环的目的在于检查 `a` 中每个元素, 保证它们都小于等于 6 并且不重复. 可以初步猜测, 这是某种序号排列的特征.

2. 
    之后检查内存, 可以发现变量 `node1` ~ `node6` , 分别有不同大小的值, 这时可以猜测本函数可能涉及到节点指针的问题, 也增加了本函数就是重排这 6 个节点的可能.
    ```c
    Node** node_arr;
    for (int i = 0; i < 6; i++) {
        Node* node = node1;
        for (int j = 1; j < a[i], a[i] > 1; j++) {
            node = node->next; // 此处表达不严谨
        }
        node_arr[i] = node; // 储存重排后的nodes
    }
    ```

    这一个循环直接验证重排节点的假设, 输入的 6 个数就代表重排后 `node1` ~ `node6` 的顺序.

3. 在第 2 和第 3 个循环之间, 存在大量涉及到 `node1` ~ `node6` 的赋值, 可以推断是执行重排操作.
    ```c
    for (int i = 5; i > 0; i++) {
        if (*node_arr[i] >= *node_arr[i+1]) explode_bomb();
    }
    ```

    这里很明显就是检查重排后节点是否为单调递增, 这也就告诉我们重排的目标.

在使用 GDB 检查 `node1` ~ `node6` 的值之后, 给出重排方式: `1 4 5 3 2 6` 即可.

## Secret Phase

首先要找到 phase4 后面需要加什么字符串. 直接可以 GDB 检查, 拿到 key string: `DrEvil` .

之后分析 `secret_phase()` 函数, 发现是只需要额外输入一个数(`int b` 且保证小于等于 1001), 调用递归函数 `fun7(int* a, int b)` , 使其返回值恰好为 7.

接下来分析 `fun7()` 初次调用传入的参数:

```asm
17b2:	89 de                	mov    %ebx,%esi
17b4:	48 8d 3d 55 3a 00 00 	lea    0x3a55(%rip),%rdi        # 5210 <n1>
```

值得注意的是第一个参数, 由 GDB 给出的注释提示, 可以推断这又是某个内置变量. 使用 GDB 检查, 我们发现这是一个满二叉树, 由 4 层 15 个节点组成. ( `n1` `n21`~`n22` `n31`~`n34` `n41`~`n48` )

猜测: `fun7()` 的递归是遍历二叉树, 然后计算某种值. 分析 `fun7()` 后可得如下伪代码, 验证猜想:

```c
int fun7(int* a, int b){
    if (a == NULL) return -1;
    if (*a > b) {
        a = a->left; // 表述不严谨
        return fun7(a, b) * 2;
    }
    else if (*a < b) {
        a = a->right; // 表述不严谨
        return fun7(a, b) * 2 + 1;
    }
    else return 0;
}
```

为了凑出 7, 对于 4 层的满二叉树, 我们只能输入最大的节点元素的值, 这一值恰好为 `b` 的上限 1001.

## 感想

这个实验作业设计的挑战性与趣味性都很强, 能够一步一步引导我看懂和熟悉汇编代码, 并且了解编译器的操作和优化风格, 大概是我写过的最酷的作业了吧 (

可以考虑适当增加Secret Phase的难度, 将树扩大/改为字典树.