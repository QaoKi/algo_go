#include <iostream>
#include <string>
#include <stdlib.h>
#include <memory.h>

using namespace std;

/*
	计数排序：计数排序是桶排序的一种特殊情况，当要排序的 n 个数据，所处的范围并不大的时候，
				比如最大值是 k，我们就可以把数据划分成 k 个桶。每个桶内的数据值都是相同的，省掉了桶内排序的时间。
				计数排序只能给非负整数排序。如果要排序的数据是其他类型的，要将其在不改变相对大小的情况下，转化为非负整数。
				比如，如果要排序的数据中有负数，数据的范围是[-1000, 1000]，那我们就需要先对每个数据都加 1000，转化成非负整数。
				
			假设有n个数进行排序，n个数在0~100的范围内，申请一个大小为100的数组，遍历这n个数，
				每个数出现几次，就在数组对应的下标加1，比如1出现了5次，那么数组中下标1的值为5

			如果你所在的省有 50 万考生，如何通过成绩快速排序得出名次呢？
				考生的满分是 900 分，最小是 0 分，这个数据的范围很小，所以我们可以分成 901 个桶，
				对应分数从 0 分到 900 分。根据考生的成绩，我们将这 50 万考生划分到这 901 个桶里。
				桶内的数据都是分数相同的考生，所以并不需要再进行排序。我们只需要依次扫描每个桶，
				将桶内的考生依次输出到一个数组中，就实现了 50 万考生的排序。
				因为只涉及扫描遍历操作，所以时间复杂度是 O(n)。
*/

/*
	计数排序：使用计数排序，要求数据的范围不大。计数排序还应用在字符串排序的键索引计数法中
*/

void sort(int array[], int len)
{
	//先找到数组中数据的范围
	int max = array[0];
	for (int i = 0; i < len; i++)
	{
		if (array[i] > max)
			max = array[i];
	}
	// 申请一个计数数组 counts，下标大小[0,max]
	int *counts = new int[max + 1];
	memset(counts, 0, sizeof(int) * (max + 1));

	//填充 counts,counts[i] 表示数组 array 中，值为 i 的元素有多少个
	for (int i = 0; i < len; i++)
	{
		counts[array[i]]++;
	}

	//接下来的问题是如何把 counts 中的数取出来排列好放回array中

	//方法1，遍历 counts，counts[i] 为几，就表示 array中值为 i 的元素有几个
	/*
	int index = 0;
	for (int i = 0; i < max + 1; i++)
	{
		if (!counts[i])
			//没有数据
			continue;
		for (int j = 0; j < counts[i]; j++)
		{
			array[index++] = i;
		}
	}
	*/

	//方法2，将counts数累加，再借助一个辅助数组。详细的讲解见极客13
	for (int i = 1; i < max + 1; i++)
	{
		counts[i] = counts[i - 1] + counts[i];
	}
	/*
		此时 counts 表示的是，在 array中，小于等于 i 的值有 counts[i] 个
		比如，如果 array 为 [2, 5, 3, 0, 2, 3, 0, 3]
		刚开始填充完以后，counts为 [2,0,2,3,0,1]，表示在 array中，值为0的元素有2个，值为1的元素有0个，值为3的值有3个
		累加完以后，counts为 [2,2,4,7,7,8]，表示在 array中，值小于等于0 的元素有2个，值小于等于3的值有7个，值小于等于5的值有8个。
	*/

	//借助一个辅助数组，存放排完序以后的数据
	int *help = new int[len];

	/*
		遍历 array，在array中，值小于等于 array[i] 的元素有 count[array[i]] 个，
		所以，array[i]在 help 中的下标为 counts[array[i]] - 1
		（比如，array[i] = 1，counts[1] = 2，表示array中，值小于等于1的元素有2个，所以，array[i]应该放到1的位置上，
		放完以后，将 counts[array[i]]--，再遇到值为1的元素时，此时counts[1] = 1，表示表示array中，值小于等于1的元素有1个（就是它自己），
		那么很明显，array[i]应该放到下标 counts[array[i]] - 1 = 0 的位置上）
	*/

	//要从后往前遍历，因为只有这样，排序才是稳定的，相等的数据，前后的顺序不会被改变，如果从前往后遍历，排序就不是稳定的了
	//原因自己在脑海中想一下数据是如何被放到help中的就知道了
	for (int i = len - 1; i >= 0; i--)
	{
		int index = counts[array[i]] - 1;
		help[index] = array[i];
		counts[array[i]]--;
	}

	//数据拷贝回array
	for (int i = 0; i < len; i++)
	{
		array[i] = help[i];
	}
	delete[] help;

	delete[] counts;
}
int main()
{

	//int array[8] = {2, 5, 3, 0, 2, 3, 0, 3};

	//int len = 8;

	int array[10] = {9, 3, 2, 4, 8, 5, 1, 6, 0, 7};

	int len = 10;

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	sort(array, len);

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	return 0;
}
