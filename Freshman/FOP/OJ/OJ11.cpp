#include<iostream>

using namespace std;

int n,num=0;
int a[13][13];//-1是坑 0是空 1是有皇后

void show(){
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(a[i][j]!=-1) cout<<a[i][j]<<' ';
            else cout<<"* ";
        }
        cout<<endl;
    }
    cout<<"-----------"<<endl;
}

bool possible(int i,int j){
	if(-1==a[i][j]) return false;
	for(int x=0;x<i;++x){
		if(a[x][j]==1) return false;
	}
	for(int y=0;y<j;++y){
		if(a[i][y]==1) return false;
	}
	for(int x=i,y=j;x>=0&&y>=0;--x,--y){
		if(a[x][y]==1) return false;
	}
	for(int x=i,y=j;x<n&&y<n;++x,++y){
		if(a[x][y]==1) return false;
	}
	for(int x=i,y=j;x>=0&&y<n;--x,++y){
		if(a[x][y]==1) return false;
	}
	for(int x=i,y=j;x<n&&y>=0;++x,--y){
		if(a[x][y]==1) return false;
	}
	return true;
}

void f(int nn,int line){
	if(0==nn) show();
	if(num+nn<n) num=n-nn;
	if(num>=n+n-line-nn) return;
	if(nn+line<num) return;
	if(0==nn||line>=n) return;

	for(int j=0;j<n;++j){
		if(possible(line,j)){
			a[line][j]=1;
			f(nn-1,line+1);
			a[line][j]=0;
		}
	}
	f(nn,line+1);
}

int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cin>>a[i][j];
			a[i][j]-=1;
		}
	}
	f(n,0);
	cout<<num;
	return 0;
}




/*#include<iostream>
 
using namespace std;
 
int n,sol=0;
bool a[10][10];
 
void show(){
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j) cout<<a[i][j]<<' ';
        cout<<endl;
    }
    cout<<"-----------"<<endl;
}
 
bool possible(int i,int j){
    for(int x=0;x<i;++x){
        if(a[x][j]) return false;
    }
    for(int y=0;y<j;++y){
        if(a[i][y]) return false;
    }
    for(int x=i,y=j;x>=0&&y>=0;--x,--y){
        if(a[x][y]) return false;
    }
    for(int x=i,y=j;x<n&&y<n;++x,++y){
        if(a[x][y]) return false;
    }
    for(int x=i,y=j;x>=0&&y<n;--x,++y){
        if(a[x][y]) return false;
    }
    for(int x=i,y=j;x<n&&y>=0;++x,--y){
        if(a[x][y]) return false;
    }
    
    return true;
}
 
void f(int nn,int line){
    //show();
    if(0==nn){
        ++sol;
        return;
    }
    
    for(int j=0;j<n;++j){
        bool ff=possible(line,j);
        if(ff){
            a[line][j]=1;
            f(nn-1,line+1);
            a[line][j]=0;
        }
    }
}
 
int main(){
    cin>>n;
    f(n,0);
    cout<<sol;
    return 0;
}*/



/*#include<iostream>
 
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
    bool flag[4]={1,1,1,1};
    ++counter;
    if(start==eend) return 1;
    if(start.x>=eend.x) return 0;
    if(start.y>eend.y) return 0;
    if(start.y<0) return 0;
    for(int i=0;i<k;++i){
        if(start==chess[i]) return 0;
        if(start.x==chess[i].x&&start.y+1==chess[i].y) flag[0]=0;
        if(start.x+1==chess[i].x&&start.y==chess[i].y){
            flag[1]=0;
            flag[3]=0;
        }
        if(start.x==chess[i].x&&start.y==1+chess[i].y) flag[2]=0;
    }
    return flag[0]*calc(start+a)+flag[1]*calc(start+b)+flag[2]*calc(start+c)+flag[3]*calc(start+d);
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
}*/



/*#include<iostream>

using namespace std;

int n;
bool like[10][10];
int take[10];
bool have[10];

void f(int d){
	if(d==n){
		for(int i=0;i<n;++i) cout<<take[i]+1<<' ';
		cout<<endl;
		return;
	}
	
	for(int i=0;i<n;++i){
		if(like[i][d]&&!have[i]){
			take[d]=i;
			have[i]=1;
			f(d+1);
			have[i]=0;
		}
	}
}

int main(){
	cin>>n;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cin>>like[i][j];
			take[j]=have[j]=0;
		}
	}
	
	f(0);
	
	return 0;
}*/
