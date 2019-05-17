#include <stdio.h>
#include <stdlib.h>

#define _NR_newcall 287

static struct prinfo {
	pid_t parent_pid;
	pid_t pid;
	pid_t first_child_pid;
	pid_t next_sibling_pid;
    long state;
	long uid;
	char comm[64];
};

void display(struct prinfo *buf, int *nr)
{
	int level= 0;
	int rec[2000] = {0};

	printf("%s,%d,%ld,%d,%d,%d,%ld\n", buf[0].comm,buf[0].pid, buf[0].state, buf[0].parent_pid,buf[0].first_child_pid, buf[0].next_sibling_pid, buf[0].uid);

	int i=1;
	while(i<*nr){
		if(buf[i].parent_pid == buf[i - 1].pid) {
			level++;
		}
		else if(buf[i].parent_pid != buf[i-1].parent_pid){
			level--;
			int tmp = buf[i-1].parent_pid;
			while(buf[i].parent_pid!=buf[rec[tmp]].parent_pid){
				level--;
				tmp = buf[rec[tmp]].parent_pid;
			}
		}

		rec[buf[i].pid] = i;

		//print
		int k=1;
		while(k<=level){
			printf("\t");
			k++;
		}

		printf("%s,%d,%ld,%d,%d,%d,%ld\n", buf[i].comm,buf[i].pid, buf[i].state, buf[i].parent_pid,buf[i].first_child_pid, buf[i].next_sibling_pid, buf[i].uid);
	        i++;
	}
}

int main()
{
	struct prinfo *buf = malloc(2000*sizeof(struct prinfo));
	int *nr = malloc(sizeof(int));

	if(buf!=NULL&&nr!=NULL){
		syscall(_NR_newcall,buf,nr);
		printf("%d processes:\n",*nr);
		display(buf,nr);
	}

	free(buf);
	free(nr);

	return 0;
}
