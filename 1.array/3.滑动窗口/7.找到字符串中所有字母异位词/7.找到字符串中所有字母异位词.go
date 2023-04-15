package main

/*
	题目： leetcode 438
		给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。
		字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

		示例1：
			输入：s: "cbaebabacd" p: "abc"
			输出：[0, 6]
			解释:
				起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
				起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。
*/

/*
	滑动窗口，当窗口中的字符是 p 的字母异位词，放入结果集中

	这道题和 3.字符串的排列 是一样的，只不过那道题只需要判断有没有，这道题需要找到所有符合的子串
*/

func findAnagrams(s string, p string) []int {
	res := []int{}
	if s == "" || p == "" || len(s) < len(p) {
		return res
	}

	cnt := [26]int{}
	for i := 0; i < len(p); i++ {
		cnt[p[i]-'a']++
		cnt[s[i]-'a']--
	}

	diff := 0
	//diff 记录的是 cnt 中不满足条件的字符个数，只要值不等于0，就不满足条件
	for i := 0; i < 26; i++ {
		if cnt[i] != 0 {
			diff++
		}
	}

	if diff == 0 {
		res = append(res, 0)
	}

	for i := len(p); i < len(s); i++ {
		// 要进的字符和要出的字符
		x, y := s[i]-'a', s[i-len(p)]-'a'

		// 进来
		cnt[x]--

		// 原来不符合的，进来以后符合了，diff减1
		if cnt[x] == 0 {
			diff--
		}

		// 原来符合的，进来以后不符合了，diff加1
		if cnt[x] == -1 {
			diff++
		}

		// 出去
		cnt[y]++

		// 原来不符合的，出去以后符合了，diff减1
		if cnt[y] == 0 {
			diff--
		}

		// 原来符合的，出去以后不符合了，diff加1
		if cnt[y] == 1 {
			diff++
		}

		if diff == 0 {
			res = append(res, i-len(p)+1)
		}
	}

	return res
}
