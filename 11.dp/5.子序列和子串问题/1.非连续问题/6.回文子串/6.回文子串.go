package main

/*
   题目：leetcode 647
   给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。
   具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

   示例 1：
       输入："abc"
       输出：3
       解释：三个回文子串: "a", "b", "c"
   示例 2：
       输入："aaa"
       输出：6
       解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

*/

/*
   可以采用和 3.最长回文子串 一样的代码。
   在 最长回文子串 中，当检测到子串 s[i..j] 是回文串，我们去检测子串的长度，
   而在本题中不需要管长度，只需要让 ans++ 即可。

   不过需要注意的是，在最长回文子串中，我们并没有计算单个字符的情况，所以要让 ans 初始化为 n
       比如 s = "abc"，此时有三个回文子串 "a", "b", "c"，但是代码中并没有处理，所以 ans 要初始化为 3

   这里就直接给出空间压缩以后的代码了。
   时间复杂度：两层循环，O(n^2)
   空间复杂度：O(n)
*/

func countSubstrings(s string) int {
	n := len(s)
	if n == 0 {
		return 0
	}

	dp := make([][]bool, n)
	for i := 0; i < n; i++ {
		dp[i] = make([]bool, n)
	}

	// base case
	for i := 0; i < n; i++ {
		dp[i][i] = true
	}

	//初始化为 n
	ret := n
	for i := n - 1; i >= 0; i-- {
		for j := i + 1; j < n; j++ {
			dp[i][j] = (s[i] == s[j]) && (dp[i+1][j-1] || (j-i+1 <= 2))
			if dp[i][j] {
				ret++
			}
		}
	}
	return ret
}

func main() {
}
