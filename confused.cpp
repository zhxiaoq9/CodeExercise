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

int local_param_test;
void localParam(void){
	//int b;
	//cout << b << endl; //只声明b却没有初始化b的话编译报错:局部变量b未初始化
	cout << local_param_test << endl;//这是全局变量,可以不初始化
}


int x = 0;
class base{
public:
	base(){ x = 1; cout << "base constructor" << endl; }
	virtual ~base(){ x = 2; cout << "base destructor" << endl; } //基类析构函数一般为虚函数
	void f(){ x = 3; cout << "base function" << endl; }
	virtual void g(){ x = 4; cout << "base virtual function" << endl; }

};

class drived : public base{
	
public:
	static int m1; //类外初始化	
	const static m2 = 2; //比较特殊,可以在类内初始化
	//const成员只能在初始化列表中初始化,因为const变量一旦被初始化就不能被改变
	//并且这种改变只是针对某一个对象而言的,而不是对类来说的,所以不能在这里初始化
	//只能在初始化列表里面初始化不能在构造函数里面使用m3=3,因为这是赋值不是初始化.
	//const int m3; 

public:
	drived(){ x = 10; cout << "drived constructor" << endl; }
	~drived(){ x = 11; cout << "drived destructor" << endl; }; //基类已经使用virtual时,派生类可以不加virtual声明
	void f(){ x = 12; cout << "drived function" << endl; }
	virtual void g(){ x = 13; cout << "drived virtual function" << endl; }

	static int getM1(){ 
		//this.m3 = 2; //因为static成员函数没有this指针,所以不能访问非静态成员变量
		m1++;
		m1--;
		return m1;
	} 

};
//类静态成员必须在类外进行初始化,因为静态成员属于整个类而不属于某个对象.
//但是这里不能指定关键字static,这是为了与普通静态成员区分
int drived::m1 = 1; 

void classTest(){
	cout << "---------start function class_test--------" << endl;
	cout << "开始构造函数和析构函数测试" << endl;
	drived *pd; //只是声明了指针,并没有构造
	cout << x << endl; //x = 0;
	cout << endl;

	base *pb = new drived; //基类指针指向派生类,先调用基类的构造函数再调用派生类构造函数
	cout << x << endl; //x=10
	pb->f(); //调用基类普通函数f
	cout << x << endl; //x=3
	pb->g(); //调用派生类虚函数g
	cout << x << endl; //x=13
	cout << endl;
	
	cout << "开始类静态成员测试" << endl;
	drived dd; //构造派生类
	cout << &(drived::m1) << endl; //静态类成员可以由类名直接访问,且依然遵循private,protected,public访问准则
	cout << &(dd.m1) << endl; //也可以通过某个实体调用静态类成员,因为类中只有一个静态成员实体,所以这里的地址是与上面的相同
	cout << drived::getM1() << endl;


	cout << "delete base pointer point to drived class" << endl;
	//先调用派生类的析构函数,再调用基类的析构函数。
	//构造函数要声明为虚函数,否则如果在派生类中使用new分配了空间则析构时不会动态绑定
	//也就是不会先调用派生类的析构函数,造成内存泄漏.
	delete pb; 
	cout << endl;

	cout << "---------exit function class_test--------" << endl;
}





int main(){
	cout << "区分字符串与指针" << endl;
	pointerANDarray();

	cout << "局部变量的初始化"<< endl;
	localParam();

	cout << "类的使用" << endl;
	classTest();

	return 0;
}
