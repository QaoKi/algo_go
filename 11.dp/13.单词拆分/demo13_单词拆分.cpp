#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;


/*
	题目： leetcode 139
		给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，
		判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
		说明：
			拆分时可以重复使用字典中的单词。
			你可以假设字典中没有重复的单词。
		示例 1：
			输入: s = "applepenapple", wordDict = ["apple", "pen"]
			输出: true
			解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
     			注意你可以重复使用字典中的单词。
		示例 2：
			输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
			输出: false
*/

/*
	方法1，回溯
		和回溯题目的 分割回文串 一样，枚举字符串的所有分割情况去 wordDict 中匹配，
		对于字符串来说，可以分割一个字符，也可以分割两个字符。
	时间复杂度：O(2^n)
	空间复杂度；O(n)，递归栈，辅助空间 set
*/

class Solution {
public:
	bool dfs(string s, unordered_set<string> &unset,int startIndex) {
		//检测到了最后
		if (startIndex >= s.length() - 1)
			return true;

		//每次可以选择切一个字符，或者切两个字符或者三个，最多可以把 s 剩余的字符都切下来。
		//还剩 s.length() - startIndex 个字符
		//如果切下来的字符串存在 unset 中，拿s剩下的字符串继续递归。
		for (int i = 1; i <= s.length() - startIndex; i++) {
			string str = s.substr(startIndex, i);
			if (unset.find(str) == unset.end()) {
				continue;
			}
			//继续递归
			if (dfs(s, unset, startIndex + i))
				return true;
		}

		return false;
	}

    bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> unset(wordDict.begin(), wordDict.end());
		return dfs(s, unset, 0);
	}
};

/*
	方法2，记忆化递归
		暴力递归存在大量的重复计算，如何标记这些重复计算，也是一个经验。
		对于这题，比如 s = "abcdefg"，wordDict = ["a", "b", "ab"]
			当我们将 "a" 分割下来，需要再递归去求 "bcdefg"， 
				再将 "b" 分割下来，需要再递归去求 "cdefg"， 
			当回溯回来，我们将 "ab" 分割下来，需要再递归去求 "cdefg"，
			此时就产生了重复计算 "cdefg"。
		使用一个数组 memory 保存每次计算的以 startIndex 起始的字符串的计算结果，
		如果 memory[startIndex] 里已经被赋值了，直接用 memory[startIndex] 的结果。
		在上面的例子中，"cdefg" 是以 s[2] 为起始的字符串，所以它的结果保存在 memory[2]，
		我们也可以用 map<string, bool> 来保存，只不过开销大。
*/

class Solution {
public:
	bool dfs(string s, unordered_set<string> &unset, vector<int> &memory, int startIndex) {
		//检测到了最后
		if (startIndex > s.length() - 1)
			return true;

		//如果之前已经计算过，直接用
		if (memory[startIndex] != -1)
			return memory[startIndex];

		for (int i = 1; i <= s.length() - startIndex; i++) {
			string str = s.substr(startIndex, i);
			if (unset.find(str) == unset.end()) {
				continue;
			}
			//继续递归
			if (dfs(s, unset, memory, startIndex + i)) {
				//这种分割可以
				memory[startIndex] = 1;
				return true;
			}
				
		}
		//这种分割不行
		memory[startIndex] = 0;
		return false;
	}

    bool wordBreak(string s, vector<string>& wordDict) {
		//初始值为 -1，表示没有计算过，值 0 表示这种分割不行，值 1 表示这种分割可以
		vector<int> memory(s.length(), -1);
		unordered_set<string> unset(wordDict.begin(), wordDict.end());
		return dfs(s, unset, memory, 0);
	}
};

/*
	方法3，动态规划
	
	定义 dp 数组
		dp[i] 表示字符串 s 的前 i 个字符组成的子串 s[0..i-1] 是否能被空格拆分成若干个字典中出现的单词。
	状态转移方程
		如何求 dp[i]？
			对于子串 s[0...i-1]，我们将其拆成两部分，s[0...j-1] 和 s[j...i-1]，我们需要检测这两部分是否都合法。
			对于前半部分 s[0...j-1]，合不合法其实就是 dp[j]，此时，如果 dp[j] 等于 true，
				并且 s[j...i-1] 组成的单词在 wordDict 中，那么整体的 dp[i] = true。
			而 j 的取值范围为 [0, i-1]，我们枚举每一种情况，只要有一种情况，使得 
				dp[j] == true && s[j...i-1] 在 wordDict 中，那么就让 dp[i] = true。
	base case
		dp[0] = true，如果字符串为空，说明出现在单词表中，这样解释有一些牵强，从递归公式中可以看出，
			dp[i] 的状态依靠 dp[j] 是否为true，那么 dp[0] 就是递归的根基，dp[0]一定要为true，否则递归下去后面都都是false了。
		
		在拆分字符串的时候，是不是可以拆成 s[0...j] 和 s[j+1...i-1] ？
			s[0...j] 是否合法，保存在 dp[j+1]，所以，判断条件变为
			如果 dp[j+1] 为true，并且 s[j+1...i-1] 在 wordDict 中，那么整体的 dp[i] = true。
		思路是对的，但是写代码的时候，就发现，base case 中，只初始化了 dp[0]，但是 j 不可能从 -1 开始循环，
			所以 dp[j+1] 不可能为 0 ，也就用不到 dp[0]，但是 dp 数组的其他值都是 false，所以结果肯定全是 false。
		所以，要拆成 s[0...j-1] 和 s[j...i-1]，并且让 j 从 0 开始，虽然从 0 开始循环，前半部分是 s[0...-1]，解释不通，
			但是为了要用上 dp[0]，不得不这样。
	时间复杂度：O(n^2)
	空间复杂度：O(n)	

*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
		//用一个哈希存单词，方便查找 s[j...i-1] 是否在 wordDict 中
		unordered_set<string> unset(wordDict.begin(), wordDict.end());

		int n = s.length();
		vector<bool> dp(n + 1, false);
		dp[0] = true;

		//外层循环：求 dp[i]
		for (int i = 1; i <= n; i++) {
			//j的取值范围为 [0, i-1]，枚举j的取值，判断每一种 s[0...j-1] 和 s[j...i-1] 的情况
			for (int j = 0; j < n; j++) {
				//优化，如果 dp[j] == false，说明这种情况下 dp[i] 不可能为 true
				if (dp[j] == false) continue;
				//截取 s[j...i-1]
				string str = s.substr(j, i - j);
				if (dp[j] == true && unset.count(str) > 0) {
					dp[i] = true;
					//dp[i] 为 true了，不用再求了，直接跳出，接着去求dp[i+1]
					break;
				}
			}
		}

		return dp[n];
	}
};

int main()
{
	return 0;
}