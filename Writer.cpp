#include <iostream>
#include "SharedObject.h"
#include "thread.h"
#include "myshared.h"

using namespace std;

//need to make sure that the threads just write to the array indicies they are responsible for

//still need a way to print out the contents of the shared memory object
//but that will be handled in reader.

int main(void)
{
	cout << "I am a Writer" << endl;

	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory

	while (true)
	{
		string response;
		int N;

		while (response != "yes" && response != "no")
		{
			cout << "would you like to create a new thread? \n";
			cin >> response;
		}

		if (response == "yes")
		{
			cout << "what should the thread wait time be? \n";
			cin >> N;

			//after the above code is executed this is when a new thread gets spawned
		}
		else
		{
			return 0;
			//this is where I terminate the threads and exit the program
			//thread1 = new WriterThread(N);
		};

		//create thread using user input
		//need to include the parameter that stores the sleep time for the thread on instantiation
		//newThread = new WriterThread(N); //add arguments as needed
	}
	//example for one thread thread1
	// thread1->flag = true;
	// delete thread1;
}

class WriterThread : public Thread
{
public:
	int threadNum;
	bool flag;

	WriterThread(int in) : Thread(8 * 1000)
	{
		this->threadNum = in; //or whatever you want/need here
	}

	virtual long ThreadMain(void) override
	{

		//declare shared memory var so this thread can access it
		Shared<MyShared> sharedMemory("sharedMemory");
		while (true)
		{
			//write to shared memory

			if (flag)
			{ //Exit loop to end the thread
				break;
			}
		}
	}
};