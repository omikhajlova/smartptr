#pragma once
#include <iostream>

namespace smartptr {
    
    class TRefCounted {
    template <
        typename T,
        typename TCheckingPolicy
    > friend class TIntrusivePtr;
    public:
        TRefCounted() : counter(1) { }
        virtual ~TRefCounted() { }
    
    private:    
        void Ref() throw() { 
            ++counter;
            printf("ref++ %d\n", counter); 
        }
        void UnRef() throw() { 
            --counter; 
            printf("ref-- %d\n", counter); 
            if (!counter) {
                delete this;
            }
        }

    private:
        int counter;
    };
}
