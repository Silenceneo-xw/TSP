/**
 * @Name	: genetic.cpp
 * @Date	: 2017-06-08-09.15.25
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.2
 */

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "genetic.h"

/**
 * 函数功能: 产生初始群体
 * 参数含义: n表示城市个数
 */
void genetic::produce(const int & n) {
	std::vector<int> v(n);
	for (int i=0; i<n; ++i)
		v[i] = i;
	for (int i=0; i<maxm; ++i) {
		std::random_shuffle(v.begin(), v.end());
		popu[i].cities = v;
	}
}

/**
 * 函数功能: 显示初始群体
 * 参数含义: n表示城市个数
 */
void genetic::show_init(const int & n) {
	std::cout << "Initial population:" << std::endl;
	for (int i=0; i<maxm; ++i) {
		for (int j=0; j<n; ++j)
			std::cout << std::setw(4) << popu[i].cities[j] << " ";	// 打印初始群体
		std::cout << popu[i].ada << std::endl;
	}
	std::cout << std::endl;
}

/**
 * 函数功能: 计算个体适应度
 * 参数含义: g表示城市距离图
 */
void genetic::fit(const graph & g) {
	double all = 0;		// 群体总路径
	int n = g.getn();
	for (int i=0; i<maxm; ++i) {
		double sum = 0;
		for (int j=0; j<n; ++j) {
			int u = popu[i].cities[j];
			int v = popu[i].cities[(j+1)%n];
			sum += g.getd(u, v);// 个体的路径求和
		}
		popu[i].ada = sum;	// 个体路径总和
		all += sum;			// 群体路径总和
	}
	double sump = 0;
	for (int i=0; i<maxm; ++i) {
		popu[i].p = 1.0-popu[i].ada/all;// 路径越短,幸存率越大
		sump += popu[i].p;
	}
	for (int i=0; i<maxm; ++i)
		popu[i].p /= sump;
}

/**
 * 函数功能: 精英保存策略
 */
void genetic::elite_preserved() {
	int maxid=0, minid=0;
	for (int i=1; i<maxm; ++i) {
		if (popu[i].p > popu[maxid].p)
			maxid = i;
		if (popu[i].p < popu[minid].p)
			minid = i;
	}
	std::swap(popu[maxid], popu[maxm-1]);
	std::swap(popu[minid], popu[maxm-2]);
	popu[maxm-2] = popu[maxm-1];
}

/**
 * 函数功能: 选择运算操作
 */
void genetic::select() {
	double p[maxm];		// 赌轮选择的概率分布
	indiv temp[maxm];	// 临时群体
	int m = maxm-2;		// 不包括精英
	double sump = 0;
	for (int i=0; i<m; ++i) {
		p[i] = popu[i].p;
		sump += p[i];
	}
	for (int i=0; i<m; ++i)
		p[i] /= sump;	// 总概率要为1
	for (int i=1; i<m; ++i)
		p[i] += p[i-1];	// 赌轮选择策略
	srand((unsigned)time(NULL));
	for (int i=0; i<m; ++i) {
		double pt = rand()%100;
		pt /= 100;
		for (int j=0; j<m; ++j)
			if (pt < p[j]) {	// 赌轮选择
				temp[i] = popu[j];// 存入临时群体
				break;
			}
	}
	for (int i=0; i<m; ++i)
		popu[i] = temp[i];	// 更新当前群体
}

/**
 * 函数功能: 交叉运算操作
 * 参数含义: g表示城市距离图
 */
void genetic::mating(const graph & g) {
	bool vis[maxm] = {false};// 标记个体是否被访问
	std::pair<int, int> grouping[maxm>>1];// 存储分组情况
	int m = maxm-2;		// 不包含精英
	// 将m个个体随机分为m/2组
	int temp = m>>1;
	srand((unsigned)time(NULL));
	for (int i=0; i<temp; ++i) {
		int t1=0, t2=0;
		do {
			t1 = rand()%m;
		} while (vis[t1]);
		do {
			t2 = rand()%m;
		} while (t2==t1 || vis[t2]);
		vis[t1] = vis[t2] = true;
		grouping[i].first = t1;
		grouping[i].second = t2;
	}
	for (int i=0; i<temp; ++i) {
		double t = rand()%100;
		t /= 100;
		if (t < pc) {
			// 小于交叉率,进行交叉操作
			int t1 = grouping[i].first;
			int t2 = grouping[i].second;
			cross(t1, t2, g);
		}
	}
}

/**
 * 函数功能: 变异运算操作
 * 参数含义: n表示城市个数
 */
