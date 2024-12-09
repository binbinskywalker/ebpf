/**
 * ebpf 用户空间程序(loader、read ringbuffer)
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>
#include "kprobe.skel.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
	return vfprintf(stderr
, format, args);
}

static volatile sig_atomic_t
 stop;
static void sig_int(int signo)
{
	stop = 
1
;
}

int main(int argc, char **argv)
{
	struct
 kprobe_bpf *skel;
	int
 err;

	/* 设置libbpf错误和调试信息回调 */
	libbpf_set_print(libbpf_print_fn);

	/* 加载并验证 kprobe.bpf.c 应用程序 */
	skel = kprobe_bpf__open_and_load();
	if
 (!skel) {
		fprintf(stderr, "Failed to open BPF skeleton\n"
);
		return 1
;
	}

	/* 附加 kprobe.bpf.c 程序到跟踪点 */
	err = kprobe_bpf__attach(skel);
	if
 (err) {
		fprintf(stderr, "Failed to attach BPF skeleton\n"
);
		goto
 cleanup;
	}

	/* Control-C 停止信号 */
	if
 (signal(SIGINT, sig_int) == SIG_ERR) {
		fprintf(stderr, "can't set signal handler: %s\n"
, strerror(errno));
		goto
 cleanup;
	}

	printf("Successfully started! Please run `sudo cat /sys/kernel/debug/tracing/trace_pipe` "
	       "to see output of the BPF programs.\n"
);

	while
 (!stop) {
		fprintf(stderr, "."
);
		sleep(
1
);
	}

cleanup:
	/* 销毁挂载的ebpf程序 */
	kprobe_bpf__destroy(skel);
	return
 -err;
}
