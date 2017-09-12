
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

int testArray() {
    int test[2][3];
    // int *p = test; // error: cannot convert ‘int (*)[3]’ to ‘int*’ in initialization
    int *p = test[0];
    p[3*1+2] = 1; // test[1][2];
    cout<<test[1][2]<<endl;
    // const int a; // error: uninitialized const ‘a’ [-fpermissive]

    int a = 100;
    int *pa = &a;
    const int *pa1 = &a;
    // *pa1 = 200; // error: assignment of read-only location ‘* pa1’
    int const *pa2 = &a;
    // *pa2 = 300; // error: assignment of read-only location ‘* pa2’
    pa2 = pa;
    int *const pa3 = &a;
    *pa3 = 400;
    // pa3 = pa; // error: assignment of read-only variable ‘pa3’

    testArray1();
}

int testReference() {
    const int &a = 1.0;
    // const int &a{1.0}; // error: narrowing conversion of ‘1.0e+0’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
    const int *p = &a;
    cout<<p<<endl;
}


template<typename T>
void swap(T &a, T&b) {
    T tmp{a};
    a = b;
    b = tmp;
}

template<typename T>
void new_swap(T &a, T&b) {
    T tmp{static_cast<T&&>(a)};
    a = static_cast<T&&>(b);
    b = static_cast<T&&>(tmp);
}

string f() {}
int testReference2() {
    string var;
    string &r1{var};
    // string &r2{f()}; // error: invalid initialization of non-const reference of type ‘@#$’ from an rvalue of type ‘#$%#’
    // string &r3{"test_string"}; // error: invalid initialization of non-const reference of type ‘@#$’ from an rvalue of type ‘#$%#’

    // string &&rr1{var}; // error: cannot bind ‘#$%$’ lvalue to ‘$%#’
    string &&rr2{f()};
    string &&rr3{"test_string"};

    const string &&rr4{f()};
    //new_swap(var,string("123")); // error: invalid initialization of non-const reference of type ‘@#$’ from an rvalue of type ‘@#$@’
}

// int operate+(const int &a,const int &b) {
//     return a + b;
// }

class TestOperator {
public:
    int a;
};



// static TestOperator&& operator+(const TestOperator *a, const TestOperator *b) // error: ‘TestOperator&& operator+(const TestOperator*, const TestOperator*)’ must have an argument of class or enumerated type
// { return Testperator(); }

// static int operator+(int a, int b) { // error: ‘int operator+(int, int)’ must have an argument of class or enumerated type
//     return a+b;
// }

struct S0 {};
struct S1 {int a;};
struct S2 {int a; S2(int aa):a(aa){}}; // 不是默认构造函数
struct S3 {int a; S3(int aa):a(aa){} S3(){}}; //是ＰＯＤ用户自定义默认构造函数
struct S4 {int a; S4(int aa):a(aa){} S4()=default;};
struct S5 {virtual void f();}; //虚函数
struct S6:S1{};
struct S7:S0{int b;};
struct S8:S1{int b;}; //不是ＰＯＤ数据既属于Ｓ１也属于Ｓ８
struct S9:S0,S1 {};
struct S10 {int a;int b; S10(int b,int a):a(a),b(b){}};
void S5::f() {}
template<typename T>
void PrintPODType() {
    if (is_pod<T>::value)
        cout<<typeid(T).name()<<" is POD"<<endl;
    else
        cout<<typeid(T).name()<<" is *NOT* POD"<<endl;
}

void PODTest() {
    PrintPODType<S0>();
    PrintPODType<S1>();
    PrintPODType<S2>();
    PrintPODType<S3>();
    PrintPODType<S4>();
    PrintPODType<S5>();
    PrintPODType<S6>();
    PrintPODType<S7>();
    PrintPODType<S8>();
    PrintPODType<S9>();
    PrintPODType<S10>();
}

struct PPN {
    unsigned int PFN : 22;
    int : 3;
    unsigned int CCA : 3;
    bool nonreachable : 1;
    bool dirty : 1;
    bool valid : 1;
    bool global : 1;
};

void bitareaTest1() {
    PPN ppn{};
    ppn.dirty = 1;
}


union U1 {
    int a;
    const char *p{""};
    int test() {return this->a;}
};

void unionTest() {
    U1 u1;
    cout<<u1.test()<<endl; // 打印ｐ指向的地址
    // U1 u2{7}; //error: no matching function for call to ‘U1::U1(<brace-enclosed initializer list>)’
}

