/* Author: Christopher Kent 

Question 1): Used circular linked list implementation because
queue is of unknown size and we will be having frequent 
additions/removals to the queue in the airport simulation. 
Planes are constantly being added/removed so linked list would
be more efficent than a circular array.

Question 2): Planes in the air have priority over planes on the 
ground to use the runway, therefore it would make more sense for 
air probability to be higher than ground probability. Doing this will
maximize the number of planes landed while keeping the ending queue size 
as small as possible.


*/


#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <unistd.h> // system calls
#include <time.h>

typedef struct _runway{
	bool vacant;
	int timeTillVacant;
	Data planeUsing;
} *Runway, RunwayImpl;

double gen_probability();
int gen_3digit();



int main(int argc, char const *argv[]){

	Queue airQ = init_queue();
	Queue groundQ = init_queue();
	unsigned i;
	unsigned planes_landed = 0;
	Data tmp;

	srand(time(NULL));

	Runway runway_ptr = (Runway)malloc(sizeof(RunwayImpl));
	if(!runway_ptr) return -1;
	double randomAir = 0.0, randomGr = 0.0; 
	double arrivalAirProb = 0.0, arrivalGroundProb = 0.0;

	int randomID, timeDuration;
	timeDuration = 0;
	randomID = 312;

	printf("Enter arrival air probability(between 0.00 and 1.00 not inclusive): \n");
	scanf("%lf", &arrivalAirProb);
	printf("Enter arrival ground probability(between 0.00 and 1.00 not inclusive):\n");
	scanf("%lf", &arrivalGroundProb);
	printf("Enter time timeDuration (integer between 1 and 20 inclusive): \n");
	scanf("%d", &timeDuration);


	runway_ptr->vacant = true;
	runway_ptr->timeTillVacant = 0;
	runway_ptr->planeUsing = 0;

	printf("\nRandom ground probability is %.0lf%%\n", (arrivalGroundProb*100));
	printf("Random air probability is %.0lf%%\n", (arrivalAirProb*100));

	for(i = 0; i < timeDuration; i++){
		
		printf("\n");
		printf("Number of seconds passed by: %d\n", i);
		printf("%d planes in the air\n", get_size(airQ));
		printf("%d planes on the ground\n", get_size(groundQ));
		sleep(1);
		randomAir = gen_probability();
		randomGr = gen_probability();

		if(randomAir < arrivalAirProb){
			randomID = gen_3digit();
			if(!en_queue(airQ, randomID))
				return -1;
			printf("%d is in the air.\n", randomID );
		}

		if(randomAir < arrivalAirProb*arrivalAirProb){
			randomID = gen_3digit();
			if(!en_queue(airQ, randomID))
				return -1;
			printf("%d is in the air.\n", randomID);
		}

		if(randomGr < arrivalGroundProb){
			randomID = gen_3digit();
			if(!en_queue(groundQ, randomID))
				return -1;
			printf("%d is on the ground.\n", randomID);
		}

		if(runway_ptr->vacant == true){

			if(!isEmpty(airQ)){
				get_front(airQ, &tmp);
				printf("Plane %d is landing\n", tmp);
				planes_landed++;
				if(!de_queue(airQ, &tmp)) return -1;
				runway_ptr->vacant = false;
				runway_ptr->timeTillVacant = 2;

			} else if(!isEmpty(groundQ)){
				if(!get_front(groundQ, &tmp)) return -1;
				printf("Plane %d is taking off\n", tmp);
				if(!de_queue(groundQ, &tmp)) return -1;
				runway_ptr->vacant = false;
				runway_ptr->timeTillVacant = 2;
			}
		
		}

		if(runway_ptr->timeTillVacant == 0){
			printf("Runway is vacant.\n");
			runway_ptr->vacant = true;
		} else {
			printf("Runway is occupied for %d more seconds\n", runway_ptr->timeTillVacant);
			runway_ptr->timeTillVacant = runway_ptr->timeTillVacant - 1;
		}
		// only 1 plane can use runway(iff its vacant)
	}

	printf("\nEnd result.\n");
	printf("Total planes landed is: %d\n", planes_landed);
	printf("Air queue has %d planes\n", get_size(airQ));
	printf("Ground queue has %d planes\n", get_size(groundQ));

	/* code */

	destroy_queue(airQ);
	destroy_queue(groundQ);
	free(runway_ptr);
	return 0;
}

double gen_probability(){
	int n = rand();
	double probability = n / (double) RAND_MAX;
	return probability;
}


int gen_3digit(){
	int n = 900;
	int s = 100;
	int random_ID;

	random_ID = (rand() % n) + s;
	return random_ID;

}
