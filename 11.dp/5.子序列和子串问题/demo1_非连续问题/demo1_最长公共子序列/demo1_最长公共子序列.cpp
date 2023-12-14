#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 1143
    给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。

    一个字符串的 子序列 是指这样一个新的字符串：
        它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
    例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

    若这两个字符串没有公共子序列，则返回 0。

    示例：
        输入：text1 = "abcde", text2 = "ace" 
        输出：3  
        解释：最长公共子序列是 "ace"，它的长度为 3。

*/

/*
    题目是求在不改变字符顺序的情况下，两个字符串有多少个字符相等。
    用两个下标指针 i, j，分别指向两个字符串，
        当 s1[i] == s2[j]时，找到一个公共字符，i++, j++，
        当s1[i] != s2[j]时，此时有两种情况，s1[i] 可能和 s2[j+1] 匹配，s2[j] 也可能和 s1[i+1] 匹配。
        所以分两种情况，i向后移或者j向后移，分别求出两个情况的结果，取最大的那个
*/

/*
    方法1，暴力递归
*/

int baoli(string s1, string s2, int i, int j) {
    if(i >= s1.length() || j >= s2.length())
        return 0;
    //比较，匹配成功，公共子序列长度加1
    if(s1[i] == s2[j]) {
        //n和m都向后移
        return 1 + baoli(s1, s2, i + 1, j + 1);
    } 

    //没有匹配成功
    return max(
            baoli(s1, s2, i + 1, j),
            baoli(s1, s2, i, j + 1));
}

/*
    方法2，备忘录
    备忘录算法是从顶往下计算，用一个dp数组，记录中间状态
*/

int help_digui(string s1, string s2, int m, int n, vector<vector<int>>& dp) {
    if(m >= s1.length() || n >= s2.length())
        return 0;
    //已经计算过
    if(dp[m][n] != -1)
        return dp[m][n];

    //比较，匹配成功
    if(s1[m] == s2[n]) {
        //n和m都向后移
        dp[m][n] = 1 + help_digui(s1, s2, m + 1, n + 1, dp);
    } else {
    //没有匹配成功
        dp[m][n] =  max(
                    help_digui(s1, s2, m + 1, n, dp),
                    help_digui(s1, s2, m, n + 1, dp));
    }

    return dp[m][n];
}

int user_help(string s1, string s2) {
    //dp[m][n]，将值初始化为-1，因为0也是一种可能的结果值
    vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1, -1));
    return help_digui(s1, s2, 0, 0, dp);
}

/*
    方法3，动态规划

    定义 dp 数组
        dp[m][n] 表示长度为 m 的字符串 s1 和 长度为 n 的字符串 s2，他们的最长公共子序列为 dp[m][n]。
        
    状态转移方程 
        如何求 dp[m][n]？
            对于 s1 的第 m 个字符 和 s2 的第 n 个字符（长度为 m 的字符串，第 m 个字符的下标为 m-1）
                如果 s1[m-1] == s2[n-1]，这两个相同的字符是公共字符，继承之前的数据 dp[m-1][n-1]，然后加 1 即可。
                如果 s1[m-1] != s2[n-1]，那么要么 s1 往前退一步，要么 s2 往前退一步，两种情况分别对应 dp[m-1][n] 和
                    dp[m][n-1]，取这两者的较大值。
        所以状态转移方程为
            如果s1[m-1] == s2[n-1], dp[m][n] = dp[m-1][n-1] + 1
            如果s1[m-1] != s2[n-1], dp[m][n] = max( dp[m][n-1], dp[m-1][n] )       
    
    base case
        dp[0][..] = dp[..][0] = 0
    
    遍历顺序
        根据状态转移方程，知道要求 dp[m][n]，需要知道左边，上边，和左上的数据，
        所以按照 外层从上往下，内层从左往右的顺序遍历
*/

