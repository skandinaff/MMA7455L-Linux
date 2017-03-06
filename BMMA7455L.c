// LIBRARY MMA7455L
// Mais informações(More information): http://www.nxp.com/assets/documents/data/en/data-sheets/MMA7455L.pdf



#include "BMMA7455L.h"


// Inicia comunicação i2c abrindo o arquivo que abstrai o barramento
// Caso o barramento não exista ou o arquivo não seja aberto é retornado o valo de -1

// Start the i2c communication opening the file that reference the bus.
int startI2C(int *file, char bus){

	switch(bus){

		case '1':
			
			*file = open("/dev/i2c-1", O_RDWR);
			break;

		case '2':
			
			*file = open("/dev/i2c-2", O_RDWR);
			break;

		case '3':
			
			*file = open("/dev/i2c-3", O_RDWR);
			break;

		default:

			return -1;

	}

	if(*file < 0){

		return -1;
	}


	ioctl(*file, I2C_SLAVE, MMA7455L);

	return 0;
}

// Fecha o arquivo referente ao barramento

// Close the file reference the bus.

int finishI2C(int *file){

	return close(*file);

}

// Esta função é responsável por configurar o o acelerômetro com o modo e a sensibilidade desejada.
// This function is responsible for configure the accelerometer with the mode end sensitivity wanted.

int configureMMA7455L(int *file, char MODE, char SENSITIVITY){


	char config[2] = {0};

	config[0] = 0x16; // Registrador de controle (Control Register)| Página 9 (Page 9)
	config[1] = MODE | SENSITIVITY;

	if(write(*file, config, 2) != 2){

		return -1;

	}

	sleep(1);

	return 0;
}

// Esta função é responsável por receber os valores dos endereços 0x00 - 0x05, que contém os valores necessários para se obter x, y e z.
// This function is responsable for recive the values of adress 0x00 - 0x005, that contains the values needed to obtain the x, y and z.

int reciveXYZ(int *file, char *dataXYZ){

	// 0x00 é o endereço onde se encontra o valor de XOUTL e a partir daí temos os outros valores(XOUTH, YOUTL, YOUTH, ZOUTL, ZOUTH).
	// 0x00 is XOUTL adress value and from this we get the outher values(XOUTH, YOUTL, YOUTH, ZOUTL, ZOUTH).
	
	char xoutl_reg[1] = {0x00};
	int t;

	if(write(*file, xoutl_reg, 1) != 1){

		return -1; // Em caso de erro na escrita é retonado -1. (When Write Error occurs, the function returns -1)

	}  

	// Aqui é feita a leitura de 6 bytes a partir do endereço XOUTL, desse modo, obtemos todos os valores
	// Here is made the 6 bytes reading from XOUTL adress, in this way, we get the values.
	
	if(read(*file, dataXYZ, 6) != 6){

		return -2; // Em caso de erro na leitura é retonado -2. (When Read Error occurs, the function returns -2)

	}

	return 0; // Nenhum erro. (No erro)


}

// Não testdo
int reciveTemperature(int *file, char *dataTemp){

	// 0x00 é o endereço onde se encontra o valor de TOUT.
	// 0x00 is TOUT adress.

	char tout_reg[1] = {0x0B};

	if(write(*file, tout_reg, 1) != 1){

		return -1; // Em caso de erro na escrita é retonado -1. (When Write Error occurs, the function returns -1)

	}  

	// Aqui é feita a leitura de 1 bytes.
	// Here is made the 1 bytes reading.
	if(read(*file, dataTemp, 1) != 1){

		return -2; // Em caso de erro na leitura é retonado -2. (When Read Error occurs, the function returns -2)

	}

	return 0; // Nenhum erro. (No erro)
}

int getXYZ(int *file, int16_t *x, int16_t *y, int16_t *z){

	char dataXYZ[6] = {0};
	int status;


	status = reciveXYZ(file, dataXYZ);


	//Verifica se o número é negativo ou não, caso seja o sinal é repassado para os demais bits e mantém-se os dois últimos bits, caso não,
	//são utilizados, apenas os dois últimos bits.

	//If the number is negative the signal is passed to the reamining bits and the last two bits are kept. In the otherwise,
	//just the last two bits are used.

 	// NEGATIVE
	// xxxx xxxx (MSB)
	//     OR
	// 1111 1100
	// ---------
	// 1111 11xx (0xFC)

 	// POSITIVE
	// xxxx xxxx (MSB)
	//    AND
	// 0000 0011 (0x03)
	// ---------
	// 0000 00xx

	if(dataXYZ[1] & 0x02){ 
		dataXYZ[1] = dataXYZ[1] | 0xFC;
	}
	else{

		dataXYZ[1] = dataXYZ[1] & 0x03;
	}

	//concatenação dos bits MSB-LSB.
	
	*x = dataXYZ[1] << 8;
	*x = *x + dataXYZ[0];

	if(dataXYZ[3] & 0x02){ 
		dataXYZ[3] = dataXYZ[3] | 0xFC;
	}
	else{

		dataXYZ[3] = dataXYZ[3] & 0x03;
	}

	//concatenação dos bits MSB-LSB.
	*y = dataXYZ[3] << 8;
	*y = *y + dataXYZ[2];


	if(dataXYZ[5] & 0x02){ 
		dataXYZ[5] = dataXYZ[5] | 0xFC;
	}
	else{

		dataXYZ[5] = dataXYZ[5] & 0x03;
	}

	//concatenação dos bits MSB-LSB.
	*z = dataXYZ[5] << 8;
	*z = *z + dataXYZ[4];

	return status;

}

// Não testdo
int getTemp(int *file, int8_t *temp){

	char dataTemp = {0};

	int status;

	status = reciveTemperature(file, &dataTemp);


	printf("%d\n", dataTemp);

	*temp = dataTemp;

	return status;

}

int startMMA7455L(int *file, char MODE, char SENSITIVITY, char bus){

	int status1;
	int status2;

	status1 = startI2C(file, bus);

	if(status1 == -1 || status1 == -2){

		printf("Erro na abrtura do arquivo\n");
		return -1;
	}

	status2 = configureMMA7455L(file, MODE, SENSITIVITY);

	if(status2 == -1 || status2 == -2){

		printf("Erro de configuracao\n");
		return -2;

	}

}