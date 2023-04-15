package main

/*
	题目： leetcode 3
		给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

		示例1：
			输入: s = "abcabcbb"
			输出: 3
			解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
*/

/*
	滑动窗口
		滑动窗口不断的扩大，用一个 map存储不断进入滑动窗口的字符及数量，
			当发现新进入滑动窗口的字符 x 的数量大于1时，说明 x 之前已经进入了滑动窗口，
			此时不断缩小滑动窗口，并将沿途的字符移出滑动窗口，直到 x 的数量小于等于1，
				比如 s = "abcdecfg"，当遍历到 e，都没问题，此时窗口长度为5，遍历到第二个c，发现已经存在，
					那么只要第一个 c 在窗口中，子串就不满足条件，所以，需要将第一个 c 移出窗口，
					并且，c之前的 ab 也要移出去
		时间复杂度：最坏情况下遍历两次s，所以时间复杂度为 O(n)，n是s的长度
		空间复杂度：每种字符不会重复进入 map，所以空间复杂度为 O(C)，C为s的字符集数量
*/
func lengthOfLongestSubstring(s string) int {

	if len(s) == 0 {
		return 0
	}

	res, left, right := 0, 0, 0
	mapExist := map[byte]int{}

	for ; right < len(s); right++ {

		//字符进入滑动窗口
		mapExist[byte(s[right])]++

		//如果该字符之前已经进入过，不断的缩小窗口，直到该字符只剩一个在窗口中
		for mapExist[byte(s[right])] > 1 {
			mapExist[byte(s[left])]--
			left++
		}

		//到这时，滑动窗口中的子串中不含有重复字符，记录长度
		if res < right-left+1 {
			res = right - left + 1
		}
	}

	return res
}
