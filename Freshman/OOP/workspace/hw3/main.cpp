#include<iostream>

using namespace std;

void f(string a,bool b=false){
	static int count = 0;
	++count;
	if(!b){
		cout<<a<<endl;
		return;
	}
	else{
		for(int i=0;i<count;++i) cout<<a<<endl;
		return;
	}
}

int main(){
	f("OOP0");
	f("OOP1");
	f("OOP2",true);
	f("OOP3",false);
	f("OOP4",true);
	return 0;
}
