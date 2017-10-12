//目的:C/C++常见的一些易混淆的知识点

#include <iostream>
using namespace std;

//数组字符串与指针
//一个指针p无论指向数组还是堆上分配的内存,sizeof(p)永远是4
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
	double b[] = { 1, 3, 5, 7, 9 };
	double *q = b;
	double *q1 = q + 1;
	cout << "double b[] = { 1, 3, 5, 7, 9 }" << endl;
	cout << "double *q = b" << endl;
	cout << "double *q1 = q + 1" << endl;
	cout << "sizeof(b) = " << sizeof(b) << endl; //5*8=40
	cout << "sizeof(q) = " << sizeof(q) << endl; //4  
	cout << "*q1 - *q = " << *q1 - *q << endl;   //2,指针指向的元素相减
	cout << "q1 - q = " << q1 - q << endl;       //1,按照元素大小相减
	cout << "(int)q1 - (int)q = " << (int)q1 - (int)q << endl; //8,将q和q1的地址相减


	cout << endl;
	void *m = malloc(10);
	cout << "void *m = malloc(10)" << endl;
	cout << sizeof(m) << endl; //4
	delete m;
	m = NULL;

}



int main(){
	cout << "区分字符串与指针" << endl;
	pointerANDarray();

	return 0;
}
