#include <iostream>
using namespace std;
#include "Rack.h"

int main() {

#ifdef TASK1
	// task 1
	// subtask 1
	Rack A; // 此时货架为空，A：
	A += 1; // 给A货架上添加一个标号为1的货物，A：1
    A += 3; // 给A货架上添加一个标号为1的货物，A：1 3
	A += 7; // 给A货架上添加一个标号为1的货物，A：1 3 7
	A += A; // 给A货架上添加A货架上同样的货物，A：1 3 7 1 3 7
	// subtask 2
	cout << "A:" << A << endl;
#endif

#ifdef TASK2
	// task 2
	// subtask 3
	Rack A; // 此时货架为空，A：
	A += 1; // 给A货架上添加一个标号为1的货物，A：1
    A += 3; // 给A货架上添加一个标号为1的货物，A：1 3
	A += 7; // 给A货架上添加一个标号为1的货物，A：1 3 7
	Rack B; // 此时货架为空，B：
	B = (A, A); // 将两个A货架拼起来。B：1 3 7 1 3 7
	B = (2023, A, 2023, A, 2023, A); // 将三个A货架拼起来，并插入三个编号为2023的货物，此时B：2023 1 3 7 2023 1 3 7 2023 1 3 7
	cout << "B:" << B << endl;
	// subtask 4
	Rack C;
	C += 4;
	C += 6;
	C += 8;
	cout << (A < B) << " ";
	cout << (C > B) << " ";
	cout << (A == C) << endl;
	// subtask 5
	Rack F,G,H;
	G += 2;
	for (int i = 1; i < 6; i++) 
		F += i;
	for (int i = 2; i < 7; i++)
		G += i;
	for(int i = 3; i < 9; i++)
		H += i;
	// F：1 2 3 4 5   G：2 2 3 4 5 6    H:3 4 5 6 7 8
    Rack D = F & G; // D：2 3 4 5
	Rack E = F & G & H; // E：3 4 5
	cout << "D:" << D << endl;
	cout << "E:" << E << endl;
#endif

#ifdef TASK3
	//task 3
	Rack A; // 此时货架为空，A：
	for (int i = 1; i < 10; i++)
		for (int j=0; j < i; j++){
			A += i;
		}
	for (int i = 1; i < 10; i++){
		cout << i << ": " << A(i) << endl;
	}
	Rack B;
	for (int i = 1; i < 6; i++)
		B += i;
	~B;
	cout << "B:" << B << endl;
	B--;
	cout << "B:" << B << endl;
	--B;
	cout << "B:" << B << endl;
#endif

#ifdef TASK4
	// task 4
	// 店长的代码
	Rack A, B, C, D;
    int n = 0, temp = 0;
    cin >> n; // 读入要添加的货物的个数
    for (int i = 0; i < n; i++){ // 初始给A和B货架添加货物
        cin >> temp;
        if (A < B) A += temp; // 如果A上的货物数量比B少就给A上添加货物
        else B += temp;
    } // 经过上述添加货物后，货架A上为第奇数个货物：1 2 4 6 8 9 ，B上为第奇数个货物：1 2 3 5 7 9
    C = (A, 2023, B, 2023); // C货架上按照 {A上的货物, 标号为2023的货物, B上的货物, 标号为2023的货物} 的顺序排列，即货架C为：1 2 4 6 8 9 2023 1 2 3 5 7 9 2023
    cout << "C:" << C << endl; // 将C货架上的元素按照加入的顺序打印出来，然后让店员摆放
    for(int i = 1; i < 5; i++){
        cout << i << ": " << C(i) << endl; // 打印出C货架上标号号为i的货物的个数,若i=1，则此处C[i]=2
    }
    D = A & B; // D由A和B中共有的元素组成,即货架D为：1 2 9
    cout << "D:" << D << endl;
    ~D; // 将C货架上的货物倒序，即货架D为：9 2 1
    D--; // 将D货架上最后一个货物卸掉（直接删掉），即货架D为：9 2 
    --D; // 将D货架上最前面一个货物卸掉（直接删掉），即货架D为：2 
    cout << "D:" << D << endl;
#endif

	return 0;
}
