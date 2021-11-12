#include <iostream>
#include "SharedObject.h"
#include "myshared.h"

using namespace std;

int main(void)
{
	cout << "I am a reader" << endl;

	Shared<MyShared> sharedMemory("sharedMemory");

	cout << "hello" << endl;
}
