#include <iostream>
#include <vector>
#include <iomanip>

#include "func.h"
#include "constfunc.h"
#include "linearfunc.h"
#include "expfunc.h"
#include "compfunc.h"
#include "combfunc.h"

using namespace std;

Func *create_const();
Func *create_linear();
Func *create_exp();
Func *create_comp();
Func *create_comb();
Func *choice(int);

int main(){
    int n, m;
    Func * functions;
    cin >> n;
    functions = choice(n);
    cin >> m;
    for(int i = 0; i < m; i++){
        double test_point;
        cin >> test_point;
        cout << setiosflags(ios::fixed) << setprecision(5) << functions->getPoint(test_point) << endl;
    }
    delete functions;
    ConstFunc::checkMemoryLeak();
    return 0;
}

Func *create_const(){
    double c;
    cin >> c;
    return new ConstFunc(c);
}

Func *create_linear(){
    double a, b;
    cin >> a >> b;
    return new LinearFunc(a, b);
}

Func *create_exp(){
    double base;
    cin >> base;
    return new ExpFunc(base);
}

Func *create_comp(){
    int k;
    cin >> k;
    Func *g = choice(k);
    cin >> k;
    Func *f = choice(k);
    return new CompFunc(f, g);
}


Func *create_comb(){
    double a, b;
    int k;
    cin >> a >> b;
    cin >> k;
    Func *f1 = choice(k);
    cin >> k;
    Func *f2 = choice(k);
    return new CombFunc(f1, f2, a, b);
}

Func * choice(int k){
    if(k == 0){ return create_const(); }
    if(k == 1){ return create_linear(); }
    if(k == 2){ return create_exp(); }
    if(k == 3){ return create_comp(); }
    if(k == 4){ return create_comb(); }
    return nullptr;
}

