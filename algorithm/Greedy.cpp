/*
题目介绍：
某餐馆有n张桌子，每张桌子有一个参数：a 可容纳的最大人数； 有m批客人，每批客人有两个参数:b人数，c预计消费金额。 
在不允许拼桌的情况下，请实现一个算法选择其中一部分客人，使得总预计消费金额最大。
输入描述:
输入包括m+2行。
第一行两个整数n(1 <= n <= 50000),m(1 <= m <= 50000)
第二行为n个参数a,即每个桌子可容纳的最大人数,以空格分隔,范围均在32位int范围内。
接下来m行，每行两个参数b,c。分别表示第i批客人的人数和预计消费金额,以空格分隔,范围均在32位int范围内。

输出一个整数,表示最大的总预计消费金额。

题目分析：
这里考察的是贪心算法，首先我们可以按照每批客人的消费金额从高到低进行排列，如果消费金额相等的话按照人数从少到多进行排列；然后将餐
桌按照容纳人数从少到多进行排列。
排列完成后按照消费金额从高到底一批批选取每批客人，并安排座位数目最合适的桌子。如果没有足够大的桌子安排的话那么就直接抛弃这批客人；
如果有桌子能容纳的话，那么就把能恰好容纳此批客人或者剩余座位比客人人数多的最少的那个桌子安排给这批客人(这样是为了能让更多的桌子用
来容纳客人)，这样一批批安排即可。
为什么要这么做呢，首先在不允许拼桌的情况下，对于任意一批客人来说，如果没有桌子能容纳他们，很明显是要抛弃掉这批客人。
那么在有桌子能容纳这批客人的情况下，当然优先选取消费额最高的那批客人挣得钱最多(这里不需要考虑此批客人人数的问题，因为无
论这批客人有多少人，他们都只占用一个桌子)，并且把座位数目最合适的桌子分配给这批客人。那为什么消费金额相等时要按照人数从
少到多排序呢，这也是为了能尽量让更多的桌子容纳更多的座位呀！
其实这就是一个贪心的问题，即将一个最优化问题分解为一个贪心过程和一个子最优化问题，并且保证这个贪心过程与子最优化问题结合就是整个
最优化问题。
*/

#include <iostream>
#include <set>
#include <map>
using namespace std;

struct guest{
	int number;
	int cost;
	guest(int number = 0, int cost = 0) : number(number), cost(cost){}
};

class sort_guest{
public:
	bool operator() (const guest &x, const guest &y){
		if (x.cost == y.cost)
			return x.number < y.number;
		return x.cost > y.cost;
	}
};
int main()
{
	int n, m;
	cin >> n >> m;
	//每桌容纳人数小到大排列,第一个int存储座位数，第二个参数表示桌子是否被使用
	multimap<int, bool, less<int> > table;
	int tmp;
	for (int i = 0; i < n; i++){
		cin >> tmp;
		table.insert(make_pair(tmp, false));
	}
	//客人的花费及人数，按照自定义的排序方式排序
	multiset<guest, sort_guest> guest_group;
	guest gt;
	for (int i = 0; i < m; i++){
		cin >> gt.number >> gt.cost;
		guest_group.insert(gt);
	}
	//注意这里最好用long long ,否则表示范围可能不够
	long long sum = 0;
	multiset<guest>::iterator it;
	multimap<int, bool>::iterator tb;
	for (it = guest_group.begin(); it != guest_group.end(); ++it){
		//获得客人的人数和消费金额
		int num = (*it).number;
		int cost = (*it).cost;
		//在table中找到第一个符合人数规则的桌子
		//注意这里lower是二分查找，不要自己遍历
		tb = table.lower_bound(num);
		if (tb != table.end()){
			table.erase(tb);
			sum += cost;
		}
	}
	cout << sum << endl;

	return 0;
}