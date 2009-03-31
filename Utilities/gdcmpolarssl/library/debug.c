/*
 *  Debugging routines
 *
 *  Based on XySSL: Copyright (C) 2006-2008  Christophe Devine
 *
 *  Copyright (C) 2009  Paul Bakker <polarssl_maintainer at polarssl dot org>
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the names of PolarSSL or XySSL nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "polarssl/config.h"

#if defined(POLARSSL_DEBUG_C)

#include "polarssl/debug.h"

#include <stdarg.h>
#include <stdlib.h>

#if defined _MSC_VER && !defined  snprintf
#define  snprintf  _snprintf
#endif

#if defined _MSC_VER && !defined vsnprintf
#define vsnprintf _vsnprintf
#endif

char *debug_fmt( const char *format, ... )
{
    va_list argp;
    static char str[512];
    int maxlen = sizeof( str ) - 1;

    va_start( argp, format );
    vsnprintf( str, maxlen, format, argp );
    va_end( argp );

    str[maxlen] = '\0';
    return( str );
}

void debug_print_msg( ssl_context *ssl, int level,
                      char *file, int line, char *text )
{
    char str[512];
    int maxlen = sizeof( str ) - 1;

    if( ssl->f_dbg == NULL )
        return;

    snprintf( str, maxlen, "%s(%04d): %s\n", file, line, text );
    str[maxlen] = '\0';
    ssl->f_dbg( ssl->p_dbg, level, str );
}

void debug_print_ret( ssl_context *ssl, int level,
                      char *file, int line, char *text, int ret )
{
    char str[512];
    int maxlen = sizeof( str ) - 1;

    if( ssl->f_dbg == NULL )
        return;

    snprintf( str, maxlen, "%s(%04d): %s() returned %d (0x%x)\n",
              file, line, text, ret, ret );

    str[maxlen] = '\0';
    ssl->f_dbg( ssl->p_dbg, level, str );
}

void debug_print_buf( ssl_context *ssl, int level,
                      char *file, int line, char *text,
                      unsigned char *buf, int len )
{
    char str[512];
    int i, maxlen = sizeof( str ) - 1;

    if( ssl->f_dbg == NULL || len < 0 )
        return;

    snprintf( str, maxlen, "%s(%04d): dumping '%s' (%d bytes)\n",
              file, line, text, len );

    str[maxlen] = '\0';
    ssl->f_dbg( ssl->p_dbg, level, str );

    for( i = 0; i < len; i++ )
    {
        if( i >= 4096 )
            break;

        if( i % 16 == 0 )
        {
            if( i > 0 )
                ssl->f_dbg( ssl->p_dbg, level, "\n" );

            snprintf( str, maxlen, "%s(%04d): %04x: ", file, line, i );

            str[maxlen] = '\0';
            ssl->f_dbg( ssl->p_dbg, level, str );
        }

        snprintf( str, maxlen, " %02x", (unsigned int) buf[i] );

        str[maxlen] = '\0';
        ssl->f_dbg( ssl->p_dbg, level, str );
    }

    if( len > 0 )
        ssl->f_dbg( ssl->p_dbg, level, "\n" );
}

void debug_print_mpi( ssl_context *ssl, int level,
                      char *file, int line, char *text, mpi *X )
{
    char str[512];
    int i, j, k, n, maxlen = sizeof( str ) - 1;

    if( ssl->f_dbg == NULL || X == NULL )
        return;

    for( n = X->n - 1; n >= 0; n-- )
        if( X->p[n] != 0 )
            break;

    snprintf( str, maxlen, "%s(%04d): value of '%s' (%d bits) is:\n",
              file, line, text, ((n + 1) * sizeof( t_int )) << 3 );

    str[maxlen] = '\0';
    ssl->f_dbg( ssl->p_dbg, level, str );

    for( i = n, j = 0; i >= 0; i--, j++ )
    {
        if( j % ( 16 / sizeof( t_int ) ) == 0 )
        {
            if( j > 0 )
                ssl->f_dbg( ssl->p_dbg, level, "\n" );

            snprintf( str, maxlen, "%s(%04d): ", file, line );

            str[maxlen] = '\0';
            ssl->f_dbg( ssl->p_dbg, level, str );
        }

        for( k = sizeof( t_int ) - 1; k >= 0; k-- )
        {
            snprintf( str, maxlen, " %02x", (unsigned int)
                      ( X->p[i] >> (k << 3) ) & 0xFF );

            str[maxlen] = '\0';
            ssl->f_dbg( ssl->p_dbg, level, str );
        }
    }

    ssl->f_dbg( ssl->p_dbg, level, "\n" );
}

void debug_print_crt( ssl_context *ssl, int level,
                      char *file, int line, char *text, x509_cert *crt )
{
    char str[512], prefix[64], *p;
    int i = 0, maxlen = sizeof( prefix ) - 1;

    if( ssl->f_dbg == NULL || crt == NULL )
        return;

    snprintf( prefix, maxlen, "%s(%04d): ", file, line );
    prefix[maxlen] = '\0';
    maxlen = sizeof( str ) - 1;

    while( crt != NULL && crt->next != NULL )
    {
        p = x509parse_cert_info( prefix, crt );

        snprintf( str, maxlen, "%s(%04d): %s #%d:\n%s",
                  file, line, text, ++i, p );

        str[maxlen] = '\0';
        ssl->f_dbg( ssl->p_dbg, level, str );

        debug_print_mpi( ssl, level, file, line,
                         "crt->rsa.N", &crt->rsa.N );

        debug_print_mpi( ssl, level, file, line,
                         "crt->rsa.E", &crt->rsa.E );

        crt = crt->next;
    }
}

#endif
