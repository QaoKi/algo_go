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
    这个问题，在背包问题中的 完全背包问题已经被提出过，本题并不强调是组合还是排列，所以可以用背包的思路解决，
        这里重提，因为也可以用爬楼梯的思路解决。
*/

/*
    方法1，暴力递归
    首先定义：
        F(S)：组成金额 S所需的最少硬币数量
        [c0...cn-1]：可选的 n 枚硬币面额值
        
    注意到这个问题有一个最优的子结构性质，
        假设我们知道组成金额S所需最少的硬币数，这些硬币中，最后一枚硬币的面值是 C。
    那么根据问题的最优子结构，转移方程应为：
        F(S) = F(S − C) + 1 （只要再加一枚硬币就可以）
    但我们不知道最后一枚硬币的面值是多少，所以我们需要枚举每个硬币面额值 c0，c1...cn-1，
        去当做最后一枚硬币，取所有结果中最小的值。
    
    这个思路和 demo1_组合总和4 中爬楼梯升级版的思路类似，都是取所有可能的值作为最后一个硬币，然后求结果。
    
    暴力递归就是最后一枚硬币选好了，再递归调用，去确定倒数第二枚硬币....，
    其实就是枚举所有的情况，先确定最后一枚，然后确定倒数第二枚...。只不过是用递归来实现的。

    画出递归树：coins = [1, 2, 5], amount = 11
                                      f(11)
                    f(10)             f(9)            f(6)
                f(9) f(8) f(5)   f(8) f(7) f(4)     f(5) f(4) f(1)
    复杂度：对每一层求最小值，比如第二层，要求出f(10)，f(9)，f(6)三者的最小值，复杂度为O(3)，第三层有3^2个数，复杂度为O(3^2)，
        树的高度不好确定，跟coins中数据的大小有关。复杂度肯定是指数级。

*/ 

int baoli(vector<int> &coins,int amount) {
    //base case
    if(amount < 0)
        return -1;
    if(amount == 0)
        return 0;

    int min = INT_MAX;
    //遍历每个硬币面额值，去当做最后一枚硬币
    for (int i = 0; i < coins.size(); i++) {
        //确定了最后一枚硬币，传给子函数，让子函数枚举倒数第二枚...
        //每种面额的硬币数量是无限的，所以coins数组不用变
        int res = baoli(coins, amount - coins[i]);
        //res是 F(S − C)的结果，注意，在和min比较之前，先不要 +1，因为res可能为负数
        if(res >= 0 && min > res + 1) {
            min = res  + 1;
        }
    }

    return min == INT_MAX ? -1 : min;
}

/*
    方法2，动态规划
        定义 dp 数组
            dp[i] 表示凑成总金额 i 所需的最少的硬币个数。
        状态转移方程
            和爬楼梯思路一样，假设最后一个硬币的+ 1金额为 C，那么 dp[i] = dp[i-C] + 1，而 C 的取值有多个，
                所以可以求出所有可能的 dp[i]，取最小的一个，
            所以，状态转移方程为 
                dp[i] = min(dp[i], dp[i-C] + 1)，(coins[0] <= C <= coins[coins.size()-1])
        base case
            1，因为状态转移方程用求的是 min，所以，我们考虑将 dp[i] 的值初始化为正无穷，这样就不会影响 min() 的值。
                但是，又不能直接定为正无穷，因为后面需要用到 dp[i][j-coins[i-1]] + 1，
                如果此时 dp[i][j-coins[i-1]] 是正无穷，加1会越界。
                
                可以考虑值初始化为 amount+1，凑成 amount 金额的硬币数最多只可能等于 amount（全用1元面值），
                所以初始化为 amount + 1 就相当于初始化为正无穷
            2，当 amount = 0 时，0个硬币可凑满，所以 dp[0] = 0，
    复杂度：
        时间复杂度为O(Sn)，空间复杂度为O(S)
*/

int dp(vector<int> &coins, int amount) {
    if(amount < 0)
        return -1;
    vector<int> dp(amount + 1, amount + 1);

    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        //i表示目前要求 dp[i] 了
        //遍历所有的面额
        for (int j = 0; j < coins.size(); j++) {
            if(i >= coins[j]) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }

     return (dp[amount] == amount + 1) ? -1 : dp[amount];
}

int main() {

    return 0;
}