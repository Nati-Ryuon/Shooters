#include"Random.h"
#include<stdlib.h>
#include<time.h>

int getRandom(int min, int max) {
	int result; 
	result = (rand() % (max - min)) + min;

	return result;
}