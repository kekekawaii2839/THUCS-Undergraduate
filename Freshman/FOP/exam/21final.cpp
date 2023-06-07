/*#include<iostream>

using namespace std;

int a[50000]={0};

int main(){
	int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;++i){
    	cin>>a[i];
    	a[i]+=a[i-1];
	}
	int minn=1e8,index1,indextemp,index2;//因为数据范围最大是50000*1000 所以minn初始值至少要是5e7 
	int val=minn;
	for(int i=k;i+k<=n;++i){
		if(a[i]<val+a[i-k]){
			val=a[i]-a[i-k];
			indextemp=i-k;
		}
		//cout<<"val="<<val<<" minn="<<minn<<" a["<<i+k<<"]="<<a[i+k]<<" a["<<i<<"]="<<a[i]<<endl;
		if(val+a[i+k]<minn+a[i]){
			minn=val+a[i+k]-a[i];
			index1=indextemp;
			index2=i;
		}
	}
	cout<<index1+1<<' '<<index2+1;
	return 0;
}*/




/*#include<iostream>
 
using namespace std;
 
int a[50000];
int r[50000]={0};
 
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;++i) cin>>a[i];
    for(int i=0;i<k;++i) r[0]+=a[i]; 
    for(int i=1;i<=n-k;++i){
    	r[i]=r[i-1]+a[k+i-1]-a[i-1];
	}
	//for(int i=0;i<n;++i) cout<<r[i]<<' ';
	//cout<<endl;
	int sum=99999999,index1,index2;
	for(int i=0;i+k+k<=n;++i){
		for(int j=i+k;j+k<=n;++j){
			if(r[i]+r[j]<sum){
				sum=r[i]+r[j];
				index1=i;
				index2=j;
			}
		}
	}
    cout<<index1+1<<' '<<index2+1;
    return 0;
}*/




#include<iostream>
#include<algorithm>

using namespace std;

class shit{
public:
	string color,shape;
	bool operator<=(const shit& a){
		if(this->color==a.color) return this->shape<=a.shape;
		else return this->color<=a.color;
	}
	bool operator>=(const shit& a){
		if(this->color==a.color) return this->shape>=a.shape;
		else return this->color>=a.color;
	}
}poop[1000];

static bool biggershit(shit &a,shit &b){
	if(a.color==b.color) return a.shape<b.shape;
	else return a.color<b.color;
}

int index=0,n;

void create(string c,string s){
	poop[index].color=c;
	poop[index++].shape=s;
}

void dup(int m,string c){
	poop[index].color=c;
	poop[index++].shape=poop[m-1].shape;
}

void crash(int m){
	for(int i=m-1;i<index;++i){
		poop[i]=poop[i+1];
	}
	poop[index].color="";
	poop[index--].shape="";
}

void order(int left,int right){
	if(right<=left) return;
	int l=left,r=right;
	shit key=poop[left];
	while(l<r){
		while(poop[r]>=key&&l<r) --r;
		while(poop[l]<=key&&l<r) ++l;
		swap(poop[l],poop[r]);
	}
	swap(poop[left],poop[l]);
	order(left,l-1);
	order(l+1,right);
}

int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		string comm;
		cin>>comm;
		if("CREATE"==comm){
			string a,b;
			cin>>a>>b;
			create(a,b);
		}
		else if("DUP"==comm){
			string a;
			int b;
			cin>>b>>a;
			dup(b,a);
		}
		else if("CRASH"==comm){
			int a;
			cin>>a;
			crash(a);
		}
		else if("ORDER"==comm){
			sort(poop,poop+index,biggershit);
			//order(0,index-1);
		}
	}
	for(int i=0;i<index;++i) cout<<poop[i].color<<' '<<poop[i].shape<<endl;
	return 0;
}




