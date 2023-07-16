#include<iostream>
#include<string>

using namespace std;

bool func(int n){
	int i=10;
	for(i=2;i<10;++i) if(n%i==0) break;
	return (i==10);
}

int main(){
	/*string a;
	cin>>a;
	for(int i=0;i<a.length();++i){
		if(0==i%2){
			if(a[i]>=97&&a[i]<=122){
				a[i]-=32;
			}
		}
		else{
			if(a[i]>=48&&a[i]<=56) ++a[i];
			else if(57==a[i]) a[i]=48;
		}
	}
	cout<<a;*/
	
	for(int i=11;i<20;++i) cout<<i<<": "<<func(i)<<endl;
	
	return 0;
}




/*#include<iostream>

using namespace std;

int n;
int a[100]={0};

int main(){
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i];
	int min_index=0;
	int b[100]={0};
	for(int i=0;i<n;++i){
		cout<<"Insert element["<<i+1<<"]:"<<endl;
		cout<<"  Init:";
		b[i]=a[i];
		int bi=b[i];
		for(int u=0;u<=i;++u) cout<<b[u]<<' ';
		cout<<endl;
		int index=i;
		bool flag=false;
		for(int u=i-1;u>=0;--u,--index){
			if(b[u]>bi){
				b[u+1]=b[u];
				cout<<"  Move back:";
				for(int z=0;z<=i;++z) cout<<b[z]<<' ';
				cout<<endl;
			}
			else break;
		}
		//cout<<"  index="<<index<<" bi="<<bi<<" flag="<<flag<<endl;
		b[index]=bi;
		cout<<"  Final:";
		for(int u=0;u<=i;++u) cout<<b[u]<<' ';
		cout<<endl;
	}
	return 0;
}*/
