#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    股票问题，
*/
/*
    题目：leetcode 121
        给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
        如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
        注意：你不能在买入股票前卖出股票。

        示例：
            输入: [7,1,5,3,6,4]
            输出: 5  
            解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
                    注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
*/

/*
    1，dp
        限定了k=1，根据demo0的状态转移方程
            dp[i][1][0] = max( dp[i-1][1][0], dp[i-1][1][1] + prices[i-1])
            dp[i][1][1] = max( dp[i-1][1][1], dp[i-1][0][0] - prices[i-1])
        而根据base case，我们知道，dp[i][0][0] = 0，
        所以
            dp[i][1][1] = max( dp[i-1][1][1], -prices[i-1])
        发现k都是1，k已经不是对结果产生影响的【状态】了，去掉
        最终
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1])
            dp[i][1] = max( dp[i-1][1], -prices[i-1])

*/

int dp(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    //base case
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][1] = INT_MIN;
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1]);
        dp[i][1] = max(dp[i - 1][1], -prices[i - 1]);
    }

    return dp[n][0];
}

/*
    2，dp再优化：
        可以看出，第n行的数据，只有第n-1行数据有关，而每一行只有两个数据，
        所以可以采用两个变量，来保存上一行的两个数据
*/

int dp_plus(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;

    //base case
    // dp[i][0] = 0
    int dp_0 = 0;
    // dp[i][1] = INT_MIN
    int dp_1 = INT_MIN;

    //这里i就从0开始取了，prices数组的下标也要改一下
    for (int i = 0; i < n; i++) {
        dp_0 = max(dp_0, dp_1 + prices[i]);
        dp_1 = max(dp_1, -prices[i]);
    }

    return dp_0;
}

/*
    3，暴力法
        考虑一种简单的思路，要想差值最大，那么首先确定一个买入时间，然后去穷举后面的每一天作为卖出时间，取一个差值最大的。
*/

int baoli(vector<int> &prices) {
    int n = prices.size(), ans = 0;
    if(n == 0) return 0;
    //将每一天都作为买入时间去穷举
    for(int i = 0; i < n; i++) {    
        //将后面的每一天作为卖出时间，穷举一个最大值
        for(int j = i + 1; j < n; ++j) {
            ans = max(ans, prices[j] - prices[i]);
        }
    }

    return ans;
}

/*
    4，一次循环。
        假如计划在第 i 天卖出股票，那么最大利润的差值一定是在[0, i-1] 之间选最低点买入，
            用一个变量minPrice，保存在第 i 天时，第1天到第i-1天之间，历史最低价是多少，这样在第i天卖出时，利润最大。
        遍历数组，每一天作为第i天，依次求每个卖出时机的的最大差值，再从中取最大值

        注意：历史最低价的理解，历史最低价，不是整个数组中的最小值，而是当处于第i天时，[0, i-1] 之间的最小值
        方法3是先确定买入时间，再去穷举卖出时间，这种方法是先确定卖出时间，假设卖出时间是第i天，那么第i天卖出的最大利润
        就是 prices[i] - min( prices[0], prices[1] ... prices[i-1])

        其实是用到了动态规划的思想，
        在第 i 天卖出股票，所能获得的最大利润，等于当天的价格减去第1天到第i-1天之间的历史最低价。
        而知道了第1天到第i-1天之间的历史最低价 min，
        求 i+1 天时的最大利润时，只要将第i天的价格跟min比较，就能求出第1天到第i天之间的历史最低价。
            再用第i+1天当天的价格减去第1天到第i天之间的历史最低价，就能得到在第i+1天卖出的最大利润
*/

int maxProfit(vector<int>& prices) {

    if(prices.size() == 0) return 0;
    
    int ans = 0, minPrice = INT_MAX;
    for(int i = 0; i < prices.size(); i++) {
        //注意，此时的minPrice是[0, i-1]之间的最小值，
        //因为一天之内，只能买卖一次，所以历史最低价要在 [0, i-1]之间筛选
        //所以需要先求出最大利润，再更新历史最低价
        ans = max(ans, prices[i] - minPrice);
        minPrice = min(minPrice, prices[i]);
    }

    return ans;
}

int main() {
    return 0;
}