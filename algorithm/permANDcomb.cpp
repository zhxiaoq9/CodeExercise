//目的:实现字符串中字符的排列组合
#include <iostream>
#include <string>
using namespace std;


bool isSwap(const string &str, int begin, int end){
	bool flag = true;
	for (int i = begin; i < end; i++){
		if (str[i] == str[end]){
			flag = false;
			break;
		}
	}
	return flag;
}

//str:要排列的字符串
//begin:第一个字符的位置
//return:排列的个数
//去重的全排列就是从第一个数字起,每个数分别与后面非重复出现的数字交换
int perm(string &str, int begin){
	int len = str.size();
	if (len < 1 || begin >= len)
		return 0;

	//统计排列组合数目
	static int num = 0;
	//第一个字符的位置是最后一个字符,已经没有可交换的了
	if (begin == len - 1){
		cout << str << endl;
		num++;
	}
	else{
		for (int i = begin; i < len; i++){
			if (isSwap(str, begin, i) == true){
				//将要交换到第一位的字符交换到第一位
				swap(str[begin], str[i]);
				//对其余位的字符,按照相同逻辑交换字符
				//并求出排列组合数目
				perm(str, begin + 1);
				//恢复原来的字符串
				swap(str[begin], str[i]);
			}
		}
	}
	return num;
}
//src:原字符串
//dest:存储临时字符串
//begin:表示正在处理src中第begin的字符
//num:组合的字符串长度
void combination(const string &src, string &dest, int begin, int num){
	//如果需要再加入的字符长度为0则说明字符串中已经有num个字符了,所以
	//这里输出字符串
	if (num == 0){
		cout << dest << endl;
		return;
	}
	//递归一直找完最后一个字符后再调用一次本函数到这里返回,即递归终止条件
	if (begin == src.size())
		return;
	//字符串中包含字符src[begin],则从剩余的字符中选n-1个放到dest中
	dest.push_back(src[begin]);
	combination(src, dest, begin + 1, num - 1);
	//字符串中不包含src[begin],则从剩余的字符中选num个放到dest中
	dest.pop_back();
	combination(src, dest, begin + 1, num);
}


//求字符串src中所有字符的组合放到dest中
void combination(const string &src){
	int len = src.size();
	if (len < 1)
		return;
	string dest; //存储临时字符串
	//i表示包含i个字符的组合
	for (int i = 1; i <= len; i++){
		combination(src, dest, 0, i);
	}

}

int main(){

	string str = "abcd";
	//int num = perm(str, 0);
	//cout << num << endl;
	combination(str);
	return 0;
}
