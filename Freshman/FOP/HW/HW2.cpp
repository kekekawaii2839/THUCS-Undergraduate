#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    int a,b,c,d,e,f,g=0,h=0,i=0,j=0,k=0,l=0,n=0;
    float m=0;
    cin>>a>>b>>c>>d>>e>>f;
    if(a%3 == 0&&a%2 == 1){
        g = a;
        n += 1;
    }
    if(b%3 == 0&&b%2 == 1){
        h = b;
        n += 1;
    }
    if(c%3 == 0&&c%2 == 1){
        i = c;
        n =+ 1;
    }
    if(d%3 == 0&&d%2 == 1){
        j = d;
        n += 1;
    }
    if(e%3 == 0&&e%2 == 1){
        k = e;
        n += 1;
    }
    if(f%3 == 0&&f%2 == 1){
        l = f;
        n += 1;
    }
    if(n == 0){
        m = 0;
    }else{
        m = (g+h+i+j+k+l)*1.0/n;
    }
    cout<< fixed<< setprecision(4)<< m;
    return 0;
}
