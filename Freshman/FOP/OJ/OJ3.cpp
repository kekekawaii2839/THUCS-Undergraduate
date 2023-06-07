#include<iostream>
#include<cmath>

using namespace std;

int main(){
	int n,k,x;
	cin>>n>>k>>x;
    int a[n];
    for(int i=0;i<n;++i) cin>>a[i];
    for(int i=0;i<n;++i){
    	if(1==k) a[i]+=x;
		else if(2==k) a[i]*=x;
		else if(3==k){
			int t=0;
			if(x/1000!=0) t=3;
			else if(((x%1000)/100)!=0) t=2;
			else if((x%100)/10!=0) t=1;
			else if((x%10)!=0) t=0;
			a[i]=a[i]*pow(10,t+1)+x;
		}
		else if(4==k){
			if(0==i%2) a[i]=a[i]%x;
		}
	}
	for(int i=0;i<n;++i){
		cout<<a[i]<<endl;
	}
    return 0;
}
