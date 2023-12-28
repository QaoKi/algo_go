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
void merge(vector<int>& nums, int L, int mid, int R) {
	//L��R������arr�ĵ�һ��ֵ�±�����һ��ֵ�±�
	int pl = L;		  //ָ��ָ���������ĵ�һ��Ԫ��
	int pr = mid + 1; //ָ��ָ���ұ�����ĵ�һ��Ԫ��
	
	vector<int> help(R - L + 1, 0);//�������飬���������������������Ժ����
	int index = 0;	  //���� help ���±�
	while (pl <= mid && pr <= R) {	
		//��plָ���ֵ����prָ���ֵ������prָ���ֵ�����򷵻�plָ���ֵ
		help[index++] = nums[pl] <= nums[pr] ? nums[pl++] : nums[pr++];
	}

	//��������û�д�����������ηŵ�help��
	while (pl <= mid) 
		help[index++] = nums[pl++];

	while (pr <= R) 
		help[index++] = nums[pr++];

	//������ԭ�������飬������±괦��Ҫע��
	for (int i = 0; i < index; i++)
		nums[L + i] = help[i];
}
//��������ĵ�һ��ֵ���±�����һ��ֵ���±�
void sort(vector<int>& nums, int L, int R) {
	//��ֹ����
	if (L >= R) return;
	/*
		С���ɣ���ֹ�����mid = L + (R-L)/2��
		a/2 == a >> 1  a����2������a����һλ������  mid = L + (R-L) >> 1��λ��������������ܶ�
		���ǣ�(R-L) >> 1 ��Ҫ�����㣬����ŵ�һ�����л����
			int temp = (R-L) >> 1;
			int mid  = L + temp;
	*/
	int temp = (R - L) >> 1;
	int mid = L + temp;

	//�������Ϊ�����֣�һ����Ϊ L��mid��һ����Ϊ mid+1��R
	//�ٽ��Ų�֣�ֱ����ֵ�ÿһ����ֻʣһ����������L=R��ʱ��ֹͣ
	sort(nums, L, mid);
	sort(nums, mid + 1, R);

	//��ÿһ���Ӳ��֣���������С�ϲ�,һֱ�����ϲ����ܵ�
	merge(nums, L, mid, R);
}

vector<int> sortArray(vector<int>& nums) {
	sort(nums, 0, nums.size() - 1);
	return nums;
}

int main()
{
	return 0;
}
