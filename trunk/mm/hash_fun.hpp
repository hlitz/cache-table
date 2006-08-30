/*
 *
 *  $Id$
 *
 *  $URL$
 *
 *  Copyright (C) 2006 Matteo Merli <matteo.merli@gmail.com>
 *
 *
 *  BSD License
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *   o Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   o Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the
 *     distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _MM_HASH_FUN_HPP__
#define _MM_HASH_FUN_HPP__

#include <cstddef>

namespace mm
{

using std::size_t;

template <class T> inline void hash_combine( size_t& seed, const T& v );


///////////////////////////////////////////////////////////////////////
// Scalar integers
///////////////////////////////////////////////////////////////////////

inline size_t hash_value( char n )           { return static_cast<size_t>( n ); }
inline size_t hash_value( unsigned char n )  { return static_cast<size_t>( n ); }
inline size_t hash_value( short n )          { return static_cast<size_t>( n ); }
inline size_t hash_value( unsigned short n ) { return static_cast<size_t>( n ); }
inline size_t hash_value( int n )            { return static_cast<size_t>( n ); }
inline size_t hash_value( unsigned int n )   { return static_cast<size_t>( n ); }
inline size_t hash_value( long n )           { return static_cast<size_t>( n ); }
inline size_t hash_value( unsigned long n )  { return static_cast<size_t>( n ); }

///////////////////////////////////////////////////////////////////////
// Sequences
///////////////////////////////////////////////////////////////////////

template <class Iterator>
inline size_t hash_range( Iterator first, Iterator last )
{
    size_t h = 0;
    for ( ; first != last; ++first )
        hash_combine( h, *first );

    return h;
}

template <class Iterator>
inline void hash_range( size_t& seed, Iterator first, Iterator last )
{
    for ( ; first != last; ++first )
        hash_combine( seed, *first );
}

inline size_t hash_value( char* s ) 
{
    return hash_range( s, s + strlen( s ) );
}

inline size_t hash_value( const char* s ) 
{
    return hash_range( s, s + strlen( s ) );
}

inline size_t hash_value( const std::string& s ) 
{
    return hash_range( s.begin(), s.end() );
}

template <class T1, class T2>
inline size_t hash_value( const std::pair<T1,T2>& p )
{
    size_t seed = 0;
    hash_combine( seed, p.first );
    hash_combine( seed, p.second );
    return seed;
}

///////////////////////////////////////////////////////////////////////

/*! Callable hash function.
 */
template <class Key>
struct hash
    : std::unary_function<Key, size_t>
{
    size_t operator() ( const Key& key ) const
    {
        size_t h = hash_value( key );
        return h;
    }
};

template <class T>
inline void hash_combine( size_t& seed, const T& v )
{
    // Taken from boost::hash::hash_combine
    seed ^= hash_value( v ) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    
    // seed *= 16777619;
    // seed ^= hash_value( v );
}

} // namespace mm

#endif // _MM_HASH_FUN_HPP__
