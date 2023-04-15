package main

/*
	leetcode 81
	��Ŀ��
		���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת
		���磬���� [0,0,1,2,2,5,6] ���ܱ�Ϊ [2,5,6,0,0,1,2]
		����һ��������Ŀ��ֵ���жϸ�����Ŀ��ֵ�Ƿ�����������С������ڷ��� true�����򷵻� false��

		�� 1.������ת�������� �������������п��԰����ظ���Ԫ��
*/

/*
	�����а������ظ���Ԫ�أ���Ȼ����֮ǰ�ķ������� mid�������Ϊ�����֣�
		�� nums[left] < nums[mid] ʱ����Ȼ�����ж�ǰ�벿��������ģ�
		���ǵ� nums[left] == nums[mid]ʱ�޷��жϣ�
			���� nums = [1 1 0 1 1 1 1 1]��left = 0, mid = 3,
				ǰ�벿��Ϊ [1 1 0 1]��nums[left] �� nums[mid] ������1������ǰ�벿��������ġ�
		���Ե� nums[left] == nums[mid] ʱ������ѡ��left++�����¶��֡����Կ����������Ժ�nums[left]���ǵ���nums[mid]��
			�ٺ��ƣ���ʱ�ҵ���target������ʵ���������������˳��������бȽ��ˣ�ʱ�临�Ӷȱ�� O(n)
		��������� 1.������ת�������� ��ͬ
*/

func search(nums []int, target int) bool {
	if len(nums) == 0 {
		return false
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			return true
		}

		//�޷��ж�ǰ�벿���Ƿ��������������Ԫ��
		if nums[left] == nums[mid] {
			left++
			continue
		}

		//ǰ�벿������
		if nums[left] < nums[mid] {
			// target �Ƿ���ǰ�벿��
			if nums[left] <= target && target < nums[mid] {
				//��ǰ�벿�֣���С��Χ
				right = mid - 1
			} else {
				//����ǰ�벿�֣�����ȥ��ֺ�벿��
				left = mid + 1
			}

		} else {
			// ǰ�벿��������ģ���ô��벿��������ģ��ж� target �Ƿ��ں�벿����
			if nums[mid] < target && target <= nums[right] {
				//�ں�벿�֣���С��Χ
				left = mid + 1
			} else {
				//���ں�벿�֣�����ȥ���ǰ�벿��
				right = mid - 1
			}
		}
	}
	return false
}
