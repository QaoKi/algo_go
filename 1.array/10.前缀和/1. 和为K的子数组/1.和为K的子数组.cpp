#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include <vector>
#include <unordered_map>
using namespace std;

/*
    leetcode 560
    题目：
        给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
        说明 :
            1，数组的长度为 [1, 20,000]。
            2，数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。
        示例 1 :
            输入:nums = [1,1,1], k = 2
            输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
*/

/*
    方法1，暴力法
        依次以数组中每个元素为起始元素，和后面的元素进行累加，
        枚举出所有的子数组 [left...right] 的累加和，判断是否等于 k
    
    时间复杂度：O(n^2)
    空间复杂度：O(1)
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        for (int left = 0; left < n; left++) {
            //依次以每个元素为起始元素，计算区间 [left...right] 累加和
            int sum = 0;
            for (int right = left; right < n; right++) {
                sum += nums[right];
                if (sum == k) {
                    ans++;
                }
            }
        }
        return ans;
    }
};

/*
    方法2，前缀和
    
    这里引出了一个新的概率：前缀和，前缀和思想经常用在求子数组和子串问题上
        设 nums 长度为 n，我们通过前缀和数组 presum 保存前 n 位的和，
        具体就是 presum[n] 保存的是 nums 数组中前 n 位的和，
            也就是 presum[1] = nums[0]
                   presum[2] = nums[0] + nums[1] = presum[1] + nums[1]。依次类推
        通过前缀和数组，我们就可以得到每个区间之间的和。
            比如我们想得到子数组 nums[2] 到 nums[4] 的和，
                presum[5] = nums[4] + nums[3] + nums[2] + nums[1] + nums[0]
                presum[2] = nums[1] + nums[0]
                直接用 presum[5] - presum[2] 就得到 nums[4] + nums[3] + nums[2]。
    
    我们现在要做的是求出所有的子数组 [left...right] 的累加和，检查是否等于 k，如果等于 k，ans++
    有了前缀和数组，从上面得到子数组 nums[2] 到 nums[4] 和的例子，我们知道，
        子数组 [left...right] 的累加和就等于 presum[right + 1] - presum[left]
    
    总结：
        这道题虽然有了前缀和的思路，解题思路有了，但是边界情况要注意，
            因为 presum[i] 保存的是 nums[0] + .. nums[i-1] 的数据。
            其实也可以让 presum[i] 保存 nums[0] + ... nums[i] 的数据。
                这样更好理解，但是写代码时要处理更多的边界情况。

    时间复杂度：O(n^2)
    空间复杂度：O(n)
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        //构建前缀和
        vector<int> presum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            presum[i + 1] = presum[i] + nums[i];
        }

        //子数组 [left...right] 的累加和等于 presum[right + 1] - presum[left]
        //left 的取值范围为 [0...n-1]，right 的取值范围为 [left...n-1]
        for (int left = 0; left < n; left++) {   
            for (int right = left; right < n; right++) {
                if (presum[right  + 1] - presum[left] == k)
                    ans++;
            }
        }

        return ans;
    }
};

/*
    方法3，前缀和 + 哈希表
    方法2 的时间复杂度，比起 方法1 并没有得到优化，依然是 O(n^2)，并且空间复杂度为 O(n)
    其实我们不用特意求出 presum 数组，我们不关心具体是哪两项的前缀和之差等于 k，
        只关心等于 k 的前缀和之差出现的次数 count，就知道了有 count 个子数组求和等于k。
    我们判断成立的条件是 presum[right + 1] - presum[left] == k，如果条件成立，我们就让 ans++，
        在构造前缀和数组的时候，我们是从前往后遍历数组，那么 presum[left] 是先于 presum[right+1] 被构造出来。
        也就是用后面项的前缀和，减去前面项的前缀和 
    
    运用这层关系，
        1，遍历数组，计算每一项的前缀和，用 map 记录其出现的次数，
            比如当前项 i 的前缀和为 presum[i]，那么就让 map[presum[i]]++，表示前缀和 presum[i] 出现的次数加 1。
        2，当前项 i 的前缀和为 presum[i]，他如果想要和某一项的前缀和之差等于 k，
            也就是 presum[i] - x = k，那么另一项的前缀和 x 必须等于 presum[i] - k。
        3，我们在 map 中存储了前缀和出现的次数，去 map 中查看是否存在键是 presum[i] - k 的数据，
            如果存在，此时满足满足了，让 ans += map[presum[i] - k]。

    需要注意的是，如果当前项的前缀和 presum[i] 本身就等于 k，此时 presum[i] - k 等于 0，
    所以去 map 中查找 0 时，应该返回 1，所以初始化时 map[0] = 1

    时间复杂度：O(n)
    空间复杂度：O(n)
*/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        //记录前缀和 x 出现的次数
        unordered_map<int, int> unmap;
        unmap[0] = 1;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            //该项的前缀和
            sum += nums[i];
            //是否存在键为 sum - k 的数据
            if (unmap.count(sum - k)) {
                ans += unmap[sum - k];
            }

            //增加该前缀和出现的次数
            unmap[sum]++;
        }

        return ans;
    }
};

int main()
{
    return 0;
}