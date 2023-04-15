package main

/*
	题目： leetcode 287
		给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
		假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

		说明：
			你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。
			nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次

		示例1：
			输入：nums = [1,3,4,2,2]
			输出：2
*/

/*
	这道题如果用哈希表或者能排序，那么很简单，但是加了不能修改 nums 和常量级 O(1) 的额外空间限制以后，
	思路就很难想了，
	方法1，暴力法，最直接的，直接去搜。
		时间复杂度：O(n^2)
		空间复杂度：O(1)
	方法2，二分查找
		预备知识：抽屉原理
			桌上有十个苹果，要把这十个苹果放到九个抽屉里，无论怎样放，我们会发现至少会有一个抽屉里面放不少于两个苹果。

		题目中说，给定的数组长度是 n + 1，元素的值是 1 到 n 之间，只有一个数字包含两个或多个，
		数值的范围在 [1, n] 之间，我们取中间值 mid，然后统计小于等于 mid 的元素有多少个，假设为 count 个，
			如果 count 大于 mid，说明重复的值小于或者等于 mid，在 [left, mid] 中继续查找
			否则，说明重复的元素比 mid 大，[mid+1, right] 中继续查找

		比如，nums = {1,5,7,4,2,3,6,6}
			设左右范围为 [1...7]，mid = 4，小于等于 4 的个数等于于 4 个，说明重复元素出现在 [5..7] 区间里

		时间复杂度：O(n*logn)
		空间复杂度：O(1)
*/

func findDuplicate1(nums []int) int {
	length := len(nums)
	//数组中的数范围是 1 到 len - 1
	left, right := 1, length-1

	//要注意这里条件不是 left <= right，因为我们并没有让 right = mid - 1，而是 right = mid，
	//所以如果让 left <= right，可能会死循环.

	for left < right {
		mid := (left + right) >> 1
		//统计小于等于 mid 的元素有多少个
		count := 0
		for _, n := range nums {
			if n <= mid {
				count++
			}
		}

		//根据抽屉原理，小于等于 4 的个数如果大于 4 个，此时重复元素一定出现在 [1..4] 区间里
		if count > mid {
			// 重复元素位于区间 [left..mid]
			right = mid
		} else {
			// 重复元素位于区间 [mid+1..right]
			left = mid + 1
		}
	}

	//最终 left 和 right 会相等，返回哪个都行
	return left
}

/*
	方法2，将数组抽象成有环的链表，用快慢指针来找入环口
		https://leetcode-cn.com/problems/find-the-duplicate-number/solution/kuai-man-zhi-zhen-de-jie-shi-cong-damien_undoxie-d/

		如何将数组抽象成有环的链表：
			将数组的下标作为指针，将元素的值也作为指针，以下标 0 为首节点
			0 指向 nums[0]，也就是说 nums[0] 等同于 0->next
			而 nums[0] 也是一个指针，指向 nums[nums[0]]
			所以我们可以将这个链表遍历出来
				node = 0
				while (1) {
					node = nums[node];	//等同于 node = node->next
				}

			比如 nums = [4,3,1,2,2]
				下标	0	1	2	3	4
				值		4	3	1	2	2
			0 为首节点，nums[0] 的值是 4，那么 0 ——> 4
			nums[4] 的值是 2，那么 4 ——> 2
			nums[2] 的值是 1，那么 2 ——> 1
			nums[1] 的值是 3，那么 1 ——> 3
			nums[3] 的值是 2，那么 3 ——> 2

			将上面的关系画出来就是
				0 ——> 4 ——> 2 ——> 1 ——> 3 ——> 2
			3 又指向了 2，形成了环，2就是入环口，也就是我们要找的重复数字。

		这样就将问题转化为求 有环链表的入环口
		注意，该题值域的范围是 1 到 n，数组的长度是 n+1，所以 nums[n] 不会越界，可以用这种方法
			node = nums[node]，相当于是 node = node->next，
			node = nums[nums[node]]，相当于 node = node->next->next

	时间复杂度：O(n)
	空间复杂度：O(1)
*/

func findDuplicate(nums []int) int {
	fast, slow := 0, 0

	for {
		//先走一次，不然上来就是 slow 等于 fast 了
		slow = nums[slow]
		fast = nums[nums[fast]]

		//这里要用 slow 和 fast 判断，不能用 nums[slow] 和 nums[fast] 判断
		//因为 slow 和 fast 才是当前指针，而 nums[slow] 和 nums[fast] 分别代表 slow->next 和 fast->next
		if slow == fast {
			break
		}
	}

	fast = 0
	for slow != fast {
		slow = nums[slow]
		fast = nums[fast]
	}

	return slow
}
