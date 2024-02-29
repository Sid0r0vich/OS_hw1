#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	int p[2];
	pipe(p);
	
	int pid = fork();
	if (pid > 0) {
		close(p[0]);
		for (int i = 1; i < argc; ++i) {
			write(p[1], argv[i], strlen(argv[i]));
			write(p[1], "\n", 1);
		}
		close(p[1]);

		wait( (int*)0 );
	}
	else if (!pid) {
		close(p[1]);

		char c;
		while ( read(p[0], &c, 1) > 0 ) {
			printf("%c", c);
		}
		
		close(p[0]);
		exit(0);
	} else {
		fprintf(2, "fork error!\n");
	} 

	return 0;
}
