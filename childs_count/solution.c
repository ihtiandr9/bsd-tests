#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <dirent.h>

typedef struct _proc
{
	int pid;
	int ppid;
} proc;

typedef struct _proclist
{
	proc _proc;
	struct _proclist *next;
	struct _proclist *children;
} proclist;

proc *procCreate(int pid, int ppid)
{
	proc *newproc = (proc *)malloc(sizeof(proc));
	newproc->pid = pid;
	newproc->ppid = ppid;
	return newproc;
}

proclist *procPushProcCopy(proclist *head, proc proccopy)
{
	proclist *newprocentry = (proclist *)malloc(sizeof(proclist));
	newprocentry->_proc = proccopy;
	newprocentry->next = head->next;
	newprocentry->children = 0;
	head->next = newprocentry;
	return newprocentry;
}

static void procTryAdopt(proc *parent, proclist *_proclist)
{
	proclist *iter;
	for (iter = _proclist; iter; iter = iter->next)
	{
		if (parent->pid == ((proc *)iter)->ppid)
		{
			printf(" %d is parent of %d\n", parent->pid, ((proc *)iter)->pid);
			procPushProcCopy(((proclist *)parent)->children, *(proc *)iter);
		}
	}
}

static inline void procFindChildren(proc *_proc)
{
	procTryAdopt((_proc), ((proclist *)_proc)->next);
}

static proclist m_proc;

int count_children(int pid)
{
	if (pid < 1)
		return 0; // exit if upper of init

	int ppid;
	int res = 1;
	char status[512];
	char fpath[512], *instr;
	proc curproc;
	proclist *procentry;

	DIR *dir;
	struct dirent *entry;

	status[0] = 0;

	m_proc._proc.pid = pid;
	m_proc._proc.ppid = 0;
	m_proc.children = 0;

	dir = opendir("/proc");
	if (!dir)
	{
		printf("dir not found");
		exit(-1);
	}
	while ((entry = readdir(dir)))
	{
		sprintf(fpath, "/proc/%s/status", entry->d_name);
		FILE *fd = fopen(fpath, "ro");
		if (!fd)
		{
			printf("file %s not found", fpath);
		}
		else
		{
			fgets(status, 512, fd);
			fclose(fd);
			instr = strtok(status, " ");
			printf("commandline: %s ", instr);
			instr = (char *)(1 + strlen(instr) + (size_t)instr);
			instr = strtok(instr, " ");
			pid = atoi(instr);
			printf("pid: %d ", pid);
			instr = (char *)(1 + strlen(instr) + (size_t)instr);
			instr = strtok(instr, " ");
			ppid = atoi(instr);
			printf("ppid: %d\n", ppid);

			curproc.pid = pid;
			curproc.ppid = ppid;
			procentry = procPushProcCopy(&m_proc, curproc);
			procentry->children = 0;
			procFindChildren((proc *)procentry);
		}
	}
	return res;
}

int main(int argc, char *argv[])
{
	if (2 > argc)
	{
		printf("Usage: ./solution pid\n");
		exit(-1);
	}

	int pid = atoi(argv[1]);
	printf("%d\n", count_children(pid));
	return 0;
}
