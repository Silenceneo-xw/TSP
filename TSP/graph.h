/**
 * @Name	: graph.h
 * @Date	: 2017-06-08-08.59.40
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>

class graph {
public:
	graph() {}
	~graph() {}

	void cal_dist();	// 计算城市两两之间的距离
	// 获取城市个数
	int getn() const { return n; }
	// 获取两城市之间的距离
	double getd(int u, int v) const { return d[u][v]; }

	friend std::istream & operator >> (std::istream &, graph &);// 重载>>运算符
	friend std::ostream & operator << (std::ostream &, const graph &);// 重载<<运算符
protected:
	double dist(int u, int v);	// 计算两城市之间的距离

	class city {
	public:
		city() {}
		~city() {}

		// 给x设置值
		void setx(int xt) { x = xt; }
		// 给y设置值
		void sety(int yt) { y = yt; }
	protected:
	private:
		int x, y;	// 城市的XY坐标
		friend class graph;
	};
public:
	static const int maxn = 205;	// 最大城市数目
private:
	int n;		// 城市个数
	city coord[maxn];	// 城市坐标
	double d[maxn][maxn];// 城市之间的距离
};

#endif // __GRAPH_H__
