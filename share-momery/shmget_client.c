#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// IPC -- inter process communication 
// shmget() is used to obtain a shared memory identifier
	// shmget() returns a shared memory ID if OK, -1 on error
	
	// Key: which lets the kernel choose a new key. IPC_PRIVATE
	// Size: side (bytes) of the shared momery
	// Flag: SHM_R, SHM_W, SHM_R | SHM_W
// shmat() returns a pointer to shared memory segment if OK, -1 on error
	// The recommended technique is to set addr and flag to zero, i.e.:
	// char *shmpointer = (char*)shmat(shmid,0,0);
	// e UNIX commands “ipcs” and “ipcrm”
// shmctl() performs various shared memory operations
	// int shmctl (int shmid, int cmd, struct shmid_ds *buf);
	// cmd can be one of IPC_STAT, IPC_SET, or IPC_RMID:
	// IPC_STAT fills the buf data structure
	// IPC_SET can change the uid, gid, and mode of the shmid
	// IPC_RMID sets up the shared memory segment to be removed
	//  shmctl() returns 0 if OK, -1 on error

int main(int argc, char *argv[]){
	int shmid;
	int size=512;
	key_t key;
	key=0xaaaa;
	char *shmpointer;
	char *shmpointer_tmp;

	shmid=shmget(key, size, SHM_R);
	shmpointer = shmat(shmid,0,0);


	printf("shmid: %d, shmpointer: %p\n",shmid,shmpointer);
	printf("shared momery msg: %s\n",shmpointer);

	printf("send a * to stop\n");
	shmpointer_tmp = shmpointer + strlen(shmpointer);
	*shmpointer_tmp='*';
	
	shmdt(&shmpointer);
	printf("program stopped!\n");
}