#include <iostream> 
#include <stdio.h>

using namespace std;
 
int main() {
	string a="TsingHua University",b="Course:Fundamentals of Programming";
	string c="Time:9:50~12:15",d="Classroom:6C202";
	cout<<a<<endl
		<<b<<endl
		<<c<<endl
		<<d<<endl
		<<"------------------------------------------------"<<endl;
	printf("%s\n%s\n%s\n%s\n",a.c_str(),b.c_str(),c.c_str(),d.c_str());//��std::stringת��Ϊ�����ַ��ĵ�ַ
																	   //�Թ�C���Ե�printf()ʹ�� 
}
