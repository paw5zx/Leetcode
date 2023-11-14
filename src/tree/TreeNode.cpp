//C++ Standard: C++17

#include <iostream>
#include <queue>

#include "TreeNode.h"
//

TreeNode::TreeNode() : TreeNode(0, nullptr, nullptr){}

TreeNode::TreeNode(int x) : TreeNode(x, nullptr, nullptr){}
//代理构造函数
TreeNode::TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

TreeNode::TreeNode(std::vector<int> values)
{
    std::cout<<"vector constructor"<<std::endl;
    //数组为空则创建0值根节点
    if(values.empty())
    {
        throw std::runtime_error("empty vector, construction fail");
    }
    //借助队列创建二叉树
    std::queue<TreeNode*> q;
    val = values[0];
    left = nullptr;
    right = nullptr;
    q.push(this);
    //
    int i = 1;
    while(!q.empty() && i<values.size())
    {
        TreeNode* current_node = q.front();
        q.pop();
        //处理左子节点
        if (values[i] != NULL) 
        {
            current_node->left = new TreeNode(values[i]);
            q.push(current_node->left);
        }
        i++;
        //先判断是否越界，再处理右子节点
        if (i < values.size() && values[i] != NULL) 
        {
            current_node->right = new TreeNode(values[i]);
            q.push(current_node->right);
        }
        i++;
    }
    
}

//要通过列表初始化构造二叉树
//列表中只能填入数字，而NULL和0会冲突
//需引入std::nullopt构造空节点
TreeNode::TreeNode(std::initializer_list<std::optional<int>> v)
{
    //注意区分0和NULL
    std::cout<<"initializer_list constructor"<<std::endl;
    
    //借助队列创建二叉树
    std::queue<TreeNode*> q;
    std::vector<std::optional<int>> values(v);
    //数组为空或根节点为nullptr，则报异常
    if(!v.size()||!values[0])
    {
        throw std::runtime_error("empty vector, construction fail");
    }
    val = values[0].value();
    left = nullptr;
    right = nullptr;
    q.push(this);
    
    int i = 1;
    while(!q.empty() && i<values.size())
    {
        TreeNode* current_node = q.front();
        q.pop();
        //处理左子节点,只要不是std::nullopt，values就为真
        if (values[i]) 
        {
            current_node->left = new TreeNode(values[i].value());
            q.push(current_node->left);
        }
        i++;
        //先判断是否越界，再处理右子节点
        if (i < values.size() && values[i]) 
        {
            current_node->right = new TreeNode(values[i].value());
            q.push(current_node->right);
        }
        i++;
    }
    
}

void TreeNode::printTree()
{
    //打印规则：逐层打印
    //分支上的首个空节点打印null，null节点后面的null不打印，
    //最后一个叶子节点null未消除，待优化
    //层序遍历打印
    std::queue<TreeNode*> q;
    q.push(this);

    while(!q.empty())
    {
        int levelsize = q.size();
        for (int i = 0; i < levelsize; ++i)
        {
            TreeNode* current_node = q.front();
            q.pop();

            if(!current_node)
            {
                std::cout<<"null ";
                continue;
            }
                
            std::cout<<current_node->val<<" ";
            
            //if(!current_node->left && !current_node->right)
                //continue;
            q.push(current_node->left);
            q.push(current_node->right);
        }
    }

    std::cout<<std::endl;
}