/**
 * @Name	: greedy.cpp
 * @Date	: 2017-06-08-09.07.52
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#include <cstring>
#include "greedy.h"

/**
 * 函数功能: 贪心算法求解TSP问题
 * 参数含义: g表示城市距离图
 */
void greedy::solve(const graph & g) {
	// 初始化操作,初始在源点
	int n=g.getn(), u=0;
	memset(vis, false, sizeof(vis));
	vis[u] = true;
	best = 0;
	ans[0] = u;
	for (int i=1; i<n; ++i) {// 选取其余n-1个点
		double temp = -1;
		int v = u;
		for (int j=1; j<n; ++j)
			if (!vis[j] && (temp<0 || temp>g.getd(u, j))) {// 每次选取未访问的点且选择最短距离
				v = j;
				temp = g.getd(u, j);
			}
		vis[v] = true;
		ans[i] = v;
		best += temp;
		u = v;
	}
	// 最后一个点需要回到源点
	best += g.getd(u, 0);
}

/**
 * 函数功能: 输出贪心所求最优解
 * 参数含义: n表示城市个数
 */
void greedy::out(const int & n) {
	std::cout << "贪心所求最优解为: " << best << std::endl;
	for (int i=0; i<n; ++i)
		std::cout << ans[i] << (" \n"[i==n-1]);
}