/*#include<iostream>

using namespace std;

int n;
char a[100][100];
bool mask[100][100]={0};

int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j) cin>>a[i][j];
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n-6;++j){
			if(a[i][j]=='p'&&a[i][j+1]=='r'&&a[i][j+2]=='o'&&a[i][j+3]=='g'&&a[i][j+4]=='r'&&a[i][j+5]=='a'&&a[i][j+6]=='m'){
				mask[i][j]=mask[i][j+1]=mask[i][j+2]=mask[i][j+3]=mask[i][j+4]=mask[i][j+5]=mask[i][j+6]=true;
			}
			else if(a[i][j]=='m'&&a[i][j+1]=='a'&&a[i][j+2]=='r'&&a[i][j+3]=='g'&&a[i][j+4]=='o'&&a[i][j+5]=='r'&&a[i][j+6]=='p'){
				mask[i][j]=mask[i][j+1]=mask[i][j+2]=mask[i][j+3]=mask[i][j+4]=mask[i][j+5]=mask[i][j+6]=true;
			}
		}
	}
	for(int j=0;j<n;++j){
		for(int i=0;i<n-6;++i){
			if(a[i][j]=='p'&&a[i+1][j]=='r'&&a[i+2][j]=='o'&&a[i+3][j]=='g'&&a[i+4][j]=='r'&&a[i+5][j]=='a'&&a[i+6][j]=='m'){
				mask[i][j]=mask[i+1][j]=mask[i+2][j]=mask[i+3][j]=mask[i+4][j]=mask[i+5][j]=mask[i+6][j]=true;
			}
			else if(a[i][j]=='m'&&a[i+1][j]=='a'&&a[i+2][j]=='r'&&a[i+3][j]=='g'&&a[i+4][j]=='o'&&a[i+5][j]=='r'&&a[i+6][j]=='p'){
				mask[i][j]=mask[i+1][j]=mask[i+2][j]=mask[i+3][j]=mask[i+4][j]=mask[i+5][j]=mask[i+6][j]=true;
			}
		}
	}
	for(int i=n-7;i>=0;--i){
		for(int ii=0;ii<n-6;++ii){
			if(a[i][ii]=='p'&&a[i+1][ii+1]=='r'&&a[i+2][ii+2]=='o'&&a[i+3][ii+3]=='g'&&a[i+4][ii+4]=='r'&&a[i+5][ii+5]=='a'&&a[i+6][ii+6]=='m'){
				mask[i][ii]=mask[i+1][ii+1]=mask[i+2][ii+2]=mask[i+3][ii+3]=mask[i+4][ii+4]=mask[i+5][ii+5]=mask[i+6][ii+6]=true;
			}
			else if(a[i][ii]=='m'&&a[i+1][ii+1]=='a'&&a[i+2][ii+2]=='r'&&a[i+3][ii+3]=='g'&&a[i+4][ii+4]=='o'&&a[i+5][ii+5]=='r'&&a[i+6][ii+6]=='p'){
				mask[i][ii]=mask[i+1][ii+1]=mask[i+2][ii+2]=mask[i+3][ii+3]=mask[i+4][ii+4]=mask[i+5][ii+5]=mask[i+6][ii+6]=true;
			}
		}
	}
	for(int i=6;i<n;++i){
		for(int ii=0;ii<n-6;++ii){
			if(a[ii][i]=='p'&&a[ii+1][i-1]=='r'&&a[ii+2][i-2]=='o'&&a[ii+3][i-3]=='g'&&a[ii+4][i-4]=='r'&&a[ii+5][i-5]=='a'&&a[ii+6][i-6]=='m'){
				mask[ii][i]=mask[ii+1][i-1]=mask[ii+2][i-2]=mask[ii+3][i-3]=mask[ii+4][i-4]=mask[ii+5][i-5]=mask[ii+6][i-6]=true;
			}
			else if(a[ii][i]=='m'&&a[ii+1][i-1]=='a'&&a[ii+2][i-2]=='r'&&a[ii+3][i-3]=='g'&&a[ii+4][i-4]=='o'&&a[ii+5][i-5]=='r'&&a[ii+6][i-6]=='p'){
				mask[ii][i]=mask[ii+1][i-1]=mask[ii+2][i-2]=mask[ii+3][i-3]=mask[ii+4][i-4]=mask[ii+5][i-5]=mask[ii+6][i-6]=true;
			}
		}
	}
	
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(mask[i][j]) cout<<a[i][j];
			else cout<<'*';
		}
		cout<<endl;
	}
	return 0;
}*/




/*#include<iostream>

using namespace std;

int main(){//20280220 20491201
	string a,b;
	cin>>a>>b;
	int sum=0;
	int y1=(a[0]-48)*1000+(a[1]-48)*100+(a[2]-48)*10+(a[3]-48),y2=(b[0]-48)*1000+(b[1]-48)*100+(b[2]-48)*10+(b[3]-48);
	int m1=a[4]*10+a[5]-480-48,m2=b[4]*10+b[5]-480-48;
	int d1=a[6]*10+a[7]-480-48,d2=b[6]*10+b[7]-480-48;
	//cout<<y1<<' '<<y2<<' '<<m1<<' '<<m2<<' '<<d1<<' '<<d2<<' '<<endl;
	for(int i=y1;i<y2;++i){
		if(0==i%4) sum+=366;
		else sum+=365;
	}
	if(m1<m2){
		for(int i=m1;i<m2;++i){
			if(1==i||3==i||5==i||7==i||8==i||10==i||12==i) sum+=31;
			else if(4==i||6==i||9==i||11==i) sum+=30;
			else if(2==i&&y1%4==0) sum+=29;
			else if(2==i&&y1%4!=0) sum+=28;
		}
	}
	else if(m2<m1){
		for(int i=m2;i<m1;++i){
			if(1==i||3==i||5==i||7==i||8==i||10==i||12==i) sum-=31;
			else if(4==i||6==i||9==i||11==i) sum-=30;
			else if(2==i&&y1%4==0) sum-=29;
			else if(2==i&&y1%4!=0) sum-=28;
		}
	}
	sum+=d2-d1+1;
	if(d2==1&&m2==12) sum--;
	cout<<sum;
	return 0;
}*/




/*#include<iostream>

using namespace std;

struct pos{
	int x,y;
};

class circle{
public:
	int x,y,r;
	bool isIn(pos a){
		return r*r>=(x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
	}
};

pos a[500];
circle b[500];
int counter[500]={0};

int main(){
	int n,m;
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i].x>>a[i].y;
	cin>>m;
	for(int i=0;i<m;++i){
		cin>>b[i].x>>b[i].y>>b[i].r;
		for(int j=0;j<n;++j){
			if(b[i].isIn(a[j])){
				++counter[i];
				//cout<<"("<<a[j].x<<","<<a[j].y<<")is in("<<b[i].x<<","<<b[i].y<<","<<b[i].r<<")"<<endl;
			}
		}
	}
	for(int i=0;i<m;++i) cout<<counter[i]<<' ';
	return 0;
}*/
