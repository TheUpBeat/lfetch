#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/utsname.h>
#include<libgen.h>
#include<sys/sysinfo.h>

int main()
{
	char *user = getenv("USER");
	if(user==NULL) return EXIT_FAILURE;

	char hostname[1024];
	gethostname(hostname, 1024);

	FILE *p;
	char ch;
	p = popen("lsb_release -sd", "r");
	if(p == NULL) return EXIT_FAILURE;

	FILE* model;
	char modelname[70];
	model = fopen("/sys/devices/virtual/dmi/id/product_name", "r");
	
	const long minute = 60;
 	const long hour = minute * 60;
 	const long day = hour * 24;
	struct sysinfo si;
	sysinfo(&si);

	struct utsname uName;
	uname(&uName);

	FILE* pak;
	char pk[7];
	pak = popen("xbps-query -l | wc -l", "r");

	char *str = getenv("SHELL");
	char *shell;
	shell = basename(str);

	char *de = getenv("DESKTOP_SESSION");
	if(de==NULL) return EXIT_FAILURE;

	const double mb = 1024 * 1024;
	double used_mb = (si.totalram / mb) - (si.freeram / mb) - (si.bufferram / mb) - (si.sharedram / mb) - (si.sharedram / mb);

	printf(" xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n");

	// Prints user@host
	printf("       .---.	 %s@%s \n", user, hostname);

	// Prints name of the distro
	int fw = 0;
	printf("      /     \\	 OS: \t\t");
	while( (ch=fgetc(p)) != EOF)
	{
		if(isalpha(ch))
		{
			fw = 1;
			putchar(ch);
		}
		else
		{
			if(fw)
			{
				putchar(' ');
				fw = 0;
			}
		}
	}
	pclose(p);
	printf("\n");

	printf("      \\.@-@./	 HOST: \t\t");
	while(fgets(modelname, sizeof(modelname), model))
	{
		printf("%s", modelname);
	}

	// Prints linux & version
	printf("      /`\\_/`\\	 KERNEL: \t%s %s\n", uName.sysname, uName.release);

	// Prints uptime
	printf("     //  _  \\\\	 UPTIME: \t%ld hours, %02ld minutes\n", (si.uptime % day) / 3600, (si.uptime % hour) / minute);

	// Prints number of packages
	printf("    | \\     )|	 PACKAGES: \t");
	while(fgets(pk, sizeof(pk), pak))
	{
		printf("%s", pk);
	}
	pclose(pak);

	// Prints shell name
	printf("   /`\\_`>  <_/ \\ SHELL: \t%s\n", shell);

	// Prints the desktop environment
	printf("   /`\\_`>  <_/ \\ DE:\t\t%s\n", de);

	// Prints free RAM (include cache ram, as it cannot be removed)
	//printf ("	RAM: \t\t%5.1f MB\n", used_mb);
	printf(" xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n");
	return 0;
}
