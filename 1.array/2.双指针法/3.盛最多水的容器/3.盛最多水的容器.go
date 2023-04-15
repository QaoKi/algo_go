package main

/*
	题目： leetcode 11
		给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
		在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。
		找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

		说明：你不能倾斜容器。

		示例1：
			有图，看原题吧
*/

/*
	理解题意，数组中的数，可以在坐标轴上表示，下标表示 x 轴，值表示 y 轴，而两个数则可以组成一个水槽，
		两个数的下标差为宽度，高度取两个值较小的那个，求的是最大的水槽面积。
		比如 nums = [1,8,6,2,5,4,8,3,7]
		6 和 8 组成的水槽，宽度为 4（下标差），高度为 min(6,8)，所以面积 = min(6,8) * 4 = 24
	现在要求最大的面积

	实现：
		1，用两个指针 i 和 j 分别指向 nums 的两端，
			设 nums 的长度为 n，那么初始化时 i = 0, j = n-1。
		2，用两个指针所指向的数字组成水槽，求出水槽的面积 S = min(nums[i], nums[j]) * (j-i)
		3，如果 nums[i] > nums[j]，也就是说左边的高度比右边高，那么 j--，i不动
			如果 nums[i] < nums[j]，也就是说右边的高度比左边高，那么 i++，j不动
			如果 nums[i] == nums[j]，此时改变 i 或者 j 都可以。
		4，每次改变了 i 或者 j 后求出新水槽的面积，当 i 和 j 重合，结束，返回面积最大的结果。

	思路：
		水槽的面积 S = min(nums[i], nums[j]) * (j-i)
		可以看到，水槽的高度，由 nums[i] 和 nums[j] 中较小的值决定
		每一个状态下，无论长板或短板收窄 1 格，都会导致水槽 底边宽度减 1
			若向内移动短板，水槽的短板 min(nums[i], nums[j])，可能变大，因此水槽面积 S(i, j) 可能增大
			若向内移动长板，水槽的短板 min(nums[i], nums[j])，不变或变小，下个水槽的面积一定小于当前水槽面积。
		因此，每次向内收窄短板可以获取面积最大值。

	举例：当 nums = [1, 8, 6, 2, 5, 4, 8, 3, 7]
		初始化时，i 指向 1，j 指向 7，S = min(1,7) * 8 = 8
		nums[i] 较小，让 i++，i 指向 8，j 指向 7，S = min(8,7) * 7 = 49
		nums[j] 较小，让 j--，i 指向 8，j 指向 3，S = min(8,3) * 6 = 18
		nums[j] 较小，让 j--，i 指向 8，j 指向 8，S = min(8,8) * 5 = 40
		nums[i] 等于 nums[j]，让 i++，i 指向 6，j 指向 8，S = min(6,8) * 4 = 24
		.....

	总结：
		之前有一个疑惑的点，就是当 nums[i] 等于 nums[j] 时，无论移动哪个，都能得到正确结果吗，
		之所以有这个疑惑，是因为当时还没有理解透 水槽的高度，由 nums[i] 和 nums[j] 中较小的值决定。
		比如 nums = [1, 8, 6, 2, 5, 20, 8, 3, 7]
			当指针 i 和 j 都指向了 8 的时候，此时矩阵的面积 S = min(8,8) * 5 = 40
			当我们选择让 i++，看似好像使得左边的  8 和右边的 20 错过了，但是要注意
				高度由 nums[i] 和 nums[j] 中较小的值决定，即使右边的值变的再大，水槽的高度也是由
				较小值决定的。所以当 nums[i] 等于 nums[j] 时，移动哪个指针都可以。
			计算一下：
				1，如果选择让 i++，那么下一组就是 i = 6,j = 8，S = min(6,8) * 4 = 24
				3，如果选择让 j--，那么下一组就是 i = 8,j = 20，S = min(8,20) * 4 = 32
			可以看到，即使选择了第二种，面积也不会比 40 大。
	时间复杂度：O(N)
	空间复杂度：O(1)
*/

func min(a, b int) int {
	if a > b {
		return b
	}
	return a
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func maxArea(height []int) int {
	lenght := len(height)
	if lenght == 0 || lenght == 1 {
		return 0
	}

	res, left, right := 0, 0, lenght-1
	for left < right {
		res = max(res, min(height[left], height[right])*(right-left))
		if height[left] > height[right] {
			right--
		} else {
			left++
		}
	}

	return res
}
