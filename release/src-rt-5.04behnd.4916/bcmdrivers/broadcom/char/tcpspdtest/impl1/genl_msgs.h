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
* File Name  : genl_msgs.h
*
* Description: This file contains the Broadcom Tcp Speed Test Generic Netlink global definitions.
*
*  Created on: Dec 20, 2017
*      Author: ilanb, yonatani
*******************************************************************************
*/

#ifndef __GENL_MSGS_H_INCLUDED__
#define __GENL_MSGS_H_INCLUDED__

#include "tcpspdtest_defs.h"

/******************************************* Functions *******************************************/
int tcpspd_genl_init(void);
int tcpspd_genl_shutdown(void);
int tcpspd_genl_send_speed_report_msg(uint8_t stream_idx, tcp_spdt_rep_t *spd_report, tcpspdtest_genl_cmd_status_t status);
int tcpspd_genl_clear_event(uint8_t stream_idx);
int tcpspd_genl_send_event(uint8_t stream_idx, tcp_spdt_rep_t *spd_report, tcpspdtest_genl_cmd_status_t status);
int tcpspd_genl_send_pending_event(uint8_t stream_idx);

#endif /* __GENL_MSGS_H_INCLUDED__ */
