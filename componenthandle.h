//
// Created by phtran on 07/05/2016.
//

#include "basecomponenthandle.h"
#include "countedpointer.h"

#ifndef FRONTEND_COMPONENTHANDLE_H
#define FRONTEND_COMPONENTHANDLE_H

namespace UI
{
    template <class T>
    class ComponentHandle : public BaseComponentHandle
    {
        counted_ptr<T> ptr_;
    public:
        ComponentHandle() { }
        ComponentHandle(counted_ptr<T>& t) : ptr_(t) { }
        T& operator*()
        {
            return *ptr;
        }
        T* operator->()
        {
            return &(*ptr_);
        }
        const T& operator*() const
        {
            return *ptr;
        }
        const T* operator->() const
        {
            return &(*ptr_);
        }

        virtual BaseComponent& obj()
        {
            return *ptr_;
        }
        virtual const BaseComponent& obj() const
        {
            return *ptr_;
        }
        virtual ComponentHandle<T>* clone() const
        {
            return new ComponentHandle<T>(*this);
        }
    };

    template <class T>
    ComponentHandle createHandle(const T& c)
    {
        return ComponentHandle<T>(counted_ptr<T>(c.clone()));
    }
}
#endif //FRONTEND_COMPONENTHANDLE_H
