/**
 * @Name	: backtrack.cpp
 * @Date	: 2017-06-08-09.05.33
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.2
 */

#include "backtrack.h"

/**
 * 函数功能: 用回溯法求解TSP问题
 * 参数含义: g表示城市距离图,cur表示当前深度
 */
void backtrack::solve(const graph & g, int cur) {
	int n = g.getn();
	if (cur == n) {		// 到达深度n表示已经访问完
		double temp = val+g.getd(path[n-1], 0);	// 获取总代价
		if (best<0 || temp<best) {
			// 存在更优的解
			best = temp;
			for (int i=0; i<n; ++i)
				ans[i] = path[i];
		}
		return ;
	}
	for (int i=1; i<n; ++i)
		if (!vis[i]) {
			// 如果当前城市未访问
			double temp = g.getd(path[cur-1], i);	// 获取访问所需的代价
			if (best<0 || val+temp<best) {
				// 当前代价不大于当前最优解,深搜
				vis[i] = true;	// 标记
				val += temp;	// 加上所需的代价
				path[cur] = i;	// 记录顺序
				solve(g, cur+1);
				val -= temp;	// 回溯还原代价
				vis[i] = false;	// 回溯取消标记
			}
		}
}

/**
 * 函数功能: 输出回溯所求最优解
 * 参数含义: n表示城市个数
 */
void backtrack::out(const int & n) {
	std::cout << "回溯所求最优解为: " << best << std::endl;
	for (int i=0; i<n; ++i)
		std::cout << ans[i] << (" \n"[i==n-1]);
}