namespace enum_class
{
enum class Light : uint8_t;
uint8_t ReadVal(Light &flag) { return static_cast<uint8_t>(flag); }
enum class Light : uint8_t
{
    Red,
    Green,
    Yellow
};
enum class Flag : uint8_t
{
    Nil = 0,
    Red = 1,
    Yellow = 2,
    Blue = 4
};
constexpr Flag operator&(Flag var, Flag flag)
{  // if(f1 & Flag::Red) { //error: could not convert ‘operator&(f1, (Flag)1u)’
    // from ‘Flag’ to ‘bool’
    return static_cast<Flag>(static_cast<char>(var) & static_cast<char>(flag));
}
constexpr Flag operator|(Flag var, Flag flag)
{
    return static_cast<Flag>(static_cast<char>(var) | static_cast<char>(flag));
}

int test()
{
    // Light s1 = 1; // error: cannot convert ‘int’ to ‘Light’ in initialization
    // uint8_t i1 = s1; // error: cannot convert ‘Light’ to ‘uint8_t {aka
    // unsigned char}’ in initialization
    // uint8_t i2 = Light::Red; // error: cannot convert ‘Light’ to ‘uint8_t
    // {aka unsigned char}’ in initialization
    // Light S2 = Red; // error: ‘Red’ was not declared in this scope
    Light S3 = Light::Red;
    // if (S3 == Flag::Red); // error: no match for ‘operator==’ (operand types
    // are ‘Light’ and ‘Flag’)
    if (S3 == Light::Red)
        ;
    Flag f1 = Flag::Red | Flag::Blue;
    if ((f1 & Flag::Red) != Flag::Nil)
    {
        cout << "f1 has Red" << endl;
    }
    switch (f1)
    {  // warning: enumeration value ‘Blue’ not handled in switch [-Wswitch]
        case Flag::Red:
            cout << "Red" << endl;
        case Flag::Yellow:
            cout << "Yellow" << endl;
        case Flag::Red &Flag::Yellow:
            cout << "Red&Yellow" << endl;
    }
    Flag f2{};
    cout << "f2: " << (int)static_cast<uint8_t>(f2) << endl;
    f2 = static_cast<Flag>(1234);  //超出范围
    cout << "f2: " << (int)static_cast<uint8_t>(f2) << endl;
}
}


enum Light : uint8_t;
uint8_t ReadVal(Light &flag) {
    return static_cast<uint8_t>(flag);
}
enum Light: uint8_t { Red, Green, Yellow };
enum Flag : uint8_t {
    Nil = 0,
    // Red = 1, // error: redeclaration of ‘Red’
    FlagRed = 1,
    FlagYellow = 2, // error: redeclaration of ‘Yellow’
    Blue = 4
};


// enum TestEnum1;  // error: use of enum ‘TestEnum’ without previous declaration
// enum TestEnum1 { TestEnumA,TestEnumB };
enum class TestEnum2;
enum class TestEnum2 { TestEnumA,TestEnumB };

constexpr Flag operator&(Flag var, Flag flag) { // if(f1 & Flag::Red) { //error: could not convert ‘operator&(f1, (Flag)1u)’ from ‘Flag’ to ‘bool’
    return static_cast<Flag>(static_cast<char>(var)&static_cast<char>(flag));
}
constexpr Flag operator|(Flag var, Flag flag) {
    return static_cast<Flag>(static_cast<char>(var)|static_cast<char>(flag));
}


class TestInit { public: TestInit() { cout<<"test init"<<endl; } };
int testinit() {
    TestInit testobj;
    return 1;
}
static int a = testinit();

int testenum() {
    // Light s1 = 1; // error: invalid conversion from ‘int’ to ‘Light’ [-fpermissive]
    Light s1;
    // s1 = 1; // error: invalid conversion from ‘int’ to ‘Light’ [-fpermissive]
    uint8_t i2 = Light::Red;
    Light S2 = Red;
    uint8_t i1 = S2;
    Light S3 = Light::Red;
    // if (S3 == Flag::Red); // error: ‘Red’ is not a member of ‘Flag’
    if (S3 == Light::Red);
    Flag f1 = Flag::FlagRed | Flag::Blue;
    if((f1 & Flag::FlagRed) != Flag::Nil) {
        cout<<"f1 has Red"<<endl;
    }
    switch(f1) { // warning: enumeration value ‘Blue’ not handled in switch [-Wswitch]
    case Flag::FlagRed:
        cout<<"Red"<<endl;
    case Flag::FlagYellow:
        cout<<"Yellow"<<endl;
    case Flag::FlagRed&Flag::FlagYellow:
        cout<<"Red&Yellow"<<endl;
    }
    Flag f2 {};
    cout<<"f2: "<<(int)static_cast<uint8_t>(f2)<<endl;
    f2 = static_cast<Flag>(1234); //超出范围
    cout<<"f2: "<<(int)static_cast<uint8_t>(f2)<<endl;
}

