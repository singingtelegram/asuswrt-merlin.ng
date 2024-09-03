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
* File Name  : tcpspdtest.h
*
* Description: This file contains the Broadcom Tcp Speed Test global definitions.
*
*  Created on: Dec 6, 2016
*      Author: yonatani, ilanb
*******************************************************************************
*/

#ifndef __TCPSPDTEST_H_INCLUDED__
#define __TCPSPDTEST_H_INCLUDED__

#include <linux/netdevice.h>
#include <linux/rtnetlink.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <net/tcp.h>
#include <net/inet_connection_sock.h>
#include <net/request_sock.h>
#include "bdmf_interface.h"
#include "rdpa_cpu.h"
#include "spdt_defs.h"
#include "tcpspdtest_defs.h"

/******************************************** Defines ********************************************/
//#define TCPSPD_DEBUG

#define PROC_DIR "driver/tcpspdtest"

/* TCPSPDTEST commands */
#define TCPSPD_CMD_ALLOC_STREAM_STR  "alloc_stream"
#define TCPSPD_CMD_FREE_STREAM_STR   "free_stream"
#define TCPSPD_CMD_CONNECT_STR       "connect"
#define TCPSPD_CMD_DISCONNECT_STR    "disconnect"
#define TCPSPD_CMD_RELEASE_STR       "release"
#define TCPSPD_CMD_DOWNLOAD_STR      "download"
#define TCPSPD_CMD_UPLOAD_STR        "upload"
#define TCPSPD_CMD_STATS_STR         "stats"
#define TCPSPD_CMD_RWND_STR          "rwnd"
#define TCPSPD_CMD_CWND_STR          "cwnd"
#define TCPSPD_CMD_RTO_STR           "rto"
#define TCPSPD_CMD_UP_RATELIMIT_STR  "ratelimit"
#define TCPSPD_CMD_DYNACK_STR        "dynack"
#define TCPSPD_CMD_SHOW_CFG_STR      "show"

/* TCPSPDTEST protocols */
#define TCPSPD_PROTOCOL_HTTP_STR     "http"
#define TCPSPD_PROTOCOL_FTP_STR      "ftp"


/******************************************** Macros *********************************************/
#ifdef TCPSPD_DEBUG
#define tc_debug(fmt, ...) \
       pr_info("%s:%d "fmt,__FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define tc_debug(fmt, ...) \
       no_printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#endif

#define tc_err(fmt, ...) \
    pr_err("%s:%d Error! "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define tc_info(fmt, ...) \
    printk(fmt, ##__VA_ARGS__);


/******************************************** Types **********************************************/
typedef enum
{
    TCPSPD_MODE_NONE = 0,
    TCPSPD_MODE_HTTP = 80,
    TCPSPD_MODE_FTP = 21,
    TCPSPD_MODE_IPERF3 = TCPSPD_MODE_FTP, /* Similar handling, port is meaningless as mode is not configurable from procfs */
    TCPSPD_MODE_BASIC = TCPSPD_MODE_FTP,  /* Similar handling, similarily to above */
} tcpspd_mode_t;

typedef enum
{
    TCPSPD_STATE_FREE,
    TCPSPD_STATE_ALLOCATED,
    TCPSPD_STATE_CONNECTED,
    TCPSPD_STATE_DISCONNECTED,
    TCPSPD_STATE_RELEASED,
    TCPSPD_STATE_RUNNING,
    TCPSPD_STATE_DONE_DATA,
} tcpspd_state_t;

typedef struct
{
    struct socket       *srv_socket;
    tcpspd_mode_t       mode;
    spdt_stream_dir_t   action;
    tcpspd_state_t        state;
    spdt_stream_params_t  stream_params;
    struct sock           *sk;
    uint8_t             end_of_test_spd_report:1;
    uint8_t             add_flow:1;
    uint8_t             hw_accel:1;
    uint32_t            rwnd_bytes;
    uint32_t            rate_Mbps;
    struct net_device   *netdev;
} tcpspd_t;

extern int rnr_engine;
extern tcpspd_t g_tcpspd[];
#define STREAM_IS_HWACCEL(idx) (rnr_engine && g_tcpspd[(idx)].hw_accel)

extern tcp_spdt_rep_t g_spd_report[];
extern struct rtnl_link_stats64 g_spd_iface_stats_start[];

/******************************************** Functions ******************************************/
/* #ib#todo#: split to .h files */
int tcpspd_cmd_connect(uint8_t stream_idx, spdt_stream_dir_t dir, tcpspd_mode_t mode, spdt_conn_params_t *params);
int tcpspd_cmd_download(uint8_t stream_idx,  char *host_str, char *filename, uint64_t length);
int tcpspd_cmd_upload(uint8_t stream_idx, char *filename, uint64_t length);
int tcpspd_cmd_oob_send(uint8_t stream_idx, char *buff, uint64_t length);
int tcpspd_cmd_disconnect(uint8_t stream_idx);
int tcpspd_cmd_release(uint8_t stream_idx);
int tcpspd_cmd_stream_idx(uint8_t *stream_idx, uint8_t *num_streams, tcpspdtest_genl_cmd_param_t cmd_param);
int tcpspd_cmd_protocol(uint8_t stream_idx, spdt_proto_t *protocol, tcpspdtest_genl_cmd_param_t cmd_param);
int tcpspd_cmd_stream_params(uint8_t stream_idx, spdt_stream_params_t *req_stream_params, spdt_stream_params_t *stream_params, tcpspdtest_genl_cmd_param_t cmd_param);
int tcpspd_cmd_num_streams(uint8_t stream_idx, uint8_t *num_streams, uint8_t *num_udp_streams);
int tcpspd_cmd_speed_report_blocking(uint8_t stream_idx);

int tcpspd_prtcl_http_download_request(uint8_t stream_idx, unsigned char *host_str, unsigned char *filename);
int tcpspd_prtcl_http_upload_request(uint8_t stream_idx, unsigned char *filename, uint64_t upload_size);
int tcpspd_prtcl_ftp_download_request(uint8_t stream_idx, uint64_t download_size);
int tcpspd_prtcl_ftp_upload_request(uint8_t stream_idx, uint64_t upload_size);
int tcpspd_prtcl_nf_hook(uint8_t stream_idx, struct sk_buff *skb, unsigned int hooknum);

int tcpspd_get_iface_stats_by_stream(uint8_t stream_idx, struct rtnl_link_stats64 *dev_stats);

static __inline__ long tcpspd_calc_delay_us(struct timeval *start_time, struct timeval *end_time)
{
    return (end_time->tv_sec - start_time->tv_sec) * 1000000 + end_time->tv_usec - start_time->tv_usec;
}

static __inline__ void tcpspd_timespec_add_us(struct timeval *end_time, uint32_t add_usec)
{
    end_time->tv_usec += add_usec;
    if (1000000 < end_time->tv_usec)
    {
        uint32_t add_sec = end_time->tv_usec / 1000000;
        if (add_sec > 1) printk("=== add_sec:%u\n", add_sec);
        end_time->tv_sec += add_sec;
        end_time->tv_usec -= add_sec * 1000000;
    }
}

#endif /* __TCPSPDTEST_H_INCLUDED__ */
