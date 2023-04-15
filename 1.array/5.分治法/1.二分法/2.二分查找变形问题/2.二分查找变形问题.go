package main

/*
	���ֲ��ҵ�������
		1�������������
		2���ܹ�ͨ���������ʣ�����һ�㶼�����飬������Ҫ�������ڴ档������������֣����ӶȻ�����
		3��������̫�٣�����ֱ�ӱ����ҡ���������̫����Ϊ����Ҫ���������ڴ�洢���Կռ�����̫��

	ʱ�临�Ӷȣ�O(logn)
*/
/*
	��������1�����ҵ�һ��ֵ���ڸ���ֵ��Ԫ��
	��������2���������һ��ֵ���ڸ���ֵ��Ԫ��
	��������3�����ҵ�һ�����ڵ��ڸ���ֵ��Ԫ��
	��������4���������һ��С�ڵ��ڸ���ֵ��Ԫ��
*/

//��������1�����ҵ�һ��ֵ���ڸ���ֵ��Ԫ�أ������±�
func find1(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			/*
				�� nums[mid] == num
				��� mid������ĵ�һ��Ԫ�أ���ô�϶��ǵ�һ��ֵ���ڸ���ֵ��Ԫ�أ�
				��� mid��ǰ��һ��������num����ô mid Ҳ�ǵ�һ��ֵ���ڸ���ֵ��Ԫ�أ�
				����Ļ�������С��Χ����
			*/
			if mid == 0 || nums[mid-1] != target {
				return mid
			} else {
				right = mid - 1
			}
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}
	return -1
}

//���ҵ�һ��ֵ���ڸ���ֵ��Ԫ�أ������±ꡣfind1�ļ��д��
func find1Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2

		//�ҵ�����ȵ�ֵ��Ҳ��ͣ����ȥ�ж��Ƿ��ǵ�һ����ȵ�Ԫ�أ�������С��Χ������
		if nums[mid] >= target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	/*
		���ַ����£���������Ҫ�ҵ�Ԫ���±�Ϊ x ���� mid ���� x ʱ��Ҳ��ͣ��������right = x - 1��
		���ҵ� x �Ժ���Ϊ��Ҳ����ִ������ if (array[mid] >= num)������right��֮���ѭ���оͲ�����ˣ�
		Ҳ����˵������ right ����һ��Ԫ�ؾ�������Ҫ�ҵ�ֵ��
		�� for ѭ��������left�͵��� right + 1��Ҳ��������Ҫ�ҵ� x

		���ַ�������ʱ��Ҫ��find1������Ϊÿ���ҵ���ȵ�ֵ����ȥ�ж��Ƿ��� x������һֱ������ left > right
	*/
	if left < len(nums) && nums[left] == target {
		return left
	}

	return -1
}

//��������2���������һ��ֵ���ڸ���ֵ��Ԫ�أ������±�
func find2(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] == target {
			/*
				�� nums[mid] == num
				��� mid������ĵ�һ��Ԫ�أ���ô�϶��ǵ�һ��ֵ���ڸ���ֵ��Ԫ�أ�
				��� mid��ǰ��һ��������num����ô mid Ҳ�ǵ�һ��ֵ���ڸ���ֵ��Ԫ�أ�
				����Ļ�������С��Χ����
			*/
			if mid == len(nums)-1 || nums[mid+1] != target {
				return mid
			} else {
				left = mid + 1
			}
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	return -1
}

//��������2���������һ��ֵ���ڸ���ֵ��Ԫ�أ������±ꡣfind2�ļ��д��
func find2Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] <= target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	//��find1Easyͬ��for ѭ�������Ժ�right ����Ҫ�ҵ��±�
	if right >= 0 && nums[right] == target {
		return right
	}
	return -1
}

//��������3�����ҵ�һ�����ڵ��ڸ���ֵ��Ԫ��
func find3(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
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

	return -1
}

//��������3�����ҵ�һ�����ڵ��ڸ���ֵ��Ԫ�ء�find3�ļ��д��
func find3Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] >= target {
			right = mid - 1
		} else {
			left = mid + 1
		}
	}

	//��find1Easyͬ��
	if left < len(nums) && nums[left] >= target {
		return left
	}
	return -1
}

//��������4���������һ��С�ڵ��ڸ���ֵ��Ԫ��
func find4(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] <= target {
			if mid == len(nums)-1 || nums[mid+1] > target {
				return mid
			} else {
				left = mid + 1
			}
		} else {
			right = mid - 1
		}
	}

	return -1
}

//��������4���������һ��С�ڵ��ڸ���ֵ��Ԫ�ء�find4�ļ��д��
func find4Easy(nums []int, target int) int {
	if len(nums) == 0 {
		return -1
	}

	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)/2
		if nums[mid] <= target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	//��find1Easyͬ��
	if right > 0 && nums[right] <= target {
		return right
	}
	return -1
}
