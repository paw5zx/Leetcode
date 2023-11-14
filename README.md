# Leetcode
使用makefile自动化构建Leetcode项目，方便调试

# 项目构建
1、在./src下自定义路径编译你自己的文件
2、在终端中进入Leetcode目录
3、使用make all构建所有项目
4、进入./bin中的相应文件夹，选择要执行的项目并执行
# 项目清理
使用make clean清理所有.o .out文件
# 快速测试
以leetcode第94题为例程快速测试，文件路径：./src/tree/094.cpp
```
// 1 进入Leetcode目录

// 2 使用make all构建所有项目
make all

// 3.1 进入./bin中相应文件夹
cd ./bin/tree

// 3.2 选择要执行的项目，并执行
./094.out
```
# 注意
- 每个文件要以`//C++ Standard: C++17`开头，否则无法正确解析C++标准
- cpp文件必须带有main函数，否则不会生成可执行文件
