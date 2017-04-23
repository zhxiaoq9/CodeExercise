#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

//���������Զ���ȽϹ���
class my_sort{
public:
	bool operator() (const vector<int> &a, const vector<int> &b){
		return ((a[0] > b[0]) && (a[1] > b[1]));
	}
};
//��ͨ������ν�ʺ���
bool fun_between(int num){
	return ((num > 1) && (num <5));
}
//�º�����ʹ��
//ע���ڱ�׼���У�Ĭ�ϵĲ��������ǰ�ֵ���ݣ����ν�ʺ�����º�����ʵ�����
//����Ҫ���ڲ�״̬�ı䣬�������׳������⡣
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
		//�Զ����С�ȽϹ���
		//set0����">"���Ӵ�С���򣬶�set1��Ĭ�ϵĴ�С��������
		set<vector<int>, my_sort > set0;
		set<vector<int>> set1;
		vector<int> tmp(2);
		for (int i = 0; i < 5; i++){
			tmp[0] = i;
			tmp[1] = i + 1;
			set0.insert(tmp);
			set1.insert(tmp);
		}


		//ν�ʺ���
		vector<int> vec = { 1, 4, 5, 6, 4, 3 };
		//ʹ����ͨ��������vec��Ԫ��ֵ��1��5�е���Ŀ
		cout << count_if(vec.begin(), vec.end(), fun_between);
		//ʹ�÷º�������vec��Ԫ��ֵ��1��5�е���Ŀ
		cout << count_if(vec.begin(), vec.end(), is_between(1, 5));
		//ʹ�÷º�������vec��Ԫ��ֵ��4��7�е���Ŀ�����Կ����º���
		//��ʹ�ñ�ֱ��ʹ����ͨ���������������
		cout << count_if(vec.begin(), vec.end(), is_between(4, 7));
		return 0;
	}