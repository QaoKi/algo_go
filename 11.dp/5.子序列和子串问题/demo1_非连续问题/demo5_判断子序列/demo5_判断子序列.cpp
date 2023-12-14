#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 392
        给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
    提示：
        两个字符串都只由小写字符组成。
    示例：
        输入：s = "abc", t = "ahbgdc"
        输出：true

*/

/*
    方法1，双指针。
        变量 i 指向 s，变量 j 指向 t
        如果 s[i] == t[j]，i 和 j 都向后移动，
        如果 s[i] != t[j]，i 不动，j 后移。
        最终如果 i == s.length()，说明将 s 都匹配完了，返回 true，否则返回 false。

        能这么简便的原因是，
            子序列是有相对顺序的，s[i] 如果没有被匹配成功，就不能去匹配 s[i] 后面的字符。
*/
class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.length() == 0) return true;
        if (t.length() == 0) return false;
        int i = 0, j = 0;
        while (i < s.length() && j < t.length()) {
            if (s[i] == t[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        return i == s.length();
    }
};

/*
    方法2，动态规划
        这道题因为比较简单，用双指针是最优解，这道题之所以放到 dp 题中，是为了对比其他的子序列题目，
        见到这种题目要先思考有没有更优解，不要上来就用 dp
        
    定义 dp 数组
        dp[i][j] 表示长度为 i 的字符串 s 是否是长度为 j 的字符串 t 的子序列。
    状态转移方程
        长度为 i 的字符串，最后一个字符的下标为 i-1
        如果 s[i-1] == t[j-1]，最后一个字符相同，是否是子序列，取决于之前的字符串，所以 dp[i][j] = dp[i-1][j-1]，
        如果 s[i-1] != t[j-1]，字符串 s 的最后一个字符没有匹配成功，那么需要和字符串 t 前面的字符去匹配，
            所以 dp[i][j] = dp[i][j-1]
    base case
        dp[0][i] = true，其中 0 <= i <= t.length()

*/

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.length() == 0) return true;
        if (t.length() == 0) return false;
        vector<vector<bool>> dp(s.length() + 1, vector<bool>(t.length() + 1, false));
        for (int i = 0; i <= t.length(); i++) {
            dp[0][i] = true;
        }

        for (int i = 1; i <= s.length(); i++) {
            for (int j = 1; j <= t.length(); j++) {
                if (s[i-1] == t[j-1])
                    dp[i][j] = dp[i - 1][j - 1];
                else 
                    dp[i][j] = dp[i][j - 1];
            }
        }
        return dp[s.length()][t.length()];
    }
};

int main() {
    return 0;
}