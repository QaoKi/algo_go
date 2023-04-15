package main

/*
	leetcode 54
	题目：给定一个整型矩阵matrix，请按照顺时针的方式打印它
	例如：
			1	2	3
			4	5	6
			7	8	9
			10	11	12
	打印结果为： 1	2	3	6	9	12	11	10	7	4	5	8
	【要求】 额外空间复杂度为O(1)
*/

/*
	思路：假设1号位置的下标为(a,b)，12号位置的下标为(c,d)，
	那么就是下面的情况：
				b		d

		a		1	2	3
				4	5	6
				7	8	9
		c		10	11	12

		对于一个 m*n的矩阵，矩阵中有数字总共 m*n个，设 num = m*n，每遍历一个数，让 num--，用 num > 1 作为循环的条件。
		打印按照从b一直加到d，再从a加到从c，再从d减到b，再从c减到a，
		打印按照左闭右闭的原则，将每一行或者每一列的最后一个数字也打印出来。
		注意，这里不能按照左闭右开，将每一行或者每一列的最后一个数字空出来，等下次再处理，
			比如，遍历第一行时，输出 1, 2，将3空出来，等遍历最后一列时，从3开始，这时再把3输出，
		这样左闭右开的方式，当矩阵只剩最后一行或者最后一列时，需要特殊处理，不然遍历不到。增加了代码的边界处理

*/

func spiralOrder(matrix [][]int) []int {
	res := []int{}
	if len(matrix) == 0 {
		return res
	}

	num := len(matrix) * len(matrix[0])

	top, down := 0, len(matrix)-1
	left, right := 0, len(matrix[0])-1

	for num > 0 {
		//从左往右
		for i := left; i <= right && num > 0; i++ {
			res = append(res, matrix[top][i])
			num--
		}
		//上边一行结束，top加1
		top++

		//从上往下
		for i := top; i <= down && num > 0; i++ {
			res = append(res, matrix[i][right])
			num--
		}
		//右边一列结束，right减1
		right--

		//从右往左
		for i := right; i >= left && num > 0; i-- {
			res = append(res, matrix[down][i])
			num--
		}
		//下边一行结束，down减1
		down--

		//从下往上
		for i := down; i >= top && num > 0; i-- {
			res = append(res, matrix[i][left])
			num--
		}
		//左边一行结束，left加1
		left++
	}

	return res
}
