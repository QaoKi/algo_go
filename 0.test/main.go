package main

import (
	"fmt"
)

func Scanf() {
	n := 0
	fmt.Scan(&n)
	fmt.Println(n)
	date := []int{}
	for i := 0; i < n; i++ {
		m := 0
		fmt.Scan(&m)
		date = append(date, m)
	}
	fmt.Println(date)
}

func sortArray(nums []int) {
	// 从第二个元素开始，一个个的从后往前插入
	for i := 1; i < len(nums); i++ {
		for j := i - 1; j >= 0; j-- {
			//从后往前对比数据，如果发现前面那个数据比后面那个数据大，直接交换
			//注意，这里不能使用 nums[j]和nums[i]进行比较，因为如果发生交换，交换之后nums[i]的值不再是要排序的值
			if nums[j] > nums[j+1] {
				nums[j], nums[j+1] = nums[j+1], nums[j]
			}
		}
	}
}

func main() {
	array := []int{8, 4, 6, 7, 2, 1, 3, 0, 9, 5}
	fmt.Println(array)

	sortArray(array)

	fmt.Println(array)
}
