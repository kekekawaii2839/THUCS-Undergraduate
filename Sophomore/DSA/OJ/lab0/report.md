# CST LAB0 实验报告

## 2.0 思考题

1. 由题目条件得: $0.5=10\times n^2\times 10^{-8}$, 解得$n=2236.1$, 因此$n_{max}=2236$.

2. 由题目条件得: $0.5=20\times n\times log_2n\times 10^{-8}$, 解得$n=1000$, 因此$n_{max}=145746$.

## 3.2

1. `solution_1.cpp` 与 `solution_2.cpp`中的bug是在每次循环的时候, `sum` 变量没有重置为0. 我找到他们的方式是通过静态检查+输出 `sum` 变量, 发现 `sum` 的值过大, 说明没有重置.

    同时, `solution_2.cpp` 还有 `rowsum` 变量下标的访问错误问题. 在修复完 `sum` 重置的bug后, 我发现 `solution_2.cpp` 的输出结果仍然不正确, 于是我进一步打印了 `rowsum` , 发现值正确, 但在后续计算结果的时候, 访问下标错位了.

2. gdb使用方式: 

    + 编译: `g++ -g solution_2.cpp -o solution_2`
    + 运行: `gdb solution_2`
    + 设置断点: `break 28` (设置在第28行, 便于后续查看 `sum` 的值)
    + 运行: `run`
    + 正常输入测试数据
    + 查看变量: `print sum`
    + 继续循环: `c` 或 `continue`
    + 查看变量: `print sum`

        ...
    + 退出: `exit`

    这样就可以检查每步 `sum` 的变化, 从而进一步定位bug.

3. `rand_input.cpp` 中 `srand(time(0))` 的作用是根据时间(秒)设置随机种子, 确保在同一机器多次运行的时候, 后续 `rand()` 函数生成的随机数不同.

4. 在 `battle.cpp` 中有如下 `system` 命令:

    + ```c++
        system("g++ rand_input.cpp -o rand_input");
        system("g++ check_input.cpp -o check_input");
        system("g++ solution_1.cpp -o solution_1");
        system("g++ solution_2.cpp -o solution_2");
        ```
        作用是编译 `rand_input.cpp`, `check_input.cpp`, `solution_1.cpp`, `solution_2.cpp` 生成可执行文件 `rand_input`, `check_input`, `solution_1`, `solution_2`, 供后续比较运行使用.
    
    + ```c++
        system("./rand_input > rand.in");
        ```
        作用是运行 `rand_input` 并将输出重定向到 `rand.in` 文件中.
    
    + ```c++
        system("./check_input < rand.in");
        ```
        作用是运行 `check_input` 并将 `rand.in` 作为输入, 之后根据返回值判断输入是否合法.
    
    + ```c++
        system("./solution_1 < rand.in > solution_1.out");
        ```
        作用是运行 `solution_1` 并将 `rand.in` 作为输入, 将输出重定向到 `solution_1.out` 文件中.
    
    + ```c++
        system("./solution_2 < rand.in > solution_2.out");
        ```
        作用是运行 `solution_2` 并将 `rand.in` 作为输入, 将输出重定向到 `solution_2.out` 文件中.
    
    + ```c++
        system("diff solution_1.out solution_2.out");
        ```
        作用是比较 `solution_1.out` 和 `solution_2.out` 文件的内容, 如果相同则返回值为0, 否则将执行后续 `if` 中的 `printf("different output!\n");` .

5. `main` 函数中 `argv[0]` 的含义是程序全名.

## 4.0 算法思路

注意到, `solution_2.cpp` 相比 `solution_1.cpp`, 实质上是空间换时间的方法, 使用了 `rowsum` 数组, 将后续查询的时间复杂度降至 $O(N)$ .

同样的思路, 我在查询前就可以将 `matrix` 数组每个位置到左上角的这个矩形的和计算出来.

`matrix` =
$$
\begin{matrix}
    1 & 2 & 3 \\
    4 & 5 & 6 \\
    7 & 8 & 9 \\
\end{matrix}
$$
`matrixsum` =
$$
\begin{matrix}
    0 & 0 & 0 & 0 \\
    0 & 1 & 3 & 6 \\
    0 & 5 & 12 & 21 \\
    0 & 12 & 27 & 45 \\
\end{matrix}
$$

这样查询的时候只需要对矩形进行拼接即可, 实际的时间复杂度便可降至 $O(1)$ .

## 4.1 性能比较

采用固定的 $n, m, q$ 测试100次, 以便于比较不同算法的性能.

$n=500, m=500, q=10000$时, 结果如下:

```bash
solution_1: 250358ms
solution_2: 5839ms
solution_3: 3390ms
```

$n=500, m=500, q=100$时, 结果如下:

```bash
solution_1: 1351ms
solution_2: 1234ms
solution_3: 1275ms
```

$n=1000, m=1, q=100000$时, 结果如下:

```bash
solution_1: 5749ms
solution_2: 6062ms
solution_3: 2003ms
```

$n=1, m=1000, q=100000$时, 结果如下:

```bash
solution_1: 5543ms
solution_2: 1801ms
solution_3: 1800ms
```

实际上, 一次查询中 `solution_1.cpp` 主要耗时在最后遍历整个子矩阵, 也就是受到 `a` 和 `b` 的影响. 考虑充分大的情况下, 这相当于受到 `n` 和 `m` 的影响. 因此 `solution_1.cpp` 的时间复杂度可以写成 $O(q\times n\times m)$ .

对于 `solution_2.cpp` , 耗时分为两部分. 第一部分是遍历整个矩阵构建 `rowsum` , 第二部分是每次查询遍历整个子矩阵的每行. 第一部分的时间复杂度为 $O(n\times m)$ , 第二部分的时间复杂度为 $O(q\times n)$ . 因此 `solution_2.cpp` 的时间复杂度可以写成 $O(n\times m+q\times n)$ .

而 `solution_3.cpp` , 耗时同样分为两部分. 第一部分是遍历整个矩阵构建 `matrixsum` , 第二部分是每次查询进行计算. 时间复杂度分别为 $O(n\times m)$ 和 $O(q)$ . 因此 `solution_3.cpp` 的时间复杂度可以写成 $O(n\times m+q)$ .

综上可知, 当 $q$ 比较小的时候, 三种算法耗时基本一致. 当 $q$ 比较大的时候, `solution_1.cpp` 的耗时将明显大于 `solution_2.cpp` 和 `solution_3.cpp` . 若此时 $n$ 不小, `solution_3.cpp` 的耗时也将明显小于 `solution_2.cpp` ; 反之, 若此时 $n$ 较小, `solution_3.cpp` 将退化为 `solution_2.cpp` , 上述实验结果也印证了这一点.

而当 $m$ 比较小的时候, 对比 $O(q\times n\times m)$ 和 $O(n\times m+q\times n)$ 可知, `solution_2.cpp` 将退化为 `solution_1.cpp` , 上述实际结果也验证了这一点.

## ps

在wsl上, 应当使用 `std::chrono::steady_clock::now()` 计时, 以得到正确且准确的结果.