int dp(string s1, string s2) {
    vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1, 0));

    for(int m = 1; m <= s1.length(); m++) {
        for (int n = 1; n <= s2.length(); n++) {
            //第m个字符对应的下标为 m-1
            if(s1[m - 1] == s2[n - 1]) {
                dp[m][n] = 1 + dp[m - 1][n - 1];
            } else {
                dp[m][n] = max(dp[m][n - 1], dp[m - 1][n]);
            }
        }
    }

    return dp[s1.length()][s2.length()];
}

/*状态压缩
    比较明显的，可以看出，只需要两个一维数组就够了，用来保存当前行和上一行（m-1是上一行，m是当前行）
    能不能像demo4完全背包问题一样，只采用一个一维数组？
        看起来好像不能，因为demo4完全背包问题中，每次求dp[n][s]，用到的是上一行的dp[n-1][s]和当前行的dp[n][s - coins[n-1]]
        而这个问题，需要用到当前行的dp[m][n - 1]和上一行的dp[m - 1][n - 1]，都需要用到[n-1]位置的数据，所以不能用一个一维数组实现

    但是我们发现，每个dp[i][j]只和它附近的三个状态有关，上一行数据的两个值，和当前行dp[i][j]左边的dp[i][j-1]
        如果画一下dp table，能更清晰的表达
            dp[i-1][j-1]    dp[i-1][j]
            dp[i][j-1]          ?
        通过上面三个点，求dp[i][j]
        可以采用一个一维数组，保存上一行的数据，再使用一个int值，保存当前行的dp[i][j-1]

    但是在实现的时候，发现会出现一维数组数据覆盖的问题，导致上一行的数据丢失，画图来检查，到底应该会辅助变量来存储哪个值？
            dp[i-1][j-1]    dp[i-1][j]  dp[i-1][j+1]
            dp[i][j-1]          A           B
        注意，只有一个一维数组，保存的是第一行的数据
        首先来求A位置的值，假设求得值为c，此时dp[j]变成c，那么dp[i-1][j]（也就是上一行的数据）被覆盖掉了，
            而在求B位置的值时，是需要这个值的，
            所以，应该在dp[i][j]被求出来之前，先保存 dp[i-1][j]的值（在dp[i][j]求出来之前，dp[j]的值是dp[i-1][j]，也就是上一行的数据）
*/

int dp_plus(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    vector<int> dp(n + 1, 0);
    
    for(int i = 1; i <= m; i++) {
        //求新一行数据的时候要重置该值
        int dp_pre = 0;
        for (int j = 1; j <= n; j++) {
            /*
                假设现在开始求A位置的数据，dp_pre保存的是dp[i-1][j-1]，dp[j]保存的是dp[i-1][j]，dp[j-1]保存的是dp[i][j-1]，
                在求出A之前，也就是dp[i-1][j]被覆盖前，用一个变量temp保存起来
                    为什么还需要一个临时变量？
                        1，dp[i-1][j]不能直接赋值给 dp_pre，dp_pre此时保存的是dp[i-1][j-1]，在求A的时候还会用到
                        2，不能在A被求出来以后，让 dp_pre = dp[j]，此时dp[j]是dp[i][j]，而dp[i-1][j]已经丢失了
                            记住，我们要保存的值是dp[i-1][j]
                在求完A以后，dp[i]保存的是A位置的数据，temp保存的是dp[i-1][j]位置的数据，把temp的值赋值给 dp_pre，
            */
            int temp = dp[j];
            //第i个字符对应的下标为 i-1
            if(s1[i - 1] == s2[j - 1]) {
                dp[j] = 1 + dp_pre;             
            }            
            else {
                dp[j] = max(dp[j-1], dp[j]);     
            }
            dp_pre = temp;
        }
    }

    return dp[n];
}


int main() {
    string s1 = "abcde";
    string s2 = "ace";

    //m ,n初始值为0
    cout << "baoli:  " << baoli(s1, s2, 0, 0) << endl;
    cout << "user_help:  " << user_help(s1, s2) << endl;
    cout << "dp_plus:  " << dp_plus(s1, s2) << endl;
    return 0;
}