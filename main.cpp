#include <iostream>
#include <vector>
#include <cassert>
#include <exception>
#include "tholder.h"
#include "tintrusive.h"
#include "testobj.h"

using namespace smartptr;

void tempFunction(TIntrusivePtr<IntrusiveTest> ptr) {
    assert(ptr->getCounter() == 3);
    assert(3 == ptr->getNum());
}

int main() {

    // THolder Test
    THolder<Test, TNullChecking> iPtr(new Test(10));
    assert(10 == iPtr->getNum());

    // Reset Test
    Test* newPtr = new Test(1);
    iPtr.Reset(newPtr);
    assert(1 == iPtr->getNum());

    // Destroy Test, exception
    iPtr.Destroy();
    try {
        std::cerr << iPtr->getNum();
        assert(false);
    } catch (std::bad_exception& exc) {
        assert(true);
    } catch (...) {
        assert(false);
    }

    // Inheritance Test
    THolder<BaseTest> basePtr(new DerivedTest(5, 'v'));
    assert(10 == basePtr->getNum()); // num + num

    // TIntrusivePtr Test
    TIntrusivePtr<IntrusiveTest> intrusivePtr(new IntrusiveTest(3));
    assert(intrusivePtr->getCounter() == 1);

    // operator =
    TIntrusivePtr<IntrusiveTest> intrusivePtr_copy = intrusivePtr;
    assert(intrusivePtr->getCounter() == 2);

    assert(3 == intrusivePtr->getNum());
    assert(3 == intrusivePtr_copy->getNum());

    // temporary obj, copy-ctor, UnRef
    tempFunction(intrusivePtr);
    assert(intrusivePtr->getCounter() == 2);
}
