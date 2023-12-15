#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
    题目：leetcode 518
        给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 
    示例：
        输入: amount = 5, coins = [1, 2, 5]
        输出: 4
        解释: 有四种方式可以凑成总金额:
                5=5
                5=2+2+1
                5=2+1+1+1
                5=1+1+1+1+1
    这个问题和我们前面讲过的两个背包问题，有一个最大的区别就是，每个物品的数量是无限的，这就是「完全背包问题」
*/

/*
    经典的0-1背包问题，是挑选硬币，总金额是否能等于给定的 amount，这道题是求可以凑成总金额的组合数目。
    能凑成总金额是amount的组合数目是我们要求的结果值。
    【状态】：不变，依然是背包的容量和可挑选的物品
        F(N, S) = x，若只使用前N个物品，当背包容量为S时，有x种方法可以装满背包。
        用dp数组表示为 dp[n][s] = x
    【选择】：硬币选出来或者不选出来
    【base case】：
        1，如果S为0，那么只有不选任何的硬币才能达成条件，只有这一种方法，所以对于任意的 0 <= n <= N，dp[n][0] = 1        

    状态转移方程和0-1背包有所不同。
    如果不把第 n 个物品装入背包，也就是说不使用 coins[n-1] 这个面值的硬币，
        那么凑出面额 s 的方法数 dp[n][s] 应该等于dp[n-1][s]，继承之前的结果。
    如果把第n个物品装入了背包，也就是说决定使用 coins[n-1] 这个面值的硬币，那么 dp[n][s] 应该等于 dp[n][s-coins[n-1]]。
        因为硬币的数量是无限的，决定使用，但是没决定要使用多少次。所以，第一维度的 n 不要减1
    状态转移方程：
        F(N, S) = F(N - 1, S) + F( N, S - coins[N - 1] )
        转成dp数组的形式就为：dp[n, s] = dp[n-1][s] + dp[n][s - coins[n-1]]

    时间复杂度：O(N*amount)，空间复杂度 O(N*amount)
*/

class Solution {
public:
    int change(int amount, vector<int>& coins) {

        vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, 0));
        //base case
        for(int s = 0; s <= amount; s++) {
            dp[s][0] = 1; 
        }
        
        for (int n = 1; n <= coins.size(); n++){
            for (int s = 1; s <= amount; s++) {
                //不装进去 + 装进去
                dp[n][s] = dp[n - 1][s] + (s >= coins[n - 1] ? dp[n][s - coins[n-1]] : 0);
            }
        }
        return dp[coins.size()][amount];
    }
};

/*
    状态压缩，状态转移方程为
        dp[n, s] = dp[n-1][s] + dp[n][s - coins[n-1]]
    和 零钱兑换1 一样，第二层循环从前往后循环
*/

int change(int amount, vector<int>& coins) {
    //上一行数据
    vector<int> dp(amount + 1, 0);
    //base case
    dp[0] = 1;
    
    for (int i = 1; i <= coins.size(); i++){
        for (int j = 1; j <= amount; j++) {
            if(j >= coins[i - 1])
                dp[j] += dp[j - coins[i - 1]];
        }
    }
    return dp[amount];
}

int main() {
    return 0;
}