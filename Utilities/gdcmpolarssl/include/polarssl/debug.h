/**
 * \file debug.h
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
#ifndef SSL_DEBUG_H
#define SSL_DEBUG_H

#include "polarssl/config.h"
#include "polarssl/ssl.h"

#if defined(POLARSSL_DEBUG_MSG)

#define SSL_DEBUG_MSG( level, args )                    \
    debug_print_msg( ssl, level, __FILE__, __LINE__, debug_fmt args );

#define SSL_DEBUG_RET( level, text, ret )                \
    debug_print_ret( ssl, level, __FILE__, __LINE__, text, ret );

#define SSL_DEBUG_BUF( level, text, buf, len )           \
    debug_print_buf( ssl, level, __FILE__, __LINE__, text, buf, len );

#define SSL_DEBUG_MPI( level, text, X )                  \
    debug_print_mpi( ssl, level, __FILE__, __LINE__, text, X );

#define SSL_DEBUG_CRT( level, text, crt )                \
    debug_print_crt( ssl, level, __FILE__, __LINE__, text, crt );

#else

#define SSL_DEBUG_MSG( level, args )            do { } while( 0 )
#define SSL_DEBUG_RET( level, text, ret )       do { } while( 0 )
#define SSL_DEBUG_BUF( level, text, buf, len )  do { } while( 0 )
#define SSL_DEBUG_MPI( level, text, X )         do { } while( 0 )
#define SSL_DEBUG_CRT( level, text, crt )       do { } while( 0 )

#endif

#ifdef __cplusplus
extern "C" {
#endif

char *debug_fmt( const char *format, ... );

void debug_print_msg( ssl_context *ssl, int level,
                      char *file, int line, char *text );

void debug_print_ret( ssl_context *ssl, int level,
                      char *file, int line, char *text, int ret );

void debug_print_buf( ssl_context *ssl, int level,
                      char *file, int line, char *text,
                      unsigned char *buf, int len );

void debug_print_mpi( ssl_context *ssl, int level,
                      char *file, int line, char *text, mpi *X );

void debug_print_crt( ssl_context *ssl, int level,
                      char *file, int line, char *text, x509_cert *crt );

#ifdef __cplusplus
}
#endif

#endif /* debug.h */
