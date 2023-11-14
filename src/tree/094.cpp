//C++ Standard: C++17

//二叉树中序遍历
#include <iostream>
#include <vector>
#include <stack>
#include "TreeNode.h"

using namespace std;
//递归
//时间复杂度：O(n)
//空间复杂度：最坏O(n)
vector<int> inorderTraversal(TreeNode* root) 
{   
    //结束条件
    if(!root)
        return {};
    vector<int> out;
    //左
    vector<int> left = inorderTraversal(root->left);
    out.insert(out.end(), left.begin(), left.end());
    //中
    out.push_back(root->val);
    //右
    vector<int> right = inorderTraversal(root->right);
    out.insert(out.end(), right.begin(), right.end());

    return out;
}

//迭代,DFS
//等价于递归
//显式使用栈
vector<int> inorderTraversal2(TreeNode* root) 
{   
    std::vector<int> ans;
    std::stack<TreeNode*> stk;
    //停止条件，栈空且所有节点都遍历完
    while(!stk.empty() || root)
    {
        //向左遍历至叶子节点
        while(root)
        {
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        ans.emplace_back(root->val);
        //回退一层，走一次右边
        stk.pop();
        root = root->right;
    }
    return ans;
}

//Morris 中序遍历
//时间复杂度：O(n)
//空间复杂度：O(1)
//好解法，过程为线索化
//思考，是否改变了原始结构？
//回答：没有，过程中通过对每个左子树的最右节点添加右儿子实现线索化，而在后面操作时已经置空恢复了
vector<int> inorderTraversal3(TreeNode* root) 
{   
    //
    std::vector<int> ans;
    //这个是全局的,代表左子树最右节点
    TreeNode* leftTreeRight;
    while(root)
    {
        //左子树存在则找到其最右节点
        if(root->left)
        {
            leftTreeRight = root->left;
            //找左子树天然最右节点
            while(leftTreeRight->right && leftTreeRight->right != root)
                leftTreeRight = leftTreeRight->right;
            
            //若天然左子树最右节点没有线索（最右节点没有右子树则证明没有被操作过）
            //则添加线索：将顶点续到最右节点后
            if(!leftTreeRight->right)
            {
                leftTreeRight->right = root;
                root = root->left;
            }
            //若天然左子树最右节点已有线索（有右子树,右子树的顶点是之前操作过的顶点）
            //证明此节点已经操作过了
            //直接当前root记录值即可
            //此时的root的右儿子的左儿子其实还是root，画图理解
            //拓扑图为近似右链树
            else
            {
                ans.emplace_back(root->val);
                //置空
                leftTreeRight->right = nullptr;
                //操作下一节点
                root = root->right;
            }
        }
        //左子树不存在则证明当前root是相较于未记录的节点，已经是最左,加入遍历序列
        //而且其之前已添加线索，指向其根节点
        //因此直接回退一层
        else
        {
            ans.emplace_back(root->val);
            root = root->right;
        }           
    }
    return ans;
}

int main()
{
    //TreeNode root = {1, NULL, 3, 2}是错误的，因为他经历了两次转换，先是{}转换为vector，再是vector转换为TreeNode
    //显示构造vector<int> v = {1, NULL, 3, 2};然后TreeNode root = TreeNode(v);
    //隐式构造的话
    //要么vector<int> v = {1, NULL, 3, 2};然后TreeNode root = v;
    //要么使用下述隐式构造
    TreeNode* root = new TreeNode({1, std::nullopt, 2, 3});    //在有initializer_list构造函数时，此式被判定为显示调用initializer_list构造

    //新增了初始化列表构造
    TreeNode* root2 = new TreeNode{1, std::nullopt, 2, 3};
    
    vector<int> out = inorderTraversal3(root2);

    for (auto it:out)
    {
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;

    return 0;
}