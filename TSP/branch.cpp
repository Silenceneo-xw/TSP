/**
 * @Name	: branch.cpp
 * @Date	: 2017-06-08-09.13.04
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.2
 */

#include <queue>
#include <cstring>
#include <algorithm>
#include "branch.h"

/**
 * 函数功能: 分支限界法求解TSP问题
 * 参数含义: g表示城市距离图
 */
void branch::solve(const graph & g) {
	double minsum = 0;	// 最小出边代价和
	int n = g.getn();
	// 求出每一个顶点的最小出边代价
	for (int i=0; i<n; ++i) {
		double temp = -1;
		for (int j=0; j<n; ++j) {
			if (j == i)
				continue;
			double t = g.getd(i, j);
			if (temp<0 || t<temp)
				temp = t;
		}
		minout[i] = temp;
		minsum += temp;
	}
	std::priority_queue<heap_node> q;
	heap_node p;
	// 初始化操作
	// 用贪心法求出上界
	best = 0;
	memset(p.vis, false, sizeof(p.vis));
	p.vis[0] = true;
	int u = 0;
	for (int i=1; i<n; ++i) {
		double temp = -1;
		int v = u;
		for (int j=1; j<n; ++j)
			if (!p.vis[j] && (temp<0||temp>g.getd(u, j))) {
				temp = g.getd(u, j);
				v = j;
			}
		p.vis[v] = true;
		best += temp;
		u = v;
	}
	best += g.getd(u, 0);
	v.clear();	// 清空当前解空间树
	p.cur = 1;	// 当前需要找第二个城市
	p.pre = -1;	// 当前结点没有父结点
	p.s = 0;	// 当前所在点:源点
	p.val = 0;	// 当前费用为0
	memset(p.vis, false, sizeof(p.vis));
	p.vis[0] = true;	// 源点访问过,其他均未访问
	p.lcost = 0;	// 当前下界为0
	p.rcost = minsum;// 当前剩余最小出边费用和
	q.push(p);
	while (!q.empty()) {
		p = q.top();
		q.pop();
		int head = v.size();// 记录父结点编号
		v.push_back(p);		// 放入当前解空间树中
		if (p.cur == n) {// 找到叶子结点,必为最优解
			int id = 1;
			ans[0] = p.s;
			while (p.pre != -1) {	// 一直找父结点直到根结点
				p = v[p.pre];
				ans[id++] = p.s;
			}
			std::reverse(ans, ans+n);
			return ;
		}
		if (p.cur == n-1) {// 叶子结点的父结点
			int id = 0;
			for (int i=1; i<n; ++i)
				if (!p.vis[i]) {
					id = i;
					break;
				}
			double t1 = g.getd(p.s, id);
			double t2 = g.getd(id, 0);
			if (!(p.val+t1+t2 > best)) {// 可能是最优解
				best = p.val+t1+t2;// 更新上界
				p.val = best;
				p.lcost = best;
				++p.cur;
				p.pre = head;	// 父结点编号
				p.s = id;		// 当前点
				q.push(p);		// 入队
			}
		}
		else {
			for (int i=1; i<n; ++i)
				if (!p.vis[i]) {// 扩展非叶结点
					double val = p.val+g.getd(p.s, i);	// 扩展代价
					double rcost = p.rcost-minout[p.s];	// 剩余最小出边费用和
					double lcost = rcost+val;	// 当前下界
					if (!(lcost > best)) {	// 下界不超过上界
						heap_node pp = p;
						++pp.cur;	// 访问下一个城市
						pp.lcost = lcost;	// 更新下界
						pp.pre = head;		// 更新父结点
						pp.rcost = rcost;	// 更新剩余最小出边费用和
						pp.s = i;			// 更新所在点
						pp.val = val;		// 更新当前代价
						pp.vis[i] = true;	// 标记该点被访问
						q.push(pp);			// 入队
					}
				}
		}
	}
}

/**
 * 函数功能: 输出分支限界所求最优解
 * 参数含义: n表示城市个数
 */
void branch::out(const int & n) {
	std::cout << "分支所求最优解为: " << best << std::endl;
	for (int i=0; i<n; ++i)
		std::cout << ans[i] << (" \n"[i==n-1]);
}
