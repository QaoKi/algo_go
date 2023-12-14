#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;

/*
    题目：leetcode 322
        给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
        如果没有任何一种硬币组合能组成总金额，返回 -1。你可以认为每种硬币的数量是无限的。
        示例 1：
            输入：coins = [1, 2, 5], amount = 11
            输出：3 
            解释：11 = 5 + 5 + 1
*/

/*
    完全背包问题 与 0-1 背包问题的区别在于，完全背包问题中，每个物品无数个，可以无限次的选择。
*/

/*
    给定不同面额的硬币 coins（不同重量的物品） 和一个总金额 amount（背包总重量），
    计算可以凑成总金额（背包总重量）所需的最少的硬币（物品）个数。
    因为硬币（物品）是无数的，所以这是一个完全背包问题。

    【状态】：背包的容量和可挑选的物品
        定义 dp[i][j] = x，若只使用前i个硬币（物品），当背包容量为j时，最少需要 x 个物品（硬币）可以装满背包。
    【选择】：硬币选出来或者不选出来
    
    如果不把第i个物品装入背包，也就是说不使用coins[i-1]这个面值的硬币， 
        那么凑出面额 j 的方法数 dp[i][j] 应该等于dp[i-1][j]，继承之前的结果。  
    如果把第i个物品装入了背包，也就是说决定使用 coins[i-1] 这个面值的硬币，
        那么dp[i][j] 应该等于 dp[i][j-coins[i-1]] + 1。
        因为硬币的数量是无限的，决定使用，但是没决定要使用多少次。所以，第一维度的 i 不要减1
    所以【状态转移方程】：
        dp[i, j] = min( dp[i-1][j], dp[i][j-coins[i-1]] + 1 )

    【base case】：
        1，如果 amount 为0，那么只需要 0 个硬币就能凑成，所以 dp[i][0] = 0, 0 <= i <= N
        2，如果 coins 为0，没有硬币可选，那么很明显，除非 amount为0，否则不可能凑成，所以 dp[0][j] = -1, 1 <= j <= amount
            但是注意，初始值不能设为-1，因为转移方程是求min，用-1会影响结果，所以要设为较大值，在最终返回结果值的时候判断一下即可
        3，虽然要设为一个较大值，但是不能设为正无穷，因为在计算的时候，需要用到 dp[i][j-coins[i-1]] + 1，
            如果此时 dp[i][j-coins[i-1]] 是正无穷，加1会越界
        


*/
int dp2(vector<int> &coins, int amount) {

    if(amount < 0)
        return -1;

    int n = coins.size();
  
    //值初始化为amount+1，凑成amount金额的硬币数最多只可能等于amount（全用1元面值），所以初始化为amount + 1就相当于初始化为正无穷
    //这里不能直接初始化为正无穷，因为后面可能会出现 dp[i][j] + 1的情况，那样的话就越界了。
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));

    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;

    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= amount; j++) {
            //不选
            int no_in = dp[i - 1][j];
            int in = INT_MAX;
            if(j >= coins[i - 1]) {
                //选出来
                in = dp[i][j - coins[i - 1]] + 1;
            }
            dp[i][j] = min(no_in, in);
        }
    }

     return dp[n][amount] > amount ? -1 : dp[n][amount];
}

/*
    状态压缩
        状态转移方程为：
            dp[i, j] = min( dp[i-1][j], dp[i][j-coins[i-1]] + 1 )
            当前行的数据，只与上一行的下标j，和当前行的下标 j-coins[i-1] 有关，coins[i-1]是大于0的，
            所以，只和当前行的下标j 数据，只和上一行的下标j 数据、当前行的低位数据有关，
            所以，第二层循环，从前往后，先把当前行的低位数据求出来
        有的问题的状态压缩，dp空间可以少申请一个，比如二维数组的时候申请为 dp(amount+1)，而状态压缩以后申请 dp(amount)
        这道题这样的话会导致一些错误，所以，以后还是不为了省劲，直接多申请一个内存，防止出错
    
    总结：
        可以看出，0-1背包问题的状态压缩，第二维遍历是从后往前的，
        而完全背包问题的状态压缩，第二维遍历是从前往后的。
*/

int dp2(vector<int> &coins, int amount) {
    if(amount < 0) 
        return -1;

    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for(int i = 1; i <= coins.size(); i++) {
        for(int j = 1; j <= amount; j++) {
            //不选
            int no_in = dp[j];
            int in = INT_MAX;
            if(j >= coins[i - 1]) {
                //选出来
                in = dp[j - coins[i - 1]] + 1;
            }

            dp[j] = min(no_in, in);
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}

int main() {

    return 0;
}