void genetic::mutation(const int & n) {
	int m = maxm-2;		// 不包括精英
	srand((unsigned)time(NULL));
	for (int i=0; i<m; ++i) {
		double t = rand()%100;
		t /= 100;
		if (t < pm) {
			// 小于变异率,进行变异操作
			int x = rand()%n;
			int y = rand()%n;
			// 交换基因即变异
			std::swap(popu[i].cities[x], popu[i].cities[y]);
		}
	}
}

/**
 * 函数功能: 找num在v中前一个位置上的元素
 * 参数含义: v表示被查找的表,num表示要查找的元素
 */
int genetic::greedy_left(const std::vector<int> & v, const int & num) {
	size_t i = 0;
	for (; i<v.size(); ++i)
		if (num == v[i])
			break;
	if (i == 0)	// 在首位,返回末尾元素
		return v.back();
	return v[i-1];
}

/**
 * 函数功能: 找num在v中后一个位置上的元素
 * 参数含义: v表示被查找的表,num表示要查找的元素
 */
int genetic::greedy_right(const std::vector<int> & v, const int & num) {
	size_t i = 0;
	for (; i<v.size(); ++i)
		if (num == v[i])
			break;
	++i;
	if (i == v.size())	// 在末尾,返回首位元素
		return v.front();
	return v[i];
}

/**
 * 函数功能: 将num从v中删除
 * 参数含义: v表示待查找表,num表示要删除的元素
 */
void genetic::greedy_erase(std::vector<int> & v, const int & num) {
	for (size_t i=0; i<v.size(); ++i)
		if (num == v[i]) {
			// 找到,删除
			v.erase(v.begin()+i);
			return ;
		}
}

/**
 * 函数功能: 对个体x和y实施具体的交叉运算
 * 参数含义: x表示个体popu[x],y表示个体popu[y],g表示城市距离图
 */
void genetic::cross(const int & x, const int & y, const graph & g) {
	std::vector<int> fx = popu[x].cities;
	std::vector<int> fy = popu[y].cities;// 两个父个体
	std::vector<int> sx, sy;	// 两个子个体
	int n = g.getn();
	int rand_city = rand()%n;// 先随机选择一个起点
	int cur_city = rand_city;// 当前所在城市
	sx.push_back(rand_city);
	while (fx.size() > 1) {
		// 从左边贪心选择
		int leftx = greedy_left(fx, cur_city);
		int lefty = greedy_left(fy, cur_city);
		int next_city = 0;// 下一个城市
		// 选择当前点出发距离小的点前往
		if (g.getd(cur_city, leftx) < g.getd(cur_city, lefty)) {
			sx.push_back(leftx);
			next_city = leftx;
		}
		else {
			sx.push_back(lefty);
			next_city = lefty;
		}
		greedy_erase(fx, cur_city);
		greedy_erase(fy, cur_city);// 删除父个体中的当前城市
		cur_city = next_city;	// 更改到新的城市
	}
	fx = popu[x].cities;
	fy = popu[y].cities;
	cur_city = rand_city;
	sy.push_back(rand_city);
	while (fy.size() > 1) {
		// 从右边贪心选择
		int rightx = greedy_right(fx, cur_city);
		int righty = greedy_right(fy, cur_city);
		// 下面与上面类似
		int next_city = 0;
		if (g.getd(cur_city, rightx) < g.getd(cur_city, righty)) {
			sy.push_back(rightx);
			next_city = rightx;
		}
		else {
			sy.push_back(righty);
			next_city = righty;
		}
		greedy_erase(fx, cur_city);
		greedy_erase(fy, cur_city);
		cur_city = next_city;
	}
	popu[x].cities = sx;
	popu[y].cities = sy;// 子代替换掉父代
}

/**
 * 函数功能: 遗传算法求解TSP问题
 * 参数含义: g表示城市距离图
 */
void genetic::solve(const graph & g) {
	int n = g.getn();
	produce(n);
	fit(g);
	show_init(n);
	for (int i=0; i<maxt; ++i) {
		elite_preserved();
		select();
		mating(g);
		mutation(n);
		fit(g);
	}
	elite_preserved();
	best = popu[maxm-1].ada;
	for (int i=0; i<n; ++i)
		ans[i] = popu[maxm-1].cities[i];
}

/**
 * 函数功能: 输出GA所求最优解
 * 参数含义: n表示城市个数
 */
void genetic::out(const int & n) {
	std::cout << "遗传所求最优解为: " << best << std::endl;
	for (int i=0; i<n; ++i)
		std::cout << ans[i] << (" \n"[i==n-1]);
}
