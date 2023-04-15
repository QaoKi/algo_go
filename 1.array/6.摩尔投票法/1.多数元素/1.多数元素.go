package main

import "sort"

/*
	leetcode 169
	题目：
		给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
		你可以假设数组是非空的，并且给定的数组总是存在多数元素。

		示例 1：
			输入：[3,2,3]
			输出：3

		示例 2：
			输入：[2,2,1,1,1,2,2]
			输出：2
*/

/*
	这题有多种方法，选一些比较经典的方法。

	方法1，借助哈希表记录数字出现的次数

		时间复杂度：O(n)
		空间复杂度：O(n)
*/

func majorityElement(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	mapCount := make(map[int]int)
	for _, n := range nums {
		mapCount[n]++
		if mapCount[n] > len(nums)/2 {
			return n
		}
	}

	return 0
}

/*
	方法2，排序
		如果将数组 nums 中的所有元素按照单调递增或单调递减的顺序排序，
			那么下标为 n/2 的元素（n是nums数组的长度，下标从0开始）一定是众数。

		时间复杂度：O(nlogn)
		空间复杂度：O(1)
*/

func majorityElement1(nums []int) int {
	if len(nums) == 0 {
		return 0
	}

	sort.Ints(nums)
	return nums[len(nums)/2]
}

/*
	方法3，摩尔投票法
		摩尔投票法解决的问题是如何在任意多的候选人中，选出票数超过一半的那个人。注意，是超出一半票数的那个人。
		https://leetcode.cn/problems/majority-element-ii/solution/liang-fu-dong-hua-yan-shi-mo-er-tou-piao-fa-zui-zh/

		原理：
			摩尔投票法分为 抵消阶段 和 计数阶段
			1，在抵消阶段，我们每次从序列里选择两个不相同的数字删除掉（或称为「抵消」），
				最后剩下一个数字，就是出现次数大于总数一半的那个元素。
			2，计数阶段，虽然最后会剩下一个数字，但是没法保证这个数字的个数超过了一半，
				所以还需要遍历一遍这个数字的个数，验证一下个数是否超过一半，
				不过本题说了一定含有多数元素，就不用验证了
		步骤
			1，我们用两个变量 major 和 count 来记录候选人及他的票数，初始化时都为0
			2，遍历数组
				如果 count == 0 ，将当前数字选为候选人，并让 count = 1。
				如果 count != 0，再比较候选人 major 和 nums[i] 是否相等
					如果 major != nums[i]，选票抵消，让 count--
					如果 major == nums[i]，选票增加，让 count++
			3，最后返回 major

		时间复杂度：O(n)
		空间复杂度：O(1)
*/
func majorityElement2(nums []int) int {
	if len(nums) == 0 {
		return 0
	}

	major, count := 0, 0
	for _, i := range nums {
		if count == 0 {
			major = i
			count++
		} else {
			if major == i {
				count++
			} else {
				count--
			}
		}
	}
	return major
}
