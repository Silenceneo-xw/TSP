/**
 * @Name	: tsp.h
 * @Date	: 2017-06-08-09.16.31
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link	: http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 1.1
 */

#ifndef __TSP_H__
#define __TSP_H__

#include "greedy.h"
#include "genetic.h"
#include "backtrack.h"
#include "dynamic.h"
#include "branch.h"

class tsp {
public:
	tsp() {}
	~tsp() {}

	void compare();	// TSP问题求解算法比较
protected:
private:
	graph g;	// 城市距离图
	greedy greedy_tsp;		// 贪心对象
	genetic genetic_tsp;	// 遗传对象
	backtrack backtrack_tsp;// 回溯对象
	dynamic dynamic_tsp;	// 动规对象
	branch branch_tsp;		// 分支对象
};

#endif // __TSP_H__
