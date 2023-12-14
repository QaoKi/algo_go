#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 354
    给定一些标记了宽度和高度的信封，宽度和高度以整数对形式 (w, h) 出现。
    当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。

    请计算最多能有多少个信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
    说明:
        不允许旋转信封。
    示例：
        输入: envelopes = [[5,4],[6,4],[6,7],[2,3]]
        输出: 3 
        解释: 最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。

*/

/*
    这道题目其实是 最长递增子序列 的一个变种，因为很显然，每次合法的嵌套是大的套小的，
        相当于找一个最长递增的子序列，其长度就是最多能嵌套的信封个数。
    但是难点在于，标准的 LIS 算法只能在数组中寻找最长子序列，而我们的信封是由(w,h)这样的二维数对形式表示的，如何把 LIS 算法运用过来呢？

    思路：首先要明确，只有宽度和高度都大于的时候才能装进去，相等的是无法装进去的
        1，将信封按照宽度 w 进行升序排列，这样在宽度上后面的信封一定可以放下前面的信封
        2，宽度 w 相同的信封，按照高度 h降序排列
        3，按照高度 h 进行LIS计算即可
    理解：
        我们需要提取高度h进行 LIS计算：
        我们考虑输入 [[1，2]，[1，4]，[1，5]，[2，3]]，如果我们直接对 h 进行 LIS 算法，
            我们将会得到 [2，4，5]，显然这不是我们想要的答案，因为 w 相同的信封是不能够套娃的（他们的w都是1）。
        为了解决这个问题。我们可以按 w 进行升序排序，若 w 相同则按 h 降序排序。
            则上述输入排序后为 [[1，5]，[1，4]，[1，2]，[2，3]]，再对 h 进行 LIS 算法可以得到 [2，3]，长度为 2，是正确的答案
*/

static bool cmp(const vector<int> &a, const vector<int> &b) {
    //宽度w是a[0]，高度h是a[1]
    if(a[0] == b[0])
        return a[1] > b[1];
    else
        return a[0] < b[0];
}

int dp(vector<vector<int>>& envelopes) {
    if(envelopes.empty()) return 0;

    sort(envelopes.begin(), envelopes.end(), cmp);

    //提取高度进行LIS计算，高度值为 envelopes[...][1]，size为 envelopes.size()

    //dp[i]定义为以 nums[i]为结尾的子序列，最长的递增子序列的长度

    //base case 初始化值为1（当递增子序列只有它自己）
    vector<int> dp(envelopes.size(), 1);
    for (int i = 1; i < envelopes.size(); i++) {
        for (int j = 0; j < i; j++) {
            //在所有的nums[i]大于nums[j]中，找一个dp[j]最大的
            if(envelopes[i][1] > envelopes[j][1])
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    //找dp数组中最大的值
    int res = INT_MIN;
    for(auto num : dp)
        res = max(res, num);

    return res;
}

/*
    方法2，贪心 + 二分查找
*/

int greed(vector<vector<int>>& envelopes) {
    if(envelopes.empty()) return 0;

    sort(envelopes.begin(), envelopes.end(), cmp);

    vector<int> tails(envelopes.size(), 0);

    int len = 0;
    for (int i = 0; i < envelopes.size(); i++) {
        int left = 0, right = len - 1;
        while(left <= right) {
            int mid = (left + right) >> 1;
            if(tails[mid] >= envelopes[i][1])
                right = mid - 1;
            else
                left = mid + 1;
        }

        if(left < len && tails[left] >= envelopes[i][1])
            tails[left] = envelopes[i][1];
        else
            tails[len++] = envelopes[i][1];
    }

    return len;
}

int main() {
    return 0;
}