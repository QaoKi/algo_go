#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 72
    给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

    你可以对一个单词进行如下三种操作：
        插入一个字符
        删除一个字符
        替换一个字符

    示例：
        输入    word1 = "horse", 
                word2 = "ros"
        输出：3
        解释：
            horse -> rorse (将 'h' 替换为 'r')
            rorse -> rose (删除 'r')
            rose -> ros (删除 'e')
*/

/*
    编辑距离问题就是给我们两个字符串s1和s2，只能用插入、删除、替换三种操作，让我们把s1变成s2，求最少的操作数。
        需要明确的是，不管是把s1变成s2还是反过来，结果都是一样的
    
    思路：
        和 最长公共子序列 类似，用两个下标指针 i, j，分别指向两个字符串，
            当 s1[i] == s2[j]时，字符相同，不需要变动，直接向后移，i++, j++，
            当 s1[i] != s2[j]时，运用插入、删除、替换三种操作解决这个问题，分别求出三种操作的结果值，取最小的。
*/

/*
    方法1，暴力递归
*/

int baoli(string s1, string s2, int i, int j) {
    //base case，一个字符串走到头了，另一个如果没走到头，那只能用删除操作把没走到头的字符串的多余字符删掉
    if(i == s1.length())
        return s2.length() - j;
    if(j == s2.length())
        return s1.length() - i;

    //比较，匹配成功，不需要消耗操作数，直接后移
    if(s1[i] == s2[j]) {
        return baoli(s1, s2, i + 1, j + 1);
    } 

    //没有匹配成功，运用三种操作（三种操作都会导致操作数增加），取结果最小的
    return min(
            baoli(s1, s2, i + 1, j) + 1,    //删掉s1[i] 或者 在s2[j]的前面插入一个和 s1[i] 一样的字符
            min(baoli(s1, s2, i, j + 1) + 1,    //删掉s2[j] 或者 在s1[i]的前面插入一个和 s2[j] 一样的字符
            baoli(s1, s2, i + 1, j + 1) + 1));   //将s1[i]和s2[j]替换成相同的字符
}

/*
    方法2，备忘录
    备忘录算法是从顶往下计算，用一个dp数组，记录中间状态
*/

int help_digui(string s1, string s2, int i, int j, vector<vector<int>>& dp) {
    if(i == s1.length())
        return s2.length() - j;
    if(j == s2.length())
        return s1.length() - i;
    //已经计算过
    if(dp[i][j] != -1)
        return dp[i][j];

    //比较，匹配成功
    if(s1[i] == s2[j]) {
        //n和m都向后移
        dp[i][j] = help_digui(s1, s2, i + 1, j + 1, dp);
    } else {
        //没有匹配成功
        dp[i][j] =  min(help_digui(s1, s2, i + 1, j, dp) + 1, 
                        min(help_digui(s1, s2, i, j + 1, dp) + 1, help_digui(s1, s2, i + 1, j + 1, dp) + 1));   
    }

    return dp[i][j];
}

int user_help(string s1, string s2) {
    //dp[m][n]，将值初始化为-1，因为0也是一种可能的结果值（防止不能准确的判断是否已经计算过，从而导致重复计算）
    vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1, -1));
    return help_digui(s1, s2, 0, 0, dp);
}

/*
    方法3，动态规划

        定义 dp 数组
            dp[i][j] 表示将长度为 i 的字符串 s 转换成长度为 j 的字符串 t，所使用的最少操作数

        状态转移方程：（长度为 i 的字符串，第 i 个字符的下标为 i-1）
            如果 s[i-1] == t[j-1]，最后一个字符相同，结果继承之前的数据，dp[i][j] = dp[i-1][j-1]，
            如果 s[i-1] != t[j-1]，运用插入、删除、替换三种操作解决这个问题，分别求出三种操作的结果值，取最小的。
            
            所以状态转移方程为
                如果 s[i-1] == t[j-1], dp[i][j] = dp[i-1][j-1]
                如果 s[i-1] != t[j-1], dp[i][j] = min( dp[i][j-1] + 1, dp[i-1][j] + 1, dp[i-1][j-1] + 1 )
    
        base case: 
            1，当 t 为空时，dp[i][0] = i，因为 t 为空，所以要把 s 都删除掉
            2，同理，当 s 为空时，dp[0][j] = j，需要把 t 都删除掉

        遍历顺序
            从状态转移方程可以看出，要求 dp[i][j]，需要知道 左上，左边，上边，三个位置的数据，
            所以遍历可以按照 外层从上到下（求每一行），内层从左到右的顺序（求每一列）
*/

int dp(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    //base case
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int i = 0; i <= n; i++)
        dp[0][i] = i;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            //第i个字符对应的下标为 i-1
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min( dp[i][j-1] + 1, min( dp[i-1][j] + 1, dp[i-1][j-1] + 1 ));
        }
    }

    return dp[m][n];
}

/*
    状态压缩，和 最长公共子序列 思路相同，但是要注意的是，因为 base case不同，所以 dp_pre 在初始化时略微不同。
    首先，根据 最长公共子序列 中的描述我们知道，dp_pre保存的是dp[i-1][j-1]
        当开始求第i行数据的时候，当j等于1时，必须提前知道dp[i-1][0], d[i-1][1]和dp[i][0] 才能求出dp[i][1]
        dp[i-1][0]对应着dp_pre，在 最长公共子序列 中，base case都是0，所以不用管，但是在这道题中，
        根据base case，dp[i-1][0]的值就是i-1，dp[i][0]的值为i
*/

int dp_plus(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    vector<int> dp(n + 1, 0);

    //base case

    for (int i = 0; i <= n; i++)
        dp[i] = i;

    for (int i = 1; i <= m; i++)
    {
        //base case
        int dp_pre = i-1;
        dp[0] = i;
        for (int j = 1; j <= n; j++)
        {
            int temp = dp[j];
            //第i个字符对应的下标为 i-1
            if (s1[i - 1] == s2[j - 1])
                dp[j] = dp_pre;
            else
                dp[j] = min( dp[j-1] + 1, min( dp[j] + 1, dp_pre + 1 ));

            dp_pre = temp;
        }
    }

    return dp[n];
}

int main() {
    return 0;
}