constexpr int testconstfun(int v) {return v+1;}
int test_switch() {
    constexpr int testval = 2;
    int a = 1;
    switch (a)
        {
        case 1:
            cout<<"1"<<endl; break;
        case testval:
            cout<<"2"<<endl; break;
        case testconstfun(testval):
            cout<<"3"<<endl; break;
            // case testconstfun(testval): // error: duplicate case value
            //     cout<<"can not"<<endl; break;
        }

    // double d = 1.0;
    // switch (d) { // error: switch quantity not an integer
    // case 1.0: // error: could not convert ‘1.0e+0’ from ‘double’ to ‘<type error>’
    //         cout<<"1.0"<<endl; break;
    // }

    int x = 1;
    switch (x) {
    case 3:
        {
            int zz = 1;
        }
    case 1:
        int y;
        // int z = 1; // error: jump to case label [-fpermissive]  note:   crosses initialization of ‘int z’
    case 2:
        cout<<"Y:"<<y<<endl;
    }

}

int get_val(int a) {
    return a + 1;
}

int testif() {
    if (int a = get_val(1)) {
        cout<<"a in if: "<<a<<endl;
    } else {
        cout<<"a in else: "<<a<<endl;
    }
}

int testforeach() {
    vector<int> testvec{1,2,3,4,5,6,7,8,9};
    for(const int &v:testvec) {
        cout<<v<<endl;
    }
}

int testfor() {
    vector<int> testvec{1,2,3,4,5,6,7,8,9};
    cout<<"++++++++++1+++++++++++++"<<endl;
    for(const int &v:testvec) { cout<<v<<endl; }

    cout<<"++++++++++2+++++++++++++"<<endl;
    for(auto i = begin(testvec); i != end(testvec); ++i) { cout<<*i<<endl; }

    cout<<"++++++++++3+++++++++++++"<<endl;
    {
        auto i = begin(testvec);
        while (i != end(testvec))
            {
                cout << *i << endl;
                ++i;
            }
    }

    for (;;) {
        cout<<1;
    }
}

int testopt() {
    bool a = true;
    bool b = false;

    if (a or b) {
        cout<<"true a or b"<<endl;
    }
}

void testopt2() {
    int x,y;
    int j = x = y;
    int *p = &++x;
    //int *q = &(x++); //error: lvalue required as unary ‘&’ operand x++返回的是++之前的临时变量，不是左值
    int *p2 = &(x>y?x:y);
    //int &r = (x<y)?x:1; //error: invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’ 1不是左值
}


constexpr int isqrt_helper(int sq, int d, int a) { return sq <= a ? isqrt_helper(sq+d,d+2,a):d; }
constexpr int isqrt(int x) { return isqrt_helper(1,3,x)/2 - 1; }

struct Point {
    int x,y,z;
    constexpr Point (int px, int py) : x(px),y(py), z(0) { }
    // constexpr Point (int px, int py) : x(px),y(py) { } // error: member ‘Point::z’ must be initialized by mem-initializer in ‘constexpr’ constructor
    constexpr Point (int px, int py, int pz) : x(px),y(py),z(pz) { }
    constexpr Point up(int d) { return {x,y,z+d}; }
    constexpr Point move(int dx,int dy) { // There need not 'const'
        // this->x += 100; //error: assignment of member ‘Point::x’ in read-only object
        return {x+dx, y+dy, z};
    }
};

constexpr Point origo { 0, 0 };
constexpr int z = origo.x;
constexpr Point constarry[] = { origo,Point{1,1},Point{2,2},origo.move(1,2) };

int squareF(int x) { return x * x; }

constexpr int x = constarry[1].x;
// constexpr Point xy{1,squareF(4)}; // error: call to non-constexpr function ‘int squareF(int)’

constexpr int square(int x) { return x*x; }
constexpr int radial_distance(Point p) {
    return isqrt(square(p.x) + square(p.y) + square(p.z));
}

constexpr Point p1 {10,20,30};
constexpr Point p2 {p1.up(20)};
constexpr int dist = radial_distance(p2);

void testconexpr() {
    const Point testpoint { 10,20,30 };
    testpoint.move(100,200);
}

constexpr const char* ps1 = "1234";
constexpr const char* ps2 = ps1;
constexpr const char* ps3 = ps1 + 2;
constexpr char c = ps1[2];

int main(int argc, char *argv[]) {
    signed char sc = 1023;

    double testd = 0.1234567890123456;
    float testf = testd;
    //cout<<(int)sc<<endl;
    cout<<setprecision(16)<<testd<<endl;
    cout<<setprecision(16)<<testf<<endl;
}



