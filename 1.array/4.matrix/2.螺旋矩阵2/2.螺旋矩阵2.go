package main

/*
	��Ŀ�� leetcode 59
		����һ�������� n ������һ������ 1 �� n2 ����Ԫ�أ���Ԫ�ذ�˳ʱ��˳���������е� n x n �����ξ��� matrix ��

		ʾ��1��
			���룺n = 3
			�����[[1,2,3],[8,9,4],[7,6,5]]
*/

/*
	ͬ demo1 ˼·һ����
	���ջ��γ�һ���߳�Ϊ n �������Σ�һ���� n*n �������� num ��¼��
		������num��1�ӵ�n*n����Ϊ��Ҫ�ŵ������У������ num--�Ļ�������Ҫ��ʹ��һ������
	���մ����ң��ٴ��ϵ��£��ٴ��ҵ����ٴ��µ��ϵķ�ʽ����
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
