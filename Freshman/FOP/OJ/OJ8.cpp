#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int main(){
	int a,b;
	cin>>a>>b;
	bool* store=new bool[b];
	for(int i=0;i<b;++i){
		store[i]=false;
	}
	for(int i=1;i<=b;++i){
		if(store[i-1]) continue;
		int digi=i;
		bool f=false;
		while(digi>=10){
			if(digi%10==7){
				f=true;
				break;
			}
			digi/=10;
		}
		f=f||(digi==7);
		if(f){
			for(int u=i;u<=b;u+=i) store[u-1]=true;
		}
	}
	int sum=0;
	for(int i=a-1;i<b;++i){
		sum+=store[i];
	}
	sum=b-a+1-sum;
	cout<<sum;
	delete []store;
	return 0;
}


/*#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(){
	ifstream input("input.txt");
	int N,M;
	input>>N>>M;
	ofstream out("output.txt");
	string buffer;
	getline(input,buffer);
	for(int i=0;i<N;++i){
		string buffer;
		getline(input,buffer);
		istringstream temp(buffer);
		string name;
		float ch,math,eng,phy;
		temp>>name>>ch>>math>>eng>>phy;
		float sum=ch+math+eng+phy;
		if(sum<M) out<<name<<endl;
	}
	input.close();
	out.close();
	return 0;
}*/

/*int lfind(string base,string target){
	if(base.length()<target.length()) return -1;
	else if(base.length()==target.length()) return (base==target)-1;
	else{
		for(int i=0;i<base.length()-target.length()+1;++i){
			bool flag=false;
			if(base[i]==target[0]){
				flag=true;
				for(int u=0;u<target.length();++u){
					if(base[i+u]!=target[u]){
						flag=false;
						break;
					}
				}
			}
			if(flag) return i;
		}
		return -1; 
	}
}

int main(){
	ifstream input("input.txt");
	string base,target,c;
	getline(input,base);
	getline(input,target);
	getline(input,c);
	input.close();
	int pos=lfind(base,target);
	ofstream out("output.txt");
	if(-1==pos) out<<base;
	else{
		base.replace(pos,target.length(),c);
		out<<base;
	}
	out.close();
	return 0;
}*/

/*int main(){
	ifstream input("input.txt");
	string base,target;
	getline(input,base);
	getline(input,target);
	input.close();
	ofstream out("output.txt");
	if(base.length()<target.length()) out<<-1;
	else if(base.length()==target.length()) out<<(base==target)-1;
	else{
		for(int i=0;i<base.length()-target.length()+1;++i){
			bool flag=false;
			if(base[i]==target[0]){
				flag=true;
				for(int u=0;u<target.length();++u){
					if(base[i+u]!=target[u]){
						flag=false;
						break;
					}
				}
			}
			if(flag){
				out<<i;
				out.close(); 
				return 0;
			}
		}
		out<<-1; 
	}
	out.close();
	return 0;
}*?




/*int size=0;

void reverse(char* a){
	for(;size<1000;++size) if(0==a[size]) break;
	for(int i=size-1;i>=(size-1)/2;--i){
		char temp=a[i];
		a[i]=a[size-1-i];
		a[size-1-i]=temp;
	}
}

int main(){
	char buffer[1000]={0};
	ifstream inp("inp");
	inp.read(buffer,1000);
	ofstream oup("oup");
	reverse(buffer);
	oup.write(buffer,size);
	return 0;
}*/
