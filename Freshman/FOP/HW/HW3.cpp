#include<iostream>
#include<cmath>

using namespace std;

int main(){
	int year;
	cin>>year;
	int month[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	if(0!=year%4) month[1]=28;
	int in=0;//表示当年1月1日输出是前面要空出多少天  比如2023.01.01要空出6天 
	for(int i=2023;i<year;++i){
		if(0==i%4) in+=366;
		else in+=365;
	}
	in=in+6;//使用了2023.01.01是周日的条件 
	in%=7;
	
	int row=in;//记录一行中已打印的天数 每到7就清零并换行 
	bool flag=true,flag2=false;//flag保证打印月份数字后不会打印多余空格
							   //flag2保证打印月份后不会进入第一个if分支 
	for(int i=0;i<12;++i){
		if(flag){
			if(i+1<10) cout<<'0'<<i+1<<' ';
			else cout<<i+1<<' ';
			flag=false;
			flag2=true;
		}
		if(0==i) for(int u=0;u<in;++u) cout<<' '<<' '<<' ';
		for(int d=1;d<=month[i];++d){
			if(0==row&&!(month[i]-d<6)&&!flag2){
				cout<<' '<<' '<<' ';
				flag=true;
			}
			else if(0==row&&month[i]-d<6&&i<11&&!flag2){
				if(i+2<10) cout<<'0'<<i+2<<' ';
				else cout<<i+2<<' ';
				flag=false;
			}
			else if(0==row&&i>=11&&!flag2) cout<<' '<<' '<<' ';
			else if(flag2) flag2=false;
			if(d<10) cout<<' '<<d<<' ';
			else cout<<d<<' ';
			++row;
			if(7==row){
				row%=7;
				cout<<endl;
			}
		}
	}
    return 0;
}
