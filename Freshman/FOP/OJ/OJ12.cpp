/*#include<iostream>

using namespace std;

int n,*h,m,*t;

int f(int l,int r){
	if(l==r) return 0;
	if(l+1==r) return 1;
	
	int max=1;
	for(int i=l+1;i<=r;++i){
		int val=0;
		if(h[i]>=h[l]&&h[i]<=h[r]){
			val=1+f(i,r);
		}
		if(max<val) max=val;
	}
	return max;
}

int ff(int r){
	int max=0;
	for(int i=0;i<r;++i){
		int val=0;
		if(h[i]<=h[r]){
			val=f(i,r);
		}
		if(i+1<n&&h[i]<h[i+1]) ++i;
		if(max<val) max=val;
	}
	return max;
}

int fff(int l){
	int max=0;
	for(int i=n-1;i>=l;--i){
		int val=0;
		if(h[i]>=h[l]){
			val=f(l,i)+1;
		}
		if(max<val) max=val;
	}
	return max;
}

int main(){
	cin>>n;
	h=new int[n];
	for(int i=0;i<n;++i) cin>>h[i];
	cin>>m;
	if(m>0){
		t=new int[m];
		for(int i=0;i<m;++i) cin>>t[i];
		
		int sum=ff(t[0]);
		for(int i=0;i<m-1;++i){
			sum+=f(t[i],t[i+1]);
		}
		sum+=fff(t[m-1]);
		cout<<sum;
		return 0;
	}
	else if(0==m){
		int max=0;
		for(int i=0;i<n;++i){
			int val=ff(i)+1;
			if(i+1<n&&h[i]<h[i+1]){
				++val;
				++i;
			}
			if(max<val) max=val;
		}
		cout<<max;
		return 0;
	}
}*/




/*#include<iostream>

using namespace std;

int n,l,*a;
long long *r;

long long s(int x,int y){//×ó¿ªÓÒ±Õ
	long long sum=0;
	for(int i=x;i<y;++i) sum+=a[i];
	return sum;
}

long long f(int left){
	if(left==n) return 0;
	if(r[left]!=0) return r[left];
	long long minn=s(left,n)-l;
	minn=minn*minn;
	long long sum_temp=0;
	for(int i=left+1;i<=n;++i){
		sum_temp+=a[i-1];
		long long temp=sum_temp-l;
		long long val=temp*temp+f(i);
		if(val<minn) minn=val;
	}
	return r[left]=minn;
}

int main(){
	cin>>n>>l;
	a=new int[n];
	r=new long long[n+1];
	for(int i=0;i<=n;++i) r[i]=0;
	for(int i=0;i<n;++i) cin>>a[i];
	cout<<f(0);
	return 0;
}*/



#include<iostream>

using namespace std;

int n,m;
int *a,*b,*dp,*r;
int money;

void ff(int length){
	for(int i=0;i<n;++i){
		for(int j=a[i];j<=m;++j){
			dp[j]=max(dp[j],dp[j-a[i]]+b[i]);
		}
	}
}

int f(int length){
	if(r[length]!=0) return r[length];
	int max=dp[length];
	for(int i=1;i<length;++i){
		int a=f(i),b=f(length-i);
		int val=a+b;
		if(a==b){
			val+=233;
			//if(val>max) cout<<i<<' '<<length-i<<endl;
		}
		if(val>max) max=val;
	}
	return r[length]=max;
}

int main(){
	cin>>n>>m;
	a=new int[n];
	b=new int[n];
	dp=new int[m+1];
	r=new int[m+1];
	for(int i=0;i<n;++i) cin>>a[i];
	for(int i=0;i<n;++i) cin>>b[i];
	for(int i=0;i<=m;++i) dp[i]=r[i]=0;
	ff(m);
	cout<<f(m);
	return 0;
}




/*#include <iostream>

using namespace std;

int r;
int **a;

int main(){
	cin>>r;
	a=new int*[r];
	for(int i=0;i<r;++i){
		a[i]=new int[r];
	}
	for(int i=0;i<r;++i){
		for(int j=0;j<=i;++j) cin>>a[i][j];
		for(int j=i+1;j<r;++j) a[i][j]=0;
	}
	for(int i=1;i<r;++i){
		a[i][0]+=a[i-1][0];
		for(int j=1;j<=i;++j) a[i][j]+=max(a[i-1][j-1],a[i-1][j]);
	}
	int res=0;
	for(int j=0;j<r;++j){
		if(a[r-1][j]>res) res=a[r-1][j];
	}
	cout<<res;
	return 0;
}*/
