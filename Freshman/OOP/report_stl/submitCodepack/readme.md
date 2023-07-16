# SGI STL Test Examples

编译指令: g++ ${fileName} -std=c++11
之后直接打开编译完成的可执行文件即可

SGI-STL目录下仅包含示例所需的文件，并且做了微小修改，使其置于namespace sgi_std下，可以做到不与编译器自带的stl冲突的同时，展现出SGI STL的设计精妙之处。

如果gcc编译器并非4.8.0版本，经实测并不影响示例效果（因为核心的部分已经完全由SGI STL目录下的代码实现）