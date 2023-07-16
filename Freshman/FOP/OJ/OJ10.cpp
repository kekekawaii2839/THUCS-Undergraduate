#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<sstream>

using namespace std;

struct shit{
	string color,shape;
}poop[1000];

int iindex=0;

void create(string arg1,string arg2){
	poop[iindex].color=arg1;
	poop[iindex].shape=arg2;
	++iindex;
}

void dup(string arg1,string arg2){
	int m=atoi(arg1.c_str())-1;
	poop[iindex].color=arg2;
	poop[iindex].shape=poop[m].shape;
	++iindex;
}

void crash(string arg){
	int m=atoi(arg.c_str())-1;
	for(int i=m;i<iindex-1;++i){
		poop[i].color=poop[i+1].color;
		poop[i].shape=poop[i+1].shape;
	}
	poop[iindex].color="";
	poop[iindex].shape="";
	--iindex;
}

void order(){
	for(int i=0;i<iindex;++i){
		for(int j=i;j<iindex;++j){
			if(poop[j].color<poop[i].color){
				shit temp;
				temp.color=poop[i].color;
				temp.shape=poop[i].shape;
				poop[i].color=poop[j].color;
				poop[i].shape=poop[j].shape;
				poop[j].color=temp.color;
				poop[j].shape=temp.shape;
			}
			else if(poop[j].color==poop[i].color){
				if(poop[j].shape<poop[i].shape){
				shit temp;
				temp.color=poop[i].color;
				temp.shape=poop[i].shape;
				poop[i].color=poop[j].color;
				poop[i].shape=poop[j].shape;
				poop[j].color=temp.color;
				poop[j].shape=temp.shape;
				}
			}
		}
	}
}

int main(){
	int n;
	string temp;
	getline(cin,temp);
	cin.clear();
	n=atoi(temp.c_str());
	string *comm=new string[n];
	for(int i=0;i<n;++i){
		getline(cin,comm[i]);
		cin.clear();
		istringstream convert(comm[i]);
		string command,arg1,arg2;
		convert>>command>>arg1>>arg2;
		if("CREATE"==command){
			create(arg1,arg2);
		}
		if("DUP"==command){
			dup(arg1,arg2);
		}
		if("CRASH"==command){
			crash(arg1);
		}
		if("ORDER"==command){
			order();
		}
	}
	for(int i=0;i<iindex;++i){
		cout<<poop[i].color<<' '<<poop[i].shape<<endl;
	}
	return 0;
}







/*#include<iostream>

using namespace std;

int f(int x){
	if(1==x) return 1;
	if(x>1&&1==x%2) return f((x-1)/2)+f((x+1)/2);
	if(0==x%2) return f(x/2);
}

int main(){
	int t;
	cin>>t;
	int *a=new int[t];
	for(int i=0;i<t;++i) cin>>a[i];
	for(int i=0;i<t;++i) cout<<f(a[i])<<endl;
	return 0;
}*/




/*#include <iostream>

using namespace std;

int n,sol=0;

bool check(bool *a,int k){
	for(int i=0;i<=k;++i) if(!a[i]) return false;
	return true;
}

bool fcheck(bool *a,int k){
	for(int i=0;i<=k;++i) if(a[i]) return false;
	return true;
}

void unsolve(bool *a,int target);
void solve(bool *a,int target,int *sol);

int main(){
	cin>>n;
	bool *a=new bool[n];//true表示卸下 false表示装上 
	for(int i=0;i<n;++i) a[i]=0;
	solve(a,n-1,&sol);
	cout<<sol;
	return 0;
}

void unsolve(bool *a,int target){
	if(target==0){
		a[target]=false;
		++sol;
		return;
	}
	if(!a[target]) return;
	if(check(a,target)){
		unsolve(a,target-1);
		a[target]=false;
		++sol;
		solve(a,target-1,&sol);
	}
}

void solve(bool *a,int target,int *sol){
	if(target==0){
		a[target]=true;
		++(*sol);
		return;
	}
	if(a[target]) return;
	if(!a[target]&&fcheck(a,target-1)){
		solve(a,target-2,sol);
		a[target]=true;
		++(*sol);
		solve(a,target-1,sol);
	}
	if(!a[target]&&check(a,target-2)&&!a[target-1]){
		a[target]=true;
		++(*sol);
		solve(a,target-1,sol);
	}
	if(!a[target]&&check(a,target-1)){
		
		bool *b=new bool[n];//true表示卸下 false表示装上 
		unsolve(a,target-1);
		
		a[target]=true;
		++(*sol);
		solve(a,target-1,sol);
	}
}*/


/*#include <iostream>

using namespace std;

int x;

void qq(int *a,int left,int right){
	if(right<=left) return;
	int p=left,q=right;
	int key=a[left];
	while(p<q){
		while(a[q]>=key&&p<q) --q;
		while(a[p]<=key&&p<q) ++p;
		swap(a[p],a[q]);
	}
	swap(a[left],a[p]);
	for(int i=0;i<x;++i) cout<<a[i]<<' ';
	cout<<endl;
	qq(a,left,p-1);
	qq(a,p+1,right);
}

int main(){
	cin>>x;
	int *a=new int[x];
	for(int i=0;i<x;++i) cin>>a[i];
	qq(a,0,x-1);
	return 0;
}*/
