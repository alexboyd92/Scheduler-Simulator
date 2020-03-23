#ifndef ENQUEUE_H
#define ENQUEUE_H
extern void enqueue (process * temp_proc, process *,int counter);
extern process dequeue(process *queue, int queue_sizes);
// function to test if the queue works
extern void testQueue( process *,int counter,process );
#endif
