//题目：
//输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{ 3，32，321 }，则打印出这三个数字能排成的最小数字为321323。
//分析：
//这道题目比较数组组成字符之后的大小，因为数组中的数组合后可能超过计算机整数的表示范围，所以整个过程都要使用字符串来比较和保存。
//并不是a<b那么ab<ba，因为3, 31拼成331>313，所以我们应该设置自己的一套比较规则，如果ab<ba那么称为a<b，所以我们需要做的是把整个数组按照我们的比较规则从小到大排列。然后从头到尾用字符串的形式串起来。


#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


string int2str(int n){
	stringstream ss;
	ss << n;
	string str;
	ss >> str;
	return str;
}

bool compare(const string &str1, const string &str2){
	string s1 = str1 + str2;
	string s2 = str2 + str1;
	return s1 < s2;
}



int main(){

	int n;
	cin >> n;
	vector<string> vec(n);

	for (int i = 0; i < n; i++){
		int tmp;
		cin >> tmp;
		vec[i] = int2str(tmp);
	}

	sort(vec.begin(), vec.end(), compare);

	for (int i = 0; i < n; i++){
		cout << vec[i];
	}
	
	return 0;
}






