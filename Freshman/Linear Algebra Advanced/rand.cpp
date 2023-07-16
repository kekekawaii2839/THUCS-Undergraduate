#include <iostream>
#include <ctime>

using namespace std;

int main(){
    size_t n = 0;
    srand(time(0));
    for(size_t i = 0; i < 1e7; ++i){ 
        bool f = false;
        int life = 3;
        int round = 0;
        while(life > 0){
            int r = rand() % 4;
            if(r != 0){
                --life;
            }
            ++round;
        }
        //cout<<"round = "<<round<<endl;
        n += round;
    }
    cout<<n<<endl;
    double res = n * 1e-7;
    cout<<res<<endl;
}