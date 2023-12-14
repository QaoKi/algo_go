#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 712
    给定两个字符串s1, s2，找到使两个字符串相等所需删除字符的ASCII值的最小和。

    示例：
        输入: s1 = "sea", s2 = "eat"
        输出: 231
        解释: 在 "sea" 中删除 "s" 并将 "s" 的值(115)加入总和。
            在 "eat" 中删除 "t" 并将 116 加入总和。
            结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。

*/

/*
   两个字符串的删除操作的变形题。
   base case:
        当s2为空字符串，那么s1所有的字符都要删除，同理，当s1为空字符串，s2所有的字符也都要删除
*/
int dp(string s1, string s2) {
    vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    //修改 base case
    for(int i = 1; i <= s1.length(); i++) {
        dp[i][0] = dp[i - 1][0] + int(s1[i - 1]);
    }

    for(int i = 1; i <= s2.length(); i ++) {
        dp[0][i] = dp[0][i - 1] + int(s2[i - 1]);
    }   

    for(int m = 1; m <= s1.length(); m++) {
        for (int n = 1; n <= s2.length(); n++) {
            //第m个字符对应的下标为 m-1
            if(s1[m - 1] == s2[n - 1]) {
                dp[m][n] = dp[m - 1][n - 1];
            } else {
                //注意，第m个字符对应的下标为 m-1，这里不要忘记了
                //选择删除s1[m - 1]，那么结果中就要加上 int(s1[m - 1])
                //选择删除s2[n - 1]，那么结果中就要加上 int(s2[n - 1])
                dp[m][n] = min(int(s1[m - 1]) + dp[m - 1][n], int(s2[n - 1]) + dp[m][n - 1]);
            }
        }
    }

    return dp[s1.length()][s2.length()];
}

int main() {
    string s1 = "sea";
    string s2 = "eat";

    //m ,n初始值为0
    cout << "dp:  " << dp(s1, s2) << endl;
    return 0;
}