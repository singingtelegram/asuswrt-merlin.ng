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
* File Name  : tcp_engine_api.h
*
* Description: This file contains the Broadcom Tcp Speed Test Engine API definitions.
*
*  Created on: Dec 6, 2016
*      Author: Nikolai Iosifov
*******************************************************************************
*/

#ifndef __TCP_ENGINE_API_H_INCLUDED__
#define __TCP_ENGINE_API_H_INCLUDED__

#include "tcpspdtest_defs.h"

#define TCP_ENGINE_DYNACK_THR_UPD_RATE_DEFAULT 16
#define TCP_ENGINE_DYNACK_THR_UPD_RATE_MAX 64

typedef void (* tcp_engine_cb_t)(uint8_t stream_idx, void *data, uint16_t len);

/* Parameters that are set once during module init */
typedef struct {
    uint32_t pktbuf_size; 
    uint32_t rto_list_len;  
} tcp_engine_config_t;

/* Parameters that are set each time connection is started */
typedef struct {
    uint16_t cwnd_initial_mss;      /* initial congestion window size in MSS */
    uint16_t cwnd_initial_thr_mss;  /* initial congestion window threshold size in MSS */
    uint16_t cwnd_max_mss;          /* max congestion window size in MSS */
} tcp_engine_conn_config_t;

/******************************************** Functions ******************************************/
void tcpspd_engine_hijack_hook_conn_learn_host_mac(uint8_t stream_idx, bdmf_mac_t *host_mac);
int tcpspd_engine_hijack_hook_conn_learn(uint8_t stream_idx, void *data, int update_conn_info);
int tcpspd_engine_hijack_tcp_in(uint8_t stream_idx, void *data, uint32_t txwscale);
int tcpspd_engine_hijack_tcp_out(uint8_t stream_idx, void *data, uint8_t ip_summed);
int tcpspd_engine_hijack_tcp_in6(uint8_t stream_idx, void *data, uint32_t txwscale);
int tcpspd_engine_hijack_tcp_out6(uint8_t stream_idx, void *data, uint8_t ip_summed);
int tcpspd_engine_send_data(uint8_t stream_idx, uint8_t *data, uint16_t size);
int tcpspd_engine_start_tx(uint8_t stream_idx, uint64_t size);
void tcpspd_engine_done_data(uint8_t stream_idx, void *data);
void tcpspd_engine_print_stats(void);
void tcpspd_engine_set_state_up(uint8_t stream_idx);
void tcpspd_engine_set_test_on_off(uint8_t is_on, uint8_t stream_idx);
int tcpspd_engine_is_state_up(uint8_t stream_idx);
int tcpspd_engine_is_sock_learned(uint8_t stream_idx);
void tcpspd_engine_set_sack(uint8_t stream_idx);
void tcpspd_engine_set_mss(uint8_t stream_idx, uint32_t snd_mss, uint32_t adv_mss);
void tcpspd_engine_set_resp_handle_token(uint8_t stream_idx, uint16_t num);
void tcpspd_engine_set_txwscale(uint8_t stream_idx, uint8_t txwscale);
void tcpspd_engine_set_rtt(uint8_t stream_idx, uint32_t rtt);
void tcpspd_engine_set_rwnd(uint8_t stream_idx, uint32_t rwnd_bytes, uint32_t rtt, uint16_t wsacle, uint32_t rate_Mbps);
int tcpspd_engine_set_rto(uint32_t initial_rto_usec, uint16_t rto_ratio, uint8_t is_dynamic_rto_time);
int tcpspd_engine_set_bucket_ratelimit(uint8_t is_enabled, uint32_t rate_Mbps);
int tcpspd_engine_set_dynack(uint8_t thr_upd_rate);
void tcpspd_engine_show_global_settings(void);
int tcpspd_engine_set_spdsts_print(uint8_t is_enabled, uint8_t is_total, uint32_t interval_ms);
void tcpspd_engine_print_last_spdsts(uint8_t stream_idx);
void tcpspd_engine_set_expected_bytes(uint8_t stream_idx, uint64_t bytes);
uint64_t tcpspd_engine_get_expected_bytes(uint8_t stream_idx);
int tcpspd_engine_get_bytes(uint8_t stream_idx, uint64_t *bytes);
int tcpspd_engine_init_rto_sack(uint8_t stream_idx);
int tcpspd_engine_uninit_rto_sack(uint8_t stream_idx);
int tcpspd_engine_cpu_flow_add(struct socket *sock, uint8_t stream_idx);
int tcpspd_engine_init_rnr_download(uint8_t stream_idx, uint16_t req_pkt_size, uint8_t is_update);
int tcpspd_engine_uninit_rnr_download(uint8_t stream_idx);
int tcpspd_engine_init_rnr_upload(uint8_t stream_idx);
int tcpspd_engine_uninit_rnr_upload(uint8_t stream_idx);
int tcpspd_engine_init_tcb(uint8_t stream_idx, uint8_t is_upload, tcp_engine_cb_t response_cb, tcp_engine_cb_t complete_cb);
int tcpspd_engine_disconnect(uint8_t stream_idx);
int tcpspd_engine_down(uint8_t stream_idx);
void tcpspd_engine_conn_config_set(uint8_t stream_idx, tcp_engine_conn_config_t *config);

int tcpspd_engine_init(tcp_engine_config_t *config);
int tcpspd_engine_shutdown(void);

#endif /* __TCP_ENGINE_API_H_INCLUDED___ */
