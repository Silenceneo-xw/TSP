/**
 * @Name	: tsp.cpp
 * @Date	: 2017-06-08-09.17.34
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#include <ctime>
#include "tsp.h"

/**
 * 函数功能: TSP问题求解算法比较
 */
void tsp::compare() {
	// 重定向到文件输入输出
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
	while (std::cin >> g) {// 输入城市信息
		g.cal_dist();	// 计算城市距离
		std::cout << std::fixed;
		std::cout.precision(4);
		std::cout << g << std::endl;// 输出城市信息
		int n = g.getn();
		// clock()记录当前程序运行了多长时间
		clock_t start = clock();
		greedy_tsp.solve(g);
		greedy_tsp.out(n);
		clock_t finish = clock();
		std::cout << "用时: " << (double)(finish-start)/CLOCKS_PER_SEC << "s.\n";
		start = clock();
		genetic_tsp.solve(g);
		genetic_tsp.out(n);
		finish = clock();
		std::cout << "用时: " << (double)(finish-start)/CLOCKS_PER_SEC << "s.\n";
		start = clock();
		backtrack_tsp.reset();
		backtrack_tsp.solve(g, 1);
		backtrack_tsp.out(n);
		finish = clock();
		std::cout << "用时: " << (double)(finish-start)/CLOCKS_PER_SEC << "s.\n";
		start = clock();
		dynamic_tsp.solve(g);
		dynamic_tsp.out(n);
		finish = clock();
		std::cout << "用时: " << (double)(finish-start)/CLOCKS_PER_SEC << "s.\n";
		start = clock();
		branch_tsp.solve(g);
		branch_tsp.out(n);
		finish = clock();
		std::cout << "用时: " << (double)(finish-start)/CLOCKS_PER_SEC << "s.\n";
		std::cout << std::endl;
	}
}
