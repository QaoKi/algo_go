package main

/*
	������ leetcode 912 ���Դ���
	�鲢����˼�룺
	���ε�˼��
*/

/*
	1.�ںϲ��Ĺ����У���� arr[L��mid]�� arr[mid+1��R]֮����ֵ��ͬ��Ԫ�أ��Ȱ� arr[L��mid]�е�Ԫ�ط��� help ���顣
		�����ͱ�֤��ֵ��ͬ��Ԫ�أ��ںϲ�ǰ����Ⱥ�˳�򲻱䡣���ԣ��鲢������һ���ȶ��������㷨��
	2.ʱ�临�Ӷȣ�������������������������ƽ�������ʱ�临�Ӷȶ��� O(nlogn)
	3.ÿ�κϲ���������Ҫ���������ڴ�ռ䣬���ںϲ����֮����ʱ���ٵ��ڴ�ռ�ͱ��ͷŵ��ˡ�
		������ʱ�̣�CPU ֻ����һ��������ִ�У�Ҳ��ֻ����һ����ʱ���ڴ�ռ���ʹ�á�
		��ʱ�ڴ�ռ����Ҳ���ᳬ�� n �����ݵĴ�С�����Կռ临�Ӷ��� O(n)��
*/

func merge(nums []int, L, mid, R int) {
	//L��R������arr�ĵ�һ��ֵ�±�����һ��ֵ�±�
	help := []int{}
	l, r := L, mid+1 //ָ��ָ���������ĵ�һ��Ԫ�� �� �ұ�����ĵ�һ��Ԫ��
	for l <= mid && r <= R {
		if nums[l] <= nums[r] {
			help = append(help, nums[l])
			l++
		} else {
			help = append(help, nums[r])
			r++
		}
	}

	for l <= mid {
		help = append(help, nums[l])
		l++
	}

	for r <= R {
		help = append(help, nums[r])
		r++
	}

	//������ԭ�������飬������±괦��Ҫע��
	for i := 0; i < len(help); i++ {
		nums[L+i] = help[i]
	}

}

//��������ĵ�һ��ֵ���±�����һ��ֵ���±�
func sort(nums []int, L, R int) {
	//��ֹ����
	if L >= R {
		return
	}

	mid := L + (R-L)/2
	//�������Ϊ�����֣�һ����Ϊ L��mid��һ����Ϊ mid+1��R
	//�ٽ��Ų�֣�ֱ����ֵ�ÿһ����ֻʣһ����������L=R��ʱ��ֹͣ
	sort(nums, L, mid)
	sort(nums, mid+1, R)
	//��ÿһ���Ӳ��֣���������С�ϲ�,һֱ�����ϲ����ܵ�
	merge(nums, L, mid, R)
}

func sortArray(nums []int) {
	sort(nums, 0, len(nums)-1)
}
