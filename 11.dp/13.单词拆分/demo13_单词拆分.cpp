#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;


/*
	��Ŀ�� leetcode 139
		����һ���ǿ��ַ��� s ��һ�������ǿյ��ʵ��б� wordDict��
		�ж� s �Ƿ���Ա��ո���Ϊһ���������ֵ��г��ֵĵ��ʡ�
		˵����
			���ʱ�����ظ�ʹ���ֵ��еĵ��ʡ�
			����Լ����ֵ���û���ظ��ĵ��ʡ�
		ʾ�� 1��
			����: s = "applepenapple", wordDict = ["apple", "pen"]
			���: true
			����: ���� true ��Ϊ "applepenapple" ���Ա���ֳ� "apple pen apple"��
     			ע��������ظ�ʹ���ֵ��еĵ��ʡ�
		ʾ�� 2��
			����: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
			���: false
*/

/*
	����1������
		�ͻ�����Ŀ�� �ָ���Ĵ� һ����ö���ַ��������зָ����ȥ wordDict ��ƥ�䣬
		�����ַ�����˵�����Էָ�һ���ַ���Ҳ���Էָ������ַ���
	ʱ�临�Ӷȣ�O(2^n)
	�ռ临�Ӷȣ�O(n)���ݹ�ջ�������ռ� set
*/

class Solution {
public:
	bool dfs(string s, unordered_set<string> &unset,int startIndex) {
		//��⵽�����
		if (startIndex >= s.length() - 1)
			return true;

		//ÿ�ο���ѡ����һ���ַ��������������ַ����������������԰� s ʣ����ַ�����������
		//��ʣ s.length() - startIndex ���ַ�
		//������������ַ������� unset �У���sʣ�µ��ַ��������ݹ顣
		for (int i = 1; i <= s.length() - startIndex; i++) {
			string str = s.substr(startIndex, i);
			if (unset.find(str) == unset.end()) {
				continue;
			}
			//�����ݹ�
			if (dfs(s, unset, startIndex + i))
				return true;
		}

		return false;
	}

    bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> unset(wordDict.begin(), wordDict.end());
		return dfs(s, unset, 0);
	}
};

/*
	����2�����仯�ݹ�
		�����ݹ���ڴ������ظ����㣬��α����Щ�ظ����㣬Ҳ��һ�����顣
		�������⣬���� s = "abcdefg"��wordDict = ["a", "b", "ab"]
			�����ǽ� "a" �ָ���������Ҫ�ٵݹ�ȥ�� "bcdefg"�� 
				�ٽ� "b" �ָ���������Ҫ�ٵݹ�ȥ�� "cdefg"�� 
			�����ݻ��������ǽ� "ab" �ָ���������Ҫ�ٵݹ�ȥ�� "cdefg"��
			��ʱ�Ͳ������ظ����� "cdefg"��
		ʹ��һ������ memory ����ÿ�μ������ startIndex ��ʼ���ַ����ļ�������
		��� memory[startIndex] ���Ѿ�����ֵ�ˣ�ֱ���� memory[startIndex] �Ľ����
		������������У�"cdefg" ���� s[2] Ϊ��ʼ���ַ������������Ľ�������� memory[2]��
		����Ҳ������ map<string, bool> �����棬ֻ����������
*/

class Solution {
public:
	bool dfs(string s, unordered_set<string> &unset, vector<int> &memory, int startIndex) {
		//��⵽�����
		if (startIndex > s.length() - 1)
			return true;

		//���֮ǰ�Ѿ��������ֱ����
		if (memory[startIndex] != -1)
			return memory[startIndex];

		for (int i = 1; i <= s.length() - startIndex; i++) {
			string str = s.substr(startIndex, i);
			if (unset.find(str) == unset.end()) {
				continue;
			}
			//�����ݹ�
			if (dfs(s, unset, memory, startIndex + i)) {
				//���ַָ����
				memory[startIndex] = 1;
				return true;
			}
				
		}
		//���ַָ��
		memory[startIndex] = 0;
		return false;
	}

