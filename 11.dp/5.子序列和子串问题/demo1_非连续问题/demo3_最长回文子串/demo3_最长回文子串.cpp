#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 5
    给你一个字符串 s，找到 s 中最长的回文子串。
    示例：
        输入：s = "babad"
        输出："bab"
        解释："aba" 同样是符合题意的答案。
*/

/*
    这道题和 最长回文子序列 是相同的问法，有了那题的经验，我们知道需要二维数组来存储状态。

    定义：dp[i][j] 表示子串 s[i..j] 是否为回文子串，
        dp[i][j] 等于 true 表示子串 s[i..j] 是回文串，否则不是回文串，注意，这道题中i和j都是在字符串s的字符下标

    一个回文串，去掉开头字符和结尾字符后，剩下的字符串仍然是回文串。
        根据这条性质，我们可以得出状态转移方程：
            dp[i][j] = ( s[i] == s[j] ) && dp[i+1][j-1]

        但是，还存在特殊情况，当 i > j 时，此时 s[i..j] 构成不了子串，所以此时 dp[i][j] 等于 false。
            比如，dp[4][3]，此时 i > j，所以 dp[4][3] = false，而当我们求 dp[3][4] 的时候，
            此时子串有两个字符，如果调用上面的状态转移方程的话，因为 dp[4][3] 等于false，
            所以会直接让 dp[3][4]也等于 false，但事实上，如果子串是 "aa" 这种的话，
            那么子串是回文串，所以会造成错误，修改状态转移方程，当 s[i] == s[j]，并且子串的长度小于等于2的时候，结果为true。
        综合下来，状态转移方程为

            dp[i][j] = ( s[i] == s[j] ) && ( dp[i+1][j-1] || ( j - i + 1 <= 2 ))

    base case：
            1，当 i == j 时，dp[i][j] 等于 true。
            2，既然是子串，那么 j 要大于等于 i，当 j < i 时，dp[i][j] 等于 false

    再次画出 dp table
            T  ？ ？ *
            F  T  ？ ？
            F  F  T  ？
            F  F  F  T
        ？是未知的值，* 是我们需要的最终结果

    由状态转移方程，我们知道，要求 dp[i][j]。需要提前知道 dp[i+1][j-1] 的值，也就是 (i,j)的左下角的值，
        结合 dp table，最合适的遍历顺序是从下到上，然后从左往右：
            设字符串的长度为n，那么 i 的遍历范围为 [n-1...0]，
            因为 j 要大于 i（等于i时，结果为 true，是已知的），所以 j 的遍历范围为 [i+1...n-1]

    这里提一下，最外层循环表示当前要求第i行的数据，第二层循环表示当前要求第j列的数据

    时间复杂度：两层循环，O(n^2)
    空间复杂度：O(n^2)

    总结：
        这题问法虽然和 最长回文子序列 类似，但是还是有不少坑的，
        1，状态转移方程有特殊情况要考虑
        2，maxLen 要初始化为1，如果初始化为0，当 s 只有一个字符，比如 s = "a"时，会返回 ""，而不是 "a"。
*/

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return s;
        
        int n = s.length();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        //因为要返回子串，所以需要记录最长的回文子串的长度 和 子串的开始下标
        //此时字符串肯定不为空，所以最少会有一个字节的长度
        int maxLen = 1, start = 0;
        //base case
        for (int i = 0; i < n; i++)
            dp[i][i] = true;
            
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                dp[i][j] = (s[i] == s[j]) && (dp[i + 1][j - 1] || (j - i < 2));
                if (dp[i][j] && j - i + 1 > maxLen) {
                    //记录更长的子串
                    maxLen = j - i + 1;
                    start = i;
                }
            }
        }
        return s.substr(start, maxLen);
    }
};

/*
    空间压缩，由状态转移方程式可知，当前行的数据，只和下一行有关，所以将二维数组降为一维数组。
    
    同样从最后一行开始求，所以，i的遍历范围仍为 [i-1..0]。
    但是，当改为一维数组后，在求出 dp[i][j-1] 后，dp[j-1] 就由 dp[i-1][j-1] 被替换成了 dp[i][j-1]。
        而在求 dp[i][j] 的时候，需要使用到 dp[i-1][j-1] 位置的数据，而此时的 dp[j-1]保存的是
        当前行 j-1 位置的数据，不再是下一行 j-1 位置的数据。找不到 dp[i-1][j-1] 了，出现数据覆盖问题。
    所以，j 不再是从前往后遍历，而是从后往前遍历。j 的遍历范围变成 [n-1..i+1]。
        可以通过上面的 dp table 来观察这种现象

    要注意 base case 的处理
*/
class Solution {
public:
    string longestPalindrome(string s) {
        if(s.empty()) return s;
        
        int n = s.length();
        vector<bool> dp(n, false);
        int maxLen = 1, start = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            //现在只能保存一行数据了，所以在每次求新的一行之前，初始化 base case
            dp[i] = true;   //那条对角线
            for (int j = n - 1; j > i; j--) {
                dp[j] = (s[i] == s[j]) && (dp[j - 1] || (j - i < 2));
                if (dp[j] && j - i + 1 > maxLen) {
                    //记录更长的子串
                    maxLen = j - i + 1;
                    start = i;
                }
            }
        }
        return s.substr(start, maxLen);
    }
};

int main() {
    return 0;
}