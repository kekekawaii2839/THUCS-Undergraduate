# HW5

## Q1

### Q1.1

- 虚拟地址

`[0,11]` `VPO`
`[12,23]` `VPN`
`[12,14]` `TLBI`
`[15,23]` `TLBT`

- 物理地址

`[0,11]` `PPO`
`[12,19]` `PPN`

### Q1.2

||`0x01DBE3`|`0x9E6CF2`|
|-|-|-|
|VPN|`0x01D`|`0x9E6`|
|TLB Index|`5`|`6`|
|TLB Tag|`0x003`|`0x13C`|
|TLB Hit? (Y/N)|`N`|`Y`|
|Page Fault? (Y/N)|`Y`|`N`|
|PPN|`-`|`0x7F`|
|访问时间（单位为 `ns` ）|`328ns`|`110ns`|

## Q2

在链接期间需要全局重定位的调用有 `test1` , `test3` , `test4` 和 `test_call` .

## Q3

1. 8 行.
2. 3 行.
3. `counter=2` .