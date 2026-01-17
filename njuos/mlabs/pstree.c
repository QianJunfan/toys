/* A lightweight pstree implementation for Lab M1. */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define CAPA	256 
#define MAX	32768

struct proc {
	char name[CAPA];
	
	int pid;
	int ppid;

	int exists;
};


struct proc list[MAX];


int is_last_child(int ppid, int idx)
{
	for (int i = idx + 1; i < MAX; i++) {
		if (list[i].exists && list[i].ppid == ppid)
			return 0;
	}
	
	return 1;
}

#define VERT	"  │ "
#define CROSS	"  ├─ %s(%d)\n"
void prttree(int ppid, char *prefix)
{
	char pf[1024];

	for (int i = 0; i < MAX; i++) {
		if (list[i].exists && list[i].ppid == ppid) {
			int last = is_last_child(ppid, i);

			printf("%s%s %s (%d)\n",
				prefix,
				last ? " └─" : " ├─",
				list[i].name,
				list[i].pid);

			snprintf(pf, sizeof(pf), "%s%s",
					prefix,
					last ? "   " : " │ ");

			prttree(list[i].pid, pf);
		}
	}
}


int main(void)
{
	DIR *dir;
	struct dirent *ent;

	memset(list, 0, sizeof(list));

	dir = opendir("/proc");

	if (!dir) {
		perror("Failed to open folder /proc");	
		return 1;
	}

	while ((ent = readdir(dir)) != NULL) {
		if (ent->d_name[0] <= '0' || ent->d_name[0] >= '9')
			continue;
		int pid = atoi(ent->d_name);

		if (pid >= MAX)
			continue;

		char path[256];
		snprintf(path, sizeof(path),"/proc/%d/stat", pid);

		FILE *f = fopen(path, "r");

		if (f) {
			int c;
			int p;

			char co[256];
			char s;
			if (fscanf(f, "%d (%[^)]) %c %d", 
				&c, co, &s, &p) == 4) {
				list[pid].pid  = c;
				list[pid].ppid = p;
				strncpy(list[pid].name, co, CAPA - 1);
				list[pid].exists = 1;
			}
			fclose(f);
		}
	}
	closedir(dir);

	printf("Linux Proc Tree:\n");
	printf("systemd(1)\n");
	prttree(1, "");

	return 0;
}
