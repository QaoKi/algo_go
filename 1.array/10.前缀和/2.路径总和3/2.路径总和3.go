#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include <vector>
#include <unordered_map>
#include "../../../5.tree/Tree/Tree.h"
using namespace std;

/*
    leetcode 437
    题目：
        给定一个二叉树，它的每个结点都存放着一个整数值。
        找出路径和等于给定数值的路径总数。
        路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
        二叉树不超过 1000 个节点，且节点数值范围是 [-1000000,1000000] 的整数。

        示例 1：
            root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
                    
                     10
                    /  \
                   5   -3
                  / \    \
                 3   2   11
                / \   \
               3  -2   1

            返回 3。和等于 8 的路径有:
                1.  5 -> 3
                2.  5 -> 2 -> 1
                3.  -3 -> 11
*/

/*
    这个系列的前两题，都是二叉树的知识点，这题虽然也是二叉树，但是用到的确实前缀和，所以放到此处。
    方法1，暴力法
        以每个节点为起始节点， 递归遍历所有的情况
*/
class Solution {
public:
    int dfs(TreeNode* node, int sum) {
        if (node == NULL) return 0;

        int ans = 0;
        sum -= node->val;
        //符合条件
        if (sum == 0) {
            ans++;
        }
        //不停下来，继续向下遍历
        return ans + dfs(node->left, sum) + dfs(node->right, sum);
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (root == NULL) return 0;
        //递归的以每个节点为起始节点， 遍历所有的情况
        return dfs(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
    }
};

/*
    方法2，前缀和
        这道题和 560 题相比，虽然采用的数据结构不一样，但是问法是类似的。
        我们定义二叉树节点上的前缀和：当前节点的前缀和等于从根节点到该节点的路径总和
        因为是二叉树，所以我们采用递归的方式遍历节点，
        依然采用一个 map 来存储前面节点的前缀和出现的次数，每次遍历到一个节点，去 map 中查找是否存在键为 
        [当前节点前缀和 - target] 的数据存在。

    不过需要注意的是，
        1，本题有一个条件：路径方向必须是向下的（只能从父节点到子节点），
            所以当递归回溯回来，我们要将当前节点的前缀和，在 map 中减去次数。
        2，根节点第一次进入 dfs函数，此时 currSum 的值等于 根节点的值，
            如果根节点的值就等于 targetSum，也是符合的，currSum - targetSum 等于 0，
            所以去 map 中查找 0 时应该返回 1，所以 map[0] = 1
    
    时间复杂度：O(n)
    空间复杂度：O(n)
*/
class Solution {
public:
    unordered_map<int, int> unmap;
    int ans = 0;
    void dfs(TreeNode *node, int targetSum, int currSum) {
        if (node == NULL) return;
        //当前节点的前缀和
        currSum += node->val;
        //map 中查找
        if (unmap.count(currSum - targetSum)) {
            ans += unmap[currSum - targetSum];
        }

        //当前节点的前缀和增加到 unmap 中
        unmap[currSum]++;
        //继续递归
        dfs(node->left, targetSum, currSum);
        dfs(node->right, targetSum, currSum);
        //回溯回来，将当前节点的前缀和从 unmap 中减去
        unmap[currSum]--;
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (root == NULL) return 0;
        unmap[0] = 1;
        dfs(root, targetSum, 0);
        return ans;
    }
};

int main()
{
    return 0;
}