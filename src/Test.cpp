
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <typeinfo>
#include <iterator>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <type_traits>

using namespace std;

void convertTest() {
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

struct BadClass {
    BadClass() { throw std::runtime_error(""); }
};

enum class AllocatorType { AllocatorX,AllocatorY };

void *operator new(size_t size, AllocatorType type) {
    cout<<"new allocator type : "<<static_cast<underlying_type<AllocatorType>::type>(type)<<endl;
    return malloc(size);
}

void operator delete(void *p, AllocatorType type) {
    free(p);
}

using INT32 = uint32_t;

int main(int argc, char *argv[]) {
    INT32 reval = 0;
    try {
        BadClass *a = new(AllocatorType::AllocatorY) BadClass;
    } catch (const std::exception &) { }


    int *i = new(AllocatorType::AllocatorY) int;
    delete i;
    /*
      Single stepping until exit from function _ZdlPv@plt,
      which has no line number information.
      0x00000000004044f0 in ?? ()
     */

}


class TestA {
public:
    int a;
    TestA() : a{0} {
    }
};


enum class AllocatorType{
    AllocatorX,
    AllocatorY
};

void *operator new(size_t s,AllocatorType at) {
    cout<<"alloc from "<<(int)(at)<<endl;
    malloc(s);
}

void operator delete(void *p,AllocatorType at) {
        cout<<"free from "<<(int)(at)<<endl;
    free(p);
}


int main(int argc, char *argv[]) {
    TestA *a = new TestA();
    TestA *b = new TestA;

    int *d = new int();
    int *c = new int;

    int *x = new(AllocatorType::AllocatorY) int;
    delete(AllocatorType::AllocatorY) x;
}



