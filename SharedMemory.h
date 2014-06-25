//SharedMemory.h
//class SharedMemory

#ifndef _SHAREDMEMORY_H_
#define _SHAREDMEMORY_H_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

union Semaphore
{
	int value;
	struct semid_ds *buffer;
	unsigned short *array;
};


class SharedMemory
{
public:
  SharedMemory();
  SharedMemory(key_t key_, size_t size_, int type_);
	~SharedMemory();

	key_t getKey();
	int getId();
	void* getAddress();
  size_t getSize();
	int getFlag();

	void write(void *source);
	void read(void *destination);

protected:

private:
  key_t key;
	int id;
	void *address;
	size_t size;

  Semaphore sem;
	int semid;

	int type;
	int flag;
	int nsems;

	void createSemaphore();
	void destroySemaphore();
	void p();
	void v();
};

#endif
