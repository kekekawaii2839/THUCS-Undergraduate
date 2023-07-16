/*#include <iostream>
using namespace std;
bool checkSpecial(int i, int n);

int main() {
    int n;
    cin >> n;
    for (int i = 10000; i < 1000000; i ++) {
        if (checkSpecial(i, n)) {
            cout << i << endl;
        }
    }
    return 0;
}

bool checkSpecial(int i, int n){
	bool flag=false;
	if(i<100000){
		if(i/10000==i%10){
			if((i-i/10000*10000)/1000==(i-i/100*100)/10) flag=true;
		}
	}
	else{
		if(i/100000==i%10){
			if((i-i/100000*100000)/10000==(i-i/100*100)/10){
				if((i-i/10000*10000)/1000==(i-i/1000*1000)/100) flag=true;
			}
		}
	}
	if(!flag) return false;
	int sum=0;
	int t=i;
	while(t>=10){
		sum+=t%10;
		t=t/10;
	}
	sum+=t;
	if(sum==n) return true;
	else return false;
}
*/

/*#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main(){
	string a;
	cin>>a;
	int sum=0;
	for(int i=3;i>=0;--i){
		sum+=(a[3-i]-48)*pow(2,i);
	}
	cout<<sum<<endl;
	return 0;
}*/

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
	float a,b,c;
	cin>>a>>b>>c;
	float p=(a+b+c)/2;
	float s=sqrt(p*(p-a)*(p-b)*(p-c));
	cout<<fixed<<setprecision(2)<<s<<endl;
	return 0;
}
