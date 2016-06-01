//
// Created by phtran on 07/05/2016.
//

#ifndef FRONTEND_COUNTEDPOINTER_H
#define FRONTEND_COUNTEDPOINTER_H

template<class T>
class counted_ptr
{

public:

    typedef T element_type;

    explicit counted_ptr( T *p = 0 )
            : itsCounter( 0 )
    {

        if ( p ) {

            itsCounter = new counter(p);

        }

    }

    ~counted_ptr()
    {

        release();

    }

    counted_ptr( const counted_ptr &r ) throw()
    {

        acquire( r.itsCounter );

    }

    counted_ptr& operator=( const counted_ptr &r )
    {

        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }

        return *this;

    }

#if 0
    #ifndef NO_MEMBER_TEMPLATES
  template <class Y> friend class counted_ptr<Y>;
  template <class Y> counted_ptr(const counted_ptr<Y>& r) throw()
    {acquire(r.itsCounter);}
  template <class Y> counted_ptr& operator=(const counted_ptr<Y>& r)
    {
      if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }
#endif // NO_MEMBER_TEMPLATES
#endif

    T& operator*() const throw() { return *itsCounter->ptr; }

    T* operator->() const throw() { return itsCounter->ptr; }

    T* get() const throw() { return itsCounter ? itsCounter->ptr : 0; }

    bool unique() const throw()
    {

        return ( itsCounter ? itsCounter->count == 1 : true );

    }

private:

    struct counter
    {
        counter( T        *p = 0,
                 unsigned  c = 1 )
                : ptr( p )
                , count(c)
        { }

        T        *ptr;
        unsigned  count;

    } *itsCounter;

    void acquire( counter *c ) throw()
    {

        itsCounter = c;
        if ( c ) {

            ++c->count;

        }

    }

    void release()
    {

        if ( itsCounter ) {

            if (--itsCounter->count == 0) {

                //delete itsCounter->ptr;
                //delete itsCounter;

            }

            itsCounter = 0;

        }

    }

};
#endif //FRONTEND_COUNTEDPOINTER_H
