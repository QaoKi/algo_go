package main

/*
	leetcode 54
	��Ŀ������һ�����;���matrix���밴��˳ʱ��ķ�ʽ��ӡ��
	���磺
			1	2	3
			4	5	6
			7	8	9
			10	11	12
	��ӡ���Ϊ�� 1	2	3	6	9	12	11	10	7	4	5	8
	��Ҫ�� ����ռ临�Ӷ�ΪO(1)
*/

/*
	˼·������1��λ�õ��±�Ϊ(a,b)��12��λ�õ��±�Ϊ(c,d)��
	��ô��������������
				b		d

		a		1	2	3
				4	5	6
				7	8	9
		c		10	11	12

		����һ�� m*n�ľ��󣬾������������ܹ� m*n������ num = m*n��ÿ����һ�������� num--���� num > 1 ��Ϊѭ����������
		��ӡ���մ�bһֱ�ӵ�d���ٴ�a�ӵ���c���ٴ�d����b���ٴ�c����a��
		��ӡ��������ұյ�ԭ�򣬽�ÿһ�л���ÿһ�е����һ������Ҳ��ӡ������
		ע�⣬���ﲻ�ܰ�������ҿ�����ÿһ�л���ÿһ�е����һ�����ֿճ��������´��ٴ���
			���磬������һ��ʱ����� 1, 2����3�ճ������ȱ������һ��ʱ����3��ʼ����ʱ�ٰ�3�����
		��������ҿ��ķ�ʽ��������ֻʣ���һ�л������һ��ʱ����Ҫ���⴦����Ȼ���������������˴���ı߽紦��

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
		//��������
		for i := left; i <= right && num > 0; i++ {
			res = append(res, matrix[top][i])
			num--
		}
		//�ϱ�һ�н�����top��1
		top++

		//��������
		for i := top; i <= down && num > 0; i++ {
			res = append(res, matrix[i][right])
			num--
		}
		//�ұ�һ�н�����right��1
		right--

		//��������
		for i := right; i >= left && num > 0; i-- {
			res = append(res, matrix[down][i])
			num--
		}
		//�±�һ�н�����down��1
		down--

		//��������
		for i := down; i >= top && num > 0; i-- {
			res = append(res, matrix[i][left])
			num--
		}
		//���һ�н�����left��1
		left++
	}

	return res
}
