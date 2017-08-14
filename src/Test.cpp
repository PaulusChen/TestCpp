
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <typeinfo>

using namespace std;

class TestClass
{
 public:
    TestClass();
    virtual int TestFunc(int a, int b);
private:
    uint32_t baseval;
};

TestClass::TestClass() {
    this->baseval = 0x33333333;
}

int TestClass::TestFunc(int a, int b) {
    return a * b;
}

class TestPlusClass : public TestClass
{
private:
    uint32_t testval;
 public:
    TestPlusClass(uint32_t val) {
        this->testval = val;
    }
  virtual int TestFunc(int a, int b);
};
int TestPlusClass::TestFunc(int a, int b) {
    TestClass::TestFunc(a, b);
    return a + b;
}

class TestMinusClass : public TestClass
{
 public:
  virtual int TestFunc(int a, int b);
};

int TestMinusClass::TestFunc(int a, int b) { return a - b; }

constexpr int TestFun(int testval);

constexpr int TestFun(int testval) {
    return testval * 2;
}

constexpr int TestVal = TestFun(2);

int *TestScanBuild() {
    int testVal;
    testVal ^= testVal;
    return &testVal;
}


void TestVTab() {
    //int reval = TestFun(TestVal);

    TestClass *pPlus1 = new TestPlusClass(0x11111111);
    TestClass *pPlus2 = new TestPlusClass(0x22222222);
    TestClass *pMinus = new TestMinusClass;

    // int (TestClass::*pFunc1)(int a, int b) = &TestClass::TestFunc;
    // int (TestPlusClass::*pFunc2)(int a, int b) = &TestPlusClass::TestFunc;
    // int (TestMinusClass::*pFunc3)(int a, int b) = &TestMinusClass::TestFunc;

    int a{100};
    int b = 50;

    cout<<"a plus b equel : "<<pPlus1->TestFunc(a, b)<<endl;
    cout<<"a plus b equel : "<<pPlus2->TestFunc(a, b)<<endl;

    cout<<"a minus b equel : "<<pMinus->TestFunc(a,b)<<endl;
    cout<<*TestScanBuild()<<endl;

}

template <typename T>
class TestUsing
{
    typedef T type_name;
   public:
    T add(T a, T b) { return a + b; }
};

template <typename T>
using NewName = TestUsing<T>;

typedef TestUsing<int> NewName2;

// template <typename T>
// typedef TestUsing<T> NewName2;

// template <typename T>
// typedef add<T> NewNameOfAdd2;

void user(const vector<int> &vi)
{
    constexpr int bufmax = 1024;
    char buffer1[bufmax];
    alignas(int) char buffer2[bufmax];
    alignas(8) char buffer3[bufmax];
    // alignas(3) char buffer3[bufmax];

    auto ai1 = alignof(buffer1);
    auto ai2 = alignof(buffer2);
    auto ai3 = alignof(buffer3);


    cout<<"alignof(buffer) : "<<ai1<<endl
        <<"and ai type is : "<<typeid(ai1).name()<<endl
        <<"buffer addr : 0x"<<ios_base::hex<<reinterpret_cast<uint64_t>(buffer1)<<endl
        <<"alignof(buffer2) : "<<ai2<<endl
        <<"buffer2 addr : 0x"<<ios_base::hex<<reinterpret_cast<uint64_t>(buffer2)<<endl
        <<"type name int : "<<typeid(bufmax).name()<<endl;

    const int max = min(vi.size(), bufmax / sizeof(int));
    uninitialized_copy(vi.begin(), vi.begin() + max, buffer1);

    using testtype = unsigned int;
}

int main(int argc, char *argv[]) {

    user(vector<int>{1,2,3,4,5});
    return 0;
}

