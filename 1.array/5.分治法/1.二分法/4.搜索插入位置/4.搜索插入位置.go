package main

/*
	leetcode 35
	����һ�����������һ��Ŀ��ֵ�����������ҵ�Ŀ��ֵ�������������������Ŀ��ֵ�������������У����������ᱻ��˳������λ�á�
	����Լ������������ظ�Ԫ�ء�
*/

/*
	���������������е�һ�����ڵ��ڸ���Ԫ�ص�λ��
*/

//���ҵ�һ�����ڵ��ڸ���ֵ��Ԫ�أ������±�
func searchInsert(nums []int, target int) int {
	if len(nums) == 0 {
		return 0
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] >= target {
			if mid == 0 || nums[mid-1] < target {
				return mid
			} else {
				right = mid - 1
			}
		} else {
			left = mid + 1
		}
	}

	//û�ҵ����ڵ��� target�ģ����뵽��������
	return len(nums)
}

/*
	������û����Ķ��ֲ���Ҳ�ܹ������
		1�����Ŀ��ֵ�������У�ûʲô��˵�ģ������ҵ���ֱ�ӷ���
		2�����Ŀ��ֵ���������У�˼�����ֲ��ҵĹ��̣����� left��ֵ�����Ǹ�Ŀ��ֵ��˳������λ��
*/

func searchInsert1(nums []int, target int) int {
	if len(nums) == 0 {
		return 0
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			return mid
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}

	}
	return left
}
