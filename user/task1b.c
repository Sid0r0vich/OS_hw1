#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
	int pid = fork();
	
	if (!pid) {
		sleep(50);
		exit(1);
	}
	else if (pid > 0) {
		printf("parent: %d, child: %d\n", getpid(), pid);

		int exit_code;
		kill(pid);
		pid = wait(&exit_code);

		printf("killed child: %d, exit code: %d\n", pid, exit_code);
	}
	else {
		fprintf(2, "fork error!");
	}
	
	return 0;
}
