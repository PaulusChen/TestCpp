
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <typeinfo>
#include <iterator>
#include <cstring>
#include <iomanip>
#include <new>
#include <algorithm>
#include <type_traits>
#include <new>
#include <functional>

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
    BadClass() { throw std::runtime_error("init failed"); }
    ~BadClass() { throw std::runtime_error(""); }
};

enum class AllocatorType { AllocatorX,AllocatorY };

void *operator new(size_t size, AllocatorType type) {
    cout<<"new allocator type : "<<static_cast<underlying_type<AllocatorType>::type>(type)<<endl;
    return malloc(size);
}

void operator delete(void *p, AllocatorType type) {
    free(p);
}

void OperatorNewOverload() {

    // int *i = new(AllocatorType::AllocatorY) int;
    // delete i;
    /*
      Single stepping until exit from function _ZdlPv@plt,
      which has no line number information.
      0x00000000004044f0 in ?? ()
    */
    BadClass *a = new(nothrow) BadClass;
    try {
        cout<<"try"<<endl;
    } catch (const std::exception &e) {
        cout<<e.what()<<" in testfunc"<<endl;
    }
    cout<<"finished"<<endl;
}

void testnothrow() {
    try {
        OperatorNewOverload();
    } catch (const std::exception &e) {
        cout<<e.what()<<" in main"<<endl;
    }
}

int test_f(int a) { return a; }

int test_initializer() {
    int v {7};
    int v2 = {7};

    int testarray[5];
    // testarray[{1}]; // error: array subscript is not an integer
    v = {8};
    v += {99};
    // v = 7 + {10}; error: initializer list cannot be used on the right hand side of operator '+'
    test_f({100});
    return {11};
}

struct TestBaseStruct {
    virtual void TestFunc() = 0;
};

void testFunc(TestBaseStruct *obj) {
    obj->TestFunc();
}

template<typename C>
class modulc_printer {
private:
    using elementType=typename C::value_type;
    ostream &os;
    int m;
public:
    modulc_printer(ostream&s,int mm) : os(s), m(mm) {}
    void operator()(elementType x) const {
        if (x%m==0) os<<x<<'\n';
    }
};

template<typename C>
void print_modulc(const C& v, ostream &os, int m) {
    for_each(begin(v), end(v),modulc_printer<typename remove_reference<decltype(v)>::type>(os,m));
}

template<typename C>
void print_modulf(const C& v, ostream &os, int m) {
    for(auto x : v)
        if (x%m==0) os<<x<<'\n';
}

template<typename C>
void print_modull(const C& v, ostream &os, int m) {
    // error: no viable conversion from '(lambda at /home/chenpeng/Documents/TestCpp/src/Test.cpp:104:29)' to 'int (*)(int)'
    // 这里编译器会在线生成一个闭包对象类型，因为函数指针无法携带捕获的函数变量等信息，所以lambda不是一个单纯的函数对象
    // int (*lambdaobj)(int) = [&os,m](int x){ if (x%m==0) os<<x<<'\n'; };

    // error: variable 'lambdaobj' declared with 'auto' type cannot appear in its own initializer
    // auto lambdaobj = [&os,m,&lambdaobj](int x){ if (x%m==0) os<<x<<'\n'; if(x != 100) lambdaobj(100); };

    // std::function<int(int)> lambdaobj = [&os,m,&lambdaobj](int x)->int { if (x%m==0) os<<x<<'\n'; if(x != 100) lambdaobj(100); return 0; };

    std::function<void(int)> lambdaobj = [&os,m,&lambdaobj](int x) { if (x%m==0) os<<x<<'\n'; if(x != 100) lambdaobj(100); };
    for_each(begin(v), end(v), lambdaobj);
}

void testlambda1() {
    vector<int> testvec{1,2,3,4,5,6,7,8,9};
    print_modull(testvec,cout,2);
    print_modulf(testvec,cout,2);
    print_modulc(testvec,cout,2);
}

int TestLambdaCapture(std::function<int(void)> &lambdaObj)
{
    int testval = 100;
    std::function<void(void)> lambdaObj2 = [testval]() {
        // error: cannot assign to a variable captured by copy in a non-mutable lambda
        // testval = 200;
    };
    std::function<void(void)> lambdaObj1 = [testval]() mutable {
        testval = 200;
    };
    lambdaObj = [&testval]() -> int {
        return testval;
    };
    cout<<lambdaObj()<<endl;
    return 0;
}

int testlambda2() {
    std::function<int(void)> lambdaObj;
    TestLambdaCapture(lambdaObj);
    cout<<lambdaObj()<<endl;

    int (*testFunPtr)(int) = [](int a) -> int { return a; };
}

class TestLambdaThisCap {
private:
    int testa;
public:
    std::function<int(void)> testfunc() { return [this]()->int { return testa; };}
};

int main(int argc, char *argv[]) {
    TestLambdaThisCap test;
    std::function<int(void)> testl = test.testfunc();
    int reval = testl(); //注意这里调用testl的时机不能超出test对象的生命周期，否则this为垂悬指针
}






















