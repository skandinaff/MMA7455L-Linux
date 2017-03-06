#include <stdio.h>
#include <stdlib.h>

#include "BMMA7455L.h"

int main(){

	int file;
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;

	startMMA7455L(&file, MENSUREMENT, S_2g, '2');
	
	while(1){

		if(getXYZ(&file, &x, &y, &z) == -1){

			printf("Erro ao obter os eixos XYZ\n");

		}
		else{

			//Para obter o resultado em valores de 'g' quando cofigurado para sensibilidade de '2g', divide-se o os eixos por 64.

			//x = x/64; 
			//y = y/64;
			//z = z/64;

			printf("X: %d, Y: %d, Z: %d\n", x, y, z);

			sleep(1);

		}

	}

	if(finishI2C(&file) == -1){

		printf("Erro no fechamento do arquivo\n");

	}

	return 0;
}