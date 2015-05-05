#ifndef _QUEUE_H_INCLUDE_
#define _QUEUE_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef enum _bool{
	false,
	true
} bool;

typedef struct _node{
	Data val;
	struct _node* next;
	struct _node* prev;
} *Node, NodeImpl;

typedef struct {
	Node head;
} *Queue, QueueImpl;


Queue init_queue();
bool destroy_queue(Queue queue);
bool en_queue(Queue queue, Data data);
bool de_queue(Queue queue, Data* data);
bool isEmpty(Queue queue);
bool empty(Queue queue);
bool get_front(Queue queue, Data* data);
unsigned get_size(Queue queue);
void display_all(Queue queue);



// when running at command line (bash) make sure Makefile is called Makefile and not Makefile.GNUwhatver
#endif
