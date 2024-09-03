/*
* <:copyright-BRCM:2021:DUAL/GPL:standard
* 
*    Copyright (c) 2021 Broadcom 
*    All Rights Reserved
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License, version 2, as published by
* the Free Software Foundation (the "GPL").
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* 
* A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
* writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
* 
* :>
 
*/

/*
*******************************************************************************
* File Name  : rnr_flow.h
*
* Description: This file contains the Broadcom Tcp Speed Test Runner Flow global definitions.
*
*  Created on: Dec 6, 2016
*      Author: yonatani, ilanb
*******************************************************************************
*/

#ifndef __RNR_FLOW_H_INCLUDED__
#define __RNR_FLOW_H_INCLUDED__

#include <rdpa_api.h>

/******************************************** Functions ******************************************/

int tcpspd_rnr_flow_get_host_mac(bdmf_mac_t *pmac, struct net_device *dev);

#endif /* __RNR_FLOW_H_INCLUDED___ */
