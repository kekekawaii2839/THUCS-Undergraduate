#include <iostream>
#include <algorithm>

struct line
{
    double w;
    int x, y;
    bool operator<(const line& a) const
    {
        return w < a.w;
    }
};

int n;
line* a;
int* seq;
double d = 0, min_d = 10e8;

void init(){
    std::cin >> n;
    a = new line[n*(n-1)/2];
    for(int i=0; i<n*(n-1)/2; i++){
        std::cin >> a[i].w;
    }
    int tmp = 0;
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            a[tmp].x = i+1;
            a[tmp].y = j+1;
            ++tmp;
        }
    }
    std::sort(a, a+n*(n-1)/2);
}

bool H(){
    int* tmp = new int[n];
    for(int i=0; i<n; ++i){
        tmp[i] = 0;
    }
    bool f = true;
    for(int i=0; i<n; ++i){
        ++tmp[a[seq[i]].x-1];
        ++tmp[a[seq[i]].y-1];
        if(tmp[a[seq[i]].x-1] > 2 || tmp[a[seq[i]].y-1] > 2){
            f = false;
            break;
        }
    }
    for(int i=0; i<n; ++i){
        if(tmp[a[seq[i]].x-1] != 2 || tmp[a[seq[i]].y-1] != 2){
            f = false;
            break;
        }
    }
    delete[] tmp;
    return f;
}

void findComb(int* nums, int start, int index){
    if(start == n){
        if(H()){
            for(int i=0; i<n; ++i) d += a[seq[i]].w;
            min_d = std::min(min_d, d);
            d = 0;
            for(int i=0; i<n; ++i) std::cout << seq[i] << " ";
            std::cout << std::endl;
            std::cout << "min_d=" << min_d << std::endl;
        }
        return;
    }
    for(int i=index; i<n*(n-1)/2; ++i){
        nums[start] = i;
        findComb(nums, start+1, i+1);
        nums[start] = -1;
    }
}

int main(){
    init();
    seq = new int[n];
    for(int i=0; i<n; ++i){
        seq[i] = -1;
    }
    findComb(seq, 0, 0);
    std::cout << min_d << std::endl;
    return 0;
}