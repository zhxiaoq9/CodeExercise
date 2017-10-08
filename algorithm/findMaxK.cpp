//目的:寻找数组中第k大的元素
//思路:类似于快速排序思想,从数组中取出一个元素将数组分为左右两个子数组,其中在这个元素左边的数组中的值全大于这个元素,右面的数组元素小于或等于这个元素
//如果左边数组元素个数大于k,则递归返回左边数组的第k个元素即可，反之则计算左边数组的个数m并返回右面数组第k-m个元素即可.(将第k个元素看作左边数组中的元素)

#include <iostream>
#include <vector>
using namespace std;

//从ary中begin到end(包括相等情况)范围内返回第k个大的数的索引(从0开始)
int partion(vector<int> &ary, int begin, int end, int k){
	//取出基准元素
	int com = ary[begin];
	while (begin < end){
		//从后向前遍历
		while (begin < end && com >= ary[end])
			end--;
		if (begin < end)
			ary[begin++] = ary[end]; //将较大的数调到左边,注意这里是begin++
		//从前向后遍历
		while (begin < end && com <= ary[begin])
			begin++;
		if (begin < end)
			ary[end--] = ary[begin];//将较小的数调到右边,注意这里是end--
	}
	//将基准元素放到重合的位置
	ary[begin] = com;
	return begin;
}

//返回数组中第k大的数
int findMaxK(vector<int> ary, int k){
	int len = ary.size();
	if (k > len)
		return -999999999;

	int index = 0;
	index = partion(ary, 0, len - 1, k);
	//index是从0开始的索引
	while (index + 1 != k){
		if (index + 1 > k)
			index = partion(ary, 0, index, k);
		else
			index = partion(ary, index + 1, len - 1, k - index - 1);
	}

	return ary[index];
}

int main(){

	vector<int> ary = { 1, 2, 3, 5, 6, 4, 3, 4, 5, 23, 45 };

	int num;
	cout << "返回最大的数: ";
	num = findMaxK(ary, 1);
	cout << num << endl;

	cout << "返回第3大的数: ";
	num = findMaxK(ary, 3);
	cout << num << endl;

	cout << "返回第6大的数: ";
	num = findMaxK(ary, 6);
	cout << num << endl;

	cout << "返回最小的数: ";
	num = findMaxK(ary, ary.size()+1);
	cout << num << endl;

	return 0;
}
