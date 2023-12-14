#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

/*
    题目：leetcode 309
        给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
        设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
            1，你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
            2，卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

        示例：
            输入：[1,2,3,0,2]
            输出：3
            解释：对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
*/

/*
    1，dp
        可以买卖无数次，但是含有冷冻期，k为无数次，那么和demo2非常相似，但是含有冷冻期，所以要对状态转移方程做一些修改
        demo2的状态转移方程为
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1])
                解释：第i天结束以后，手里没有股票，可能的情况有
                    1，第i-1天结束后就没有股票，在第i天选择休息
                    2，第i-1天结束时有股票，在第i天选择把股票卖出，所以要加上收益
            dp[i][1] = max( dp[i-1][1], dp[i-1][0] - prices[i-1])
                解释：第i天结束以后，手里有股票，可能的情况有
                        1，第i-1天结束后就有股票，在第i天选择休息
                        2，第i-1天结束后没有股票，在第i天选择买入，所以收益要减去第i天的股票价格

        我们之前表示手里是否有股票时，用0表示当天结束以后手里没有股票，1表示当天结束以后手里有股票，
            现在再定义一个状态2，表示在当天把股票卖出了。所以，当天结束以后，手里没有股票，并且下一天处于冷冻期
                比如 dp[i][2]，表示在第i天把股票卖出，第i+1天处于冷冻期
        状态转移方程为：
            dp[i][0] = max( dp[i-1][0], dp[i-1][2])
                解释：第i天结束以后，手里没有股票，可能的情况有
                    1，第i-1天结束后就没有股票，第i天选择休息
                    1，第i-1天中把股票卖出，第i天处于冷冻期
            dp[i][1] = max( dp[i-1][1], dp[i-1][0] - prices[i-1])   
                解释：第i天结束以后，手里有股票，可能是第i-1天就有股票，第i天选择休息，也可能是第i-1天没有股票，第i天选择买入股票。
            dp[i][2] = dp[i-1][1] + prices[i-1]      
                解释：第i天结束以后，进入冷冻期，只能是第i-1天持有股票，第i天选择卖出
        很明显，最大值，应该在 dp[i][0] 和 dp[i][2]中选

    base case: 
        dp[n][0][0] = 0，当没有交易次数时，结果值依然为0
        dp[0][k][1] = INT_MIN，当没有天数时，不可能持有股票，结果值依然为 INT_MIN
        dp[0][k][2] = 0，可以理解成第0天买入又卖出，那么第0天后就是“不持股且当天卖出了”这个状态了，其收益为0
            
*/

int dp(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    //base case
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][1] = INT_MIN;
        dp[i][2] = 0;
    }

    //遍历天数和k，将手里是否有股票列出来
    for (int i = 1; i <= n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][2]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i - 1]);
        dp[i][2] = dp[i - 1][1] + prices[i - 1];
    }

    return max(dp[n][0], dp[n][2]);
}

/*
    状态压缩
*/
int dp_plus(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;

    //base case
    int dp_0 = 0;
    int dp_1 = INT_MIN;
    int dp_2 = 0;
    
    for(int i = 0; i < n; i++) {
        int dp_0_pre = dp_0;
        dp_0 = max(dp_0, dp_2);
        dp_2 = dp_1 + prices[i];
        dp_1 = max(dp_1, dp_0_pre - prices[i]);
    }

    return max(dp_0, dp_2);
}

/*
    2，dp优化，换一种思路
        我们再看demo2的状态转移方程
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1])
            dp[i][1] = max( dp[i-1][1], dp[i-1][0] - prices[i-1])
                解释：第i天结束以后，手里有股票，可能的情况有
                            1，第i-1天结束后就有股票，在第i天选择休息
                            2，第i-1天结束后没有股票，在第i天选择买入，所以收益要减去第i天的股票价格
        我们现在要加一个冷冻期，如果在第i天想买入股票，那么，第i天不能是冷冻期，也就是说不能在第i-1天卖出股票，
            那么只能选择在第 i-2 天及其之前的时间内卖出股票，也就是说在第 i-2 天结束后，手里是没有持有股票的状态。
        所以状态转移方程为：
            dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1])
                不用变，因为卖出的时间没有限制
            dp[i][1] = max( dp[i-1][1], dp[i-2][0] - prices[i-1])
                在第i-2天结束后，手里是没有股票的状态，才能在第i天买股票

                会有个疑问，在第i-1天结束后，手里没有股票的状态，也就是 dp[i-1][0] 的形成，可能是两个原因造成的，
                    1，在第i-2天结束后，手里没有股票，第i-1天什么也不做，这种是符合在第i天买股票的
                    2，在第i-2天结束后，手里有股票，第i-1天选择卖出，这种是不符合在第i天买股票的
                发现dp[i-1][0]，是有一种可能符合在第i天买股票的，为什么直接用 dp[i-2][0]代替了dp[i-1][0]？
                    这是因为，原因1 虽然符合在第i天买股票，但仔细看它的条件：在第i-2天结束后，手里没有股票，这不就是dp[i-2][0]吗，
                        并且在第i-1天什么也不做，原因1 的结果值，还是继承了dp[i-2][0]，所以，可以直接用 dp[i-2][0]代替dp[i-1][0]

*/

int dp2(vector<int> &prices, int k) {
    int n = prices.size();
    if(n == 0) return 0;

    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    //base case
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][1] = INT_MIN;
    }

    //遍历天数和k，将手里是否有股票列出来
    for (int i = 1; i <= n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
        dp[i][1] = max(dp[i - 1][1], (i >= 2 ? dp[i - 2][0] : 0) - prices[i - 1]);
    }

    return dp[n][0];
}

/*
    状态压缩，需要用到上一行的两个数据，和上上行的一个数据
*/
int dp2_plus(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;

    //base case
    int dp_0 = 0;
    int dp_1 = INT_MIN;
    int dp_0_pre = 0;   //上上行的一个数据
    
    for(int i = 0; i < n; i++) {
        int temp = dp_0;
        dp_0 = max(dp_0, dp_1 + prices[i]);
        dp_1 = max(dp_1, dp_0_pre - prices[i]);
        dp_0_pre = temp;
    }

    return dp_0;
}

int main() {
    return 0;
}