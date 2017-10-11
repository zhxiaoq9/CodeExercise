//目的:动态规划求解最长公共子序列,它不要求所得字符在所查找的字符串中是连续的,例如对字符串BDCABA和ABCBDAB,字符串BCBA和BDAB都是最长公共子序列
//题目描述:如果字符串1所有字符按照其在字符串中的顺序出现在另一个字符串2中(不一定连续出现),则字符串1称为字符串2的字串,编写函数实现此功能
//思路:设字符串A = {A0, A1, ... Am-1} B = {B0, B1, ... Bn-1}它们的最长公共子串为Z={Z0, Z1, ... Zk-1},我们从A和B的最后向前考虑
//情况1:当Am-1 = Bn-1,即A和B的末尾相同时,很明显这个末尾的字符也属于Z,此时Zk-1 = Am-1 = Bn-1,这时我们再找{A0, A1, ... Am-2}和{B0, B1, ... Bn-2}
//      的最长公共子串加上Am-1 = Bn-1就是最长子串
//情况2:当Am-1 != Bn-1时, 若Zk-1 != Am-1此时{A0, A1, ... Am-2}与{B0, B1, ... Bn-1}的最长公共子串就是{A0, A1, ... Am-1}与{B0, B1, ... Bn-1}的
//      最长公共子串. 这用反证法可以证明.假设我们已经求出{A0, A1, ... Am-2}与{B0, B1, ... Bn-1}的最长公共子串Z',现在向A中添加元素Am-1,如果这时
//      求得的最长公共子串变成了Z'',那么可以知道Z''的末尾字符一定是Am-1,此时Z''的Zk-1明显与Am-1相等,与假设矛盾.
//      同理当Am-1 != Bn-1时, 若Zk-1 != Bn-1时{A0, A1, ... Am-1}与{B0, B1, ... Bn-2}的最长公共子串就是{A0, A1, ... Am-1}与{B0, B1, ... Bn-1}的
//      最长公共子串.
//      在情况2中的两种情况中的最长子串就是情况2的最长子串
//解决方法:我们用数组c[m][n]存储A和B的最长公共子序列的长度,其中c[i][j]表示A长度为i,B长度为j时的最长子串长度.则有递推关系式:
//            -     0                           if i = 0 or j = 0      
//           |
// c[i,j] =  |      c[i-1,j-1] + 1              if i,j > 0 and Ai = Bj
//           |
//            -     max(c[i,j-1], c[i-1,j])     if i,j >0 and Ai != Bj

#include <iostream>

using namespace std;

#define MAX_NUM  100 //字符串最大长度

int lcsLength(char *x, char *y, int xlen, int ylen, int b[][MAX_NUM + 1]){
	if (x == NULL || y == NULL || xlen < 1 || ylen < 1)
		return 0;
	int c[MAX_NUM + 1][MAX_NUM + 1];
	//初始化数组,任意字符串长度为0时最长公共子序列长度为0
	for (int i = 0; i <= xlen; i++){
		c[i][0] = 0;
	}
	for (int i = 0; i <= ylen; i++){
		c[0][i] = 0;
	}
	//
	for (int i = 1; i <= xlen; i++){
		for (int j = 1; j <= ylen; j++){
			//情况1:当最末尾元素相同时
			if (x[i - 1] == y[j - 1]){
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1; //标志位
			}
			//情况2:当两个字符串末尾元素不相等时
			else{
				//x前缀与y的最长公共子序列比较长
				if (c[i - 1][j] > c[i][j - 1]){
					c[i][j] = c[i - 1][j];
					b[i][j] = 2;
				}
				else{
					c[i][j] = c[i][j - 1];
					b[i][j] = 3;
				}
			}
		}
	}
	cout << "子序列查找情况:" << endl;
	for (int i = 1; i <= xlen; i++){
		for (int j = 1; j <= ylen; j++){
			cout << c[i][j] << " ";
		}
		cout << endl;
	}

	return c[xlen][ylen];
}

void lcsDisplay(char* x, int x_pos, int y_pos, int b[][MAX_NUM + 1], char result[MAX_NUM + 1], int len){
	if (x_pos == 0 || y_pos == 0){
		return;
	}
	//情况1:当末尾元素相等时,此元素属于最长公共子序列,打印此元素并递归打印
	if (b[x_pos][y_pos] == 1){
		len--;
		result[len] = x[x_pos - 1];//如果传入的是y字符串那么应该赋y[y_pos - 1],因为x_pos,y_pos实际上是表示字符串长度
		                           //是以下标1开始的,而x中的字符是以下标0开始的,所以这里要减1
		lcsDisplay(x, x_pos - 1, y_pos - 1, b, result, len);
	}
	else{
		if (b[x_pos][y_pos] == 2){
			lcsDisplay(x, x_pos - 1, y_pos, b, result, len);
		}
		else{
			lcsDisplay(x, x_pos, y_pos - 1, b, result, len);
		}
	}
}



int main(){
	char a[] = "ABCBDAB";
	char b[] = "BDCABA";
	int a_len = strlen(a);
	int b_len = strlen(b);
	int m[MAX_NUM + 1][MAX_NUM + 1];
	int len = lcsLength(a, b, a_len, b_len, m);

	char result[MAX_NUM + 1];
	lcsDisplay(a, a_len, b_len, m, result, len);
	
	cout << "最长公共子序列长为:" << len << endl;
	for (int i = 0; i < len; i++){
		cout << result[i];
	}
	
	return 0;
}
