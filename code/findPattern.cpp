//目的:从字符串中找到匹配的字符串

#include <iostream>
using namespace std;

//从str中找到第一个与pattern字符串匹配的位置,并返回其在str中的下标
//如果匹配失败就返回-1
int findPattern(char *str, char *pattern){
	if (str == NULL || pattern == NULL)
		return -1;

	int plen = strlen(pattern);
	int slen = strlen(str);

	for (int i = 0; i < slen - plen; i++){
		int j;
		for (j = 0; pattern[j] == str[i + j]; j++);
		if (j == plen)
			return i;
	}
	return -1;
}


int main(){
	char* str = "helloworld";
	char* pattern = "llo";
	int len = strlen(pattern);
	int index = findPattern(str, pattern);

	if (index >= 0){
		for (int i = 0; i < len; i++){
			cout << *(str + i + index);
		}
	}

	return 0;
}

