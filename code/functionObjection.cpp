//目的:熟悉C++函数对象的应用

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//函数对象自定义比较规则
class my_sort{
public:
	bool operator() (const vector<int> &a, const vector<int> &b){
		return ((a[0] > b[0]) && (a[1] > b[1]));
	}
};
//普通函数做谓词函数
bool fun_between(int num){
	return ((num > 1) && (num <5));
}
//仿函数的使用
//注意在标准库中，默认的参数传递是按值传递，因此谓词函数与仿函数的实现最后
//都不要有内部状态改变，否则容易出现问题。
class is_between{
public:
	is_between(int small = 0, int large = 0) :m_small(small), m_large(large){}
	bool operator() (int num){
		return ((num > m_small) && (num < m_large));
	}

private:
	int m_small;
	int m_large;
};

	int main()
{
		//自定义大小比较规则
		//set0会以">"即从大到小排序，而set1以默认的从小到大排序
		set<vector<int>, my_sort > set0;
		set<vector<int>> set1;
		vector<int> tmp(2);
		for (int i = 0; i < 5; i++){
			tmp[0] = i;
			tmp[1] = i + 1;
			set0.insert(tmp);
			set1.insert(tmp);
		}


		//谓词函数
		vector<int> vec = { 1, 4, 5, 6, 4, 3 };
		//使用普通函数查找vec中元素值在1到5中的数目
		cout << count_if(vec.begin(), vec.end(), fun_between);
		//使用仿函数查找vec中元素值在1到5中的数目
		cout << count_if(vec.begin(), vec.end(), is_between(1, 5));
		//使用仿函数查找vec中元素值在4到7中的数目，可以看到仿函数
		//的使用比直接使用普通函数更具有灵活性
		cout << count_if(vec.begin(), vec.end(), is_between(4, 7));
		return 0;
	}
