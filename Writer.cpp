#include <iostream>
#include "SharedObject.h"
#include "thread.h"
#include <string>
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

class WriterThread : public Thread
{
public:
	//the locally defined variables for each thread
	//this information will ultimately be written to
	//the sharedMemory location as the value to the 's' prefixed variables
	int delay;
	int threadID;
	int reportID = 1;
	bool flag;

	WriterThread(int in, int threadid) : Thread(8 * 1000)
	{
		this->delay = in;
		this->threadID = threadid;
	}

	virtual long ThreadMain(void) override
	{

		//declare shared memory var so this thread can access it
		Shared<MyShared> sharedMemory("sharedMemory");

		Semaphore wSemaphore("writerSemaphore");
		Semaphore rSemaphore("readerSemaphore");

		while (true)
		{
			wSemaphore.Wait();

			//write to shared memory using the local thread data values
			sharedMemory->sthreadID = threadID; //write the threadID to memory
			sharedMemory->sreportID = reportID; //update the number of reports
			reportID++;							//increment the reportID so the next write operation displays the correct value
			sharedMemory->sdelay = delay;		//set the amount of time the thread will wait

			wSemaphore.Signal();
			rSemaphore.Signal();

			sleep(delay); //wait the amount of time the user specified to update the sharedMemory

			if (flag)
			{ //Exit loop to end the thread
				break;
			}
		}
		return 0;
	}
};

int main(void)
{
	Semaphore wSemaphore("writerSemaphore", 1, true);
	Semaphore rSemaphore("readerSemaphore", 0, true);

	string response; //this will hold the users response to the main loop
	int N;			 //this will hold the user input for the thread delay

	int threadNumber = 1;
	//this value will be used for instantiating WriterThread objects
	//threadNumber will be used for the threadIDs upon instantiation

	cout << "I am a Writer" << endl;

	WriterThread *thread; //declare threads

	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory

	shared->srunning = true;
	//set the sharedMemory owner running value to true
	//so that the reader can can begin to check the sharedMemory

	while (true)
	{

		while (response != "yes" && response != "no")
		{
			cout << "would you like to create a new thread? (please enter yes or no) \n";
			cin >> response;
		}

		if (response == "yes")
		{
			cout << "what should the thread delay time be? \n";
			cin >> N;

			thread = new WriterThread(N, threadNumber); //instantiate the thread

			threadNumber++;		//increment the threadNumber so that the next instantiated thread
								//has the correct threadID
			response = "reset"; //make sure the
		}
		else if (response == "no")
		{
			if (threadNumber - 1 != 0) //if there are active threads
			{
				shared->srunning = false; //terminate the parent process of the sharedMemory location
				break;
			}
			else
			{
				break;
			}
			//this is where I terminate the threads and exit the program
		};
	}
	if (threadNumber - 1 != 0) //if there are active threads
	{
		thread->flag = true;
		delete thread;
	}
	return 0; //terminate the main function with the return value
}
