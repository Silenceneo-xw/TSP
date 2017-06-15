/**
 * @Name	: greedy.h
 * @Date	: 2017-06-08-09.06.43
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#ifndef __GREEDY_H__
#define __GREEDY_H__

#include "graph.h"

class greedy {
public:
	greedy() {}
	~greedy() {}

	void solve(const graph &);	// 贪心求解TSP问题
	void out(const int &);		// 输出所求最优解
protected:
	bool vis[graph::maxn];	// 标记城市是否被访问
private:
	double best;		// 所求最优解
	int ans[graph::maxn];// 对应的城市访问顺序
};

#endif // __GREEDY_H__
