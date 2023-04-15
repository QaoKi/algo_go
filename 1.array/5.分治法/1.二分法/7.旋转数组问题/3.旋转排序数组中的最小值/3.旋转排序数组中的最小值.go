package main

/*
	leetcode 153
	��Ŀ��
		���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת��Ҳ����û��ת
		���磬���� [0,1,2,4,5,6,7] ���ܱ�Ϊ [4,5,6,7,0,1,2]
		���ҳ�������С��Ԫ�ء�

		�����в������ظ���Ԫ�ء�
*/

/*
	�����в������ظ���Ԫ�أ���ô����Ԫ��λ�� [left, right] �����ڡ�
	��� nums[left] <= nums[right]��˵�� [left, right] ������û����ת�ģ��� nums[left] ������Сֵ��ֱ�ӷ��ء�
	��� [left, right] ���䷢���˷�ת��ȡһ���м�ֵ nums[mid]��
		��� nums[left] <= nums[mid]��˵������ [left,mid] ����������
			����СԪ��һ������������������ֱ���ų�����ˣ��� left = mid+1���� [mid+1,right] ��������
				����Ϊ�����Ѿ������˷�ת������������������䣬�϶���ԭ����������Ԫ�ط�ת����ǰ�棩��
				���� nums = [7 8 9 1 2]����ʱnums[mid] = 9��nums[left] = 7���������϶�����Ҫ�ҵ����䡣
		����˵������ [left,mid] ������������СԪ��һ��������������ˣ��� right = mid���� [left,mid] ��������
			ע�� right ����ʱ����Ϊ mid ������ mid-1����Ϊ mid �޷����ų��Ƿ���Ҫ�ҵ�Ԫ�ء�

*/
func findMin(nums []int) int {
	left, right := 0, len(nums)-1
	for left <= right {
		//Ԫ����[left, right]�����ڣ���������������������ģ���ônums[left]������С��ֵ��ֱ�ӷ���
		if nums[left] <= nums[right] {
			return nums[left]
		}

		//���⣬˵������[left, right]�������������˷�ת
		mid := left + (right-left)/2
		if nums[left] <= nums[mid] {
			//[left, mid] �����������䣬�ų�
			left = mid + 1
		} else {
			//[left, mid] ��������Ҫ�ҵ�Ԫ�ؾ������������
			right = mid
		}
	}

	return -1
}
