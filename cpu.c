#include "a2.h"
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "queue.h"
void age(process queue[],os system,int queue_size){
        for (size_t i = 0; i< queue_size; i++) {
                queue[i].wait++;// increment wait
                queue[i].waitSum++;// increment total wait


                if((queue[i].wait%system.wait==0)&&(queue[i].curPrior<15)) // if it has been at
                        queue[i].curPrior++; // inc currrent priority
        }
        my_sort(queue,queue_size);
}
void my_sort(process queue[],int queue_size){
        process temp_proc;
        int j;
        for (int i = 0; i < queue_size; i++) {
                j = i - 1;
                temp_proc= queue[i];
                while (j >= 0 && queue[j].curPrior < temp_proc.curPrior) {
                        queue[j + 1] = queue[j];
                        j--;
                }
                queue[j + 1] = temp_proc;
        }
}

int  removeCPU(int * queue_size, process * queue,process *cpu,int ioCount, process *io){
        // increase total time in the cpu

        cpu->cpuTotal+= cpu->curCpu;

        cpu->curCpu=0;

        if((cpu->cpuTotal%cpu->cpu)==0) {

                cpu->ioTotal++;
                io[ioCount]=*cpu;
                ioCount++;




        }
        else{

                enqueue( cpu, queue,*queue_size);
                (*queue_size)++;


        }

        return ioCount;
}
process addCPU(process *queue,int queue_size ){

        queue[0].waitSum+=queue[0].wait;
        if(queue[0].wait>queue[0].waitMax)
                queue[0].waitMax=queue[0].wait;
        if(queue[0].wait<queue[0].waitMin)
                queue[0].waitMin= queue[0].wait;
        queue[0].wait=0;
        queue[0].curPrior=queue[0].priority;
        return dequeue(queue,queue_size);
}
