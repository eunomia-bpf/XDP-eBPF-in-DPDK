#include <stdio.h>
#include <signal.h>

#include <rte_lcore.h>

#include <base.h>

volatile bool force_quit;
RTE_DEFINE_PER_LCORE(int, queue_id);

static void signal_handler(int signum)
{
	if (signum == SIGINT || signum == SIGTERM) {
		printf("\n\nSignal %d received, preparing to exit...\n",
		       signum);
		force_quit = true;
	}
}

static int thread_main(void *arg)
{
	uint32_t thread_id = (int)(long)(arg);
  printf("Worker main\n");
#if 0
	printf("Thread id is %d and pipelines are tx %d rx %d\n", thread_id,
	       TX_PIPELINE_THREAD_ID, RX_PIPELINE_THREAD_ID);

	if (thread_id == RX_PIPELINE_THREAD_ID)
		recv_pipeline_main((void *)(long)thread_id);
	else if (thread_id == TX_PIPELINE_THREAD_ID)
		send_pipeline_main((void *)(long)thread_id);
	else
		worker_main((void *)(long)thread_id);
#endif

	return 0;
}

int main(int argc, char **argv)
{
	int count, lcore_id, ret = 0;

	printf("Hello world\n");

	dpdk_init(&argc, &argv);

	/* set signal handler for proper exiting */
	force_quit = false;
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	/* Setup dispatcher workers communication rings */
	count = rte_lcore_count();
	printf("There are %d cores\n", count);

	RTE_LCORE_FOREACH_WORKER(lcore_id)
	{
		rte_eal_remote_launch(thread_main, (void *)(long)count,
				      lcore_id);
		count++;
	}

	thread_main((void *)(long)0);

	RTE_LCORE_FOREACH_WORKER(lcore_id)
	{
		if (rte_eal_wait_lcore(lcore_id) < 0) {
			ret = -1;
			break;
		}
	}

	dpdk_terminate();
	return ret;
}
