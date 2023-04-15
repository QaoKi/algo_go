package main

/*
	leetcode 74
	����Ŀ��
			��дһ����Ч���㷨������ m x n ���� matrix �е�һ��Ŀ��ֵ target ���þ�������������ԣ�
				ÿ���е����������Ұ��������С�
				ÿ�еĵ�һ����������ǰһ�е����һ��������
			���磺

				1	3	5	7
				10	11	16	20
				23	30	34	60
			��� target Ϊ 7������true����� target Ϊ 6������false��
*/

/*
	����Ҳ���� 1.array/4.matrix/5.������ά����2 �ķ�����������һ�����ַ���������д������
	ע�⵽��һ�������� ÿ�еĵ�һ����������ǰһ�е����һ��������
		��ô����ѵ�ǰ�е��������֣��ӵ���һ�еĺ��棬��Ȼ������ġ�
		����
			1	3	5	7
			10	11	16	20
		�ѵڶ��нӵ���һ�еĺ��棬1	 3	5	7	10	11	16	20 ��Ȼ������ġ�

	����1�����ζ���
	��һ�ζ��֣����ҵ����ʵ���
		�ҵ����һ�� target >= matrix[row][0]����ô�� row �о��Ƿ��ϵ��С�
		����ʵ�Ƕ��ֱ�����Ŀ�еĵ����֣��������һ��С�ڵ��ڸ���ֵ��Ԫ��
	�ڶ��ζ��֣�
		�ڵ� i ���ж��ֲ����Ƿ���� target

	ʱ�临�Ӷȣ�O(logm + logn)
	�ռ临�Ӷȣ�O(1)
*/

func searchMatrix(matrix [][]int, target int) bool {
	if len(matrix) == 0 {
		return false
	}

	// �ܹ��� len(matrix) ��
	left, right := 0, len(matrix)-1

	// �����ҵ����һ�� matrix[i][0] <= target
	row := -1
	for left <= right {
		mid := left + (right-left)/2
		if matrix[mid][0] == target {
			return true
		} else if matrix[mid][0] > target {
			right = mid - 1
		} else {
			//mid�����һ�У�������һ�еĵ�һ�������� target����ô mid �о��� target ���ڵ���
			if mid == len(matrix)-1 || matrix[mid+1][0] > target {
				row = mid
				break
			} else {
				left = mid + 1
			}
		}
	}

	// û�ҵ����ʵ���
	if row == -1 {
		return false
	}

	// �� row ���ж��ֲ����Ƿ���� target
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
	����2��һ�ζ���
	��������˵���� ����ѵ�ǰ�е��������֣��ӵ���һ�еĺ��棬��Ȼ������ġ�
	��ô�Ϳ��԰Ѷ�ά��������һ��һά���飬��һά�����ж��ֲ��� target

	ʱ�临�Ӷȣ�O(log(mn))
	�ռ临�Ӷȣ�O(1)
*/

func searchMatrix1(matrix [][]int, target int) bool {
	if len(matrix) == 0 {
		return false
	}

	row, col := len(matrix), len(matrix[0])
	left, right := 0, row*col-1
	for left <= right {
		mid := left + (right-left)/2
		// �ҵ���ȷ������
		// ÿһ���� col ��������ô mid/col ���ܵó�λ����һ��
		// �������� col ���࣬�ܵó������к�
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
