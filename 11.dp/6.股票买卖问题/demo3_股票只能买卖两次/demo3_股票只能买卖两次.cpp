#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

/*
    题目：leetcode 123
        给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
        设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
        注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

        示例：
            输入：prices = [3,3,5,0,0,3,1,4]
            输出：6
            解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
                    随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
*/

/*
    1，dp
        k为2，根据demo0的状态转移方程
            dp[i][k][0] = max( dp[i-1][k][0], dp[i-1][k][1] + prices[i-1])
            dp[i][k][1] = max( dp[i-1][k][1], dp[i-1][k-1][0] - prices[i-1])

        下面是之前题目的dp解法
                for (int i = 1; i <= n; i++) {
                    dp[i][0] = max( dp[i-1][0], dp[i-1][1] + prices[i-1]);
                    dp[i][1] = max(dp[i - 1][1], -prices[i - 1]);
                }

        之前的题目，只遍历了天数，那是因为之前的题目中，k不再是影响因素，
            而手中是否持有股票，只有0和1两个值，把这两个值都列出来，也就省去了for循环的过程，
            但实质上，都列出来，也是穷举的过程
        本题有三个【状态】，除去可以穷举的手中是否持有股票，还需要用两个for循环把其他两个状态遍历一遍
            
            
*/

int dp(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;
    
    int k = 2;
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, 0)));
    //base case
    for(int i = 0; i <= n; i++) {
        dp[i][0][0] = 0;
        dp[i][0][1] = INT_MIN;
    }

    for(int i = 0; i <= k; i++) {
        dp[0][i][0] = 0;
        dp[0][i][1] = INT_MIN;
    }

    //遍历天数和k，将手里是否有股票列出来
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
            dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i - 1]);
        }       
    }

    return dp[n][k][0];
}

/*
    2，dp优化，在上面的题解中，我们说因为手里是否有股票，只有0和1两个有效值，所以不需要for循环遍历，直接都列出来。
        而在这道题中，k=2，有效值只有0和1，
        那么手里是否有股票和k的有效值个数相乘为4，发现数量也不大，可以直接都列出来，用4个变量保存。
*/

int dp_plus(vector<int> &prices) {
    int n = prices.size();
    if(n == 0) return 0;
    
    int k = 2;
    //base case
    int dp_1_0 = 0, dp_1_1 = INT_MIN;
    int dp_2_0 = 0, dp_2_1 = INT_MIN;

    //这里i就从0开始取了，prices数组的下标也要改一下
    for (int i = 0; i < n; i++) {
        //要注意，求 dp_1_0 会用 dp_1_1，所以，为了防止上一行数据被覆盖，要先计算 dp_1_0 再计算 dp_1_1
        //而求 dp_2_1 时，会用到上一行的数据 dp_1_0，要先计算完了 dp_2_1 之后再计算 dp_1_0
        //同样 dp_2_0 会用到 dp_2_1，要先计算 dP_2_0 再计算 dp_2_1
        dp_2_0 = max(dp_2_0, dp_2_1 + prices[i]);
        dp_2_1 = max(dp_2_1, dp_1_0 - prices[i]); 
        dp_1_0 = max(dp_1_0, dp_1_1 + prices[i]); 
        //dp_1_1 = max(dp_1_1, dp_0_0 - prices[i])，因为 dp_0_0为0，所以直接写成下面这种   
        dp_1_1 = max(dp_1_1, -prices[i]);       
    }

    //很明显，k越大，利润会越大
    return dp_2_0;
}


int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "dp:  " << dp(prices) << endl;
    return 0;
}