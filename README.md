Este repositório contém uma biblioteca destinada a configuração e utilização do CI MMA7455L que consiste em acelerômetro de 3 eixo com comunicação I2C.

###########################
PARA A UTILIZAÇÃO DO CÓDIGO:

1. Crie um inteiro para ser o arquivo, como é feito no exemplo (int file). Este arquivo será passado como ponteiro para todas as funções utilizadas. Ele "representa" a sua comunicação I2C, pois como sabido, o Linux abstrai seu acesso a hardware com arquivos.

2. Crie três variáveis do tipo 'int16_t' onde serão armazenados os valores de X, Y e Z.

3. A primeira função chamada será a 'startMMA7455L()' seus argumentos são: ponteiro para o arquivo, modo de operação do acelerômetro, sensibilidade e em qual barramento I2C o acelerômetro está conectado.

3. Em seguida chame a função 'getXYZ()' ela irá obter os valores dos três eixos, seus argumentos são: ponteiro para arquivo, ponteiro para X, Y e Z.

4. Ao final, é recomendado utilizar a função 'finishI2C()', pois ela encerra a comunicação I2C, fechando o arquivo. Seu argumento é: ponteiro para arquivo.
