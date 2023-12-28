#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
	可以用 leetcode 912 测试代码
	经典快速排序思想：
		刚开始选定数组尾部的元素 x，将小于x的元素放到左边，大于x的元素放到数组右边，数组被分为两部分，
		再分别选定左右数组的尾部元素，将小于的放到左边，大于的放到右边，分治思想
	快排的时间复杂度：O(n*logn)
	空间复杂度：O(1)，但快排不是稳定的排序
*/

/*
	解题步骤：
		假设给定数组的第一个元素下标为0，0的左边有一个小于区域，元素都是小于num，那么小于区域的最后一个元素下标为-1，
		最后一个元素下标为 len-1,len-1的右边有一个大于区域，元素都是大于num,那么大于区域的第一个元素下标为len，
		刚开始让下标pl指向-1的元素，pr指向len的元素,从前往后遍历数组，
		1，当curr指向的元素等于num时，不用管，curr后移
		2，当curr指向的元素小于num时，让curr指向的元素和pl指向的元素的下一个元素交换,并让pl后移一位,即让小于区域向右增加一个，
			如果curr指向0时就小于num,自己和自己交换，然后pl++
		3，如果curr指向的元素大于num时，让curr指向的元素和pr指向的元素的前一个元素交换，
			并让pr--，即让大于区域向左增加一个，此时先不让curr++，先判断此时交换过来的值的大小
		当curr和pr相碰时停止
*/
void sort(vector<int> &nums, int L, int R) {

	if (L >= R) return;

	//每次取最后一个值作为num值
	int num = nums[R];
	int pl = L - 1; //指向小于num值区域的最后一个值
	int pr = R + 1; //指向大于num值区域的第一个值
	int curr = L;	//当前值的下标，遍历的指针

	//遍历所有的数，小于num的放到小于区域，大于的放到大于区域，等于放到中间
	while (curr < pr) {
		if (nums[curr] < num)
			swap(nums[curr++], nums[++pl]);
		else if (nums[curr] == num)
			curr++;
		else
			//curr先不加1，再判断换过来的这个数的值
			swap(nums[curr], nums[--pr]);
	}
	//到这时，数组从L-pl的数据是小于num的数，pr-R是大于num的值
	//再继续拆分，直到剩一个数
	sort(nums, L, pl);
	sort(nums, pr, R);
}

vector<int> sortArray(vector<int>& nums) {
	sort(nums, 0, nums.size() - 1);
	return nums;
}

int main()
{
	return 0;
}