    bool wordBreak(string s, vector<string>& wordDict) {
		//��ʼֵΪ -1����ʾû�м������ֵ 0 ��ʾ���ַָ�У�ֵ 1 ��ʾ���ַָ����
		vector<int> memory(s.length(), -1);
		unordered_set<string> unset(wordDict.begin(), wordDict.end());
		return dfs(s, unset, memory, 0);
	}
};

/*
	����3����̬�滮
	
	���� dp ����
		dp[i] ��ʾ�ַ��� s ��ǰ i ���ַ���ɵ��Ӵ� s[0..i-1] �Ƿ��ܱ��ո��ֳ����ɸ��ֵ��г��ֵĵ��ʡ�
	״̬ת�Ʒ���
		����� dp[i]��
			�����Ӵ� s[0...i-1]�����ǽ����������֣�s[0...j-1] �� s[j...i-1]��������Ҫ������������Ƿ񶼺Ϸ���
			����ǰ�벿�� s[0...j-1]���ϲ��Ϸ���ʵ���� dp[j]����ʱ����� dp[j] ���� true��
				���� s[j...i-1] ��ɵĵ����� wordDict �У���ô����� dp[i] = true��
			�� j ��ȡֵ��ΧΪ [0, i-1]������ö��ÿһ�������ֻҪ��һ�������ʹ�� 
				dp[j] == true && s[j...i-1] �� wordDict �У���ô���� dp[i] = true��
	base case
		dp[0] = true������ַ���Ϊ�գ�˵�������ڵ��ʱ��У�����������һЩǣǿ���ӵݹ鹫ʽ�п��Կ�����
			dp[i] ��״̬���� dp[j] �Ƿ�Ϊtrue����ô dp[0] ���ǵݹ�ĸ�����dp[0]һ��ҪΪtrue������ݹ���ȥ���涼����false�ˡ�
		
		�ڲ���ַ�����ʱ���ǲ��ǿ��Բ�� s[0...j] �� s[j+1...i-1] ��
			s[0...j] �Ƿ�Ϸ��������� dp[j+1]�����ԣ��ж�������Ϊ
			��� dp[j+1] Ϊtrue������ s[j+1...i-1] �� wordDict �У���ô����� dp[i] = true��
		˼·�ǶԵģ�����д�����ʱ�򣬾ͷ��֣�base case �У�ֻ��ʼ���� dp[0]������ j �����ܴ� -1 ��ʼѭ����
			���� dp[j+1] ������Ϊ 0 ��Ҳ���ò��� dp[0]������ dp ���������ֵ���� false�����Խ���϶�ȫ�� false��
		���ԣ�Ҫ��� s[0...j-1] �� s[j...i-1]�������� j �� 0 ��ʼ����Ȼ�� 0 ��ʼѭ����ǰ�벿���� s[0...-1]�����Ͳ�ͨ��
			����Ϊ��Ҫ���� dp[0]�����ò�������
	ʱ�临�Ӷȣ�O(n^2)
	�ռ临�Ӷȣ�O(n)	

*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
		//��һ����ϣ�浥�ʣ�������� s[j...i-1] �Ƿ��� wordDict ��
		unordered_set<string> unset(wordDict.begin(), wordDict.end());

		int n = s.length();
		vector<bool> dp(n + 1, false);
		dp[0] = true;

		//���ѭ������ dp[i]
		for (int i = 1; i <= n; i++) {
			//j��ȡֵ��ΧΪ [0, i-1]��ö��j��ȡֵ���ж�ÿһ�� s[0...j-1] �� s[j...i-1] �����
			for (int j = 0; j < n; j++) {
				//�Ż������ dp[j] == false��˵����������� dp[i] ������Ϊ true
				if (dp[j] == false) continue;
				//��ȡ s[j...i-1]
				string str = s.substr(j, i - j);
				if (dp[j] == true && unset.count(str) > 0) {
					dp[i] = true;
					//dp[i] Ϊ true�ˣ����������ˣ�ֱ������������ȥ��dp[i+1]
					break;
				}
			}
		}

		return dp[n];
	}
};

int main()
{
	return 0;
}