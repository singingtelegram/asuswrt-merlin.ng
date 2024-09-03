/*
<:copyright-BRCM:2018:DUAL/GPL:standard

   Copyright (c) 2018 Broadcom 
   All Rights Reserved

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation (the "GPL").

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.

:>
*/

/*
*******************************************************************************
* File Name  : sock_mgr.h
*
* Description: This file contains the Broadcom Tcp Speed Test global definitions.
*
*  Created on: Dec 6, 2016
*      Author: yonatani, ilanb, Nikolai Iosifov
*******************************************************************************
*/

#ifndef __SOCK_MGR_H_INCLUDED__
#define __SOCK_MGR_H_INCLUDED__

#include <linux/net.h>
#include <linux/types.h>

#include "tcpspdtest_defs.h"

/******************************************** Functions ******************************************/
int  tcpspd_sock_mgr_connect(uint8_t stream_idx, struct socket **sock, spdt_conn_params_t *params);
int  tcpspd_sock_mgr_sendmsg(uint8_t stream_idx, uint8_t *data, uint32_t len);
int  tcpspd_sock_mgr_wait_send_complete(uint8_t stream_idx, struct socket *sock);
void tcpspd_sock_mgr_set_nf_hook_prtcl(uint8_t stream_idx, int accept);
int  tcpspd_sock_mgr_disconnect(uint8_t stream_idx, struct socket *sock);
int  tcpspd_sock_mgr_release(uint8_t stream_idx, struct socket *sock);
int  tcpspd_sock_mgr_init(void);
int  tcpspd_sock_mgr_shutdown(uint8_t stream_idx);

int udpspd_sock_mgr_init(void);
int udpspd_sock_mgr_uninit(void);

#endif /* __SOCK_MGR_H_INCLUDED__ */
