/*
<:copyright-BRCM:2022:DUAL/GPL:standard

   Copyright (c) 2022 Broadcom 
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

#ifndef __SPDSVC_TR471_H_INCLUDED__
#define __SPDSVC_TR471_H_INCLUDED__

#define TR471_HW_STREAM_IDX(connindex) connindex

enum _tr471_flow_state_t {
    TR471_FLOW_STATE_INACTIVE,
    TR471_FLOW_STATE_ACTIVE_SW,
    TR471_FLOW_STATE_ACTIVE_HW
};

typedef enum  {
    TR471_THREAD_MODE_INVALID,
    TR471_THREAD_MODE_SW_GEN,
    TR471_THREAD_MODE_HW_DONE,
    TR471_THREAD_MODE_FWD_N_RECYCLE_RX_BUFF
}_tr471_thread_mode_t;

typedef struct {
    void *fkb_p;                /* fkb */
    unsigned char   *data;      /* data pointer */
    unsigned int    len;        /* packet length */
    int             l3_offset;  /* L3 header offset from data */
    int             l4_offset;  /* L4 header offset from data */
    int             lHdr_offset;/* Load Hdr offset from data */
} spdsvc_tr471_ref_pkt_info_t;

typedef struct {
    int is_hw_tx;
    uint8_t hw_index;
    spdsvc_tr471_ref_pkt_info_t ref_pkt_info;
    enum _tr471_flow_state_t flow_state;
    uint32_t tx_count;
    spdsvc_tuple_t tr471_tx_tuple; /* Used only to compare */
} spdsvc_tr471_flow_info_t;

#define SPDSVC_TR471_RX_RECYCLE_QUEUE_SIZE  1024 // Must be power of 2
#define SPDSVC_RX_MAX_RECYCLE_BUDGET        8

typedef struct {
   int        action;
   int        connindex;
   pNBuff_t   pRxNBuf;
   struct loadHdr *lhdr_p;
} spdsvc_tr471_rx_recycle_queue_entry_t;

typedef struct {
    int                             installed;
    void                            *netdev_p;
    int                              is_v6;
    spinlock_t                       spdsvc_lock;
    int                              rx_recycle_budget;
    spdsvc_tr471_flow_info_t         flowinfo[SPDSVC_MAX_CONN];
    bcm_async_queue_t                spdsvc_tr471_rx_recycle_queue;
} spdsvc_tr471_t;

enum tr471_NF_pkt_result_t {
    TR471_NF_PKT_PASS, /* NF_ACCEPT */
    TR471_NF_PKT_DROP, /* NF_STOLEN + Free pkt */
    TR471_NF_PKT_FWDED,/* NF_STOLEN + Pkt Forwarded */
    TR471_NF_PKT_LHDR  /* NF_STOLEN + Pass lHdr + Free Pkt */
};
extern spdsvc_tr471_t _spdsvc_tr471_state_g;

int tr471_send_tx_pkts(int connindex, spdsvc_t *spdsvc_p);
void spdsvc_fc_blog_flowevent(int connindex, unsigned long event, uint32_t event_type);
int spdsvc_tr471_store_ref_pkt_info(int connindex, void *skb, spdsvc_tr471_ref_pkt_info_t *ref_info_p);
void spdsvc_tr471_reset_state_machine(int connindex);
int  spdsvc_tr471_get_result(int connindex, spdsvc_result_t *result_p);
void spdsvc_tr471_generator_setup(int connindex);
int spdsvc_tr471_analyzer_enable(int connindex, spdsvc_socket_t *socket_p, spdsvc_config_tr471_t *tr471_p);
int spdsvc_tr471_analyzer_disable(int connindex);
int spdsvc_tr471_start_generator(int connindex);
void spdsvc_tr471_generator_burst_cmpl(int connindex);
void spdsvc_tr471_generator_disable(int connindex);
int spdsvc_tr471_update_ref_pkt_lHdr(int connindex, struct loadHdr *lHdr_p);

/* TODO - temporary */
void spdsvc_tr471_gen_start(int connindex);
unsigned int spdsvc_tr471_process_out_udp(int connindex, void *skb, void *payload_p, Blog_t **blog_pp, int is_v6);
unsigned int spdsvc_tr471_process_in_udp(int connindex, void *skb, void *payload_p, void **skb_dev_pp, Blog_t **blog_pp, int is_v6, int lkup_result, int frag_id);
int spdsvc_conn_lookup (void *ip_payload_p, int is_v6, int *connindex_p);

#define tr471_record_pktgen_time(start, cmpl) tr471_update_pktgen_time(spdsvc_g.tr471.firstBurst, spdsvc_g.tr471.burstsize, start, cmpl)
#define tr471_record_tsk_wkup_time(start, cmpl) tr471_update_task_wkup_time(spdsvc_g.tr471.firstBurst, spdsvc_g.tr471.burstsize, start, cmpl)
#define tr471_record_total_burst_time(start, cmpl) tr471_update_total_time(spdsvc_g.tr471.firstBurst, spdsvc_g.tr471.burstsize, start, cmpl)
#define tr471_record_burst_gen_set_time(start, cmpl) tr471_update_burst_gen_set_time(spdsvc_g.tr471.firstBurst, spdsvc_g.tr471.burstsize, start, cmpl)

#endif // __SPDSVC_FC_H_INCLUDED__
