package main

/*
	题目： leetcode 30
		给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
		注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

		示例1：
			输入: s = "barfoothefoobarman", words = ["foo","bar"]
			输出: [0,9]
			解释: 从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
				输出的顺序不重要, [9,0] 也是有效答案。
		示例2：
			输入: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
			输出：[]
*/

/*
	滑动窗口
		这道题，和 3.字符串的排列 类似，只不过每个字符的排序，变成了每个字符串的排列，
		方法相同，设 words 中每个单词的长度为 size，一共 n 个单词，那么固定滑动窗口大小为 len = size*n，
		每次滑动窗口滑动时，不再进出一个字符，而是进出一个长度为 size 的单词。

		上面的思路不对：
			每次在 s 中，从右指针开始，取大小与 size 的字符串作为一个单词，这点是没错的，
			但是右指针在朝后移动的时候，也就是滑动窗口扩大的时候，不能一下子跳过 size，
				比如 s = "aaabbbcccddd"，words = ["aab", "abb"]，size = 3，
				如果一下子跳过 size，那么只能遍历到单词 aaa, bbb ,ccc, ddd，而不能遍历到单词 aab abb bbc 这些。
		方法：
			从 s 中取长度为 length = size*n 的子串
				依次取 [0, length - 1], [1, length], [2, length + 1]...[m-length, m-1]，作为子串去判断符不符合：
				比如 s = "aabbccdd", words = ["aa", "bb"]
				分别取s中的 aabb, abbc, bbcc, bccd, ccdd 进行判断
			如果判断子串是否符合？
				把子串看做一个单独的字符串，每次从子串中截取长度为 size 的单词，判断是否存在 words中，并判断数量是否一致，
					和之前的方法一致，这次当右指针后移，直接跳过 size，而且也不需要左指针了。

			时间复杂度：设s的长度为m，words中每个单词长度为size，一共n个单词，每次从s中取子串进行判断，取了 m - size*n次，
				判断一个子串的时间复杂度为n，所以，总的时间复杂度为 O(m*n - size*n*n)，
					因为是减，所以直接忽略后面的，复杂度为 o(m*n)

			空间复杂度：两个 HashMap，假设 words 里有 n 个单词，就是 O（n）。

*/

func findSubstring(s string, words []string) []int {
	res := []int{}
	if s == "" || len(words) == 0 {
		return res
	}
	// n 个单词，每个单词的长度为 size
	n, size := len(words), len(words[0])
	if len(s) < n*size {
		return res
	}

	// 滑动窗口固定大小
	length := n * size
	mapWords := make(map[string]int)
	for _, word := range words {
		mapWords[word]++
	}

	//取以下标 i 为开头，长度为 length 的子串进行判断，最后一个子串的开始下标为 len(s) - length
	for i := 0; i <= len(s)-length; i++ {
		//在判断的时候，我们再申请一个 map 进行数量判断，不然如果直接修改 mapWords 中的值，每次取新的子串，都要重新初始化 mapWords
		mapHelp := make(map[string]int)
		have := 0 //有多少个单词及数量满足了
		for index := i; index < i+length; index += size {
			//每次从子串中取出一个单词，判断是否在 words 中
			word := s[index : index+size]

			if _, ok := mapWords[word]; !ok {
				//没有这个单词，直接跳过这个子串
				break
			}

			mapHelp[word]++
			if mapHelp[word] == mapWords[word] {
				have++
			}
		}

		//符合
		if have == len(mapWords) {
			res = append(res, i)
		}
	}
	return res
}
