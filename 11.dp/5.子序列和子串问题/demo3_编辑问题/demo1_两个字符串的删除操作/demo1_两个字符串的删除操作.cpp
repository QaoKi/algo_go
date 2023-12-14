#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 583
    给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

    示例：
        输入: "sea", "eat"
        输出: 2
        解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"

*/

/*
    这个系列的题目，适合求两个字符串如何操作能变得相等等类似问题。

    该题是在求，在不改变字符顺序的情况下，两个字符串有多少个字符不相等。
    定义 dp 数组
        dp[m][n] = x 表示长度为 m 的单词  word1 和长度为 n 的单词 word2 想要变成相同的的单词，所需的最小步数为x，
        
    状态转移方程
        如果 word1[m-1] == word2[n-1]，说明最后一个字符相同，dp[m][n] = dp[m-1][n-1]，继承之前的数据
        如果 word1[m-1] != word2[n-1]，这两个字符不同，那这两个字符肯定要删除一个，删除哪个分成两种情况，取值最小的
            所以 dp[m][n] = 1 + min(dp[m-1][n], dp[m][n-1])。

    base case: 
        对于长度为 m 的单词 word1 和长度为 n 的单词 word2
            如果m=0，那么 dp[0][i] = i, 0 <= i <= n
            如果n=0，那么 dp[i][0] = i, 0 <= i <= m
*/
int dp(string word1, string word2) {
    vector<vector<int>> dp(word1.length() + 1, vector<int>(word2.length() + 1, 0));

    for(int i = 0; i <= word1.length(); i ++)
        dp[i][0] = i;
    for(int i = 0; i <= word2.length(); i ++)
        dp[0][i] = i;

    for(int m = 1; m <= word1.length(); m++) {
        for (int n = 1; n <= word2.length(); n++) {
            //第m个字符对应的下标为 m-1
            if(word1[m - 1] == word2[n - 1]) {
                dp[m][n] = dp[m - 1][n - 1];
            } else {
                dp[m][n] = 1 + min(dp[m][n - 1], dp[m - 1][n]);
            }
        }
    }

    return dp[word1.length()][word2.length()];
}

int main() {
    return 0;
}