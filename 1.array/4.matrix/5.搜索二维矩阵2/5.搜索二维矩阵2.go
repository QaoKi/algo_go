package main

/*
	leetcode 240 剑指offer 04
	【题目】
			编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
				每行的元素从左到右升序排列。
				每列的元素从上到下升序排列。
			例如：

				0	1	2	5
				2	3	4	7
				4	4	4	8
				5	7	7	9
			如果 target 为7，返回true；如果 target 为6，返回false。
*/

/*
	两种思路，一个是从右上角开始找，一种是从左下角开始找
	从右上角开始找：
		右上角第一个数 curr 和 target 对比，
			如果 curr 比 target 小，说明 curr 所在行的前面的数不会有 target，
				因为 curr 所在行中，curr 是最大的，此时 curr 向下移动一位，
			如果 curr 比 target 大，说明 curr 所在列的下面不会有 target，
				因为 curr 所在行，curr 是最小的，此时 curr 向左移动一位，
			一直到如果行或列都找完还没有，就没有
	从左下角开始找同理

	如果从 matrix[0][0] 开始找，如果 matrix[0][0] < target，此时有两条路，向下或者向右，
		不如从右上或者左下开始找方便。
	这种方法，其实是将矩阵逆时针旋转 45°，形成一个类似于二叉搜索树的结构
		比如，
			5	2	3
			8	1	4
			6	9	7
		逆时针旋转 45°后，变成
				3
			2		4
		5		1		7
			8		9
				6

	时间复杂度：O(m+n)
	空间复杂度：O(1)
*/

func searchMatrix(matrix [][]int, target int) bool {
	if len(matrix) == 0 {
		return false
	}

	//行、列
	row, col := len(matrix), len(matrix[0])
	//初始位置，从右上角开始
	x, y := 0, col-1
	for x < row && y >= 0 {
		if matrix[x][y] == target {
			return true
		} else if matrix[x][y] > target {
			// 大了，matrix[x][y] 是该列中最小的值，越朝下数越大，所以要向左移，列减1
			y--
		} else {
			// 小了，matrix[x][y] 是该行中最大的值，越朝左数越小，所以要向下移，行加1
			x++
		}
	}
	return false
}
