#include <iostream>
#include <vector>
#include "ref_counted.h"

namespace smartptr {
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

        virtual int getNum() const {
            return num;
        }

    protected:
        int num;

    };

    class DerivedTest : public BaseTest { 
    public:
        DerivedTest(int num, char c) : BaseTest(num), c(c) {
            std::cerr << "T2" << std::endl;
        }

        virtual ~DerivedTest() {
            std::cout << "~T2" << std::endl;
        }

        virtual void print() {
            std::cerr << "T2 " << num << " char " << c << std::endl; 
        }

        virtual int getNum() const {
            return num + num;
        }

        char getChar() const {
            return c;
        }

    private:
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
}
