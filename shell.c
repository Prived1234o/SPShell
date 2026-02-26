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
#include <stdbool.h>
#include <time.h>
#include <termios.h>

char cwd[512];
char prm[512];
char *cmd;
char hostname[HOST_NAME_MAX];
char dist[90];
char *endi;
short rnew;
short cch;
int sch;
char usin[128];
struct termios oldt, newt;
short ns;

int main() {
	char h[128] = "/home/";
	strcat(h, getlogin());
	setvbuf(stdout, NULL, _IONBF, 0);
	// write os id to variable "endi"
	FILE *fidi = fopen("/etc/os-release", "r");
	char line[256];
	while (fgets(dist, sizeof(dist), fidi)) {
		if (strncmp(dist, "ID=", 3) == 0) {
			endi = dist + 3;
			break;
		}
	}
	fclose(fidi);
	// print ASCII art
	setlocale(LC_ALL, "");
	printf("\033[37m\033[40m|¯¯¯¯¯¯¯\033[37m\033[44m¯¯¯¯¯¯¯¯\033[37m\033[40m¯¯¯¯¯¯¯|\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|_______\033[37m\033[44m________\033[37m\033[40m_______|\033[0m\n");

	// print greeting
	printf("\n!!! НЕТ ВОЙНЕ !!!\n\nHi, %s!\nWhat would you do?\n For list of command write 'help'\n\n", getlogin());


	// =============================== MAIN CYCLE ===============================

    while (1) {

	// ----- greeting block -----

	// print greeting
	struct termios oldt, newt;
    	int rows = 0, cols = 0;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        write(STDOUT_FILENO, "\033[6n", 4);
	scanf("\033[%d;%dR", &rows, &cols);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    	if (cols > 1) printf("\n");
	gethostname(hostname, HOST_NAME_MAX);
	getcwd(cwd, sizeof(cwd));
	snprintf(prm, sizeof(prm), "%s | %s | %s $ ", getlogin(), hostname, cwd);

	// input command
	cmd = readline(prm);
	if (!cwd) break;
	if (*cwd) {
	    add_history(cmd);
	}

	// ----- command block -----

	// command q (quit)
	if (strncmp(cmd, "q", 1) == 0) {
	    printf("\n");
	    free(cmd);
	    break;
    }
	// command cd (change directory)
	else if (strncmp(cmd, "cd", 2) == 0) {
	    if (strncmp(cmd + 3, "~", 1) == 0) {
		chdir(h);
	    } else {
	        chdir(cmd + 3);
	    }
    }
	// command sus
	else if (strncmp(cmd, "sus", 3) == 0) {
	    printf("This looks kinda SUS...");
    }
	// command hi
	else if (strncmp(cmd, "hi", 2) == 0) {
		printf("Hello!");
    }
	// command news
	else if (strncmp(cmd, "news", 4) == 0) {
		srand(time(NULL));
		rnew = rand() % 10;
		switch (rnew) {
			case 0:
				printf("Wheatley says, he isn't a moron! Everyone is laughing, but GLaDOS is potato.");
				break;
			case 1:
				printf("Microslop (didn't) make windows open source!!!!!!!!!");
				break;
			case 2:
				printf("I use Arch BTW");
				break;
			case 3:
				printf("Vladimir Putin says, internet is drugs!");
				break;
			case 4:
				printf("CEO of OpenAI says, vibecoding is our future! Is he right?");
				break;
			case 5:
				printf("'Tomorrow's wind will blow tomorrow' - Karych");
				break;
			case 6:
				printf("Scientists have taken on one of the most difficult questions in human history: Why do people dislike Viette's theorem so much?");
				break;
			case 7:
				printf("When you feel stupid, remember that Windows users don't use the terminal on a daily basis.");
				break;
			case 8:
				printf("Roskomnadzor has banned the letter 'A'");
				break;
			case 9:
				printf("Cheese ball.");
				break;
		}
    }
	// command rps (rock paper scissors)
	else if (strncmp(cmd, "rps", 3) == 0) {
	    struct termios t;
	    int sch = 0, cch, u;
            char b;
	    tcgetattr(0, &t);
	    struct termios n = t;
	    n.c_lflag &= ~(ICANON | ECHO);
	    tcsetattr(0, TCSANOW, &n);
	    srand(time(0));
	    while (printf("1. Rock\n2. Paper\n3. Scissors\n4. Quit\n") && read(0, &b, 1) && b != '4') {
		u = b - '0';
		cch = rand() % 3 + 1;
		printf("\nComputer: ");
		if (cch == 1) printf("rock");
		if (cch == 2) printf("paper");
		if (cch == 3) printf("scissors");
		printf(" | ");
		if (u == cch) printf("Draw");
		else if ((u % 3) + 1 == cch) { printf("You lost"); sch--; }
		else { printf("You won"); sch++; }
		printf(" | Score: %d\n\n", sch);
	    }
	    tcsetattr(0, TCSANOW, &t);
    }
	// command I am not a moron (reference to portal 2)
	else if (strncmp(cmd, "I am not a moron!", 17) == 0) {
	    printf("Yes, you are!!!\n");
	    sleep(1);
	    printf("You are the moron, they built to make me an idiot!");
    }
	// command potato (reference to PWGood)
	else if (strncmp(cmd, "potato", 6) == 0) {
	    printf("Картошка!\n");
	    sleep(1);
	    printf("картошка\nкартошка\nкартошка!");
    }
	// command inst (install)
	else if (strncmp(cmd, "inst", 4) == 0) {
	    char incm[256];
	    if (strncmp(endi, "arch", 4) == 0) {
                sprintf(incm, "sudo pacman -S %s", (cmd + 5)); // ARCH
            } else if (strncmp(endi, "ubuntu", 6) == 0 || strncmp(endi, "debian", 6) == 0) {
                sprintf(incm, "sudo apt install %s", (cmd + 5)); // UBUNTU or DEBIAN
            } else if (strncmp(endi, "gentoo", 6) == 0) {
                sprintf(incm, "sudo emerge --ask %s", (cmd + 5)); // GENTOO
            } else if (strncmp(endi, "fedora", 6) == 0) {
                sprintf(incm, "sudo dnf install %s", (cmd + 5)); // FEDORA
            } else {
		break;
	    }
	    system(incm);
    }
	// command ua (update all)
	else if (strncmp(cmd, "ua", 2) == 0) {
	    if (strncmp(endi, "arch", 4) == 0) {
		system("sudo pacman -Syu"); // ARCH
	    } else if (strncmp(endi, "ubuntu", 6) == 0 || strncmp(endi, "debian", 6) == 0) {
		system("sudo apt update"); // UBUNTU or DEBIAN
	    } else if (strncmp(endi, "gentoo", 6) == 0) {
		system("sudo emerge --sync"); // GENTOO
		system("sudo emerge -avuDN @world");
	    } else if (strncmp(endi, "fedora", 6) == 0) {
		system("sudo dnf upgrade --refresh"); // FEDORA
	    }
    }
    // command help (display all commands)
    else if (strncmp(cmd, "help", 4) == 0){
        printf("q -- quit from the program\n");
        printf("cd <argument> -- change working directory to <argument>\n");
        printf("inst <arguments> -- install packet with packet manager for current OS\n");
        printf("ua -- update all outdated packets\n");
        printf("rps -- play rock paper scissors with random computer output\n");
        if (strncmp(cmd + 5, "--with-spoilers", 15) == 0){
            printf("sus -- print 'This looks kinda sus...'\n");
            printf("hi -- print 'Hello!'\n");
            printf("potato -- print word potato in russian 4 times\n");
            printf("news -- print a random news title (not real)\n");
            printf("I am not a moron! -- print 'Yes, you are!!!' 'You are the moron, they built to make me an idiot!'\n");
        else {
            printf("other commands are:  sus   hi   potato   news   I am not a moron!\n");
            printf("\nTo see spoilers to commands write 'help --with-spoilers'\n");
        }
    }
	// other commands are redirected to the OS
	else {
	    system(cmd);
	}

	// clear memory
	free(cmd);
    }
    printf("\n");
    return 0;
}#include <stdio.h>
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
#include <stdbool.h>
#include <time.h>
#include <termios.h>

char cwd[512];
char prm[512];
char *cmd;
char hostname[HOST_NAME_MAX];
char dist[90];
char *endi;
short rnew;
short cch;
int sch;
char usin[128];
struct termios oldt, newt;
short ns;

int main() {
	char h[128] = "/home/";
	strcat(h, getlogin());
	setvbuf(stdout, NULL, _IONBF, 0);
	// write os id to variable "endi"
	FILE *fidi = fopen("/etc/os-release", "r");
	char line[256];
	while (fgets(dist, sizeof(dist), fidi)) {
		if (strncmp(dist, "ID=", 3) == 0) {
			endi = dist + 3;
			break;
		}
	}
	fclose(fidi);
	// print ASCII art
	setlocale(LC_ALL, "");
	printf("\033[37m\033[40m|¯¯¯¯¯¯¯\033[37m\033[44m¯¯¯¯¯¯¯¯\033[37m\033[40m¯¯¯¯¯¯¯|\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[41m\033[37m|       \033[37m\033[45m        \033[41m\033[37m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|       \033[37m\033[44m        \033[37m\033[40m       |\033[0m\n");
	printf("\033[37m\033[40m|_______\033[37m\033[44m________\033[37m\033[40m_______|\033[0m\n");

	// print greeting
	printf("\n!!! НЕТ ВОЙНЕ !!!\n\nHi, %s!\nWhat would you do?\n For list of command write 'help'\n\n", getlogin());


	// =============================== MAIN CYCLE ===============================

    while (1) {

	// ----- greeting block -----

	// print greeting
	struct termios oldt, newt;
    	int rows = 0, cols = 0;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        write(STDOUT_FILENO, "\033[6n", 4);
	scanf("\033[%d;%dR", &rows, &cols);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    	if (cols > 1) printf("\n");
	gethostname(hostname, HOST_NAME_MAX);
	getcwd(cwd, sizeof(cwd));
	snprintf(prm, sizeof(prm), "%s | %s | %s $ ", getlogin(), hostname, cwd);

	// input command
	cmd = readline(prm);
	if (!cwd) break;
	if (*cwd) {
	    add_history(cmd);
	}

	// ----- command block -----

	// command q (quit)
	if (strncmp(cmd, "q", 1) == 0) {
	    printf("\n");
	    free(cmd);
	    break;
    }
	// command cd (change directory)
	else if (strncmp(cmd, "cd", 2) == 0) {
	    if (strncmp(cmd + 3, "~", 1) == 0) {
		chdir(h);
	    } else {
	        chdir(cmd + 3);
	    }
    }
	// command sus
	else if (strncmp(cmd, "sus", 3) == 0) {
	    printf("This looks kinda SUS...");
    }
	// command hi
	else if (strncmp(cmd, "hi", 2) == 0) {
		printf("Hello!");
    }
	// command news
	else if (strncmp(cmd, "news", 4) == 0) {
		srand(time(NULL));
		rnew = rand() % 10;
		switch (rnew) {
			case 0:
				printf("Wheatley says, he isn't a moron! Everyone is laughing, but GLaDOS is potato.");
				break;
			case 1:
				printf("Microslop (didn't) make windows open source!!!!!!!!!");
				break;
			case 2:
				printf("I use Arch BTW");
				break;
			case 3:
				printf("Vladimir Putin says, internet is drugs!");
				break;
			case 4:
				printf("CEO of OpenAI says, vibecoding is our future! Is he right?");
				break;
			case 5:
				printf("'Tomorrow's wind will blow tomorrow' - Karych");
				break;
			case 6:
				printf("Scientists have taken on one of the most difficult questions in human history: Why do people dislike Viette's theorem so much?");
				break;
			case 7:
				printf("When you feel stupid, remember that Windows users don't use the terminal on a daily basis.");
				break;
			case 8:
				printf("Roskomnadzor has banned the letter 'A'");
				break;
			case 9:
				printf("Cheese ball.");
				break;
		}
    }
	// command rps (rock paper scissors)
	else if (strncmp(cmd, "rps", 3) == 0) {
	    struct termios t;
	    int sch = 0, cch, u;
            char b;
	    tcgetattr(0, &t);
	    struct termios n = t;
	    n.c_lflag &= ~(ICANON | ECHO);
	    tcsetattr(0, TCSANOW, &n);
	    srand(time(0));
	    while (printf("1. Rock\n2. Paper\n3. Scissors\n4. Quit\n") && read(0, &b, 1) && b != '4') {
		u = b - '0';
		cch = rand() % 3 + 1;
		printf("\nComputer: ");
		if (cch == 1) printf("rock");
		if (cch == 2) printf("paper");
		if (cch == 3) printf("scissors");
		printf(" | ");
		if (u == cch) printf("Draw");
		else if ((u % 3) + 1 == cch) { printf("You lost"); sch--; }
		else { printf("You won"); sch++; }
		printf(" | Score: %d\n\n", sch);
	    }
	    tcsetattr(0, TCSANOW, &t);
    }
	// command I am not a moron (reference to portal 2)
	else if (strncmp(cmd, "I am not a moron!", 17) == 0) {
	    printf("Yes, you are!!!\n");
	    sleep(1);
	    printf("You are the moron, they built to make me an idiot!");
    }
	// command potato (reference to PWGood)
	else if (strncmp(cmd, "potato", 6) == 0) {
	    printf("Картошка!\n");
	    sleep(1);
	    printf("картошка\nкартошка\nкартошка!");
    }
	// command inst (install)
	else if (strncmp(cmd, "inst", 4) == 0) {
	    char incm[256];
	    if (strncmp(endi, "arch", 4) == 0) {
                sprintf(incm, "sudo pacman -S %s", (cmd + 5)); // ARCH
            } else if (strncmp(endi, "ubuntu", 6) == 0 || strncmp(endi, "debian", 6) == 0) {
                sprintf(incm, "sudo apt install %s", (cmd + 5)); // UBUNTU or DEBIAN
            } else if (strncmp(endi, "gentoo", 6) == 0) {
                sprintf(incm, "sudo emerge --ask %s", (cmd + 5)); // GENTOO
            } else if (strncmp(endi, "fedora", 6) == 0) {
                sprintf(incm, "sudo dnf install %s", (cmd + 5)); // FEDORA
            } else {
		break;
	    }
	    system(incm);
    }
	// command ua (update all)
	else if (strncmp(cmd, "ua", 2) == 0) {
	    if (strncmp(endi, "arch", 4) == 0) {
		system("sudo pacman -Syu"); // ARCH
	    } else if (strncmp(endi, "ubuntu", 6) == 0 || strncmp(endi, "debian", 6) == 0) {
		system("sudo apt update"); // UBUNTU or DEBIAN
	    } else if (strncmp(endi, "gentoo", 6) == 0) {
		system("sudo emerge --sync"); // GENTOO
		system("sudo emerge -avuDN @world");
	    } else if (strncmp(endi, "fedora", 6) == 0) {
		system("sudo dnf upgrade --refresh"); // FEDORA
	    }
    }
    // command help (display all commands)
    else if (strncmp(cmd, "help", 4) == 0){
        printf("q -- quit from the program\n");
        printf("cd <argument> -- change working directory to <argument>\n");
        printf("inst <arguments> -- install packet with packet manager for current OS\n");
        printf("ua -- update all outdated packets\n");
        printf("rps -- play rock paper scissors with random computer output\n");
        if (strncmp(cmd + 5, "--with-spoilers", 15) == 0){
            printf("sus -- print 'This looks kinda sus...'\n");
            printf("hi -- print 'Hello!'\n");
            printf("potato -- print word potato in russian 4 times\n");
            printf("news -- print a random news title (not real)\n");
            printf("I am not a moron! -- print 'Yes, you are!!!' 'You are the moron, they built to make me an idiot!'\n");
        else {
            printf("other commands are:  sus   hi   potato   news   I am not a moron!\n");
            printf("\nTo see spoilers to commands write 'help --with-spoilers'\n");
        }
    }
	// other commands are redirected to the OS
	else {
	    system(cmd);
	}

	// clear memory
	free(cmd);
    }
    printf("\n");
    return 0;
}
