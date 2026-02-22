#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <wchar.h>
#include <locale.h>
#include <pwd.h>
#include <limits.h>

char cwd[512];
char prm[512];
char *cmd;
char hostname[HOST_NAME_MAX];

int main() {
	setlocale(LC_ALL, "");
	printf("\033[37m\033[40m|¯¯¯¯¯¯¯\033[37m\033[44m¯¯¯¯¯¯¯¯\033[37m\033[40m¯¯¯¯¯¯¯|\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\n");
	printf("\033[37m\033[40m|_______\033[37m\033[44m________\033[37m\033[40m_______|\n");

	printf("\033[0m\nHi, %s!\nWhat would you do?\n\n", getlogin());

    while (1) {

	gethostname(hostname, HOST_NAME_MAX);
	printf("%s | %s", getlogin(), hostname);
	getcwd(cwd, sizeof(cwd));
	snprintf(prm, sizeof(prm), " | %s $ ", cwd);
	
	cmd = readline(prm);
	if (!cwd) break;
	if (*cwd) {
	    add_history(cmd);
	}

	if (strncmp(cmd, "q", 1) == 0) {
	    free(cmd);
	    break;
	} else if (strncmp(cmd, "cd", 2) == 0) {
	    chdir(cmd + 3);
	} else if (strncmp(cmd, "I am not a moron!", 17) == 0) {
		printf("Yes, you are!!!\n");
		sleep(1);
		printf("You are the moron, they built to make me an idiot!\n");
	} else if (strncmp(cmd, "potato", 6) == 0) {
		printf("Картошка!\n");
		sleep(1);
		printf("Картошка\n");
		printf("Картошка\n");
		printf("Картошка!\n");
	} else {
	    system(cmd);
	}

	free(cmd);
    }
    return 0;
}
