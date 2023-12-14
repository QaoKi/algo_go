#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 115
        给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。

    示例 1：
        输入：s = "rabbbit", t = "rabbit"
        输出：3
        解释：
            如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。(上箭头符号 ^ 表示选取的字母)
            rabbbit
            ^^^^ ^^

            rabbbit
            ^^ ^^^^

            rabbbit
            ^^^ ^^^
*/

/*
    这道题换一个说法会更好理解：计算在 s 的所有子序列中 t 出现的次数。

    思考一下匹配成功后的【选择】
        两个指针 i 和 j 分别指向 s 和 t，设 s 和 t 的长度分别为 m 和 n
        当 s[i] == t[j]，这个字符匹配成功了，
            此时对于字符串 t 来说有两种选择，
                1，让 t[j] 和 s[i] 匹配，然后去求子串 s[i+1, m] 的所有子序列中字符串 t[j+1,n] 出现的次数。
                2，不让 t[j] 和 s[i] 匹配，跳过 s[i]，那么就要求子串 s[i+1, m] 的所有子序列中字符串 t[j,n] 出现的次数。
            两种不同的挑选方式，各自做下去所产生的方式数，相加，是该大问题的解
            比如 s = "bbagbg", t = "bag"
                当 i = 0, j = 0 时，s[i] == t[j]，
                此时我们可以选择让 t[j] 和 s[i] 匹配，然后再递归去求 s = "bagbg" 的所有子序列中 t = "ag" 出现的次数。
                也可以选择不匹配，然后递归去求 s = "bagbg" 的所有子序列中 t = "bag" 出现的次数。
        当 s[i] != t[j]，此时只能让 i 后移，去求子串 s[i+1, m] 的所有子序列中字符串 t[j,n] 出现的次数。

    运用到动态规划中，思路和上面相同，只不过匹配是从最后一个字符开始从后往前匹配。
    定义 dp 数组
        dp[i][j] 表示长度为 i 的字符串 s 的子序列 在长度为 j 的字符串 t 中出现的个数。
    
    状态转移方程
        如何求 dp[i][j]？（长度为 i 的字符串，最后一个字符的下标为 i-1）
        如果 s[i-1] == t[j-1]，有两种选择
            1，让 t[j-1] 和 s[i-1] 进行匹配，结果就是子串 s[i+1, m] 的所有子序列中字符串 t[j+1,n] 出现的次数。
                也就是 dp[i-1][j-1]
            2，不让 t[j-1] 和 s[i-1] 匹配，结果就是子串 s[i+1, m] 的所有子序列中字符串 t[j,n] 出现的次数。
                也就是 dp[i-1][j]
            dp[i][j] 等于这两种情况相加。

        如果 s[i-1] != t[j-1]，结果就是子串 s[i+1, m] 的所有子序列中字符串 t[j,n] 出现的次数，也就是 dp[i-1][j]

        比如，s = "babgbag", t = "bag"，最后一个字符 s[m-1] 等于 t[n-1]，
            如果选择匹配，那么 dp[i][j] 等于 s = "babgba", t = "ba" 的计算结果，也就是 dp[i-1][j-1]
            如果选择不匹配，那么 dp[i][j] 等于 s = "babgba", t = "bag" 的计算结果，也就是 dp[i][j-1]

        所以，状态转移方程为
            如果 s[i-1] == t[j-1], dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
            如果 s[i-1] != t[j-1], dp[i][j] = dp[i-1][j]

        从前往后匹配和从后往前匹配都可以，如果是从前往后匹配，那么状态转移方程就是 dp[i][j] 和 dp[i+1][j+1] 的关系了。
    base case
        1，如果 t 为空，那么 s 无论多长，都只有一个解，所以 dp[i][0] = 1，0 <= i <= s.length()
        2，如果 t.length() > s.length()，没有结果

    遍历顺序
        从状态转移方程得出，要求 dp[i][j] 需要知道左上，上方两个点的数据，
        所以可以采用外层从上到下（求每一行），内层从左到右（求每一列）的顺序遍历。
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        if (t.length() > s.length())
            return 0;
        //这里用 unsigned long long，有的例子会越界
        vector<vector<unsigned long long>> dp(s.length() + 1, vector<unsigned long long>(t.length() + 1, 0));
        for (int i = 0; i <= s.length(); i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= s.length(); i++) {
            for (int j = 1; j <= t.length(); j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }        
        }
        return dp[s.length()][t.length()];
    }
};

/*
    状态压缩
        从状态转移方程可以看出，当前行的数据只和上一行有关，所以可以压缩到一维数组
        遍历顺序
            在求 dp[i][j] 的时候，需要用到 dp[i-1][j-1] 和 dp[i-1][j]，
            内层循环需要从右往左遍历，不然会出现数据覆盖问题。
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        if (t.length() > s.length())
            return 0;
        //这里用 unsigned long long，有的例子会越界
        vector<unsigned long long> dp(t.length() + 1, 0);

        //base case
        dp[0] = 1;

        for (int i = 1; i <= s.length(); i++) {
            for (int j = t.length(); j >= 1; j--) {
                if (s[i - 1] == t[j - 1])
                    dp[j] = dp[j - 1] + dp[j];
            }        
        }
        return dp[t.length()];
    }
};

int main() {
    return 0;
}