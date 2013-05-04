#include <iostream>
#include <vector>
#include <cassert>
#include <exception>
#include "tholder.h"
#include "smartptr.h"

using namespace smartptr;

struct Test {
    Test(int num) : num(num) {
        std::cerr << "test" << std::endl;
    }

    ~Test() {
        std::cerr << "~test" << std::endl;
    }

    void f() {
        std::cerr << "f " << num << std::endl;
    }

    void exception() {
        std::cerr << "exception" << std::endl;
        throw std::exception();
    }

    int getNum() const {
        return num;
    }

private:
    Test(const Test&);
    void operator=(const Test&);
    int num;
};

class BaseTest {
public:
    BaseTest(int num) : num(num) {
        std::cerr << "BaseTest" << std::endl;
    }

    virtual ~BaseTest() {
        std::cerr << "~BaseTest" << std::endl;
    }

    virtual void print() {
        std::cerr << "BaseTest " << num << std::endl; 
    }

    int getNum() const {
        return num;
    }

private:
    BaseTest(const BaseTest&);
    void operator=(const BaseTest&);
    int num;

};

class T2 : public BaseTest { 
public:
    T2(int num, char c) : BaseTest(num), c(c) {
        std::cerr << "T2" << std::endl;
    }

    virtual ~T2() {
        std::cout << "~T2" << std::endl;
    }

    virtual void print() {
        std::cerr << "T2 " << num << " char " << c << std::endl; 
    }

    char getChar() const {
        return c;
    }

private:
    T2(const T2&);
    void operator=(const T2&);
    int num;
    char c;
};

class IntrusiveTest : public TRefCounted {
public:
    IntrusiveTest(int num) : TRefCounted(), num(num) {
        array = new int[10];
        std::cerr << "IntrusiveTest" << std::endl;
    }

    virtual ~IntrusiveTest() {
        delete[] array;
        std::cerr << "~IntrusiveTest" << std::endl;
    }

    void print() {
        std::cerr << "IntrusiveTest " << num << std::endl; 
    }

    int getNum() const {
        return num;
    }

private:
    IntrusiveTest(const IntrusiveTest&);
    void operator=(const IntrusiveTest&);
    int num;
    int* array;

};

int main() {
    THolder<Test, TNullChecking> iPtr(new Test(10));
    assert(10 == iPtr->getNum());

    Test* newPtr = new Test(1);
    iPtr.Reset(newPtr);
    assert(1 == iPtr->getNum());

    iPtr.Destroy();
    try {
        iPtr->getNum();
    } catch (std::bad_exception& exc) {
        assert(true);
    } catch (...) {
        assert(false);
    }

    THolder<BaseTest> basePtr(new T2(5, 'v'));
    assert(5 == basePtr->getNum());

    TIntrusivePtr<IntrusiveTest> intrusivePtr(new IntrusiveTest(3));
    TIntrusivePtr<IntrusiveTest> intrusivePtr_copy = intrusivePtr;

    assert(3 == intrusivePtr->getNum());
    assert(3 == intrusivePtr_copy->getNum());
}
