package main

import (
	"math/rand"
	"time"
)

/*
	������ leetcode 912 ���Դ���
	���������������⣺
		������Ϊ  1,2,3,4,5,6  ���������״��ʱ�� ÿ��ѡ�����һ������Ϊnum����ô����num�������û����
		ÿ��һ��ֻ�ܸ㶨һ������ʱ�临�Ӷȱ�ΪO(n^2)
		������ţ�
		ÿ���������������ѡ��һ��ֵ�ŵ�����������Ϊnum�������漰�����ʣ�����������ʱ�临�Ӷȣ�O(n*logn)��

	��������ǹ�������õģ���Ϊʱ�临�Ӷȵĳ�����ȹ鲢������
*/

func sort(nums []int, L, R int) {
	//��ֹ����
	if L >= R {
		return
	}
	//���ݵ�����״���ǲ��ɿصģ����ǿ��Բ��÷��������ҹ̶�������״��
	//1.����������������ȡֵ��������״���޹�
	//2.��ϣ
	//�����������������ȡһ��ֵ�ŵ���������
	index := rand.Intn(R-L+1) + L
	num := nums[index]

	l := L - 1 //ָ��С��numֵ��������һ��ֵ
	r := R + 1 //ָ�����numֵ����ĵ�һ��ֵ
	curr := L  //��ǰֵ���±꣬������ָ��

	//�������е�����С��num�ķŵ�С�����򣬴��ڵķŵ��������򣬵��ڷŵ��м�
	for curr < r {
		if nums[curr] == num {
			curr++
		} else if nums[curr] < num {
			l++
			nums[l], nums[curr] = nums[curr], nums[l]
			curr++
		} else {
			r--
			nums[r], nums[curr] = nums[curr], nums[r]
			//curr�Ȳ���1�����жϻ��������������ֵ
		}
	}

	//����ʱ�������L-l��������С��num������pr-r�Ǵ���num��ֵ
	//�ټ�����֣�ֱ��ʣһ����
	sort(nums, L, l)
	sort(nums, r, R)
}

func sortArray(nums []int) {
	rand.Seed(time.Now().Unix())
	sort(nums, 0, len(nums)-1)
}
