//
// is_write_buffered.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOFA_PBRPC_BOOST_ASIO_IS_WRITE_BUFFERED_HPP
#define SOFA_PBRPC_BOOST_ASIO_IS_WRITE_BUFFERED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <sofa/pbrpc/boost/asio/detail/config.hpp>
#include <sofa/pbrpc/boost/asio/buffered_stream_fwd.hpp>
#include <sofa/pbrpc/boost/asio/buffered_write_stream_fwd.hpp>

#include <sofa/pbrpc/boost/asio/detail/push_options.hpp>

namespace sofa {
namespace pbrpc {
namespace boost {
namespace asio {

namespace detail {

template <typename Stream>
char is_write_buffered_helper(buffered_stream<Stream>* s);

template <typename Stream>
char is_write_buffered_helper(buffered_write_stream<Stream>* s);

struct is_write_buffered_big_type { char data[10]; };
is_write_buffered_big_type is_write_buffered_helper(...);

} // namespace detail

/// The is_write_buffered class is a traits class that may be used to determine
/// whether a stream type supports buffering of written data.
template <typename Stream>
class is_write_buffered
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true only if the Stream type supports buffering of
  /// written data.
  static const bool value;
#else
  BOOST_ASIO_STATIC_CONSTANT(bool,
      value = sizeof(detail::is_write_buffered_helper((Stream*)0)) == 1);
#endif
};

} // namespace asio
} // namespace boost
} // namespace pbrpc
} // namespace sofa

#include <sofa/pbrpc/boost/asio/detail/pop_options.hpp>

#endif // SOFA_PBRPC_BOOST_ASIO_IS_WRITE_BUFFERED_HPP