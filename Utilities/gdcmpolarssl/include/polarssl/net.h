/**
 * \file net.h
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
#ifndef POLARSSL_NET_H
#define POLARSSL_NET_H

#define POLARSSL_ERR_NET_UNKNOWN_HOST                      -0x0F00
#define POLARSSL_ERR_NET_SOCKET_FAILED                     -0x0F10
#define POLARSSL_ERR_NET_CONNECT_FAILED                    -0x0F20
#define POLARSSL_ERR_NET_BIND_FAILED                       -0x0F30
#define POLARSSL_ERR_NET_LISTEN_FAILED                     -0x0F40
#define POLARSSL_ERR_NET_ACCEPT_FAILED                     -0x0F50
#define POLARSSL_ERR_NET_RECV_FAILED                       -0x0F60
#define POLARSSL_ERR_NET_SEND_FAILED                       -0x0F70
#define POLARSSL_ERR_NET_CONN_RESET                        -0x0F80
#define POLARSSL_ERR_NET_TRY_AGAIN                         -0x0F90

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Initiate a TCP connection with host:port
 *
 * \return         0 if successful, or one of:
 *                      POLARSSL_ERR_NET_SOCKET_FAILED,
 *                      POLARSSL_ERR_NET_UNKNOWN_HOST,
 *                      POLARSSL_ERR_NET_CONNECT_FAILED
 */
int net_connect( int *fd, char *host, int port );

/**
 * \brief          Create a listening socket on bind_ip:port.
 *                 If bind_ip == NULL, all interfaces are binded.
 *
 * \return         0 if successful, or one of:
 *                      POLARSSL_ERR_NET_SOCKET_FAILED,
 *                      POLARSSL_ERR_NET_BIND_FAILED,
 *                      POLARSSL_ERR_NET_LISTEN_FAILED
 */
int net_bind( int *fd, char *bind_ip, int port );

/**
 * \brief          Accept a connection from a remote client
 *
 * \return         0 if successful, POLARSSL_ERR_NET_ACCEPT_FAILED, or
 *                 POLARSSL_ERR_NET_WOULD_BLOCK is bind_fd was set to
 *                 non-blocking and accept() is blocking.
 */
int net_accept( int bind_fd, int *client_fd, void *client_ip );

/**
 * \brief          Set the socket blocking
 *
 * \return         0 if successful, or a non-zero error code
 */
int net_set_block( int fd );

/**
 * \brief          Set the socket non-blocking
 *
 * \return         0 if successful, or a non-zero error code
 */
int net_set_nonblock( int fd );

/**
 * \brief          Portable usleep helper
 *
 * \note           Real amount of time slept will not be less than
 *                 select()'s timeout granularity (typically, 10ms).
 */
void net_usleep( unsigned long usec );

/**
 * \brief          Read at most 'len' characters. len is updated to
 *                 reflect the actual number of characters read.
 *
 * \return         This function returns the number of bytes received,
 *                 or a negative error code; POLARSSL_ERR_NET_TRY_AGAIN
 *                 indicates read() is blocking.
 */
int net_recv( void *ctx, unsigned char *buf, int len );

/**
 * \brief          Write at most 'len' characters. len is updated to
 *                 reflect the number of characters _not_ written.
 *
 * \return         This function returns the number of bytes sent,
 *                 or a negative error code; POLARSSL_ERR_NET_TRY_AGAIN
 *                 indicates write() is blocking.
 */
int net_send( void *ctx, unsigned char *buf, int len );

/**
 * \brief          Gracefully shutdown the connection
 */
void net_close( int fd );

#ifdef __cplusplus
}
#endif

#endif /* net.h */
