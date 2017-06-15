/**
 * @Name	: genetic.h
 * @Date	: 2017-06-08-09.14.11
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.2
 */

#ifndef __GENETIC_H__
#define __GENETIC_H__

#include <vector>
#include "graph.h"

class genetic {
public:
	genetic() {}
	~genetic() {}

	void produce(const int &);	// 随机产生初始群体
	void show_init(const int &);// 显示初始群体
	void fit(const graph &);	// 计算群体中个体的适应度
	void elite_preserved();		// 获取精英并保存
	void select();				// 选择算子
	void mating(const graph &);	// 交叉算子
	void mutation(const int &);	// 变异算子
	void solve(const graph &);	// GA求解TSP问题
	void out(const int &);		// 输出所求最优解
public:
	static const int maxm = 36;		// 种群规模
	static const int maxt = 255;	// 最大迭代次数
	static const double pc = 0.95;	// 交叉率
	static const double pm = 0.01;	// 变异率
protected:
	class indiv {
	private:
		std::vector<int> cities;// 城市的访问顺序
		double ada, p;	// 个体的适应度和幸存率
		friend class genetic;
	} popu[maxm];	// 当前群体
	// 找后者在前者中前一个位置的元素
	int greedy_left(const std::vector<int> &, const int &);
	// 找后者在前者中后一个位置的元素
	int greedy_right(const std::vector<int> &, const int &);
	// 将后者从前者中删除
	void greedy_erase(std::vector<int> &, const int &);
	// 对两者实施具体的交叉运算
	void cross(const int &, const int &, const graph &);
private:
	double best;		// 近似最优解
	int ans[graph::maxn];// 最终城市访问顺序
};

#endif // __GENETIC_H__
