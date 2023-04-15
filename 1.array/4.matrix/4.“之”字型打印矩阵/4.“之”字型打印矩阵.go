package main

/*
	题目：给定一个整型矩阵matrix

	例如：
			1	2	3	4
			5	6	7	8
			9	10	11	12

	按照“之”字形的方式打印这个矩阵,结果为：1，2，5，9，6，3，4，7，10，11，8，12
	也就是每次都斜着打印
	【要求】 额外空间复杂度为O(1)
*/

/*
	思路：这道题目，数值的下标移动没有规律可找
		  采用两个辅助指针，两个点a和b，初始都在第一行和第一列，
				a
			b	1	2	3	4
				5	6	7	8
				9	10	11	12
		  a向右走，每次走一步，当向右走到头时，向下走，一直到走到最右下角
		  b向下走，每次走一步，当向下走到头时，向右走，一直到走到最右下角
			      a
			  1	  2	  3	  4
			b 5	  6	  7	  8
			  9	  10  11  12

			a和b之间就构成了一条斜线，比如，从a打印到b，让a的列号--，行号++，一直打印到b，
			从b打印到a，让b的列号++，行号--,一直打印到a

*/
func printMatrix(matrix [][]int) []int {
	//行、列
	row, col := len(matrix), len(matrix[0])
	if row == 0 || col == 0 {
		return []int{}
	}

	res := make([]int, row*col)
	ax, ay, bx, by := 0, 0, 0, 0
	//打印方向，先从b到a
	aTob := false

	//只有当a走到最后的时候，a的行号 ax 才会等于 row-1
	//只有当b走到最后的时候，b的列号 by 才会等于 col-1
	for ax <= row-1 && by <= col-1 {
		//打印当前a和b组成的斜线上的数
		tmp := printLevel(matrix, ax, ay, bx, by, aTob)
		res = append(res, tmp...)

		//让a和b每次移动一个位置
		//如果 a 的列号 ay 等于 col-1，说明a向右走到了头，让a向下移动，行号加1,否则行号不变，列号加1
		if ay == col-1 {
			ax++
		} else {
			ay++
		}

		//如果 b 的行号 bx 等于 row-1，说明b向下走到了头，让b向右移动，列号加1,否则列号不变，行号加1
		if bx == row-1 {
			by++
		} else {
			bx++
		}

		aTob = !aTob
	}

	return res
}

func printLevel(matrix [][]int, ax, ay, bx, by int, aTob bool) []int {
	res := []int{}
	if aTob {
		for ax <= bx {
			res = append(res, matrix[ax][ay])
			ax++
			ay--
		}
	} else {
		for ay >= by {
			res = append(res, matrix[bx][by])
			bx--
			by++
		}
	}
	return res
}
