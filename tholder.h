#pragma once

#include "checking_policy.h"
#include "delete_policy.h"

namespace smartptr {

    template <
        typename T,
        typename TCheckingPolicy = TNoChecking,
        typename TDeletePolicy = TDelete<T>
    > class THolder {
    public:
        THolder(T *ptr) : ptr(ptr) { 
            TCheckingPolicy::Check(ptr);
        }

        ~THolder() throw() {
            Destroy();
        }

        T& operator*() const {
            TCheckingPolicy::Check(ptr);
            return * ptr;
        }

        T* operator->() const {
            TCheckingPolicy::Check(ptr);
            return  ptr;
        }

        void Destroy() throw() {
            if (!ptr) {
                TDeletePolicy::Delete(ptr);
                ptr = 0;
            }
        }

        T* Release() throw() {
            T* temp = ptr;
            ptr = 0;
            return temp;
        }

        void Reset(T* new_ptr) {
            if (new_ptr != ptr) {  
                TCheckingPolicy::Check(new_ptr);  
                Destroy();
                ptr = new_ptr;
            }
        }

    private:
        THolder(const THolder&);
        void operator=(const THolder&);

    private:
        T*  ptr;
    };
}
