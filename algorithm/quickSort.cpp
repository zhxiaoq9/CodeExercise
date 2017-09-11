#include <iostream>
#include <vector>

using namespace std;

int getPartion(vector<int> &vec, int head, int tail){
	int key = vec[head];
	if (head < tail){
		while (head < tail){
			while (vec[tail] >= key && head < tail){
				tail--;
			}
			if (head < tail)
				vec[head++] = vec[tail];

			while (vec[head] <= key && head < tail){
				head++;
			}
			if (head < tail)
				vec[tail--] = vec[head];
		}
	}
	vec[head] = key;
	return head;
}


void quickSort(vector<int> &vec, int l , int r){
	if (l < r){
		int index = getPartion(vec, l, r);
		quickSort(vec, l, index - 1);
		quickSort(vec, index + 1, r);
	}
	return;
}

int main(){

	//vector<int> vec = { 7, 5, 6, 12, 15, 9, 1, 4, 3 };
	vector<int> vec = { 1, 0, 6, 7, 4, 7, 1, 3, 3 };
	quickSort(vec, 0, vec.size() - 1);

	for (auto val : vec){
		cout << val << " ";
	}

	return 0;
}






