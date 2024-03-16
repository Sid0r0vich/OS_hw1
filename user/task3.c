#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	int p[2];
	int res = pipe(p);

	if (res < 0) {
		fprintf(2, "pipe error!\n");
		exit(1);
	}
	
	int pid = fork();
	if (pid > 0) {
		close(p[0]);
		for (int i = 1; i < argc; ++i) {
			int res = write(p[1], argv[i], strlen(argv[i]));
			if (res < 0) {
				fprintf(2, "write error!");
				break;
			}
			
			res = write(p[1], "\n", 1);
			if (res < 0) {
				fprintf(2, "write error!");
				break;
			}
		}
		close(p[1]);

		wait( (int*)0 );
	}
	else if (!pid) {
		close(p[1]);

		close(0);
		dup(p[0]);;
		close(p[0]);

		char *argv[] = {"/wc", 0};
		exec("/wc", argv);
		fprintf(2, "exec error!\n");
		
		exit(0);
	} else {
		fprintf(2, "fork error!\n");
	} 

	return 0;
}
