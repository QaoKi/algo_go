package main

/*
	题目： leetcode 567
		给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。
		换句话说，第一个字符串的排列之一是第二个字符串的子串。

		示例1：
			输入: s1 = "ab" s2 = "eidbaooo"
			输出: True
			解释: s2 包含 s1 的排列之一 ("ba").
*/

/*
	2个字符串的排列相等 ==> 2个字符串 各个字符 的个数都一一相等。
	比如 aabc 和 baca 这 2 个字符串的排列是相等的，都包含 2 个 a、1 个 b、1 个 c。

	方法1：
		用 2.最小覆盖子串 的方法，求出最小覆盖子串后，判断最小覆盖子串的长度是否和 s1 相等，如果相等，说明可以
	方法2：
		记 s1 的长度为 n，s2 的长度为 m，维护一个长度为 n 的滑动窗口，每次进、出一个字符后，判断该滑动窗口中
			的子串是否是 s1 的排列

		使用一个 map cnt ，cnt 统计 s1 中各个字符的个数，每次从 s2 中进一个字符，就减去，
		当 cnt 中key的值都为0时，符合
		滑动窗口每向右滑动一次，就多统计一次进入窗口的字符，少统计一次离开窗口的字符。
			然后，判断 cnt 中key的值是否都为0，都为 0 时符合
		因为map的比较比较麻烦，而题目中说了字符串只有小写字母，所以，用[26]int数组表示

		时间复杂度：数组的长度为 26，检查一次复杂度为O(26)，遍历一次m和n，所以复杂度为 复杂度为 O(26*(m+n))，
					常数项省略，复杂度为 O(m+n)
		空间复杂度：设字符集为C（本题中是26），空间复杂度为 O(C)
*/

func checkInclusion(s1 string, s2 string) bool {
	if s1 == "" || s2 == "" || len(s1) > len(s2) {
		return false
	}

	cnt := [26]int{}
	check := func() bool {
		for i := 0; i < 26; i++ {
			if cnt[i] != 0 {
				return false
			}
		}
		return true
	}

	// 先取 s2 的前 n 个字符
	for i := 0; i < len(s1); i++ {
		cnt[s1[i]-'a']++
		cnt[s2[i]-'a']--
	}

	if check() {
		return true
	}

	for i := len(s1); i < len(s2); i++ {
		//滑动窗口大小固定为 n，进来一个就出去一个
		cnt[s2[i]-'a']--
		cnt[s2[i-len(s1)]-'a']++

		if check() {
			return true
		}
	}

	return false
}

/*
	优化：每次都去判断数组中所有的值，显然复杂度会很高。
		注意到每次窗口滑动时，只统计了一进一出两个字符，却判断了整个 cnt 数组
		用一个变量 diff 来记录 cnt 中不满足条件的字符的个数。于是就转换成了判断 diff 是否为0

		每次窗口滑动，记 cnt 中一进一出的两个字符为 x 和 y
		若 x 等于 y，则对 cnt 无影响，跳过
		若 x 不等于 y，对于字符 x 和 y 进来和出去以后需要做处理

		用这个方法需要注意的是，进入循环前，需要先处理好 s2 的前 n 个字符，循环从 s2 的第n+1个字符开始
*/

func checkInclusion1(s1, s2 string) bool {
	n, m := len(s1), len(s2)
	if n > m {
		return false
	}

	cnt := [26]int{}
	diff := 0
	for i := 0; i < n; i++ {
		cnt[s1[i]-'a']++
		cnt[s2[i]-'a']--
	}

	// 初始化 diff 的值
	//diff 记录的是 cnt 中不满足条件的字符的个数，只要值不等于0，就不满足条件
	for _, c := range cnt {
		if c != 0 {
			diff++
		}
	}

	// s2 的前 n 个就满足，直接返回
	if diff == 0 {
		return true
	}

	for i := n; i < m; i++ {
		// 要进的字符和要出的字符
		x, y := s2[i]-'a', s2[i-n]-'a'

		// 两个字符相等，对 cnt 无影响
		if x == y {
			continue
		}

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
			return true
		}
	}

	return false
}
