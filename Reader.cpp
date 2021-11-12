//written by Anthony Barros thursday nov 11, 2021

#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

using namespace std;

//all shared variables use the 's' prefix to indicate it is the shared variable
//delay is the amount of time that has elapsed since the last report
//threadID is the unique identifier of the thread in question
//reportID is the total number of times the thread has reported
//running is a boolean value used to indicate wether the thread should be active
struct MyShared
{
	int sdelay;
	int sthreadID;
	int sreportID;
	bool srunning;
};

int main(void)
{
	cout << "I am a reader" << endl;

	//the sharedMemory object stores the information on each thread
	//it keeps track of three things: the threadID, reportID, delay, and wether or not the thread is running

	//the only thing that doesnt get displayed is the status of wether or not the process is running
	Shared<MyShared> sharedMemory("sharedMemory");

	Semaphore rSemaphore("readerSemaphore");

	while (true)
	{
		//Reader is checking the sharedMemory to make sure if it is being used
		//if the sharedMemory is active then display the information
		//otherwise break the execution
		if (sharedMemory->srunning == true)
		{
			rSemaphore.Wait();

			cout << "threadID: " << sharedMemory->sthreadID << " reportID: " << sharedMemory->sreportID << " delay: " << sharedMemory->sdelay << endl;
			// sleep(1); this is no longer needed beacause of the semaphores
		}
		else
		{
			break;
		}
	}
}
