#pragma once

/* DPDK functionality */
void dpdk_init(int *argc, char ***argv);
void dpdk_terminate(void);
void dpdk_poll(uint16_t queue_id);
void dpdk_out(struct rte_mbuf *pkt);

RTE_DECLARE_PER_LCORE(int, queue_id);
