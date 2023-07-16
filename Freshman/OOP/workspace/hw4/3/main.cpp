#include <iostream>
#include "myptr.h"

using namespace std;

class Test {
private:
	static int count;
	int x;
public:
	Test(int _x = 0): x(_x) {
		count++;
	}
	~Test() {
		count--;
	}
	int getX() {return x;}
	int operator+= (int what) {
		return x += what;
	}
	friend ostream& operator<<(ostream& o, Test& t);
	static int getCount() {return count;}
};

ostream& operator<<(ostream& o, Test& t) {
	o << t.x;
	return o;
}

int Test::count = 0;

// 测试内存管理
#ifdef _SUBTASK_1_
void f1() {
	my_ptr<Test> ptr1(new Test(1));
	my_ptr<Test> ptr2(new Test(2));
	return;
}
#endif

// 测试移动构造和赋值，以及拷贝构造和拷贝赋值是否被禁用
#ifdef _SUBTASK_2_
void f2() {
	my_ptr<Test> ptr1(new Test(1));
	my_ptr<Test> ptr2(ptr1);
	my_ptr<Test> ptr3(std::move(ptr1));
	my_ptr<Test> ptr4 = ptr3;
	my_ptr<Test> ptr5 = std::move(ptr3);
	return;
}
#endif


// 测试运算符重载以及空指针保护
#ifdef _SUBTASK_3_
void f3() {
	my_ptr<Test> ptr1(new Test(1248794));
	cout << *ptr1 << endl;
	my_ptr<Test> ptr2(new Test(9864123));
	cout << ptr2->getX() << endl;
	*ptr2 += -5927312;
	cout << *ptr2 << endl;
	my_ptr<Test> ptr3, ptr4;
	cout << *ptr3 << endl;
	cout << *ptr4 << endl;
	*ptr3 = 8234356;
	cout << ptr4->getX() << endl;
	return;
}
#endif

// 综合测试
#ifdef _SUBTASK_4_
void f4() {
	my_ptr<Test> ptr[10];
	for (int i = 0; i < 9; i++) {
		ptr[i] = my_ptr<Test>(new Test(i));
	}
	ptr[1] = ptr[2];
	ptr[3] = std::move(ptr[4]);
	ptr[5] = std::move(ptr[3]);
	ptr[6] = std::move(ptr[5]);
	ptr[7] = ptr[6];
	cout << *ptr[3] << endl;
	cout << *ptr[4] << endl;
	cout << *ptr[5] << endl;
	cout << *ptr[6] << endl;
	cout << *ptr[7] << endl;
	cout << ptr[8]->getX() + 10 << endl;
	cout << *ptr[9] << endl;
	return;
}
#endif


int main()
{
	#ifdef _SUBTASK_1_
		f1();
	#endif
	#ifdef _SUBTASK_2_
		f2();
	#endif
	#ifdef _SUBTASK_3_
		f3();
	#endif
	#ifdef _SUBTASK_4_
		f4();
	#endif

	if (Test::getCount() > 1) {
		cout<<"Test::getCount()="<<Test::getCount()<<endl;
		cout << "Memory leak detected!" << endl;
	}
	else {
		cout << "Accepted!" << endl;
	}
	return 0;
}