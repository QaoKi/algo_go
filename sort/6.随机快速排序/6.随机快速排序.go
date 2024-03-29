package main

import (
	"math/rand"
	"time"
)

/*
	可以用 leetcode 912 测试代码
	经典快速排序的问题：
		当数组为  1,2,3,4,5,6  有序的数据状况时， 每次选定最后一个数作为num，那么大于num的区域就没有了
		每次一趟只能搞定一个数，时间复杂度变为O(n^2)
		随机快排：
		每次随机的在数组中选定一个值放到数组的最后作为num，这样涉及到概率，长期期望的时间复杂度：O(n*logn)，

	随机快排是工程中最常用的，因为时间复杂度的常数项比归并排序少
*/

func sort(nums []int, L, R int) {
	//终止条件
	if L >= R {
		return
	}
	//数据的数据状况是不可控的，但是可以采用方法，打乱固定的数据状况
	//1.随机，从数组中随机取值，和数据状况无关
	//2.哈希
	//在这里随机从数组中取一个值放到数组的最后
	index := rand.Intn(R-L+1) + L
	num := nums[index]

	l := L - 1 //指向小于num值区域的最后一个值
	r := R + 1 //指向大于num值区域的第一个值
	curr := L  //当前值的下标，遍历的指针

	//遍历所有的数，小于num的放到小于区域，大于的放到大于区域，等于放到中间
	for curr < r {
		if nums[curr] == num {
			curr++
		} else if nums[curr] < num {
			l++
			nums[l], nums[curr] = nums[curr], nums[l]
			curr++
		} else {
			r--
			nums[r], nums[curr] = nums[curr], nums[r]
			//curr先不加1，再判断换过来的这个数的值
		}
	}

	//到这时，数组从L-l的数据是小于num的数，pr-r是大于num的值
	//再继续拆分，直到剩一个数
	sort(nums, L, l)
	sort(nums, r, R)
}

func sortArray(nums []int) {
	rand.Seed(time.Now().Unix())
	sort(nums, 0, len(nums)-1)
}
