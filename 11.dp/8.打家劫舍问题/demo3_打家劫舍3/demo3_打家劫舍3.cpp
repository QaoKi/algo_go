#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


/*
	��Ŀ�� leetcode 337
		������ÿ���˼ң��Ƕ���������ʽ��Ҫ�󸸽ڵ���ӽڵ㲻��ͬʱ͵����������档
		ʾ����
			��ԭ���

*/

/*
	����ÿ���ڵ㣬��Ȼ������ѡ��͵���߲�͵��
		�����ǰ�ڵ�ѡ��͵����ô���������ӽڵ㶼������͵�ˣ�
		�����ǰ�ڵ�ѡ��͵����ô���������ӽڵ����ѡ��͵Ҳ����ѡ��͵��
	���Կ��������ڵ��ѡ����Ҫ���ݸ��ӽڵ㡣
	
	���ڵ�����ѡ���Ժ��ٴ����ӽڵ㣬�����Զ����£�������ѡ���Ե����ϣ����ݵķ�ʽ��
	������ӽڵ�����ѡ���Ժ�����ݣ��ݹ�����������ڵ㣬���ڵ�����ѡ���Ժ������ϴ��ݡ�
	�������������Ȼ�Ļ��ݹ��̣�����ʹ�ú������
		�����Ŀ�Ķ���������˼�룬ҲӦ������ 236 �� tree\demo18_�������������������

	1������״̬ת�Ʒ���
		�����ӽڵ���˵������ѡ��͵���߲�͵����������������������ڵ㴫��������ֵ������һ���ṹ�������棬����ֱ�ۡ�
		struct SNodeStatus {
			int selected;		//ѡ��͵�����ж���Ǯ
			int noSelected;		//ѡ��͵���ж���Ǯ
		};

		�赱ǰ�ڵ� node �յ���������������ֵ left����������������ֵ right��
		�����ǰ�ڵ�ѡ��͵����ô�ӽڵ�ֻ��ѡ��͵
			selected = node->val + left.noSelected + right.noSelected
		�����ǰ�ڵ�ѡ��͵����ô�ӽڵ����ѡ��͵��Ҳ����ѡ��͵��ȡ���ֵ
			noSelected = max(left.selected, left.noSelected) + max(right.selected, right.noSelected)
		Ȼ�󣬵�ǰ�ڵ�� {selected, noSelected} �������ĸ��ڵ�

		���գ����Ƿ��ظ��ڵ�� max(selected, noSelected)
	2��base case
		���ڵ�Ϊ NULL ʱ������ {0, 0}
*/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct SNodeStatus {
	int selected;		//ѡ��͵�����ж���Ǯ
	int noSelected;		//ѡ��͵���ж���Ǯ
};

class Solution {
public:

	SNodeStatus dfs(TreeNode * node) {
		if (node == NULL)
			return {0, 0};
		//�������������ֵ
		auto left = dfs(node->left);
		auto right = dfs(node->right);

		//��ǰ�ڵ�ѡ��͵�Ͳ�͵
		int selected = node->val + left.noSelected + right.noSelected;
		int noSelected = max(left.selected, left.noSelected) + max(right.selected, right.noSelected);
		return {selected, noSelected};
	}

    int rob(TreeNode* root) {
		auto status = dfs(root);
		return max(status.selected, status.noSelected);
	}
};

int main()
{
	return 0;
}