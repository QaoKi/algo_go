package main

/*
	��Ŀ�� leetcode 76
		����һ���ַ��� s ��һ���ַ��� t ������ s �к��� t �����ַ�����С�Ӵ���
		��� s �в����ں��� t �����ַ����Ӵ����򷵻ؿ��ַ��� "" ��
		ע�⣺��� s �д����������Ӵ������Ǳ�֤����Ψһ�Ĵ𰸡�

		ʾ��1��
		���룺s = "ADOBECODEBANC", t = "ABC"
		�����"BANC"
*/

/*
	�������ڣ��ο�https://leetcode-cn.com/problems/minimum-window-substring/solution/tong-su-qie-xiang-xi-de-miao-shu-hua-dong-chuang-k/
		��������ָ�� left �� right ������ָ��֮�����һ���������ڣ�����ָ����ָ���Ԫ�أ�Ҳ�����ڴ����У���
		�����˼·���� ������С�������� ���ƣ�
		�����������γɵ��Ӵ���û�а��� t �������ַ��� right ����ƶ������󻬶����ڣ�һֱ�����������γɵ��Ӵ��������� t �������ַ���
			��ʱ���ϵ��� left ����ƶ������ϵĳ�����С���ڣ������Ƿ����������������ҵ���С�����������Ļ������ڵĳ���

		�����ǣ�����жϻ��������γɵ��Ӵ����Ƿ������ t �������ַ���
			1��������һ�� mapByte := map[byte]int ���洢������������Ҫ�������ַ������������������γɵ��Ӵ���
				��Ҫ������Щ�������ַ��ŷ������������� t ���е��ַ�����ʼ�� mapByte
			2��������չ���ڣ�ÿ��������һ���ַ���������֤һ������ַ��Ƿ���� t �У���ֹ����Ҫ�Ŀռ��˷ѣ���
				��������ڣ�����Ч���ַ����Ͳ����ˣ�������ڣ����� mapByte ������ַ���������1������������ַ�������������1����
			3���� mapByte ������Ԫ�ص�������С�ڵ���0ʱ��˵����ǰ�������ڰ����� t �������ַ������������ˡ�
			4���������ڷ��������Ժ󣬲��ϵ���С���ڣ������Ƿ�������������Ϊ���ҵ���̵ķ����������Ӵ���
				����С�����У�ÿ�δ����Ƴ���ĳ���ַ�ʱ��ͬ�����ж�����ַ��Ƿ���� t �У�������ڣ��� mapByte ������ַ���������1��

		��Ϊ����Ҫ�����ַ��������ԣ���Ҫ��¼���з��������Ļ��������У�������С�Ļ������ڵĳ��ȺͿ�ʼ�±꣬�ñ�������

		ʱ�临�Ӷȣ���mΪs�ĳ��ȣ�nΪt�ĳ���
			��Ϊ�����˹�ϣ���洢�ַ������Բ��ң������ʱ�临�Ӷ�ΪO(1)
			����ÿ�� check()��ʱ����Ҫ����һ���ַ��� t �������ַ�������t�������ַ���ΪC����Ϊ t �п������ظ��ַ������Բ�ȡ���ȣ�
				���磬t = "AABBCC"������Ϊ 6�����������ַ���Ϊ 3
			�����£���Ҫ����check()��2m�飨���󴰿�һ�飬��С����һ�飩
			���ԣ�ʱ�临�Ӷ�Ϊ O(C*m + n)����������汾��leetcode�лᳬʱ
		�ռ临�Ӷȣ���ϣ������ģ���ϣ��ֻ������t�������ַ��������ԣ��ռ临�Ӷ�Ϊ O(C)

*/

func minWindow(s string, t string) string {
	left, right := 0, 0
	length, index := len(s)+1, 0
	mapByte := map[byte]int{}
	for _, c := range t {
		mapByte[byte(c)]++
	}

	check := func() bool {
		for _, c := range t {
			if mapByte[byte(c)] > 0 {
				return false
			}
		}
		return true
	}

	for ; right < len(s); right++ {
		// ���󻬶�����
		if _, ok := mapByte[s[right]]; ok {
			mapByte[s[right]]--
		}

		for check() {
			// �ҳ�����С�ķ��������Ļ�������
			if length > right-left+1 {
				length = right - left + 1
				index = left
			}

			if _, ok := mapByte[s[right]]; ok {
				mapByte[s[left]]++
			}

			left++
		}
	}

	if length == len(s)+1 {
		return ""
	}

	return s[index : index+length]
}

/*
	�Ż���ÿ���жϻ��������Ƿ������������Ҫ����һ��t�������ַ��� C�����Ӷȸ�
		��һ���������洢��ǰ���������У��ж��ٸ��ַ�������t �е��ַ���

		ʱ�临�Ӷȣ�O(m + n)��m��n��s��t�ĳ���
		�ռ临�Ӷ���ȻΪ O(C)

	ע��ĵ㣬�������ӣ�
		1�����ж� have �Ƿ�Ӧ�� +1 ��ʱ��ע���ж�����
		2�����ж� have �Ƿ�Ӧ�� -1 ��ʱ��ҲҪע������������ע�⵽�������ж�����������ͬ��
*/

func minWindow1(s string, t string) string {
	left, right := 0, 0
	length, index := len(s)+1, 0

	mapByte := map[byte]int{}
	for _, c := range t {
		mapByte[byte(c)]++
	}

	have := 0

	for ; right < len(s); right++ {
		// ���󻬶�����
		if _, ok := mapByte[s[right]]; ok {
			mapByte[s[right]]--
			/*
				����ҲҪ�Ե��ϣ�����ַ����������
				ע�⣬���ﲻ��ʹ�� <= 0�����統 t = "ABC"���� s = "AABDC"��
				������s�ĵ�һ��"A"ʱ��mapByte["A"]��Ϊ0�����ϣ�have++��
				������s�ĵڶ���"A"��mapByte["A"]��Ϊ-1������� <= 0�����Ƿ��ϣ�have++�����Ǻ����ԣ�������
			*/
			if mapByte[s[right]] == 0 {
				have++
			}
		}

		for have == len(mapByte) {
			// �ҳ�����С�ķ��������Ļ�������
			if length > right-left+1 {
				length = right - left + 1
				index = left
			}

			if _, ok := mapByte[s[left]]; ok {
				mapByte[s[left]]++
				// ����0��˵���������ˣ�have--
				if mapByte[s[left]] > 0 {
					have--
				}
			}

			left++
		}
	}

	if length == len(s)+1 {
		return ""
	}

	return s[index : index+length]
}
