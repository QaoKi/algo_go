package main

/*
	leetcode 50
	题目：
		实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，x^n）
		提示：
			-100.0 < x < 100.0
		示例 1：
			输入：x = 2.00000, n = 10
			输出：1024.00000
		示例 2：
			输入：x = 2.00000, n = -2
			输出：0.25000
			解释：2^(-2) = 1/(2^2) = 1/4 = 0.25
*/

/*
	方法1，暴力法，
		直接让 n 个 x 相乘，
		如果 n 为0，那么 ans = 1.0，所以 ans 初始值为 1.0
		如果 n 为负数，让结果取倒数（1/ans），

		时间复杂度 O(n)
*/

func myPow(x float64, n int) float64 {
	res := float64(1)
	if n == 0 {
		return res
	}

	num := n
	if n < 0 {
		num = -n
	}

	for i := 0; i < num; i++ {
		res *= x
	}
	//如果 n < 0，结果取倒数
	if n < 0 {
		res = 1 / res
	}
	return res
}

/*
	方法2，快速幂法（分治思想）：
		x^n = x^(n/2) * x^(n/2) = x^(n/4) * x^(n/4) * x^(n/4) * x^(n/4)
		因为 x^n = x^(n/2) * x^(n/2)，所以，我们可以先求出 x^2，设为 num，再让 num * num，就得到了x^4。
		比如要计算 x^64，可以按照：x -> x^2 -> x^4 -> x^8 -> x^16 -> x^32 -> x^64 的顺序，
			从 x 开始，每次直接把上一次的结果进行平方，计算 6 次就可以得到 x^64 的值，而不需要对 x 乘 63 次 x。

		如果 n 是奇数的话，比如要求 x^77，可以按照：x -> x^2 -> x^4 -> x^9 -> x^19 -> x^38 -> x^77 的顺序，
			在 x^4 -> x^9，x^9 -> x^19，x^38 -> x^77 这些步骤中，把上一次的结果进行平方后，还要额外乘一个 x。
		但是如果按照从左到右的方式求，我们不知道在将上一次的结果平方之后，还需不需要额外乘 x。
		如果我们从右往左看，分治的思想就十分明显了：
			1，当我们要求 x^n 时，可以先递归求出 y = x^(n/2)
			2，知道了 x^(n/2) 的值，根据 n 的值求 x^n
				如果 n 是偶数，那么 x^n = y^2；
				如果 n 是奇数，那么 x^n = y^2*x，再多乘一个 x
			3，递归的边界为 n = 0，任意数的 0 次方均为 1，n = 1 时，返回 x
	时间复杂度：O(logn)
	空间复杂度：O(logn)，即为递归的层数，消耗的栈空间。

	还有一个迭代法，空间复杂度优化到 O(1)，这里就不写了
*/

func dfs(x float64, n int) float64 {
	if n == 0 {
		return 1
	}

	if n == 1 {
		return x
	}

	//要求 x^n，先递归求出 x^(n/2)
	y := dfs(x, n/2)

	//再根据 n 的奇偶性确定 x^n
	if n%2 == 0 {
		return y * y
	}

	//如果是奇数，再多乘一个 x
	return y * y * x
}

func myPow1(x float64, n int) float64 {
	res := float64(1)
	if n == 0 {
		return res
	}

	if n < 0 {
		return 1 / dfs(x, -n)
	}

	return dfs(x, n)
}
