#include "a2.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "cpu.h"
#include <limits.h>
void  readFile(process[], FILE*, int *);
void simulate( int time,process* queue,process* io,int queue_size,os system);
void removeIO(process* io,process *queue,int *queue_size,int toRemove);
void shiftEmpty(int ioCount,process* io);
int main(int argc, char const *argv[]) {
        os system ={.quantum=70,.wait=30};         // sytem settings
        FILE * infile;
        int time=10000;// time to run the simulation
        int queue_size =0;
        process *queue;// array of proccesses waiting for CPU
        process *io;// array of proccesses watiing for IO
        io = malloc(sizeof(process)*48);
        queue= malloc(sizeof(process)*48);
        // open file
        infile=fopen("a2in.txt","r");
        // check if filed failed to open
        if(infile==NULL)
                perror("Failed: ");
        else{
                // read file line by line
                readFile(queue,infile,&queue_size);
                // run the simulation
                simulate(time,queue,io,queue_size,system);

        }
        printStats(queue,system);// after loop print info
        return 0;
}
void readFile(process queue[], FILE* infile,int *queue_size){
        process temp_proc; // procces to hold input
        ui trash=0; //trash variable to get rid of lifespan
        while(fscanf(infile,"%u %u %u %u ",&temp_proc.priority,&temp_proc.cpu,&temp_proc.io,&trash)!=EOF) {

                temp_proc.curCpu=0; // count of current time in CPU
                temp_proc.curIo=0; // count of time waiting for I/O
                temp_proc.wait=0; // current count of time in ready queue
                temp_proc.curPrior=temp_proc.priority; // adjusted for starvation
                temp_proc.cpuTotal=0; // sum of time in cpu
                temp_proc.ioTotal=0; // sum of time doing io
                // statistics
                temp_proc.waitSum=0; // total time in ready queue
                temp_proc.waitCount=0; // how many times in ready queue (for average)
                temp_proc.waitMin=UINT_MAX; // smallest time in ready queue
                temp_proc.waitMax=0; // longet time in ready queu

                // enque process
                enqueue(&temp_proc,queue,*queue_size);

                (*queue_size)++;
        }
}

void simulate( int time, process* queue,process* io,int queue_size,os system){
        process cpu; // struct for cpu
        int cpuEmpty=1; // is the cpu free
        int ioCount=0; // how many processes are waiting on IO
        int removedIO =0;
        for (size_t i = 0; i < time; i++) {
                age(queue,system,queue_size);    // first age everything in waitque
                if(cpuEmpty==1) {               // if cpu is empty
                        cpu=  addCPU(queue,queue_size);// fill the cpuEmpty
                        cpuEmpty=0;   // set cpu empty to false
                        queue_size--;   // decrement size of waitqueue
                }

                else if(cpuEmpty==0) {  // if cpu isnt empty
                        if((cpu.curCpu)>=system.quantum) { // check if the process need to be removed
                                ioCount=removeCPU(&queue_size,queue,&cpu,ioCount,io);// remove it and inc io count
                                cpuEmpty=1; // set cpuEmpy to true

                        }
                        else // if it can stay in increment the time in cpu
                                cpu.curCpu++;
                }

                if(ioCount>0) { // if there is anything in io
                        for (int i = 0; i < ioCount; i++) { // loop through everything in io

                                if(io[i].curIo>=io[i].io) { // if prcces is done waiting on io
                                        removeIO(io,queue,&queue_size,i); // remove from io
                                        removedIO++;  //increment the number of io removed
                                        shiftEmpty(ioCount,io); // shift over the empty values
                                        ioCount=(ioCount-removedIO);// set ioCount to the acutal amount
                                        removedIO=0;// reset number of items
                                }

                                else
                                        io[i].curIo++; // for all elements increment the time of curent io

                        }


                }

        }

}
void removeIO(process* io,process *queue,int *queue_size,int toRemove){
        enqueue(&io[toRemove],queue,*queue_size);
        (*queue_size)++;

        io[toRemove].curIo=UINT_MAX;

}
void shiftEmpty(int ioCount, process* io){
// modified version of shift all zeros to end of array from geeksForgeeks
//https://www.geeksforgeeks.org/move-zeroes-end-array/
        int count = 0; // Count of non empty elements;

        //Traverse the array. If element encountered is non null is encountered
        //then replace the element at index 'count'   with this element
        for (int i = 0; i < ioCount; i++) {
                if (io[i].curIo != UINT_MAX)
                        io[count++] = io[i]; // is set to i then incremented
        }
}
