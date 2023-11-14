//C++ Standard: C++17

//二叉树构造
#include <iostream>
#include <vector>
#include <optional>


#ifndef TREENODE_H
#define TREENODE_H
using namespace std;


class TreeNode 
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
public:
    TreeNode();
    TreeNode(int x);
    TreeNode(int x, TreeNode *left,TreeNode *right);  //代理构造函数
    TreeNode(std::vector<int> values);    //转换构造函数，不加explicit，允许隐式构造
    TreeNode(std::initializer_list<std::optional<int>> values);    

    //序列化，层序遍历，父节点为nullptr，则不将其子节点的null打印；除了最后一个叶子节点外，所有空节点都被打印为null
    void printTree();
};

#endif