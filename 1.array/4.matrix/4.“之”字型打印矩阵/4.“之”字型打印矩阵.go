package main

/*
	��Ŀ������һ�����;���matrix

	���磺
			1	2	3	4
			5	6	7	8
			9	10	11	12

	���ա�֮�����εķ�ʽ��ӡ�������,���Ϊ��1��2��5��9��6��3��4��7��10��11��8��12
	Ҳ����ÿ�ζ�б�Ŵ�ӡ
	��Ҫ�� ����ռ临�Ӷ�ΪO(1)
*/

/*
	˼·�������Ŀ����ֵ���±��ƶ�û�й��ɿ���
		  ������������ָ�룬������a��b����ʼ���ڵ�һ�к͵�һ�У�
				a
			b	1	2	3	4
				5	6	7	8
				9	10	11	12
		  a�����ߣ�ÿ����һ�����������ߵ�ͷʱ�������ߣ�һֱ���ߵ������½�
		  b�����ߣ�ÿ����һ�����������ߵ�ͷʱ�������ߣ�һֱ���ߵ������½�
			      a
			  1	  2	  3	  4
			b 5	  6	  7	  8
			  9	  10  11  12

			a��b֮��͹�����һ��б�ߣ����磬��a��ӡ��b����a���к�--���к�++��һֱ��ӡ��b��
			��b��ӡ��a����b���к�++���к�--,һֱ��ӡ��a

*/
func printMatrix(matrix [][]int) []int {
	//�С���
	row, col := len(matrix), len(matrix[0])
	if row == 0 || col == 0 {
		return []int{}
	}

	res := make([]int, row*col)
	ax, ay, bx, by := 0, 0, 0, 0
	//��ӡ�����ȴ�b��a
	aTob := false

	//ֻ�е�a�ߵ�����ʱ��a���к� ax �Ż���� row-1
	//ֻ�е�b�ߵ�����ʱ��b���к� by �Ż���� col-1
	for ax <= row-1 && by <= col-1 {
		//��ӡ��ǰa��b��ɵ�б���ϵ���
		tmp := printLevel(matrix, ax, ay, bx, by, aTob)
		res = append(res, tmp...)

		//��a��bÿ���ƶ�һ��λ��
		//��� a ���к� ay ���� col-1��˵��a�����ߵ���ͷ����a�����ƶ����кż�1,�����кŲ��䣬�кż�1
		if ay == col-1 {
			ax++
		} else {
			ay++
		}

		//��� b ���к� bx ���� row-1��˵��b�����ߵ���ͷ����b�����ƶ����кż�1,�����кŲ��䣬�кż�1
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
