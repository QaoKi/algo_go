package main

/*
    题目：
        给定一个数组nums，和一个整数K。如果可以任意选择nums中的
        数字，每个数字只能选择一次，能不能累加得到K，返回true或者false
*/

/*
    和 分割等和子集 类似，转成0-1背包问题：选取的物品的重量之和正好为背包总容量
    写出状态转移方程。
        F(N, K) = F(N-1, K) || F(N-1, K - nums[N-1])
    
    base case: 
        当 K=0，对于所有 0 <= i < n，都有dp[i][K] = true
*/ 

func dp(nums []int, K int) {
    dp := make([][]bool, )
}






bool dp(vector<int> &nums, int K) {
    if(K == 0) return true;
    int N = nums.size();
    if(N == 0) return false;

    vector<vector<bool>> dp(N + 1, vector<bool>(K + 1, false));

    //base case
    for (int i = 0; i < N; i++) {
        dp[i][0] = true;
    }

    for (int n = 1; n <= N; n++)
    {
        for (int k = 1; k <= K; k++)
        {
            //装或者不装
            dp[n][k] = dp[n - 1][k] || (k >= nums[n - 1] ? dp[n - 1][k - nums[n - 1]] + nums[n - 1] : false);
        }
    }

    return dp[N][K];
}

//状态压缩
bool dp2(vector<int> &nums, int K) {
    if(K == 0) return true;
    int N = nums.size();
    if(N == 0) return false;

    vector<bool> dp(K + 1, 0);
    dp[0] = true;
    for (int n = 1; n <= N; n++) {
        for (int k = K; k >= 1; k--) {
            //装或者不装
            dp[k] = dp[k] || (k >= nums[n - 1] ? dp[k - nums[n - 1]] : false);
        }
    }
    return dp[K];
}

func main() {
    
}