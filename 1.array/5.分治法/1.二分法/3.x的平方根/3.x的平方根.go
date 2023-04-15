package main

/*
	leetcode 69
	����һ�����������������ƽ�������������9������3
	��ȷ��С�����nλ
	��ʾ��
		0 <= x <= 2^31 - 1
*/

/*
	���ö��ַ���0 <= k^2 <= num�������½���Ͻ��������Ϊ 0 �ʹ���� num
	С�����ң�����С�����һλ����x.0��(x+1).0��������ֹ����������һ������ǰ��С�ڣ���0.1����

	��ֹ�����
		�� x ���� 2^31 - 1 ʱ��mid*mid ��������
		1.�� if int64(mid*mid) == num �жϣ�
			����д if mid*mid == num Ҳû���⣬go�����Զ��� mid*mid װ���� int64
			������c++�в���Ҫ�� if((long long) mid*mid == num) �ж�

			����Ϊ���㣬һ��ʼ��ֱ�Ӱ�����ֵת��int64

		2.�� if mid == num / mid���������ַ���Ҫע�� mid Ϊ0 ��ʱ������
*/

//ֻ����������
func mySqrt(x int) int {
	if x == 0 {
		return 0
	}

	num := int64(x)
	//��ʼ�������ҽ���0��num
	left, right := int64(0), num
	for left <= right {
		mid := left + (right-left)/2
		/*
			��Ϊ mid ����������������һ���� mid ��ʱ��mid���ʵ�ʵ�С
			���� left + right ����3��ԭ�� midӦ��Ϊ1.5���������Ϊ1����С�ˡ�
			�������жϵ�ʱ��Ҫ���⴦����� mid*mid С�� num���� (mid + 1) * (mid + 1) > num��˵�� mid����Ҫ�ҵ�ֵ
		*/
		if mid*mid == num {
			return int(mid)
		} else if mid*mid < num {
			if (mid+1)*(mid+1) > num {
				return int(mid)
			}
			//�������ϣ�������
			left = mid + 1
		} else {
			right = mid - 1
		}
	}
	return 0
}

//��ȷ��С�����nλ
func Sqrt(num int, n int) float32 {
	if num == 0 {
		return 0
	}

	//��������λ
	interval := mySqrt(num)
	/*
		����С��λ��һλһλ���ң�����С������һλ�����ҵڶ�λ������ÿһλ���Ƕ����ġ�����������˼��һ����
		������С������һλ����� mid * mid < num �� (mid + 0.1) * (mid + 0.1) > num��˵�� mid ����Ҫ�ҵ�ֵ
		��ȷ��С�����nλ����ѭ�� n �Σ����Զ�ѭ��һ�Σ���ΪҪ�����һλ���������룩
	*/

	//interval ��ʱ������λ����ȷ��С��λ���� interval �� interval + 1 ֮��
	mid := float32(interval)
	pos := float32(1)
	for i := 0; i < n; i++ {
		left, right := mid, mid+pos //��С�����һλ���ҽ��� mid �� mid + 1֮�䣻����λ���ҽ��� mid �� mid + 0.1֮��
		pos *= 0.1
		//ÿһ�� for ѭ����������˵���ҵ��˵�i+1λС������mid�͵��ھ�ȷ��С����� i+1λ��ֵ
		for left <= right {
			mid = left + (right-left)/2
			if mid*mid == float32(num) {
				break
			} else if mid*mid < float32(num) {
				if (mid+pos)*(mid+pos) > float32(num) {
					break
				}

				//��������
				left = left + pos
			} else {
				right = right - pos
			}

		}
	}
	return mid
}
