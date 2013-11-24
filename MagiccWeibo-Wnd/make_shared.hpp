#ifndef _MAKE_SHARED_HPP_INCLUDED
#define _MAKE_SHARED_HPP_INCLUDED

#ifdef BOOST_MAKESHARED
#include <boost/make_shared.hpp>
using boost::make_shared;
#else
#include <boost/shared_ptr.hpp>
#include <new>

namespace weibo {
template< class T  >
boost::shared_ptr< T > make_shared()
{
    return boost::shared_ptr< T >( ::new T() );
}

template< class T, class A1 >
boost::shared_ptr< T > make_shared( A1 const & a1 )
{
    return boost::shared_ptr< T >( ::new T(a1) );
}

template< class T, class A, class A1 >
boost::shared_ptr< T > allocate_shared( A const & a, A1 const & a1 )
{
    return boost::shared_ptr< T >( ::new T(a, a1) );
}
}

#endif
#endif
