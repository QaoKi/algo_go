package main

/*
	题目： leetcode 76
		给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
		如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
		注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。

		示例1：
		输入：s = "ADOBECODEBANC", t = "ABC"
		输出："BANC"
*/

/*
	滑动窗口：参考https://leetcode-cn.com/problems/minimum-window-substring/solution/tong-su-qie-xiang-xi-de-miao-shu-hua-dong-chuang-k/
		采用两个指针 left 和 right ，两个指针之间组成一个滑动窗口（两个指针所指向的元素，也包含在窗口中）。
		该题的思路，和 长度最小的子数组 类似，
		当滑动窗口形成的子串，没有包含 t 的所有字符， right 向后移动，扩大滑动窗口，一直到滑动窗口形成的子串，包含了 t 的所有字符。
			此时不断的让 left 向后移动（不断的尝试缩小窗口，看看是否还能满足条件）。找到最小的满足条件的滑动窗口的长度

		问题是，如何判断滑动窗口形成的子串，是否包含了 t 的所有字符？
			1，我们用一个 mapByte := map[byte]int 来存储滑动窗口中需要包含的字符及数量（滑动窗口形成的子串，
				需要包含这些数量的字符才符合条件），用 t 所有的字符来初始化 mapByte
			2，不断扩展窗口，每次新增了一个字符，首先验证一下这个字符是否存在 t 中（防止不必要的空间浪费），
				如果不存在，是无效的字符，就不管了，如果存在，就让 mapByte 中这个字符的数量减1，代表所需该字符的数量减少了1个。
			3，当 mapByte 中所有元素的数量都小于等于0时，说明当前滑动窗口包含了 t 的所有字符，符合条件了。
			4，滑动窗口符合条件以后，不断的缩小窗口，看看是否还能满足条件（为了找到最短的符合条件的子串）
				在缩小过程中，每次窗口移除了某个字符时，同样先判断这个字符是否存在 t 中，如果存在，让 mapByte 中这个字符的数量加1。

		因为本题要返回字符串，所以，需要记录所有符合条件的滑动窗口中，长度最小的滑动窗口的长度和开始下标，用变量保存

		时间复杂度：设m为s的长度，n为t的长度
			因为采用了哈希来存储字符，所以查找，插入的时间复杂度为O(1)
			但是每次 check()的时候，需要遍历一遍字符串 t 的所有字符集，设t的所有字符集为C（因为 t 中可能有重复字符，所以不取长度）
				比如，t = "AABBCC"，长度为 6，但是所有字符集为 3
			最坏情况下，需要调用check()，2m遍（扩大窗口一遍，缩小窗口一遍）
			所以，时间复杂度为 O(C*m + n)，不过这个版本在leetcode中会超时
		空间复杂度：哈希表的消耗，哈希中只保存了t的所有字符集，所以，空间复杂度为 O(C)

*/

func minWindow(s string, t string) string {
	left, right := 0, 0
	length, index := len(s)+1, 0
	mapByte := map[byte]int{}
	for _, c := range t {
		mapByte[byte(c)]++
	}

	check := func() bool {
		for _, c := range t {
			if mapByte[byte(c)] > 0 {
				return false
			}
		}
		return true
	}

	for ; right < len(s); right++ {
		// 增大滑动窗口
		if _, ok := mapByte[s[right]]; ok {
			mapByte[s[right]]--
		}

		for check() {
			// 找长度最小的符合条件的滑动窗口
			if length > right-left+1 {
				length = right - left + 1
				index = left
			}

			if _, ok := mapByte[s[right]]; ok {
				mapByte[s[left]]++
			}

			left++
		}
	}

	if length == len(s)+1 {
		return ""
	}

	return s[index : index+length]
}

/*
	优化：每次判断滑动窗口是否符合条件，都要遍历一遍t的所有字符集 C，复杂度高
		用一个变量来存储当前滑动窗口中，有多少个字符集符合t 中的字符集

		时间复杂度：O(m + n)，m和n是s和t的长度
		空间复杂度依然为 O(C)

	注意的点，有两个坑：
		1，在判断 have 是否应该 +1 的时候，注意判断条件
		2，在判断 have 是否应该 -1 的时候，也要注意条件，可以注意到，两次判断条件，是相同的
*/

func minWindow1(s string, t string) string {
	left, right := 0, 0
	length, index := len(s)+1, 0

	mapByte := map[byte]int{}
	for _, c := range t {
		mapByte[byte(c)]++
	}

	have := 0

	for ; right < len(s); right++ {
		// 增大滑动窗口
		if _, ok := mapByte[s[right]]; ok {
			mapByte[s[right]]--
			/*
				数量也要对的上，这个字符集才算符合
				注意，这里不能使用 <= 0，比如当 t = "ABC"，而 s = "AABDC"，
				遍历到s的第一个"A"时，mapByte["A"]变为0，符合，have++，
				遍历到s的第二个"A"，mapByte["A"]变为-1，如果用 <= 0，还是符合，have++，但是很明显，不符合
			*/
			if mapByte[s[right]] == 0 {
				have++
			}
		}

		for have == len(mapByte) {
			// 找长度最小的符合条件的滑动窗口
			if length > right-left+1 {
				length = right - left + 1
				index = left
			}

			if _, ok := mapByte[s[left]]; ok {
				mapByte[s[left]]++
				// 大于0，说明不符合了，have--
				if mapByte[s[left]] > 0 {
					have--
				}
			}

			left++
		}
	}

	if length == len(s)+1 {
		return ""
	}

	return s[index : index+length]
}
