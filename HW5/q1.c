#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 

int global_positives = 0; 

typef struct list {
struct list *next; //My note: 
double val; 
} * list; //My note: 

void *count_positives(struct list *l){
struct list *p;
    for(p = l; p -> next; p = p -> next)
    {
        if(p -> val > 0.0)
                ++global_positives; 
    }
}


int main()
{
    //Thread A
    //count_positives(<list containing only negative numbers>)


    return 0; 
}