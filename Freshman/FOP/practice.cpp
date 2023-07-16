#include<iostream>

using namespace std;

int main(){
	string n,c;
	//getline(cin,n);
	for(char i=32;i<=126;++i) n+=i;
	cout<<n;
	cin>>c;
	int a[100]={0},num=0;
	for(int i=0;i<c.length();++i) a[num++]=c[i]-'0';
	int p=0;
	for(int i=0;i<n.length();++i){
		if(n[i]>='A' and n[i]<='Z') n[i]+=32;
		if(n[i]>='a' and n[i]<='z'){
			n[i]=(n[i]+a[p++]-'a')%26+'a';
			if(p==num) p=0;
		}
	}
	cout<<n;
	return 0;
}




/*#include<iostream>
#include<algorithm>

using namespace std;

class pos{
public:
	int x,y;
	pos& operator+(const pos& a){
		pos res={this->x+a.x,this->y+a.y};
		return res;
	}
	bool operator==(const pos&a){
		return (this->x==a.x)&&(this->y==a.y);
	}
}mov[4]={{1,2},{1,-2},{2,1},{2,-1}},bar[4]={{0,1},{0,-1},{1,0},{1,0}};

pos me[225];

int main(){
	int k=3;
	me[0]={0,1};me[1]={1,1};me[2]={1,2};
	pos a={0,0},b={1,1};
	cout<<(a+mov[0]).x<<' '<<(a+mov[0]).y<<endl;
	cout<<(find(me,me+k,pos(a+mov[0]))==me+k)<<endl<<(find(me,me+k,b)==me+k);
	return 0;
}*/




/*#include<iostream>//分书问题 

using namespace std;

bool like[10][10];
int assigned[10]={0};
int n;

void ttry(int reader){
	if(reader>=n){
		for(int i=0;i<n;++i) cout<<assigned[i]<<' ';
		cout<<endl;
		return;
	}
	for(int i=0;i<n;++i){
		if(0==assigned[i]&&like[reader][i]){
			assigned[i]=reader+1;
			ttry(reader+1);
			assigned[i]=0;
		}
	}
}

int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j) cin>>like[i][j];
	}
	ttry(0);
	return 0;
}*/



/*#include<iostream>
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
	bool operator==(const shit&a){
		return (this->color==a.color)&&(this->shape==a.shape);
	}
};

static bool biggershit(shit &a,shit &b){
	if(a.color==b.color) return a.shape<b.shape;
	else return a.color<b.color;
}

int main(){
	shit a[]={{"RED","DEER"},{"YELLOW","TIGER"},{"GREEN","CAT"},{"ORANGE","MOUSE"},{"ORANGE","DRAGON"}};
	sort(a,a+5,biggershit);
	for(int i=0;i<5;++i) cout<<a[i].color<<' '<<a[i].shape<<endl;
	shit target={"RED","DEER"};
	shit *b=find(a,a+5,target);
	cout<<"-----------------------"<<endl;
	cout<<b->color<<' '<<b->shape;
    return 0;
}*/
