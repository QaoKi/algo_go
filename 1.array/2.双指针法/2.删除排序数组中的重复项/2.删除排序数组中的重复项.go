package main

/*
	��Ŀ�� leetcode 26
		����һ�����������С����飬����Ҫ�� ԭ�� ɾ���ظ����ֵ�Ԫ�أ�ʹ��ÿ��Ԫ��ֻ����һ�Σ������Ƴ���������³��ȡ�
		��Ҫʹ�ö��������ռ䣬������� ԭ�� �޸��������� ����ʹ�� O(1) ����ռ����������ɡ�

		ʾ��1��
		���룺nums = [1,1,2]
		�����2, ����ԭ���� nums ��ǰ����Ԫ�ر��޸�Ϊ 1, 2��
*/

/*
	˫ָ�뷨�������Ѿ��������
		ʹ������ָ�� left �� right
		left ָ������������һ��Ԫ�أ�right ����������� nums ��ÿ��Ԫ��

		�տ�ʼ left ָ���±�Ϊ0��Ԫ�أ�right ָ���±�Ϊ 0 �����±�Ϊ 1 ��Ԫ�ض����ԣ�
			��� nums[left] �� nums[right] ��ȣ�˵�� nums[right] ����ЧԪ�أ�����
			��� nums[left] �� nums[right] ����ȣ�˵�� nums[right] ����ЧԪ�أ�
				�� nums[right] ���뵽�������β������Ϊ��ʱ left ָ������������һ��Ԫ�أ�
				����Ҫ�� nums[right] ���뵽 nums[left] ����һ��Ԫ�أ�
				��Ϊ�������Ԫ�������ˣ����� left ����
		ֱ�� right ���������ĩβ����������³���Ϊ left + 1

		��Ϊ����ֵ�� left+1����������� nums Ϊ�յĻ�������������ں�����ͷ��һ�� basecase
*/

func removeDuplicates(nums []int) int {
	length := len(nums)
	if length == 0 || length == 1 {
		return length
	}

	left, right := 0, 0
	for ; right < length; right++ {
		if nums[right] != nums[left] {
			nums[left+1] = nums[right]
			left++
		}
	}

	return left + 1
}
