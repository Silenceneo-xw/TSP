/**
 * @Name	: dynamic.cpp
 * @Date	: 2017-06-08-09.10.11
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#include "dynamic.h"

/**
 * 函数功能: 动规求解TSP问题
 * 参数含义: g表示城市距离图
 */
void dynamic::solve(const graph & g) {
	int n = g.getn();
	int len = (1<<(n-1))-1;
	for (int i=0; i<n; ++i)
		dp[i][0] = g.getd(i, 0);// 叶结点直接求解
	for (int j=1; j<len; ++j)	// 遍历除全集之外的所有集合
		for (int i=1; i<n; ++i)
			if (!(j & (1<<(i-1)))) {// i不在j集合中
				dp[i][j] = -1;
				for (int k=1; k<n; ++k)
					if (j & (1<<(k-1))) {// k要在j集合中
						double temp = g.getd(i, k)+dp[k][j&(~(1<<(k-1)))];// 状态转移方程为
																		// dp[i][j]=min{dp[i][j], d[i][k]+dp[k][j/k]},
																		// j/k表示j集合中去掉k,不是除
						if (dp[i][j]<0 || temp<dp[i][j]) {
							// 该状态有更优解
							dp[i][j] = temp;
							f[i][j] = k;	// 记录选择城市
						}
					}
			}
	// 结果单独处理一下,因为其满足不了上述条件
	dp[0][len] = -1;
	for (int k=1; k<n; ++k) {
		double temp = g.getd(0, k)+dp[k][len&(~(1<<(k-1)))];
		if (dp[0][len]<0 || temp<dp[0][len]) {
			dp[0][len] = temp;
			f[0][len] = k;
		}
	}
	best = dp[0][len];
	ans[0] = 0;
	int id = 1;
	// 根据择优记录不断得到所选城市
	for (int i=0, j=len; j>0; j=j&(~(1<<(i-1)))) {
		i = f[i][j];
		ans[id++] = i;
	}
}

/**
 * 函数功能: 输出动规所求最优解
 * 参数含义: n表示城市个数
 */
void dynamic::out(const int & n) {
	std::cout << "动规所求最优解为: " << best << std::endl;
	for (int i=0; i<n; ++i)
		std::cout << ans[i] << (" \n"[i==n-1]);
}
