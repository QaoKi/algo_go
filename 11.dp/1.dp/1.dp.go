package main

/*
	动态规划：
		动态规划比较适合用来求解最优问题，比如求最大值、最小值等等。
	动态规划思路：把问题分解为多个阶段，每个阶段对应一个决策。我们记录每一个阶段可达的状态集合（去掉重复的），
				然后通过当前阶段的状态集合，来推导下一个阶段的状态集合，动态地往前推进。
	动态规划理论：
		一个模型三个特征。
		一个模型：
			多阶段决策最优解模型：我们一般是用动态规划来解决最优问题。而解决问题的过程，需要经历多个决策阶段。
				每个决策阶段都对应着一组状态。然后我们寻找一组决策序列，经过这组决策序列，能够产生最终期望求解的最优值。
		三个特征：
			1，最优子结构：最优子结构指的是，问题的最优解包含子问题的最优解。反过来说就是，我们可以通过子问题的最优解，推导出问题的最优解。
						子问题之间相互独立。
			2，无后效性，无后效性有两层含义，第一层含义是，在推导后面阶段的状态的时候，我们只关心前面阶段的状态值，
				不关心这个状态是怎么一步一步推导出来的。第二层含义是，某阶段状态一旦确定，就不受之后阶段的决策影响。
			3. 重复子问题：在暴力递归中，存在大量重复计算的结果值
	写出状态转移方程是最难的，如何思考写出方程？
	明确以下内容：
		明确我们要求的最终结果是什么。
		【状态】：影响结果的因素是什么，根据这些因素，定义dp数组。
		【选择】：对于每个状态，可以做出什么选择改变当前结果
		【base case】：临界情况

*/
func main() {
}
