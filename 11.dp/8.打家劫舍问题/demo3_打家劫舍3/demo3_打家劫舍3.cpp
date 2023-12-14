#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	题目： leetcode 337
		给定的每户人家，是二叉树的形式，要求父节点和子节点不能同时偷，问最大收益。
		示例：
			看原题吧

*/

/*
	对于每个节点，依然有两种选择，偷或者不偷，
		如果当前节点选择偷，那么它的左右子节点都不能再偷了，
		如果当前节点选择不偷，那么它的左右子节点可以选择偷也可以选择不偷。
	可以看出，父节点的选择，需要传递给子节点。
	
	父节点做出选择以后再传给子节点，这是自顶向下，而我们选择自底向上，回溯的方式，
	先求出子节点做出选择以后的数据，递归回来传给父节点，父节点做出选择以后，再向上传递。
	后序遍历就是天然的回溯过程，所以使用后序遍历
		这道题目的二叉树回溯思想，也应用在了 236 题 tree\demo18_二叉树的最近公共祖先

	1，定义状态转移方程
		对于子节点来说，可以选择偷或者不偷，所以左右子树都会给父节点传回来两个值，定义一个结构体来保存，更加直观。
		struct SNodeStatus {
			int selected;		//选择偷，会有多少钱
			int noSelected;		//选择不偷，有多少钱
		};

		设当前节点 node 收到左子树传回来的值 left，右子树传回来的值 right，
		如果当前节点选择偷，那么子节点只能选择不偷
			selected = node->val + left.noSelected + right.noSelected
		如果当前节点选择不偷，那么子节点可以选择偷，也可以选择不偷，取最大值
			noSelected = max(left.selected, left.noSelected) + max(right.selected, right.noSelected)
		然后，当前节点把 {selected, noSelected} 传给它的父节点

		最终，我们返回根节点的 max(selected, noSelected)
	2，base case
		当节点为 NULL 时，返回 {0, 0}
*/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct SNodeStatus {
	int selected;		//选择偷，会有多少钱
	int noSelected;		//选择不偷，有多少钱
};

class Solution {
public:

	SNodeStatus dfs(TreeNode * node) {
		if (node == NULL)
			return {0, 0};
		//求出左右子树的值
		auto left = dfs(node->left);
		auto right = dfs(node->right);

		//当前节点选择偷和不偷
		int selected = node->val + left.noSelected + right.noSelected;
		int noSelected = max(left.selected, left.noSelected) + max(right.selected, right.noSelected);
		return {selected, noSelected};
	}

    int rob(TreeNode* root) {
		auto status = dfs(root);
		return max(status.selected, status.noSelected);
	}
};

int main()
{
	return 0;
}