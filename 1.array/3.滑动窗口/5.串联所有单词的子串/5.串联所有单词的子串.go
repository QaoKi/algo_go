package main

/*
	��Ŀ�� leetcode 30
		����һ���ַ��� s ��һЩ������ͬ�ĵ��� words���ҳ� s ��ǡ�ÿ����� words �����е��ʴ����γɵ��Ӵ�����ʼλ�á�
		ע���Ӵ�Ҫ�� words �еĵ�����ȫƥ�䣬�м䲻���������ַ���������Ҫ���� words �е��ʴ�����˳��

		ʾ��1��
			����: s = "barfoothefoobarman", words = ["foo","bar"]
			���: [0,9]
			����: ������ 0 �� 9 ��ʼ���Ӵ��ֱ��� "barfoo" �� "foobar" ��
				�����˳����Ҫ, [9,0] Ҳ����Ч�𰸡�
		ʾ��2��
			����: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
			�����[]
*/

/*
	��������
		����⣬�� 3.�ַ��������� ���ƣ�ֻ����ÿ���ַ������򣬱����ÿ���ַ��������У�
		������ͬ���� words ��ÿ�����ʵĳ���Ϊ size��һ�� n �����ʣ���ô�̶��������ڴ�СΪ len = size*n��
		ÿ�λ������ڻ���ʱ�����ٽ���һ���ַ������ǽ���һ������Ϊ size �ĵ��ʡ�

		�����˼·���ԣ�
			ÿ���� s �У�����ָ�뿪ʼ��ȡ��С�� size ���ַ�����Ϊһ�����ʣ������û��ģ�
			������ָ���ڳ����ƶ���ʱ��Ҳ���ǻ������������ʱ�򣬲���һ�������� size��
				���� s = "aaabbbcccddd"��words = ["aab", "abb"]��size = 3��
				���һ�������� size����ôֻ�ܱ��������� aaa, bbb ,ccc, ddd�������ܱ��������� aab abb bbc ��Щ��
		������
			�� s ��ȡ����Ϊ length = size*n ���Ӵ�
				����ȡ [0, length - 1], [1, length], [2, length + 1]...[m-length, m-1]����Ϊ�Ӵ�ȥ�жϷ������ϣ�
				���� s = "aabbccdd", words = ["aa", "bb"]
				�ֱ�ȡs�е� aabb, abbc, bbcc, bccd, ccdd �����ж�
			����ж��Ӵ��Ƿ���ϣ�
				���Ӵ�����һ���������ַ�����ÿ�δ��Ӵ��н�ȡ����Ϊ size �ĵ��ʣ��ж��Ƿ���� words�У����ж������Ƿ�һ�£�
					��֮ǰ�ķ���һ�£���ε���ָ����ƣ�ֱ������ size������Ҳ����Ҫ��ָ���ˡ�

			ʱ�临�Ӷȣ���s�ĳ���Ϊm��words��ÿ�����ʳ���Ϊsize��һ��n�����ʣ�ÿ�δ�s��ȡ�Ӵ������жϣ�ȡ�� m - size*n�Σ�
				�ж�һ���Ӵ���ʱ�临�Ӷ�Ϊn�����ԣ��ܵ�ʱ�临�Ӷ�Ϊ O(m*n - size*n*n)��
					��Ϊ�Ǽ�������ֱ�Ӻ��Ժ���ģ����Ӷ�Ϊ o(m*n)

			�ռ临�Ӷȣ����� HashMap������ words ���� n �����ʣ����� O��n����

*/

func findSubstring(s string, words []string) []int {
	res := []int{}
	if s == "" || len(words) == 0 {
		return res
	}
	// n �����ʣ�ÿ�����ʵĳ���Ϊ size
	n, size := len(words), len(words[0])
	if len(s) < n*size {
		return res
	}

	// �������ڹ̶���С
	length := n * size
	mapWords := make(map[string]int)
	for _, word := range words {
		mapWords[word]++
	}

	//ȡ���±� i Ϊ��ͷ������Ϊ length ���Ӵ������жϣ����һ���Ӵ��Ŀ�ʼ�±�Ϊ len(s) - length
	for i := 0; i <= len(s)-length; i++ {
		//���жϵ�ʱ������������һ�� map ���������жϣ���Ȼ���ֱ���޸� mapWords �е�ֵ��ÿ��ȡ�µ��Ӵ�����Ҫ���³�ʼ�� mapWords
		mapHelp := make(map[string]int)
		have := 0 //�ж��ٸ����ʼ�����������
		for index := i; index < i+length; index += size {
			//ÿ�δ��Ӵ���ȡ��һ�����ʣ��ж��Ƿ��� words ��
			word := s[index : index+size]

			if _, ok := mapWords[word]; !ok {
				//û��������ʣ�ֱ����������Ӵ�
				break
			}

			mapHelp[word]++
			if mapHelp[word] == mapWords[word] {
				have++
			}
		}

		//����
		if have == len(mapWords) {
			res = append(res, i)
		}
	}
	return res
}
