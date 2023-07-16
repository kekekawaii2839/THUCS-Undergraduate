#include<iostream>

using namespace std;

int main(){
	int year;
	cin>>year;
	if(0==year%400) cout<<"YES"<<endl;
	else if(0==year%100) cout<<"NO"<<endl;
	else if(0==year%4) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
    return 0;
}
