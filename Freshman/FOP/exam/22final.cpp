/*#include<iostream>

using namespace std;

int a[2000]={0},dp[2000]={0};

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i];
	for(int i=0;i<n;++i){//枚举以a[i]结尾的单增子序列 
		dp[i]=a[i];
		for(int j=0;j<i;++j){
			if(a[j]<a[i]) dp[i]=max(dp[i],dp[j]+a[i]);
		}
	}
	int maxx=-1e8;
	for(int i=0;i<n;++i) if(maxx<dp[i]) maxx=dp[i];
	cout<<maxx;
	return 0;
}*/




/*#include<iostream>
#include<algorithm>

using namespace std;

class shit{
public:
	string name;
	int height;
}poop[1000];

static bool biggershit(shit &a,shit &b){
	if(a.height==b.height) return a.name<b.name;
	else return a.height<b.height;
}

int index=0,n;

void add(string n,int h){
	poop[index].name=n;
	poop[index++].height=h;
}

void select(string n){
	int p=0;
	for(int i=0;i<index;++i){
		if(poop[i].name==n){
			p=i;
			break;
		}
	}
	shit temp=poop[p];
	for(int i=p-1;i>=0;--i){
		poop[i+1]=poop[i];
	}
	poop[0]=temp;
}

void leave(string n){
	int p=0;
	for(int i=0;i<index;++i){
		if(poop[i].name==n){
			p=i;
			break;
		}
	}
	for(int i=p;i<index;++i){
		poop[i]=poop[i+1];
	}
	poop[index].name="";
	poop[index--].height=0;
}

int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		string comm;
		cin>>comm;
		if("ADD"==comm){
			string a;
			int b;
			cin>>a>>b;
			add(a,b);
		}
		else if("SELECT"==comm){
			string a;
			cin>>a;
			select(a);
		}
		else if("LEAVE"==comm){
			string a;
			cin>>a;
			leave(a);
		}
		else if("ORDER"==comm){
			sort(poop,poop+index,biggershit);
		}
	}
	for(int i=0;i<index;++i) cout<<poop[i].name<<' '<<poop[i].height<<endl;
	return 0;
}*/ 




/*#include<iostream>

using namespace std;

int main(){
	char x,y,z,q;
	cin>>x>>y>>z>>q;
	bool res[4]={0};
	for(char a='A';a<'D';++a){
		for(char b=a+1;b<='D';++b){
			
		}
	}
	for(char p='A';p<='D';++p){
		int count=(x==p)+(y!=p)+(z==p)+(q!=p);
		if(2==count){
			res[p-'A']=1;
		}
	}
	for(int i=0;i<4;++i){
		if(res[i]) cout<<char('A'+i);
	}
	return 0;
}*/ 




#include<iostream>

using namespace std;

int main(){
	string a,b,c,d;
	cin>>a>>b>>c>>d;
	int t1=(a[0]*10+a[1]-480-48)*60+a[3]*10+a[4]-480-48;
	int t2=(b[0]*10+b[1]-480-48)*60+b[3]*10+b[4]-480-48;
	int t3=(c[0]*10+c[1]-480-48)*60+c[3]*10+c[4]-480-48;
	if(t3>1439) t3=(c[0]-48)*60+c[2]*10+c[3]-480-48
	int t4=(d[0]*10+d[1]-480-48)*60+d[3]*10+d[4]-480-48;
	if(t1>t3){
		int temp=t1;
		t1=t3;
		t3=temp;
		temp=t2;
		t2=t4;
		t4=temp;
	}
	if(t1==t3&&t2>t4){
		int temp=t2;
		t2=t4;
		t4=temp;
	}
	if(t2<=t3) cout<<-1;
	else{
		cout<<min(t2,t4)-t3;
	}
	return 0;
}




/*#include<iostream>

using namespace std;

bool a[10000]={0};

int main(){
	int n,m;
	cin>>n>>m;
	int *t=new int[m];
	for(int i=0;i<m;++i){
		cin>>t[i];
		a[t[i]-1]=true;
	}
	bool all=1;
	for(int i=0;i<n;++i){
		if(!a[i]){
			cout<<i+1<<' ';
			all=0;
		}
	}
	if(all) cout<<"ALL";
	return 0;
}*/
