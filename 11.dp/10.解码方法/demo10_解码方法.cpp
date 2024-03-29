#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	题目： leetcode 91
		一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
			'A' -> 1
			'B' -> 2
			...
			'Z' -> 26
		要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。
		例如，"111" 可以将 "1" 中的每个 "1" 映射为 "A"，从而得到 "AAA" ，
			或者可以将 "11" 和 "1"（分别为 "K" 和 "A" ）映射为 "KA" 。
		注意，"06" 不能映射为 "F" ，因为 "6" 和 "06" 不同。

		给你一个只含数字的非空字符串 s ，请计算并返回解码方法的总数 。

		示例 1：
			输入：s = "12"
			输出：2
			解释：它可以解码为 "AB"（1 2）或者 "L"（12）。
		示例 2：
			输入：s = "0"
			输出：0
			解释：没有字符映射到以 0 开头的数字。含有 0 的有效映射是 'J' -> "10" 和 'T'-> "20" 。
				由于没有字符，因此没有有效的方法对此进行解码，因为所有数字都需要映射。
		示例 3：
			输入：s = "06"
			输出：0
			解释："06" 不能映射到 "F" ，因为字符串开头的 0 无法指向一个有效的字符。
*/

/*
	1，dp
		首先要明确的是，如果字符串中有一个字符不能解码，那么整个字符串就不能解码
		定义 dp[i] 为以s[i]为结尾的子串 s[0...i]的译码方法总数。

		其次，要明确dp[i]和dp[i-1]之间的关系，
		对于字符 s[i]，有两种解码方式，一个是单独解码，一个是和前面的字符s[i-1]合并解码，
			这就和爬楼梯是一样的，每次能爬1级台阶或者2级台阶，对于总共n级台阶，最后一步可以选择爬1级台阶，也可以选择爬2级台阶，
			所以状态转移方程为 f(n) = f(n-1) + f(n-2)
			它意味着爬到第 n 级台阶的方案数是爬到第 n-1 级台阶的方案数和爬到第 n-2 级台阶的方案数的和。
		所以，对于本题，如果没有其他限制条件，那么 dp[i] = dp[i-1] + dp[i-2]
			解释：s[i]和s[i-1]合并解码，就相当于最后一步爬2级台阶，所以为 dp[i-2]
				s[i]单独解码，相当于最后一步爬1级台阶，所以为 dp[i-1]

		现在有了其他限制条件，字符 '0' 是一个需要考虑的点，它不能单独解码。
		考虑s[i]能否单独解码
			如果 s[i] != '0'，那么 s[i] 可以单独解码，此时 dp[i] = dp[i-1]，
		再考虑s[i]是否能和s[i-1]合并解码
			int temp = (s[i-1] - '0') * 10 + (s[i] - '0')
			如果 temp >= 10 && temp <= 26，那么s[i]可以和s[i-1]合并解码，此时dp[i] += dp[i-2]，
		base case:
			1，如果s[0] == '0'，首个字符是'0'，无法解码，返回0
			2，dp[0] = 1
		注意的点，
			1，s[i]转成int，不能直接int(s[i])，而应该s[i]-'0'，int(s[i])是转成acsii码了
			2，代码中不能用 if(10 <= temp <= 26)，而应该 if(temp >= 10 && temp <= 26)
*/

int dp(string s) {
	int n = s.length();
	if(n == 0 || s[0] == '0') return 0;

	//dp[i]表示以s[i]为结尾的子串 s[0...i]的译码方法总数。
	vector<int> dp(n, 0);
	dp[0] = 1;

	for (int i = 1; i < n; i++) {
		//先看s[i]能否单独解码
		if(s[i] != '0') {
			dp[i] = dp[i - 1];
		}

		//再看s[i]和s[i-1]能否合并解码
		int temp = (s[i-1] - '0') * 10 + (s[i] - '0');
		if(temp >= 10 && temp <= 26) {
			//因为循环因子i是从1开始的，而在这里要用到dp[i-2]，所以特殊处理一下i=1的情况
			if(i == 1)
				dp[i] += 1;
			else
				dp[i] += dp[i - 2];
		}
	}

	return dp[n - 1];
}

/*
	2，状态压缩
		既然和爬楼梯一样，那么自然可以压缩到空间复杂度为O(1)
		用两个变量保存之前的状态
*/

int dp_plus(string s) {
	int n = s.length();
	if(n == 0 || s[0] == '0') return 0;

	int n_1 = 1;	//dp[i-1]
	//这里直接初始化dp[i-2]为1，当i=1的时候，就不需要特殊处理了
	int n_2 = 1;	//dp[i-2]

	for (int i = 1; i < n; i++) {
		int curr = 0;
		if (s[i] != '0')
			curr = n_1;

		int temp = (s[i - 1] - '0') * 10 + (s[i] - '0');
		if(10 <= temp && temp <= 26) 
			curr += n_2;
			
		n_2 = n_1;
		n_1 = curr;
	}

	return n_1;
}

int main()
{
	return 0;
}