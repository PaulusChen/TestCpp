
#include <iostream>
#include <stdio.h>
#include <stdint.h>

using namespace std;

constexpr int TestFun(int testval);

constexpr int TestFun(int testval) {
    return testval * 2;
}

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

constexpr int TestVal = TestFun(2);

int *TestScanBuild() {
    int testVal;
    return &testVal;
}

int main(int argc, char *argv[]) {
    int reval = TestFun(TestVal);

    TestClass *pPlus1 = new TestPlusClass(0x11111111);
    TestClass *pPlus2 = new TestPlusClass(0x22222222);
    TestClass *pMinus = new TestMinusClass;

    int (TestClass::*pFunc1)(int a, int b) = &TestClass::TestFunc;
    int (TestPlusClass::*pFunc2)(int a, int b) = &TestPlusClass::TestFunc;
    int (TestMinusClass::*pFunc3)(int a, int b) = &TestMinusClass::TestFunc;

    int a{100};
    int b = 50;

    cout<<"a plus b equel : "<<pPlus1->TestFunc(a, b)<<endl;
    cout<<"a plus b equel : "<<pPlus2->TestFunc(a, b)<<endl;

    cout<<"a minus b equel : "<<pMinus->TestFunc(a,b)<<endl;
    cout<<*TestScanBuild()<<endl;

    return 0;
}
