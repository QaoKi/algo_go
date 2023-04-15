package main

/*
	题目： leetcode 59
		给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。

		示例1：
			输入：n = 3
			输出：[[1,2,3],[8,9,4],[7,6,5]]
*/

/*
	同 demo1 思路一样。
	最终会形成一个边长为 n 的正方形，一共有 n*n 个数，用 num 记录，
		本题让num从1加到n*n，因为需要放到数组中，如果让 num--的话，还需要再使用一个变量
	按照从左到右，再从上到下，再从右到左，再从下到上的方式遍历
*/

func generateMatrix(n int) [][]int {
	res := make([][]int, n)
	if n <= 0 {
		return res
	}

	for i := 0; i < n; i++ {
		res[i] = make([]int, n)
	}

	top, down := 0, n-1
	left, right := 0, n-1
	num := 1
	for num <= n*n {
		for i := left; i <= right; i++ {
			res[top][i] = num
			num++
		}
		top++

		for i := top; i <= down; i++ {
			res[i][right] = num
			num++
		}
		right--

		for i := right; i >= left; i-- {
			res[down][i] = num
			num++
		}
		down--

		for i := down; i >= top; i-- {
			res[i][left] = num
			num++
		}
		left++
	}

	return res
}
