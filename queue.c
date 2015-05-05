/* Author: Christopher Kent 
Implementation of queue data structure using 
a circular linked list */

#include "queue.h"

Queue init_queue() {
	Queue queue = (Queue)malloc(sizeof(QueueImpl));
	if(!queue)
		return 0;
	queue->head = NULL;
	return queue;
}

bool en_queue(Queue queue, Data data) {
	if(!queue) 
		return false;
	Node elem = (Node)malloc(sizeof(NodeImpl));
	if(!elem)
		return false;
	
	if(queue->head) { // list is not empty
		const Node head = queue->head, tail = queue->head->prev;

		elem->next = head;
		elem->prev = tail;

		head->prev = elem;
		tail->next = elem;
	} else { // list is empty
		elem->next = elem->prev = elem;
	}
	queue->head = elem;
	elem->val = data;
	return true;
}

bool de_queue(Queue queue, Data *data) {
	Node head, tail;
	if(!queue || !(head = queue->head)) 
		return false;

	if(head->next == head) { // self referential head = 1 element list
		*data = head->val;
		free(head);
		queue->head = NULL; // queue is now empty
		return true;
	}

	*data = (tail = head->prev)->val;
	tail->prev->next = head; // remove the tail
	head->prev = tail->prev;
	free(tail);
	return true;
}

bool empty(Queue queue){
	if(!queue)
		return false;
	Data val;
	while(de_queue(queue, &val));
	return true;
}

bool isEmpty(Queue queue){
	return !queue->head;
}

bool destroy_queue(Queue queue){
	Data data;
	while(de_queue(queue, &data));
	return true;
}

bool get_front(Queue queue, Data* data){
	if(!queue|| !queue->head) 
		return false;
	*data = queue->head->prev->val;
	return true;

}

unsigned get_size(Queue queue){
	 unsigned i = 0;
	 const Node head = queue->head;
	 Node iter = queue->head;
	 if(head){
	 	iter = head->next;
	 	i++;
	 } else return 0;
	 
	 while(iter != head){
	 	iter = iter->next;
	 	i++;
	 }
	 
	 return i;
}

void display_all(Queue queue){
	
	for(Node iter = queue->head->prev; iter != queue->head; iter = iter->prev)
		printf("%d\n", iter->val);

	printf("%d\n", queue->head->val);
}

