#include<iostream>

using namespace std;

class pos{
public:
	int x,y;
	pos operator+(const pos &a);
	bool operator==(const pos &a);
}chess[225],eend;

pos pos::operator+(const pos &a){
	pos res{this->x+a.x,this->y+a.y};
	return res;
}

bool pos::operator==(const pos &a){
	return (this->x==a.x)&&(this->y==a.y);
}

int counter=0,k;

int calc(pos start){
	pos a={1,2},b={2,1},c={1,-2},d={2,-1};
	++counter;
	if(start==eend) return 1;
	if(start.x>=eend.x) return 0;
	if(start.y>eend.y) return 0;
	if(start.y<0) return 0;
	for(int i=0;i<k;++i){
		if(start==chess[i]) return 0;
	}
	return calc(start+a)+calc(start+b)+calc(start+c)+calc(start+d);
}

int main(){
	int n,m;
	cin>>n>>m>>k;
	for(int i=0;i<k;++i) cin>>chess[i].x>>chess[i].y;
	pos start={0,0};
	eend.x=n;
	eend.y=m;
	cout<<calc(start);
	return 0;
}



/*#include <iostream>

using namespace std;

int n;
int a[100];

void swap(int &i,int &j){
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
	cout<<"swap(a["<<i<<"], a["<<j<<"]):";
	for(int i=0;i<n;++i) cout<<a[i]<<' ';
	cout<<endl;
}

int main(){
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i];
	for(int i=0;i<n;++i){
		int min=a[i],min_index=i;
		for(int j=i;j<n;++j){
			if(a[j]<min){
				min=a[j];
				min_index=j;
			}
		}
		swap(i,min_index);
	}
	return 0;
}*/



/*#include <iostream>

using namespace std;

int calc(int n,int x,int y){
	if(n<x) return 0;
	if(n==x) return 1;
	if(n==y) return 1+calc(n-x,x,y);
	if(x==y) return calc(n-x,x,y);
	else{
		return calc(n-x,x,y)+calc(n-y,x,y);
	}
}

int main(){
	int n,x,y;
	cin>>n>>x>>y;
	int res=calc(n,x,y);
	if(0==res) cout<<"sorry";
	else cout<<res;
	return 0;
}*/



/*#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> a;
int h;

int calc(int start){
	if((find(a.begin(),a.end(),start)!=a.end())) return 0;
	if(3+start==h){
		int waterCount=(find(a.begin(),a.end(),start+1)!=a.end())+(find(a.begin(),a.end(),start+2)!=a.end());
		if(1==waterCount) return 2;
		else if(2==waterCount) return 1;
		else if(0==waterCount) return 4;
		//else cout<<"error!"<<endl;
	}
	else if(2+start==h){
		int waterCount=(find(a.begin(),a.end(),start+1)!=a.end());
		if(0==waterCount) return 2;
		else if(1==waterCount) return 1;
		else return 0;
	}
	else if(1+start==h) return 1;
	else if(start==h) return 0;
	else{
		//if(start==0) cout<<calc(start+1)<<' '<<calc(start+2)<<' '<<calc(start+3)<<endl;
		return calc(start+1)+calc(start+2)+calc(start+3);
	}
}

int main(){
	int n;
	cin>>h>>n;
	for(int i=0;i<n;++i){
		int t;
		cin>>t;
		a.push_back(t);
	}
	cout<<calc(0);
	return 0;
}*/



/*#include <iostream>

using namespace std;

int f(int n,int x){
	if(n<=0) return 0;
	else if(1==n) return x;
	else return f(n-1,x)+f(n/2,x)+f(n/3,x);
}

int main(){
	int x,n;
	cin>>x>>n;
	cout<<f(n,x);
	return 0;
}*/
