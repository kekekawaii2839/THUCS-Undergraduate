#include <iostream>  	// cout
#include <cstring>    // strcmp
using namespace std;

char week_name[7][4] = { 	"mon", "tu", "wed", 
                                "thu", "fri", "sat", "sun"};

class WeekTemperature {
    int temperature[7] = {0};
    int error_temperature = -100;
public:
    int& operator[] (const char* name)  // (D)
    {
        for (int i = 0; i < 7; i++) {
            if (strcmp(week_name[i], name) == 0) 
                return temperature[i];
        }
        return error_temperature; 
    }
};

void ref(int &x) {
    cout << "left " << x << endl;
    x = 1;  // (C)
}

void ref(int &&x) {
    cout << "right " << x << endl;
    // x = 1;  // (A)
}

int main() 
{
    WeekTemperature beijing;
    beijing["mon"] = -3;	 // (B)
    ref(beijing["mon"]);
    cout 	<< "Monday Temperature: " 
            << beijing["mon"] << endl;
    return 0;
}
