# HW6

## Q1

- `file1.txt` 的内容是 `ddccbbaa`

- `./program2` 是从 `STDIN_FILENO` 读入两个字符到自己的 `buf` 中, 然后再将 `buf` 的内容写入 `STDOUT_FILENO`

- `./program1` 在 `fork()` 前从 `fd_x` 和 `fd_y` 分别读入了 2 和 4 个字符, 紧挨着写入了 `buf` 数组, 此时 `buf` 中的内容为 `aaaabb` , 两个文件的指针分别增加 2 和 4

- 子进程将 `STDIN_FILENO` 和 `STDOUT_FILENO` 分别重定向到 `fd_y` 和 `fd_x` , 然后调用 `./program2` , 过程中两个文件的指针都增加 2. 这时候 `file1.txt` 的内容变为 `aaccccdd`

- 之后, `./program1` 又从 `fd_y` 读取 2 个字符到 `buf` 的最后两位, `buf` 变为 `aaaabbdd` , 之后一系列写入操作使得 `file1.txt` 
依次变为 `ddccccdd` , `ddccbbdd` 和 `ddccbbaa` , 最后关闭所有文件并退出.

## Q2

|空格|值|
|--|--|
|`A`|`1`|
|`B`|`0`|
|`C`|`0`|
|`D`|`P(&board)`|
|`E`|`V(&physics)`|
|`F`|`V(&chemistry)`|
|`G`|`&physics`|
|`H`|`&board`|
|`I`|`&chemistry`|
|`J`|`&board`|

## Q3

A E

## Q4

1. `a=1\n`
2. `a=1\na=1\n`
3. `a=2\n` or `a=1\n`
4. `a=1\na=1\na=2\n` or `a=1\na=2\na=1\n` or `a=2\na=1\na=1\n`