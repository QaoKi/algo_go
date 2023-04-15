package main

/*
	leetcode 74
	【题目】
			编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
				每行中的整数从左到右按升序排列。
				每行的第一个整数大于前一行的最后一个整数。
			例如：

				1	3	5	7
				10	11	16	20
				23	30	34	60
			如果 target 为 7，返回true；如果 target 为 6，返回false。
*/

/*
	这题也能用 1.array/4.matrix/5.搜索二维矩阵2 的方法，不过有一个二分法，在这里写下来。
	注意到有一个条件是 每行的第一个整数大于前一行的最后一个整数。
		那么如果把当前行的所有数字，接到上一行的后面，仍然是升序的。
		比如
			1	3	5	7
			10	11	16	20
		把第二行接到第一行的后面，1	 3	5	7	10	11	16	20 仍然是升序的。

	方法1，两次二分
	第一次二分，先找到合适的行
		找到最后一个 target >= matrix[row][0]，那么第 row 行就是符合的行。
		这其实是二分变形题目中的第四种：查找最后一个小于等于给定值的元素
	第二次二分，
		在第 i 行中二分查找是否存在 target

	时间复杂度：O(logm + logn)
	空间复杂度：O(1)
*/

func searchMatrix(matrix [][]int, target int) bool {
	if len(matrix) == 0 {
		return false
	}

	// 总共有 len(matrix) 行
	left, right := 0, len(matrix)-1

	// 二分找到最后一个 matrix[i][0] <= target
	row := -1
	for left <= right {
		mid := left + (right-left)/2
		if matrix[mid][0] == target {
			return true
		} else if matrix[mid][0] > target {
			right = mid - 1
		} else {
			//mid是最后一行，或者下一行的第一个数大于 target，那么 mid 行就是 target 所在的行
			if mid == len(matrix)-1 || matrix[mid+1][0] > target {
				row = mid
				break
			} else {
				left = mid + 1
			}
		}
	}

	// 没找到合适的行
	if row == -1 {
		return false
	}

	// 在 row 行中二分查找是否存在 target
	left, right = 0, len(matrix[row])-1
	for left <= right {
		mid := left + (right-left)/2
		if matrix[row][mid] == target {
			return true
		} else if matrix[row][mid] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	return false
}

/*
	方法2，一次二分
	我们上面说过了 如果把当前行的所有数字，接到上一行的后面，仍然是升序的。
	那么就可以把二维数组抽象成一个一维数组，在一维数组中二分查找 target

	时间复杂度：O(log(mn))
	空间复杂度：O(1)
*/

func searchMatrix1(matrix [][]int, target int) bool {
	if len(matrix) == 0 {
		return false
	}

	row, col := len(matrix), len(matrix[0])
	left, right := 0, row*col-1
	for left <= right {
		mid := left + (right-left)/2
		// 找到正确的坐标
		// 每一行有 col 个数，那么 mid/col 就能得出位于哪一行
		// 对总列数 col 求余，能得出所在列号
		i := mid / col
		j := mid % col
		if matrix[i][j] == target {
			return true
		} else if matrix[i][j] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	return false
}
