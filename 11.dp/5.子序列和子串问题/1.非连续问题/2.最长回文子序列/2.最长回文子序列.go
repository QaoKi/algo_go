package main

/*
   题目：leetcode 516
   给定一个字符串 s ，找到其中最长的回文子序列，并返回该序列的长度。可以假设 s 的最大长度为 1000 。

   示例：
       输入："bbbab"
       输出：4
       解释：一个可能的最长回文子序列为 "bbbb"

*/

/*
   乍一看，只有一个字符串，思考用一个一维数组来定义状态转移方程，
       定义 dp[n] = x 表示前n个字符组成的字符串的最长回文子序列长度为 x，
       那么如何求出dp[n]和dp[n-1]之间的关系呢？
           本题是求回文，假设dp[n-1]我们已经求出，当把第n个字符算进来，根本没有思路去判断第n个字符对已经求出的回文子序列有什么影响
   转变思路用二维数组。
       定义：在子串 s[i..j] 中，最长回文子序列的长度为 dp[i][j]，注意，这道题中i和j都是在字符串s的字符下标
           dp[i][j] 就是从 s 中截取出来的字串

   假设已经知道了 dp[i + 1][j - 1]，如何求 dp[i][j]？
       用图来表示：第一行表示下标，第二行表示字符串s

                   i   i+1             j-1  j
                   ?    b   a   c   b   d   ?
       从图中可以看出，dp[i + 1][j - 1] 等于3，（回文子序列为 "bab"）
       如何求 dp[i][j]？
           如果s[i] == s[j]，说明可以直接组成回文子序列，假设s[i] == s[j] == "e"，那么组成回文子序列为 "ebabe",
               所以，dp[i][j] = dp[i + 1][j - 1] + 2
           如果s[i] != s[j]，有两种情况，
               1，s[i]和s[i+1..j-1]组成的新子串 s[i...j-1]的最长回文子序列的长度
               2，s[j]和s[i+1..j-1]组成的新子串 s[i+1...j]的最长回文子序列的长度
           取这两种情况的最大值，
               所以 dp[i][j] = max(dp[i][j-1], dp[i+1][j])

       base case：
               1, 当 i == j 时，dp[i][j] = 1，（因为字符s[i...j]只有一个字符）
               2, dp[i][j] 表示子串 s[i..j] 的最长回文子序列的长度，
                   当 i > j时，根本构不成子串，所以当 i > j 时，dp[i][j] = 0;

       我们设 字符串的长度为 n，来思考几个问题。
       1，思考 base case 的第2种情况，dp是二维数组，当 i > j时，对应的其实就是对角线的下半部分，所以对角线的下半部分值都为0，
           而对角线的部分是 base case 的第1种情况，值为1，所以，dp table 是下面的情况：
           （二维数组的行和列都取的字符串的长度，所以是一个正方形，假设 n 为4）
               1  ？ ？ *
               0  1  ？ ？
               0  0  1  ？
               0  0  0  1
           ？是未知的值，* 是我们需要的最终结果。

       2，再来看一下遍历的顺序问题。
           根据状态转移方程，我们知道，想求 dp[i][j]，需要知道 dp[i+1][j-1]，dp[i+1][j]，dp[i][j-1] 这三个位置的值：
               比如：
                   4  ？
                   3  5
               需要根据4,3,5来求 ？处的值，所以，想求dp[i][j]，必须提前知道dp[i][j]的左边，左下，下边位置的值。
           所以，结合上面的 dp table，可以看出，最合适的遍历顺序，是从下往上，从左往右求，一直到求出我们要的结果 dp[0][n-1]，
           所以，i 的遍历范围为 [n-1...0]，而 j 要大于 i （等于i时，结果为1，是已知的），所以 j 的遍历范围为 [i+1, n-1]
               n 是字串的长度

       这里提一下，最外层循环表示当前要求第i行的数据，第二层循环表示当前要求第j列的数据
       总结：base case 很重要，根据 base case，可以画出大概的 dp table，然后根据状态转移方程，确定遍历顺序。
*/

/*
   时间复杂度：两层循环，O(n^2)
   空间复杂度：O(n^2)
*/

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func longestPalindromeSubseq(s string) int {
	dp := make([][]int, len(s))
	for i := 0; i < len(s); i++ {
		dp[i] = make([]int, len(s))
	}

	// base case
	for i := 0; i < len(s); i++ {
		dp[i][i] = 1
	}

	for i := len(s) - 1; i >= 0; i-- {
		for j := i + 1; j < len(s); j++ {
			if s[i] == s[j] {
				dp[i][j] = dp[i+1][j-1] + 2
			} else {
				dp[i][j] = max(dp[i][j-1], dp[i+1][j])
			}
		}
	}
	return dp[0][len(s)-1]
}

func main() {
}
