#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BMMA7455L.h"

int main(){

	int file;
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;

	startMMA7455L(&file, MENSUREMENT, S_2g, '1');
	
	while(1){

		if(getXYZ(&file, &x, &y, &z) == -1){

			printf("Error when obtaining the axes XYZ\n");

		}
		else{

			//Para obter o resultado em valores de 'g' quando cofigurado para sensibilidade de '2g', divide-se o os eixos por 64.
			//To obtain the result in 'g' values when co-fired for '2g' sensitivity, the axles are divided by 64

			//x = x/64; 
			//y = y/64;
			//z = z/64;

			printf("X: %d, Y: %d, Z: %d\n", x, y, z);

			//sleep(1);
			usleep(500);

		}

	}

	if(finishI2C(&file) == -1){

		printf("Error at file closure\n");

	}

	return 0;
}