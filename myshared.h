#ifndef MYSHARED_H
#define MYSHARED_H

struct MyShared
{
    //this is where to specify what type of information the threads will be reporting

    //size of the arrays is pretty arbitrar, just need enough space for a few threads
    //testing should never really go past 4-5 threads created so 20 is probably overkill anyways
    //could use the vector data structure to dynamically resize but the static array should suffice

    int threadID[20] = {};   //unique identifier of the specific thread
    int reportID[20] = {};   // the total number of times this thread has reported
    int timePassed[20] = {}; // the time that has passed since the last report
};

#endif // MYSHARED_H