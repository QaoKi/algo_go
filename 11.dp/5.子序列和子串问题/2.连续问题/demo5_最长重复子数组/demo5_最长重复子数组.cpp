#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 718
    给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度
    示例：
        输入：
            A: [1,2,3,2,1]
            B: [3,2,1,4,7]
        输出：3
        解释：长度最长的公共子数组是 [3, 2, 1] 。
*/

/*
    和 最长公共子序列 类似，不过最长公共子序列不要求连续，本题要求数据连续，既然要求连续，
        那么在求状态转移方程时，就需要参考 最大子序和 的模式
    定义 dp 数组
        dp[i][j] 表示长度为 i，以 A[i-1] 作为末尾端的子数组，与长度为j，以 B[j-1] 作为末尾端的子数组，
            二者的最大公共后缀子数组长度。

    状态转移方程 （长度为 i 的数组，第 i 个元素的下标为 i-1）
        dp 数组的定义，虽然和 最长公共子序列 没什么区别，不过求状态转移方程是不同的，
            在求 dp[i][j] 时，如果 A[i-1] != B[j-1] 这里并不会继承之前的数据，
                比如 dp[i-1][j-1] = 3，如果 A[i-1] == B[j-1]，直接继承 dp[i-1][j-1] 的数据，然后加1，
                如果 A[i-1] != B[j-1]，并不会继承 dp[i-1][j-1] 的数据，而是重新开始计算，
                    因为 A[i-1] != B[j-1] ，所以 dp[i][j] = 0。
        所以状态转移方程为
            如果 A[i-1] == B[j-1]，dp[i][j] = dp[i-1][j-1] + 1
            如果 A[i-1] != B[j-1]，dp[i][j] = 0
        因为当遇到 A[i-1] != B[j-1] 时，dp[i][j] 会变成 0 重新计算，所以，在求 dp 数组的过程中，
            也要不断的取最大值，将最大值返回。
    遍历顺序
        从状态转移方程可以看出，dp[i][j] 只和 dp[i-1][j-1] 有关，也就是左上角的数据，
        所以可以按照 外层遍历从上往下，内层遍历从左往右的顺序遍历。（也就是 i 和 j 都从小到大）
    base case
        不需要再额外初始化，
        比如，如果 A[0] 和 B[0] 相同的话，dp[1][1] = dp[0][0] + 1，dp[0][0] 初始为0，符合递推公式逐步累加起来。

*/

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int ans = 0;
        vector<vector<int>> dp(A.size() + 1, vector<int>(B.size() + 1, 0));
        for (int i = 1; i <= A.size(); i++) {
            for (int j = 1; j <= B.size(); j++) {
                //第 i 个字符，在 A 中的下标为 i-1
                if (A[i - 1] == B[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = 0;
                }
                //记录最大值
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};

/*
    空间压缩，由状态转移方程式可知，当前行的数据，只和上一行有关，所以将二维数组降为一维数组。
    遍历顺序
        当前位置 dp[i][j] 和 dp[i-1][j-1] 有关，也就是上一行的低位列有关，所以内层遍历需要
        从后往前遍历，防止出现数据覆盖问题。
*/
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int ans = 0;
        vector<int> dp(B.size() + 1, 0);
        for (int i = 1; i <= A.size(); i++) {
            for (int j = B.size(); j >= 1; j--) {
                //第 i 个字符，在 A 中的下标为 i-1
                if (A[i - 1] == B[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                } else {
                    dp[j] = 0;
                }
                //记录最大值
                ans = max(ans, dp[j]);
            }
        }
        return ans;
    }
};


int main() {
    return 0;
}