package main

/*

	数组的特征：
	1，线性表数据，只有前后两个方向
	2，连续的内存空间
	3，相同类型的数据
		2,3这两个特性，使数组可以随机访问，但同时插入和删除变得低效，因为要保持数据的连续性，所以插入和删除做大量的数据搬移
	4.二维数组，比如 int[3][4]，并不是连续的12字节内存，而是3个连续的4字节内存
	随机访问的寻址公式：
		a[i]_address = base_address + i * data_type_size，其中 data_type_size 表示数组中每个元素的大小

	数组下标为什么从0开始
		数组的随机访问，是根据偏移量来计算位置，数组a 的首地址就是a，所以a[0]就是偏移量为0的位置，计算a[k]只需要套入
		公式  a[k]_addrss = base_address + k * data_type_size
		如果下标从1开始，那么公式就变为	a[k]_addrss = base_address + (k - 1) * data_type_size
		对于 CPU 来说，就是多了一次减法指令

*/
