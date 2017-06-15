/**
 * @Name	: dynamic.h
 * @Date	: 2017-06-08-09.08.53
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#ifndef __DYNAMIC_H__
#define __DYNAMIC_H__

#include "graph.h"

class dynamic {
public:
	dynamic() {}
	~dynamic() {}

	void solve(const graph &);	// 动规求解TSP问题
	void out(const int &);	// 输出所求最优解
public:
	static const int maxn = 20;	// 最大城市数目
protected:
	double dp[maxn][1<<maxn];	// 状态表示,dp[i][j]表示从i经过j中所有点后回到源点的最短距离
	int f[maxn][1<<maxn];		// 择优记录状态所选的对应城市
private:
	double best;	// 所求最优解
	int ans[maxn];	// 对应的城市访问顺序
};

#endif // __DYNAMIC_H__
