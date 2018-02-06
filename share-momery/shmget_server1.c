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
	int size=4096+128;
	key_t key;
	key=0xbbbb;
	char *shmpointer;

	char *shmpointer_abs;
	int i,j;
	unsigned char x,y;
	int BytesRequired=4096;
	int offset_bytes=128;

	shmid=shmget(key, size, IPC_CREAT | 0666);
	shmpointer_abs = shmat(shmid,0,0);
	
	shmpointer = shmpointer_abs + offset_bytes;
	printf("key: %x, shmid: %d, shmpointer_abs: %p\n",key,shmid,shmpointer_abs);

	unsigned char buff[BytesRequired];
	int playing=1;
	while(playing){	
		x=0;
		for(i=0;i<BytesRequired;i++){
			//buff[i]=rand();
			buff[i]=x;
			x++;
		}
		
		
			memcpy(shmpointer,buff,BytesRequired);
		//	shmpointer++;
			usleep(100000);
			shmpointer = shmpointer_abs + offset_bytes;
	}
		
	shmdt(&shmpointer);
	printf("stop program!\n");
}








