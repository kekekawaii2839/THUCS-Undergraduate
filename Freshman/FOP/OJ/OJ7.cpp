#include <iostream>
using namespace std;

struct Node{
    int x, y;
} a, b;

Node mean(Node a,Node b){
	Node c;
	c.x=(a.x+b.x)/2;
	c.y=(a.y+b.y)/2;
	return c;
}

int main() {
  
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    
    Node c = mean(a,b);
    cout<< c.x << " "<<c.y << endl;
    return 0;
}


/*#include<iostream>

using namespace std;

int f(int a,int b){
	int res=1;
	for(int i=b;i>=b-a+1;--i) res*=i;
	int u=1;
	for(int i=1;i<=a;++i) u*=i;
	res=res/u;
	return res;
}

int main(){
	int n=0,x=0,y=0;
	cin>>n>>x>>y;
	if(x==y){
		if(0==n%x){
			cout<<1;
			return 0;
		}
		else{
			cout<<"sorry"<<endl;
			return 1;
		}
	}
	
	int res=0;
	int a=n/x,b=n/y;
	for(int i=0;i<=a;++i){
		for(int j=0;j<=b;++j){
			if(i*x+j*y==n){
				if(0!=i&&0!=j) res+=f(i,i+j);
				else ++res;
				//cout<<i<<' '<<j<<' '<<res<<endl;
			}
		}
	}
	if(0==res) {
		cout<<"sorry"<<endl;
		return 1;
	}
	cout<<res<<endl;
	return 0;
}





/*#include<iostream>

using namespace std;

string reverse(string a){
	string res;
	for(int i=a.length()-1;i>=0;--i) res.push_back(a[i]);
	return res;
}

bool isLetter(char a){
	if(a>='a'&&a<='z') return true;
	else if(a>='A'&&a<='Z') return true;
	else return false;
}

int main(){
	string res;
	char buf[100]={0};
	cin.get(buf,100);
	string a(buf);
	for(int i=0;i<a.length();++i){
		if(a[i]>='A'&&a[i]<='Z') a[i]+=32;
		if(!isLetter(a[i])&&!(a[i]>=48&&a[i]<=57)){
			a.erase(a.begin()+i);
			--i;
		}
	}
	cout<<(a==reverse(a));
	return 0;
}*/









/*#include<iostream>
#include<string>
#include<cstring>

using namespace std;

bool isLetter(char a){
	if(a>='a'&&a<='z') return true;
	else if(a>='A'&&a<='Z') return true;
	else return false;
}

string reverse(string a){
	string res;
	for(int i=a.length()-1;i>=0;--i) res.push_back(a[i]);
	return res;
}

int main(){
	string res;
	char buf[5000]={0};
	cin.get(buf,5000);
	string a(buf);
	string temp;
	for(int i=0;i<a.length();++i){
		if(isLetter(a[i])) temp+=a[i];
		else{
			res+=reverse(temp)+a[i];
			temp="";
		}
		if(a.length()==i+1) res+=reverse(temp);
	}
	cout<<res;
	return 0;
}*/
