/**
 * @Name	: branch.h
 * @Date	: 2017-06-08-09.11.33
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.2
 */

#ifndef __BRANCH_H__
#define __BRANCH_H__

#include <vector>
#include "graph.h"

class branch {
public:
	branch() {}
	~branch() {}

	void solve(const graph &);	// 分支限界求解TSP问题
	void out(const int &);		// 输出所求最优解
protected:
	class heap_node {
	public:
		// 代价小的先出队列
		bool operator < (const heap_node & p) const { return lcost > p.lcost; }
	private:
		bool vis[graph::maxn];	// 标记顶点是否被访问
		double lcost;	// 子树费用的下界
		double rcost;	// 未访问顶点最小出边费用和
		double val;		// 当前费用
		int cur, pre, s;// 当前访问的节点数,当前节点的父节点编号,当前城市
		friend class branch;
	};
	std::vector<heap_node> v;	// 存储当前解空间树的结点
	double minout[graph::maxn];	// 各城市的最小出边费用
private:
	double best;	// 所求最优解
	int ans[graph::maxn];// 对应的城市访问顺序
};

#endif // __BRANCH_H__
