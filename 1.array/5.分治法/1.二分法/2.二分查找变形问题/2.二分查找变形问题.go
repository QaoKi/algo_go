package main

/*
	二分查找的条件：
		1，必须是有序的
		2，能够通过索引访问，所以一般都是数组，所以需要连续的内存。如果是链表这种，复杂度会增高
		3，数据量太少，不如直接遍历找。而数据量太大，因为数据要用连续的内存存储，对空间消耗太大

	时间复杂度：O(logn)
*/
/*
	变形问题1：查找第一个值等于给定值的元素
	变形问题2：查找最后一个值等于给定值的元素
	变形问题3：查找第一个大于等于给定值的元素
	变形问题4：查找最后一个小于等于给定值的元素
*/

//变形问题1：查找第一个值等于给定值的元素，返回下标
func find1(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			/*
				当 nums[mid] == num
				如果 mid是数组的第一个元素，那么肯定是第一个值等于给定值的元素，
				如果 mid的前面一个数不是num，那么 mid 也是第一个值等于给定值的元素，
				否则的话继续缩小范围查找
			*/
			if mid == 0 || nums[mid-1] != target {
				return mid
			} else {
				right = mid - 1
			}
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}
	return -1
}

//查找第一个值等于给定值的元素，返回下标。find1的简便写法
func find1Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2

		//找到了相等的值，也不停，不去判断是否是第一个相等的元素，继续缩小范围朝左找
		if nums[mid] >= target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	/*
		这种方法下，比如我们要找的元素下标为 x ，当 mid 等于 x 时，也不停下来，让right = x - 1，
		而找到 x 以后，因为再也不会执行条件 if (array[mid] >= num)，所以right在之后的循环中就不会变了，
		也就是说，最终 right 的下一个元素就是我们要找的值，
		当 for 循环结束，left就等于 right + 1，也就是我们要找的 x

		这种方法运行时间要比find1长，因为每次找到相等的值，不去判断是否是 x，而是一直遍历到 left > right
	*/
	if left < len(nums) && nums[left] == target {
		return left
	}

	return -1
}

//变形问题2：查找最后一个值等于给定值的元素，返回下标
func find2(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			/*
				当 nums[mid] == num
				如果 mid是数组的第一个元素，那么肯定是第一个值等于给定值的元素，
				如果 mid的前面一个数不是num，那么 mid 也是第一个值等于给定值的元素，
				否则的话继续缩小范围查找
			*/
			if mid == len(nums)-1 || nums[mid+1] != target {
				return mid
			} else {
				left = mid + 1
			}
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	return -1
}

//变形问题2：查找最后一个值等于给定值的元素，返回下标。find2的简便写法
func find2Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] <= target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	//和find1Easy同理，for 循环结束以后，right 就是要找的下标
	if right >= 0 && nums[right] == target {
		return right
	}
	return -1
}

//变形问题3：查找第一个大于等于给定值的元素
func find3(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] >= target {
			if mid == 0 || nums[mid-1] < target {
				return mid
			} else {
				right = mid - 1
			}
		} else {
			left = mid + 1
		}
	}

	return -1
}

//变形问题3：查找第一个大于等于给定值的元素。find3的简便写法
func find3Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] >= target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	//和find1Easy同理
	if left < len(nums) && nums[left] >= target {
		return left
	}
	return -1
}

//变形问题4：查找最后一个小于等于给定值的元素
func find4(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] <= target {
			if mid == len(nums)-1 || nums[mid+1] > target {
				return mid
			} else {
				left = mid + 1
			}
		} else {
			right = mid - 1
		}
	}

	return -1
}

//变形问题4：查找最后一个小于等于给定值的元素。find4的简便写法
func find4Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] <= target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	//和find1Easy同理
	if right > 0 && nums[right] <= target {
		return right
	}
	return -1
}
