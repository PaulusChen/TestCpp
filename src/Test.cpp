
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <typeinfo>
#include <cstring>

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


template<typename T>
int testfunc2(T t) {
    cout<<"typeid of lambda : "<<typeid(t).name()<<endl;
    t();
    return 0;
}

template<typename T>
int testfunc(T t) {
    char *oldname = (char *)typeid(t).name();
    // strcpy(oldname,"cpmark");
    testfunc2(t);
    return 0;
}

class TestConstructor
{
   public:
    //! Default constructor
    TestConstructor() {
        cout<<"default constructor"<<endl;
    }

    //! Copy constructor
    TestConstructor(const TestConstructor &other);

    //! Move constructor
    TestConstructor(TestConstructor &&other) noexcept;

    //! Destructor
    virtual ~TestConstructor() noexcept;

    //! Copy assignment operator
    TestConstructor &operator=(const TestConstructor &other);

    //! Move assignment operator
    TestConstructor &operator=(TestConstructor &&other) noexcept;

   protected:
   private:
};


//user(vector<int>{1,2,3,4,5});
//testfunc([](){ cout<<"test lambda"<<endl; });

auto const testValA = 100;
auto constexpr testValB = 100;

int use2() {
    cout << "type name : " << typeid(decltype(testValA)).name() << endl;
    auto x = decltype(testValA){10};
    cout << "type name : " << typeid(decltype(x + 100)).name()
         << " the value is " << x << endl;

    int a = 100;
    int &ra = a;
    auto autora = ra;
    cout << "Is lvalue reference: " << is_lvalue_reference<decltype(autora)>::value << endl;
    auto &autorra = ra;
    cout << "Is lvalue reference: " << is_lvalue_reference<decltype(autorra)>::value << endl;

    auto autoval1{100};
    cout<<"type of autoval1 : "<<typeid(autoval1).name()<<endl;
    auto autoval2 = {100};
    cout<<"type of autoval2 : "<<typeid(autoval2).name()<<endl;
    auto autoval3 = {100, 200, 300}; //error :  direct-list-initialization of ‘auto’ requires exactly one element [-fpermissive]
    cout << "type of autoval3 : " << typeid(autoval3).name() << endl;

    using Char2 = char;
    //unsigned Char2 testval; //error: expected initializer before ‘testval’
    //using Uchar = unsigned char;

    // int *test = static_cast<int *>(123); // invalid static_cast from type ‘int’ to type ‘int*’
    int *test = static_cast<int *>((void *)123);
    int *test2 = reinterpret_cast<int *>(123);

    void (*userfun)(const vector<int> &) = user;
    //void *testPtr = userfun; //error: invalid conversion from ‘void (*)(const std::vector<int>&)’ to ‘void*’ [-fpermissive]
    return 0;
}


int testArrayParam(uint8_t ta[100]) {
    cout<<"sizeof(ta) in fun:"<<sizeof(ta)<<" typeid(ta):"<<typeid(ta).name()<<endl;
    // sizeof(ta) in fun:8 typeid(ta):Ph
    return ta[0];
}

int testStr() {
    uint8_t testArray[100];
    uint8_t testArray2[100];
    // testArray2 = testArray; // error: invalid array assignment
    // uint8_t &rtestArray[100] = testArray; // error: declaration of ‘rtestArray’ as array of references
    // uint8_t (&rtestArray)[] = testArray; // error: invalid initialization of reference of type ‘uint8_t (&)[] {aka unsigned char (&)[]}’ from expression of type ‘uint8_t [100] {aka unsigned char [100]}’
    uint8_t (&rtestArray)[100] = testArray;
    cout<<"sizeof(ta) in main:"<<sizeof(rtestArray)<<" typeid(ta):"<<typeid(rtestArray).name()<<endl;
    // sizeof(ta) in main:100 typeid(ta):A100_h
    testArrayParam(rtestArray);
    // uint32_t intArray[2] = {1, 2, 3}; // error: too many initializers for ‘uint32_t [2] {aka unsigned int [2]}’
    char *str = "test string"; // warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
    // str[2] = 'a';
    const char *rawStr = R"(abcx123\\ "")";
    const char *rawStr2 = R"*ab(abcx123\\ "")*ab";

    cout << rawStr << endl;
    cout << rawStr2 << endl;

    const char *testc = "testc";
    const char *testu8 = u8"testu8";
    const char *testu8r = u8R"(testu8r)";
    // const char *testu = u"testu"; // error: cannot convert ‘const char16_t*’ to ‘const char*’ in initialization
    // const wchar_t *testu1 = u"testu"; // error: cannot convert ‘const char16_t*’ to ‘const wchar_t*’ in initialization
    const char16_t *testu = u"testu";
    const char32_t *testU = U"testU";
    // const char16_t *testlu = Lu"testu"; // ‘Lu’ was not declared in this scope
    // const char16_t *testul = uL"testu"; // ‘uL’ was not declared in this scope
    const char16_t *testuR = uR"(testuR)";

    const wchar_t *testw = L"testw";
    // const char16_t *testwc16 = testw; // error: cannot convert ‘const wchar_t*’ to ‘const char16_t*’ in initialization

    char testA[] = "abcd";
    3[testA] = 'f';
    cout<<testA<<endl;
}

void testArray2(int (*pArray)[3]) { return ; }
void testArray3(int **pArray) { return; }
int testArray1() {
    int testAA[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; //这里数组间都插入了4个字节的缝隙，对齐到了16字节，不知道具体原因
    int testPA1[] = {1, 2, 3};
    int testPA2[] = {4, 5, 6};
    int testPA3[] = {7, 8, 9};
    int *testPA[] = { testPA1, testPA2, testPA3 };

    testArray2(testAA);
    // testArray3(testAA); // error: cannot convert ‘int (*)[3]’ to ‘int**’ for argument ‘1’ to ‘void testArray3(int**)’
    // testArray2(testPA); // error: cannot convert ‘int**’ to ‘int (*)[3]’ for argument ‘1’ to ‘void testArray2(int (*)[3])’
    testArray3(testPA);

    cout<<"dump testAA[i]"<<endl;
    for (int i = 0; i != 3; ++i)
        cout<<" i : "<<i<<" val : "<<*testAA[i]<<endl;

    cout<<"dump testPA[i]"<<endl;
    for (int i = 0; i != 3; ++i)
        cout << "i : " << i << " val : " << testPA[i] << endl;

    cout<<"dump testPA"<<endl;
    for (int i = 0; i != 3; ++i)
        for (int j = 0; j != 3; ++j)
            cout<<"i : "<<i<<" j : "<<j<<" val : "<<testPA[i][j]<<endl;
}

int main(int argc, char *argv[]) {

    testArray1();
}
