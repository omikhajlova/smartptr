#pragma once

#include <exception>

namespace smartptr {
    
    class TNoChecking {
    public:
        static void Check(void*) { }
    };

    class TNullChecking {
    public:
        static void Check(void* ptr) {
            if (!ptr) {
                throw std::bad_exception();
            }
        }
    };
}
