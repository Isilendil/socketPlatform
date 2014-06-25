//SharedMemory.cpp

#include "SharedMemory.h"

#include <cstring>
#include <cstdlib>

SharedMemory::SharedMemory(key_t key_, size_t size_, int type_)
 : key(key_), size(size_), type(type_)
{
	if(type == 0)
	{
		flag = IPC_CREAT|0666;
		nsems = 1;
	}
	else if(type == 1)
	{
		flag = 0666;
		nsems = 0;
	}

	id = shmget(key, size, flag);
	address = shmat(id, 0, 0);

	createSemaphore();
}

SharedMemory::~SharedMemory()
{
	shmdt(address);
	destroySemaphore();
}

key_t SharedMemory::getKey()
{
	return key;
}

int SharedMemory::getId()
{
	return id;
}

void* SharedMemory::getAddress()
{
	return address;
}

size_t SharedMemory::getSize()
{
	return size;
}

int SharedMemory::getFlag()
{
	return flag;
}

void SharedMemory::write(void *source)
{
	p();
	memcpy(address, source, size);
	v();
}

void SharedMemory::read(void *destination)
{
	p();
	memcpy(destination, address, size);
	v();
}

void SharedMemory::createSemaphore()
{
	sem.value = 1;
	semid = semget(key, nsems, flag);

	if(semid == -1)
	{
		exit(-1);
	}

	semctl(semid, 0, SETVAL, sem);

}

void SharedMemory::destroySemaphore()
{
	sem.value = 0;
	semctl(semid, 0, IPC_RMID, sem);
}

void SharedMemory::p()
{
	struct sembuf sem_p;
	sem_p.sem_num = 0;
	sem_p.sem_op = -1;
	if(semop(semid, &sem_p, 1) == -1)
	{
		exit(-1);
	}
}

void SharedMemory::v()
{
	struct sembuf sem_v;
	sem_v.sem_num = 0;
	sem_v.sem_op = +1;
	if(semop(semid, &sem_v, 1) == -1)
	{
		exit(-1);
	}
}



