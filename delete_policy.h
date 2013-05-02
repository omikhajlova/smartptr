#pragma once

namespace smartptr {

    template <
        typename T
    > class TDelete {
    public:
        static void Delete(T* ptr) {
            delete ptr;
        }
    };

    template <
        typename T
    > class TDeleteArray {
    public:
        static void Delete(T* ptr) {
            delete[] ptr;
        }
    };
}
