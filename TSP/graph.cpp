/**
 * @Name	: graph.cpp
 * @Date	: 2017-06-08-09.02.02
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#include <cmath>
#include <iomanip>
#include "graph.h"

/**
 * 函数功能: 计算两两城市之间的距离
 */
void graph::cal_dist() {
	for (int i=0; i<n; ++i) {
		d[i][i] = 0;
		for (int j=i+1; j<n; ++j)
			d[i][j] = d[j][i] = dist(i, j);
	}
}

/**
 * 函数功能: 计算两城市之间的距离
 */
double graph::dist(int u, int v) {
	double t1 = coord[u].x-coord[v].x;
	double t2 = coord[u].y-coord[v].y;
	return sqrt(t1*t1+t2*t2);
}

/**
 * 函数功能: 重载>>运算符,使其能用于graph类对象
 * 参数含义: in表示输入流对象,p表示graph类对象
 */
std::istream & operator >> (std::istream & in, graph & p) {
	in >> p.n;
	int x, y;
	for (int i=0; i<p.n; ++i) {
		in >> x >> y;
		p.coord[i].setx(x);
		p.coord[i].sety(y);
	}
	return in;
}

/**
 * 函数功能: 重载<<运算符,使其能用于graph类对象
 * 参数含义: out表示输出流对象,p表示graph类对象
 */
std::ostream & operator << (std::ostream & out, const graph & p) {
	out << "城市个数: " << p.n << "\n";
	out << "城市之间的距离矩阵如下所示:" << "\n";
	for (int i=0; i<p.n; ++i)
		for (int j=0; j<p.n; ++j)
			out << std::setw(12) << p.d[i][j] << (" \n"[j==p.n-1]);
	return out;
}
