#include<iostream>
#include<cmath>

using namespace std;

int main(){
	int year;
	cin>>year;
	int month[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	if(0!=year%4) month[1]=28;
	int in=0;//��ʾ����1��1�������ǰ��Ҫ�ճ�������  ����2023.01.01Ҫ�ճ�6�� 
	for(int i=2023;i<year;++i){
		if(0==i%4) in+=366;
		else in+=365;
	}
	in=in+6;//ʹ����2023.01.01�����յ����� 
	in%=7;
	
	int row=in;//��¼һ�����Ѵ�ӡ������ ÿ��7�����㲢���� 
	bool flag=true,flag2=false;//flag��֤��ӡ�·����ֺ󲻻��ӡ����ո�
							   //flag2��֤��ӡ�·ݺ󲻻�����һ��if��֧ 
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
