/**
 * @Name	: backtrack.h
 * @Date	: 2017-06-08-09.03.52
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.2
 */

#ifndef __BACKTRACK_H__
#define __BACKTRACK_H__

#include "graph.h"

class backtrack {
public:
	backtrack() {}
	~backtrack() {}

	// 重置最优解,根据回溯的原理,其余值不需要
	void reset() { best = -1; }
	void solve(const graph &, int);	// 回溯求解TSP问题
	void out(const int &);		// 输出所求最优解
protected:
	double val;	// 当前代价
	bool vis[graph::maxn];// 标记城市是否被访问
	int path[graph::maxn];// 当前城市访问顺序
private:
	double best;		// 所求最优解
	int ans[graph::maxn];// 对应的城市访问顺序
};

#endif // __BACKTRACK_H__
