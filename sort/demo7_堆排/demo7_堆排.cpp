#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

/*
	堆是一个完全二叉树的结构
		满二叉树：树中除了叶子节点，每个节点都有两个子节点
		完全二叉树：若设二叉树的深度为h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，
					第 h 层所有的结点都连续集中在最左边，这就是完全二叉树
	完全二叉树可以用数组表示：
		对于从下标0开始使用的数组，下标为i的元素，
			它的左孩子下标为 2*i+1，它的右孩子下标为 2*i+2，如果越界，代表没有这个子节点。它的父节点下标为 (i-1)/2。
		对于从下标1开始使用的数组，下标为i的元素，
			它的左孩子下标为 2*i，它的右孩子下标为 2*i+1，它的父节点下标为 i/2。
		下标从1开始使用，计算子节点和父节点的时候，更方便直观，但是在应用的时候下标可能会搞混，所以还是从下标0开始使用吧

	堆分为大根堆和小根堆
		大根堆：在完全二叉树中，一个子树中的最大值，就是子树的头节点，即在树中，任何一个头节点，比它的左右节点的值都大
		小根堆：在完全二叉树中，一个子树中的最小值，就是子树的头节点，即在树中，任何一个头节点，比它的左右节点的值都小
*/

/*
	可以用 leetcode 912 测试代码
	堆排序：先用数组构建一个大根堆，数组的第一个元素变为最大的，与数组的最后一个元素交换，
	进行heapify操作，最后一个元素变为最大的，不参与heapify操作，一直到排好
	1，堆排序空间复杂度为O(1)
	2，堆排序包括建堆和排序两个操作，建堆过程的时间复杂度是 O(n)，排序过程的时间复杂度是 O(nlogn)，
		所以，堆排序整体的时间复杂度是 O(nlogn)
	3，堆排序不是稳定的排序算法，因为在排序的过程，存在将堆的最后一个节点跟堆顶节点互换的操作，
		所以就有可能改变值相同数据的原始相对顺序

	堆排序相比快排的缺点：极客 28
*/

/*
	buildHeap :将数组变为大根堆
	将数组变为大根堆的时间复杂度分析：
		每次要插入的节点，因为只需要和它的父节点比较，所以最多需要比较这棵树的高度次，高度是几次，就最多比较几次，
		一个节点为N的完全二叉树，深度为log2N
		当第N个节点插进来，前面N-1个节点组成的完全二叉树的高度为log2(N-1)，
		所以插入第N个节点的时间复杂度为log2(N-1)，也就是O(logN)
		所以建立一个大根堆总的时间复杂度为 log1 +log2+....+log(N-1)	结果为O(N)

	heapinsert：向堆中插入数据
		一个新节点加入到堆里面，这个节点往上调整，一直到它的值不比它的父节点大，就停止

	heapify： 一个大根堆的其中一个节点，值改变了，变小了，让这个节点向下沉，让这个树重新排成大根堆
		找到这个节点的左右节点，比较左右节点的值，较大的那个和这个节点比较，如果这个节点小，则下沉
		时间复杂度为O(logN)

	heapinsert 和 heapify只需要调整树的高度的次数，所以都是 O(logN)的时间复杂度
*/

void heapify(vector<int>& nums, int len, int index) //index 是值改变的节点的下标
{
	int left = index * 2 + 1; //左孩子的下标
	while (left < len) {
		//当右孩子不越界，并且比左孩子的值大时，largest 为右孩子下标，否则 largest 为左孩子下标
		int largest = left + 1 < len && nums[left] < nums[left + 1] ? left + 1 : left;
		//把左右孩子中较大的值，再与改变后的值比较
		if (nums[index] >= nums[largest]) //改变后的值还是比左右孩子大，就不用动
			break;

		//当改变后的值没有左右孩子大
		swap(nums[index], nums[largest]);

		//交换完以后，改变的值的下标变成了 largest，把下标换换，还要再接着比较交换完以后的左右孩子大小
		index = largest;
		left = index * 2 + 1;
	}
}

//构建堆，时间复杂度O(n)
void buildHeap(vector<int>& nums) {
	/*
		遍历整个数组，从前往后，让每个元素去和它的父节点比较，
		为什么要从前往后，因为比如当遍历到数组的中间元素，从前往后的话，那么这个元素前面的所有元素，已经组成了大根堆，
		只需要用这个节点去和它的父节点比较
	*/
	for(int i = 0; i < nums.size(); i++) {
		int index = i;
		int father = (index - 1) / 2;
		//只要这个节点比它的父节点大，就和父节点交换
		while(father >= 0 && nums[index] > nums[father]) {
			swap(nums[index], nums[father]);
			//此时这个节点的下标已经变了,变成原来的父节点的下标，它会有一个新的父节点，再和新的父节点比较
			index = father;
			father = (index - 1) / 2;
		}
	}
}

vector<int> sortArray(vector<int>& nums) {
	if(nums.empty()) return nums;
	//给定一个数组，构建成大根堆
	buildHeap(nums);
	/*
		变成大根堆以后，每次将数组的第一个元素(大根堆的头结点，数组中最大的数)和数组的最后一个数交换（最大的值就排好了），
		让排序的数组长度减1（让最后一个数不再参与heapify操作），然后进行heapify操作
	*/

	int length = nums.size();
	while (length > 1) {
		//将当前根堆中最大的元素移到数组的后面
		swap(nums[0], nums[--length]);
		heapify(nums, length, 0);
	}
	return nums;
}

int main()
{
	return 0;
}
