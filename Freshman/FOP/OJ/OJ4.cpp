#include <iostream>
using namespace std;
int a1 = 0,a2 = 0;
int max2(int number);

int main() {
    int res = 0;
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) {
        int num;
        cin >> num;
        res = max2(num);
    }
    cout << res << endl;
    return 0;
}

int max2(int number){
	if(number>a1){
		a2=a1;
		a1=number;
	}
	else if(number>a2) a2=number;
	return a2;
}
