package main

/*
	leetcode 704
	��Ŀ��
		����һ�� n ��Ԫ������ģ������������� nums ��һ��Ŀ��ֵ target��
		дһ���������� nums �е� target�����Ŀ��ֵ���ڷ����±꣬���򷵻� -1��

	���ֲ��ҵ�������
		1�������������
		2���ܹ�ͨ���������ʣ�����һ�㶼�����飬������Ҫ�������ڴ档������������֣����ӶȻ�����
		3��������̫�٣�����ֱ�ӱ����ҡ���������̫����Ϊ����Ҫ���������ڴ�洢���Կռ�����̫��

	ʱ�临�Ӷȣ�O(logn)
*/

func search(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		/*
			С���ɣ���ֹ�����mid = L + (R-L)/2��
			a/2 == a >> 1  a����2������a����һλ������  mid = L + (R-L) >> 1��λ��������������ܶ�
			���ǣ�(R-L) >> 1 ��Ҫ�����㣬����ŵ�һ�����л����
				int temp = (R-L) >> 1;
				int mid  = L + temp;
		*/

		mid := left + (right-left)/2
		if nums[mid] == target {
			return mid
		} else if nums[mid] > target {
			right = mid - 1 //ע�� left �� right ֵ���µı߽磬��Ȼ���ܻ�Ϳ���һ��������ѭ��
		} else {
			left = mid + 1
		}

	}
	return -1
}
