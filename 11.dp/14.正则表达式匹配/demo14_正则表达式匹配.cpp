#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;


/*
	题目： leetcode 10
		给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
			'.' 匹配任意单个字符
			'*' 匹配零个或多个前面的那一个元素
		所谓匹配，是要涵盖整个字符串 s 的，而不是部分字符串。

		示例 1：
			输入：s = "aa" p = "a"
			输出：false
			解释："a" 无法匹配 "aa" 整个字符串。
		示例 2：
			输入：s = "aa" p = "a*"
			输出：true
			解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。
				因此，字符串 "aa" 可被视为 'a' 重复了一次。
		示例 3：
			输入：s = "ab" p = ".*"
			输出：true
			解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
		示例 4：
			输入：s = "aab" p = "c*a*b"
			输出：true
			解释：因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
*/

/*
	先理解题意，需要 p 通过一些规则变化后和 s 完全匹配，而不能是包含关系，
		比如 s = "aab" p = "aaab"。这样是不可以的。
	而对于 s = "aab" p = "c*a*b"，虽然 p 中的字符 'c' 和 s 中的任何字符都不匹配，
		但是 'c' 后面跟着 '*'，可以选择匹配零个 'c'，这样就让 'c' 消失了
*/

/*
	定义 dp[i][j] 表示 s 的前 i 个字符是否能被 p 的前 j 个字符匹配
	
*/

class Solution {
public:
    bool isMatch(string s, string p) {

    }
};

int main()
{
	return 0;
}