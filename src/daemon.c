#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include "daemon.h"

volatile int g_stopping = 0;

#ifdef _WIN32
int daemonize(int argc, char *argv[], int watchdog)
{
	char cmd[1024], args[1024];
	args[0] = 0;
	strcpy(cmd, argv[0]);
	strcat(cmd, ".exe");
	int i;

	for (i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--daemon"))
			continue;

		if (!args[0])
			strcat(args, " ");

		strcat(args, "\"");
		strcat(args, argv[i]);
		strcat(args, "\"");
	}

	STARTUPINFO startInfo = {0};
	PROCESS_INFORMATION process = {0};

	startInfo.cb = sizeof(startInfo);
	startInfo.dwFlags = STARTF_USESHOWWINDOW;
	startInfo.wShowWindow = SW_HIDE;

	if (!CreateProcessA(
			(LPSTR)cmd,			// application name
			(LPSTR)args,		// command line arguments
			NULL,				// process attributes
			NULL,				// thread attributes
			FALSE,				// inherit (file) handles
			DETACHED_PROCESS,	// Detach
			NULL,				// environment
			NULL,				// current directory
			&startInfo,			// startup info
			&process)			// process information
        )
	{
		printf("Creation of the process failed\n");
		return 1;
	}

	return 0;
}
#else
int daemonize(int watchdog)
{
	pid_t pid;

	if ((pid = fork()) < 0)		// Error
		return -1;
	else if (pid != 0)			// Parent
		return 0;

	if (watchdog)
		signal(SIGCHLD, SIG_IGN);

	while (watchdog && !g_stopping)
	{
		pid_t pid;

		if ((pid = fork()) < 0)		// Error
			return -1;
		else if (pid != 0)			// Parent
		{
			if (watchdog)
			{
				int status;
				wait(&status);

				if (g_stopping)
					break;

				sleep(1);
			}
			else
				return 0;
		}
		else						// Child
			break;
	}

	if (g_stopping)
		return 0;

	setsid();
	umask(0);
	close(2);
	close(1);
	close(0);
	open("/dev/null", O_RDONLY);
	open("vermeer.log", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

	if (!dup(1))
		return 0;

	return 1;
}
#endif
