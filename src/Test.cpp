
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <typeinfo>
#include <iterator>
#include <cstring>
#include <iomanip>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    int i = 1234567890;
    float f = i;
    cout<<"int "<<i<<" to float "<<setprecision(16)<<f<<endl;

    double d = 123456789012345;
    i = d;
    cout<<"double "<<setprecision(16)<<d<<" to int "<<i<<endl;

    d = 0.123456789012345;
    i = d;
    cout<<"double "<<setprecision(16)<<d<<" to int "<<i<<endl;
}



