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
            ptr->UnRef(); 
        }

        TIntrusivePtr(const TIntrusivePtr& smartprt) : ptr(smartprt.ptr){
            TCheckingPolicy::Check(ptr); 
            ptr->Ref();
        }

        TIntrusivePtr operator=(const TIntrusivePtr& smartprt) { 
            if (this != &smartprt) {
                ptr = smartprt.ptr;
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
