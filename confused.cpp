//目的:C/C++常见的一些易混淆的知识点

#include <iostream>
using namespace std;

//数组字符串与指针
void pointerANDarray(){
	char a[] = "12345";
	char *p = a;
	cout << "char a[] = \"12345\"" << endl;
	cout << "char *p = a" << endl;

	cout << "strlen(a) = " << strlen(a) << endl; //5
	cout << "sizeof(a) = " << sizeof(a) << endl; //6
	cout << "strlen(p) = " << strlen(p) << endl; //5
	cout << "sizeof(p) = " << sizeof(p) << endl; //4

	cout << endl;
	int b[] = { 1, 3, 5, 7, 9 };
	int *q = b;
	int *q1 = q + 1;	
	cout << "int b[] = { 1, 3, 5, 7, 9 }" << endl;
	cout << "int *q = b" << endl;
	cout << "int *q1 = q + 1" << endl;
	cout << "sizeof(b) = " << sizeof(b) << endl; //4*5=20
	cout << "sizeof(q) = " << sizeof(q) << endl; //4     
	cout << "q1 - q = " << q1 - q << endl;       //1
	cout << "*q1 - *q = " << *q1 - *q << endl;   //2

}



int main(){
	cout << "区分字符串与指针" << endl;
	pointerANDarray();

	return 0;
}
