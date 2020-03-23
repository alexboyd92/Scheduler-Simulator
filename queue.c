#include "a2.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// add element to queue based off inside of insertion sort
// testQueue(queue,counter,temp_proc);
void enqueue (process  * temp_proc, process *queue,int counter){

        temp_proc->waitCount++;

        int j = counter - 1;
        while (j >= 0 && queue[j].curPrior < temp_proc->curPrior) {
                queue[j + 1] = queue[j];
                j--;
        }
        queue[j + 1] = *temp_proc;


}
process dequeue(process *queue,int queue_size){
        // select proccess at top of queu

        process to_cpu=queue[0];
        // Shift all others down one
        for (size_t i = 1; i < queue_size; i++) {
                queue[i-1]=queue[i];
        }


        return to_cpu;

}
void testQueue( process *queue,int counter,process temp_proc){
        srand(time(0));
        for (size_t i = 0; i <12; i++) {
                int random = rand()%15;

                temp_proc.curPrior=random;
                enqueue(&temp_proc,queue,counter );
                counter++;


        }


        for (int i = 0; i < 12; i++) {
                printf("%u\n",queue[i].curPrior );
        }

        for (int i = 0; i < 12; i++) {
                process dump = dequeue(queue,12);

                printf("to cpu %d\n",dump.curPrior );
        }
}
