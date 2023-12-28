package main

/*
	可以用 leetcode 912 测试代码
	归并排序思想：
	分治的思想
*/

/*
	1.在合并的过程中，如果 arr[L…mid]和 arr[mid+1…R]之间有值相同的元素，先把 arr[L…mid]中的元素放入 help 数组。
		这样就保证了值相同的元素，在合并前后的先后顺序不变。所以，归并排序是一个稳定的排序算法。
	2.时间复杂度：不管是最好情况、最坏情况，还是平均情况，时间复杂度都是 O(nlogn)
	3.每次合并操作都需要申请额外的内存空间，但在合并完成之后，临时开辟的内存空间就被释放掉了。
		在任意时刻，CPU 只会有一个函数在执行，也就只会有一个临时的内存空间在使用。
		临时内存空间最大也不会超过 n 个数据的大小，所以空间复杂度是 O(n)。
*/

func merge(nums []int, L, mid, R int) {
	//L和R是数组arr的第一个值下标和最后一个值下标
	help := []int{}
	l, r := L, mid+1 //指针指向左边数组的第一个元素 和 右边数组的第一个元素
	for l <= mid && r <= R {
		if nums[l] <= nums[r] {
			help = append(help, nums[l])
			l++
		} else {
			help = append(help, nums[r])
			r++
		}
	}

	for l <= mid {
		help = append(help, nums[l])
		l++
	}

	for r <= R {
		help = append(help, nums[r])
		r++
	}

	//拷贝回原来的数组，这里的下标处理要注意
	for i := 0; i < len(help); i++ {
		nums[L+i] = help[i]
	}

}

//传入数组的第一个值的下标和最后一个值的下标
func sort(nums []int, L, R int) {
	//终止条件
	if L >= R {
		return
	}

	mid := L + (R-L)/2
	//将数组分为两部分，一部分为 L到mid，一部分为 mid+1到R
	//再接着拆分，直到拆分到每一部分只剩一个数，即当L=R的时候停止
	sort(nums, L, mid)
	sort(nums, mid+1, R)
	//把每一个子部分，两两按大小合并,一直到最后合并成总的
	merge(nums, L, mid, R)
}

func sortArray(nums []int) {
	sort(nums, 0, len(nums)-1)
}
