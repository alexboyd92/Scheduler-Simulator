#ifndef CPU_H
#define CPU_H


extern void age(process que[],os system,int queue_size);
extern void my_sort(process que[],int queue_size);
extern int  removeCPU(int  * queue_size, process * queue,process *cpu,int ioCount, process* io);
extern process addCPU(process* queue, int queue_size);
#endif
