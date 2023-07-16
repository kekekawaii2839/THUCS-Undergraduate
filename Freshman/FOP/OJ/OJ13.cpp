#include<iostream>

using namespace std;

int main(){
	int ans[5][2];
	bool state[5]={1,1,1,1,1};
	int sol=0;
	bool flag=true;
	for(int i=0;i<5;++i) cin>>ans[i][0]>>ans[i][1];
	for(int i=0;i<5;++i){
		state[i]=false;
		for(int ii=i+1;ii<5;++ii){//Ã¶¾Ù¼äµý
			state[ii]=false;
			for(int j=0;j<5;++j){
				if(state[j]){
					if(state[ans[j][0]-1]!=ans[j][1]){
						flag=false;
						break;
					}
				}
				else{
					if(state[ans[j][0]-1]==ans[j][1]){
						flag=false;
						break;
					}
				}
			}
			if(flag){
				++sol;
				//cout<<i<<' '<<ii<<endl;
			}
			flag=true;
			for(int j=0;j<5;++j) state[j]=true;
			state[i]=false;
		}
	}
	cout<<sol;
	return 0;
}




/*#include<iostream>
#include<string.h>

using namespace std;

string toUpper(string a){
	for(int i=0;i<a.size();++i){
		if(islower(a[i])) a[i]+='A'-'a';
	}
	return a;
}

string toLower(string a){
	for(int i=0;i<a.size();++i){
		if(isupper(a[i])) a[i]-='A'-'a';
	}
	return a;
}

string reverse(string a){
	for(int i=0;i<a.size()/2;++i){
		char temp=a[i];
		a[i]=a[a.size()-i-1];
		a[a.size()-i-1]=temp;
	}
	return a;
}

string upperlower(string a){
	for(int i=0;i<a.size();++i){
		if(islower(a[i])){
			a[i]+='A'-'a';
			continue;
		}
		if(isupper(a[i])){
			a[i]-='A'-'a';
			continue;
		}
	}
	return a;
}

string compress(string a){
	a=toLower(a);
	if(a.size()<3) return a;
	for(int i=0;i<a.size()-2;++i){
		if(a[i+2]==a[i+1]+1&&a[i+1]==a[i]+1){
			int j=i+1,val=a[i];
			while(a[j]==val+1){
				val=a[j];
				++j;
			}
			string re;
			re+=a[i];
			re+="-";
			re+=a[j-1];
			a.replace(a.begin()+i,a.begin()+j,re);
		}
	}
	return a;
}

int main(){
	int comm;
	string a;
	cin>>comm>>a;
	switch(comm){
		case 1:
			cout<<toUpper(a);
			break;
		case 2:
			cout<<toLower(a);
			break;
		case 3:
			cout<<reverse(a);
			break;
		case 4:
			cout<<upperlower(a);
			break;
		case 5:
			cout<<compress(a);
			break;
	}
	return 0;
}*/




/*#include<iostream>

using namespace std;

int dp[2001][2001];

int main(){
	string a,b;
	cin>>a>>b;
	for(int i=1;i<=a.size();++i) dp[i][0]=i;
	for(int i=1;i<=b.size();++i) dp[0][i]=i;
	for(int i=0;i<a.size();++i){
		for(int j=0;j<b.size();++j){
			if(a[i]==b[j]) dp[i+1][j+1]=dp[i][j];
			else dp[i+1][j+1]=min(min(dp[i+1][j],dp[i][j+1]),dp[i][j])+1;
		}
	}
	cout<<dp[a.size()][b.size()];
	return 0;
}*/




/*#include<iostream>

using namespace std;

int dp[1001];
int dd[2][100];

int main(){
	int t,m;
	cin>>t>>m;
	for(int i=0;i<m;++i) cin>>dd[0][i]>>dd[1][i];
	for(int i=0;i<m;++i){
		for(int j=t;j>=dd[0][i];--j){
			dp[j]=max(dp[j],dp[j-dd[0][i]]+dd[1][i]);
		}
	}
	//for(int i=1;i<=t;++i) cout<<dp[i]<<' ';
	//cout<<endl;
	cout<<dp[t];
	return 0;
}*/




/*#include<iostream>

using namespace std;

int dp[1001][1001];

int main(){
	string a,b;
	cin>>a>>b;
	for(int i=0;i<a.size();++i){
		for(int j=0;j<b.size();++j){
			if(a[i]==b[j]){
				dp[i+1][j+1]=dp[i][j]+1;
			}
			else dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
		}
	}
	cout<<dp[a.size()][b.size()];
	return 0;
}*/
