#include <iostream>
#include <string>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

using namespace std;

/*
	桶排序：
	核心思想是将要排序的数据分到几个有序的桶里(找容器放起来)，每个桶里的数据再单独进行排序。
	桶内排完序之后再把每个桶里的数据按照顺序依次取出，组成的序列就是有序的了。
	桶排序不是基于比较的排序，与被排序的样本的实际数据状况很有关系，所以实际中并不经常使用
		首先，要排序的数据需要很容易就能划分成 m 个桶，并且，桶与桶之间有着天然的大小顺序。
		这样每个桶内的数据都排序完之后，桶与桶之间的数据不需要再进行排序。
		其次，数据在各个桶之间的分布是比较均匀的。如果数据经过桶的划分之后，
		有些桶里的数据非常多，有些非常少，很不平均，那桶内数据排序的时间复杂度就不是常量级了。
		在极端情况下，如果数据都被划分到一个桶里，那就退化为 O(nlogn) 的排序算法了
	时间复杂度O(N)，额外空间复杂度O(N)，桶排序是稳定的排序
	桶的用法等：极客第13
*/

/*
	补充问题
		给定一个数组，求如果排序之后，相邻两数的最大差值，要求时间复杂度O(N)，且要求不能用非基于比较的排序。

	思路数：可以借助桶，假设有n个数，准备n+1个桶，编号为0~n，将数组中最小的数，放到0号桶，最大的数，放到n号桶，
		并且n号桶，只放最大的数，把[min,max)剩下的，放到 0~n-1号桶中
		那么，0~n-1号桶，每个桶负责的区间 d = (max - min)/n ，那么，数组中某个数num,应该放到第 (num - min)/d 号桶中
		即 (num - min)*n/(max - min)

		比如现在有10个数，最大数99，最小数0，准备11个桶，0号桶放0~9,1号桶放10~19
		2号桶放20~29.....9号桶放90~98,10号桶放99

		放好之后，1~n-1号桶中最少有一个空桶，因为n个数，定义了n+1个桶，而这个空桶，既不是0号也不是n号，那么相邻两数的最大差值，肯定不来自
		一个桶内的两个数，因为每一个桶放入数的范围是一样的，那么，一个空桶的后一个非空桶中的值 减去 这个空桶的前一个非空桶的值
		肯定比一个桶内两个值相减要大，因为他们之前至少差了一个桶的范围值
		比如，3号桶有两个数 30,39 4号桶是空的，5号桶有两个数 50,59，一个桶中两个数的最大差值为桶的范围值-1，为9，但是5号桶的50
		和3号桶的39，也是相邻的两个数，他们的差值为11
		但是上面只是证明了相邻两数的最大差值肯定不来自同一个桶，但是也不一定是来自空桶的前一个桶和空桶的下一个桶
		比如1号桶中进来一个数,19,2号桶为空，3号桶进来一个数30，4号桶进来一个数49，差值最大的，来自于3和4两个非空桶

		所以，遍历数组，再用三个数组，分别记录这些痛是否是空桶，桶的最大值和最小值，遍历完之后
		从1号桶开始，找一个非空桶，然后找这个非空桶的前一个非空桶，用他的最大值减去前一个桶的最小值
*/

//返回每一个数，应该放几号桶
int bucket(int num, int n, int iMin, int iMax)
{
	//当num为iMax时，桶号为 n，num为iMin时，桶号为0
	return (int)((num - iMin) * n / (iMax - iMin));
}

int maxGap(int arr[], int n)
{

	//先找到系统中的最小值和最大值
	int iMin = arr[0];
	int iMax = arr[0];

	for (int i = 0; i < n; i++)
	{
		if (arr[i] < iMin)
			iMin = arr[i];

		if (arr[i] > iMax)
			iMax = arr[i];
	}

	cout << "最大值：" << iMax << "  最小值：" << iMin << endl;
	if (iMax == iMin) //如果最小值和最大值相等，最大差值为0
		return 0;

	//声明 n+1个桶，编号为 0~n，iMin放到0号桶，iMax放到n号桶
	//三个数组，存放每个桶的最大值最小值和是否是空桶
	int *iMaxs = new int[n + 1];
	int *iMins = new int[n + 1];
	int *iHasNum = new int[n + 1];

	memset(iMaxs, 0, sizeof(int) * (n + 1));
	memset(iMins, 0, sizeof(int) * (n + 1));
	memset(iHasNum, 0, sizeof(int) * (n + 1));

	int bid = 0;
	//把数都放到对应的桶中
	for (int i = 0; i < n; i++)
	{
		//当arr[i]为iMax时，桶号为 n，arr[i]为iMin时，桶号为0。所以不用再单独处理 iMin 和 iMax
		bid = bucket(arr[i], n, iMin, iMax); //这个数应该放到几号桶
		if (iHasNum[bid])					 //如果里面已经有值，这个数和桶里面的值比较大小
		{
			iMaxs[bid] = arr[i] > iMaxs[bid] ? arr[i] : iMaxs[bid];
			iMins[bid] = arr[i] < iMins[bid] ? arr[i] : iMins[bid];
		}
		else
		{
			iHasNum[bid] = 1; //里面没有值时，让最大值和最小值都等于这个值
			iMaxs[bid] = arr[i];
			iMins[bid] = arr[i];
		}
	}

	for (int i = 0; i < n + 1; i++)
	{
		cout << i << "   max:" << iMaxs[i] << "  min:" << iMins[i] << "  b:" << iHasNum[i] << endl;
	}

	int res = 0; //最大的差值
	int pre = 0; //前一个非空桶，刚开始前一个非空桶为0号桶
	//从第一个桶开始，查找非空桶，并且找到它的前一个非空桶，用它的最大值，减去前一个桶的最小值
	for (int i = 1; i < n + 1; i++)
	{
		if (!iHasNum[i])
			continue;
		res = iMaxs[i] - iMins[pre] > res ? iMaxs[i] - iMins[pre] : res;
		pre = i;
	}

	delete[] iMins;
	delete[] iMaxs;
	delete[] iHasNum;

	return res;
}

int main()
{

	int array[50] = {0};

	int n = 50;

	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		int number1 = rand() % 100 + 1;
		array[i] = number1;
	}

	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;

	int iMaxGap = maxGap(array, n);

	cout << "最大差值： " << iMaxGap << endl;
	return 0;
}
