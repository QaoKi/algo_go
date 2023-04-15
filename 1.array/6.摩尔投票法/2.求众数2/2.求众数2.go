package main

/*
	leetcode 229
	题目：
		给定一个大小为 n 的整数数组，找出其中所有出现超过 ⌊ n/3 ⌋ 次的元素。
		进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1)的算法解决此问题。

		示例 1：
			输入：[3,2,3]
			输出：[3]

		示例 2：
			输入：nums = [1]
			输出：[1]

		示例 3：
			输入：[1,1,1,3,3,2,2,2]
			输出：[1,2]
*/

/*
	方法1，哈希表计数，先统计每个元素出现的次数，再遍历哈希表，将次数大于 1/3 的元素返回。
*/
func majorityElement(nums []int) []int {
	res := []int{}
	if len(nums) == 0 {
		return res
	}

	mapCount := map[int]int{}

	/*
		这里不能像 多数元素 那题那样一边遍历一遍判断，因为可能会将元素重复加入
		比如 nums = [2,2]，
		如果代码是这样
			for _, n := range nums{
				mapCount[n]++
				if mapCount[n] > len(nums)/3 {
					res = append(res, k)
				}
			}
		遍历第一个 2 的时候，符合，res变成[2]，遍历第二个 2 同样符合，res变成[2,2]
		但正确答案应该是 [2]
	*/
	for _, n := range nums {
		mapCount[n]++
	}

	for k, v := range mapCount {
		if v > len(nums)/3 {
			res = append(res, k)
		}
	}
	return res
}

/*
	方法2，摩尔投票法
		这道题目是 多数元素的升级版，多数元素求的是超过一半的元素，而该题求的是超过 1/3 的元素。
		需要注意的是，
			至少超过 1/2 票数，那么最多只能选出一个代表。也就是有0个或1个代表
			至少超过 1/3 票数，那么最多能选出两个代表。也就是有0个或1个或2个代表
			最少超过 1/m 票数，那么最多能选出 m-1 个代表。

		1，抵消阶段
			因为票数超过 1/3 的人，最多会有两个，所以，先选出两个候选人 A 和 B，
			遍历数组，分三种情况：
				1，如果投 A（当前元素等于 A ），则 A 的票数++;
				2，如果投 B（当前元素等于 B ），B 的票数++；
				3，如果 A,B 都不投（即当前与 A，B 都不相等）,那么检查此时 A 或 B 的票数是否减为 0：
					如果为0,则当前元素成为新的候选人；
					如果 A,B 两个人的票数都不为 0，那么 A,B 两个候选人的票数均减一；
		2，计数阶段
			遍历结束后选出了两个候选人，但是并不能保证这两个候选人满足大于 n/3
			还需要再遍历一遍数组，找出两个候选人的具体票数来验证

		时间复杂度：O(n)
		空间复杂度：O(1)
*/
func majorityElement1(nums []int) []int {
	res := []int{}
	if len(nums) == 0 {
		return res
	}

	// 初始化两个候选人，以及他们的计数票
	A, B := nums[0], nums[0]
	countA, countB := 0, 0

	for _, n := range nums {
		//这四个 if 条件，前两个是一组，后两个是一组
		//顺序不能弄反了，得先判断 n 和A、B的值是否相等，再去判断countA, countB的值是否为0
		//具体原因就不打了
		if n == A {
			countA++
			continue
		}

		if n == B {
			countB++
			continue
		}

		if countA == 0 {
			A = n
			countA = 1
			continue
		}

		if countB == 0 {
			B = n
			countB = 1
			continue
		}

		//若此时两个候选人的票数都不为0，且当前元素不投AB，那么A,B对应的票数都要--;
		countA--
		countB--
	}

	//上一轮遍历找出了两个候选人，但是这两个候选人是否均满足票数大于N/3仍然没法确定，需要重新遍历，确定票数
	countA = 0
	countB = 0
	for _, n := range nums {
		if n == A {
			countA++
		} else if n == B {
			countB++
		}
	}

	if countA > len(nums)/3 {
		res = append(res, A)
	}

	if countB > len(nums)/3 {
		res = append(res, B)
	}
	return res
}
