#pragma once

#include "checking_policy.h"
#include "delete_policy.h"
#include "ref_counted.h"

namespace smartptr {

    template <
        typename T,
        typename TCheckingPolicy = TNoChecking
    >
    class TIntrusivePtr {
    public:
        TIntrusivePtr(T *ptr) : ptr(ptr) { 
            TCheckingPolicy::Check(ptr);
        }

        ~TIntrusivePtr() throw() {
            if (ptr) {
                ptr->UnRef();
            } 
        }

        TIntrusivePtr(const TIntrusivePtr& iPtr) : ptr(iPtr.ptr){
            TCheckingPolicy::Check(ptr); 
            ptr->Ref();
        }

        TIntrusivePtr operator=(const TIntrusivePtr& iPtr) { 
            if (this != &iPtr) {
                ptr = iPtr.ptr;
                ptr->Ref();
            }
            return *this;
        }

        T& operator*() const {
            TCheckingPolicy::Check(ptr);
            return * ptr;
        }

        T* operator->() const {
            TCheckingPolicy::Check(ptr);
            return  ptr;
        }

    private:
        T*  ptr;
    };
}
