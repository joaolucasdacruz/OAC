#include <stdio.h>
#include <stdint.h>


#define MEM_SIZE 4096 
int32_t mem[MEM_SIZE];


typedef struct parameters{
	
	uint32_t add_base;
	int16_t add_incr;
	int8_t dado_8;
	int16_t dado_16;
	int32_t dado_32;
	
}param;

/*----------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------dump_mem PARA IMPRIMIR BLOCOS DE MEMÒRIA--------------------------------------------------------*/

void dump_mem(uint32_t add,uint32_t size){	/* Imprime o conteúo em palavras em formato hexadecimal.*/
		
/*add é o endereço em bytes a partir o qual o conteúdo será impresso.*/
/*size é o tamnho em bytes do bloco de memória que será impresso.*/
/*size_w é o tamnho o bloco e memória a ser impresso em words*/
/*add_at é o valor atualizado o campo de memória a ser impresso no loop*/
	
	uint32_t add_at=add;
	uint32_t size_w;
	int  i; 
	
	size_w = size/4;
	printf("\n Número de palavras mostradas: %u \n", size_w); 
/*loop de impressão de dados da memória*/	
	for(i=add;i<add+size_w; i++){	
		printf("Mem[%d] = %08x\n",i,mem[add_at]);
		add_at +=1;
	}
}	


/*----------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------MOSTRA MENU DE INSTRUÇÔES D||ISPONÌVEIS------------------------------------------------------*/

int choose_option(){ /*Função de escolha da instrução a ser executada*/ 
	
	int op;
	
	while(op != 1  && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && op != 8 && op != 9 && op!= 10){ 
		printf(" Escolha uma opção para executar uma das instruções disponíveis, ou fechar o programa \n\n");
		printf("\n 1. lw  \n");
		printf("\n 2. lh  \n");
		printf("\n 3. lhu\n");
		printf("\n 4. lb\n");
		printf("\n 5. lbu\n");
		printf("\n 6. sw \n");
		printf("\n 7. sh \n");
		printf("\n 8. sb \n");
		printf("\n 9. dump_mem \n");
		printf("\n 10. fechar o programa\n");
		printf(">>");
		scanf("%d", &op);
		while(getchar() != '\n');
	
		if(op!= 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && op !=8 && op != 9 && op!= 10 ){
			printf("Opção invállida, escolha uma opção de 1 a 8 para executar uma instrução: \n");
		}
	}
	return(op);	
}
/*---------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------LOAD WORD-------------------------------------------------------------*/


int32_t lw(uint32_t address, int16_t kte){
	
	int32_t regis;
	
	regis = mem[address/4 + kte/4];
		
	return(regis);
}

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------LOAD HALF-------------------------------------------------------------*/
int32_t lh(uint32_t address, int16_t kte){
	
	int16_t leitura;
	int32_t regis;
	
	if((kte/2)%2 == 0)
		leitura = mem[(address/4) + (kte/4)];
	else
		leitura = mem[(address/4) + (kte/4)] >> 16;
	
	regis = leitura;
	
	return(regis);
} 

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------LOAD HALF UNSIGNED---------------------------------------------------------*/

uint16_t lhu(uint32_t address, int16_t kte){
	
	uint16_t leitura;
	uint32_t regis;
	
		if((kte/2)%2 == 0)
			leitura = mem[(address/4) + (kte/4)];
		else
			leitura = mem[(address/4) + (kte/4)] >> 16;
		regis = leitura;
	
	return(regis);
}

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------LOAD BYTE----------------------------------------------------------------*/

int32_t lb(uint32_t address, int16_t kte){
	
	int i;
	int pos_byte;
	int8_t leitura;
	int32_t reg_aux;
	int32_t regis;
	
	pos_byte = kte % 4;
	reg_aux = mem[address/4 + kte/4];
	for(i=0;i<pos_byte;i++){
		reg_aux = reg_aux >> 8;		
	}
	leitura = reg_aux;
	regis = leitura;
	
	return(regis);

}
/*---------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------LOAD BYTE UNSIGNED-----------------------------------------------------------*/

uint32_t lbu(uint32_t address, int16_t kte){
	
	int i;
	int pos_byte;
	uint8_t leitura;
	uint32_t reg_aux;
	
	pos_byte = kte % 4;
	reg_aux = mem[address/4 + kte/4];
	for(i=0;i<pos_byte;i++){
		reg_aux = reg_aux >> 8;		
	}
	leitura = reg_aux;
	reg_aux = leitura;
	return(reg_aux);

}

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------STORE WORD---------------------------------------------------------------*/

void sw (uint32_t address, int16_t kte, int32_t dado){ 
	
		mem[(address/4)+(kte/4)] = dado;
			
}

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------STORE HALF---------------------------------------------------------------*/

void sh (uint32_t address, int16_t kte, int16_t dado){

/*dado_esq são os 16 MSB que irão ficar na  palavra do endereço de memória após a operação*/
/*dado_dir são os 16 LSB que irão ficar na palavra do endereço de memória após a operação*/
	uint32_t dado_esq=0;
	uint32_t dado_dir=0;
	
/*Se o número de meias palavras a serem puladas no vetor de memória for par*/
/*O novo dado deve ser salvo nos 16 LSB e os 16 MSB devem ser preservados na palavra*/
	if ((kte/2) % 2 == 0){
		dado_dir = dado;
		dado_esq = mem[address/4 + kte/4];
		dado_esq = dado_esq >> 16;
		dado_esq = dado_esq <<16;
		mem[address/4 + kte/4] = dado_esq + dado_dir;
		
	}
/*Caso o contrário, o novo dado deve ser salvo nos 16 MSB */
	else{
		
		dado_esq = dado;
		dado_esq = dado_esq << 16;
		dado_dir = mem[address/4 + kte/4];
		dado_dir = dado_dir << 16;
		dado_dir = dado_dir >> 16;
		mem[address/4 + kte/4] = dado_esq + dado_dir;
		printf("\n O dado presente na memória é agora é: %08x \n", mem[address/4 + kte/4]);
		
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------STORE BYTE------------------------------------------------------------*/


void sb (uint32_t address, int16_t kte, int8_t dado){
	
	int i;
	int pos_word;
	uint8_t dado_aux[2];
	uint32_t dado32 = dado;
	
	pos_word = kte % 4;
	
	for(i=0;i<pos_word;i++){
		dado_aux[i] = mem[(address/4) + (kte/4)];
		mem[(address/4) + (kte/4)] = mem[(address/4) + (kte/4)] >> 8;

	}
	mem[(address/4) + (kte/4)] = mem[(address/4) + (kte/4)] >> 8;
	mem[(address/4) + (kte/4)] = mem[(address/4) + (kte/4)] << 8;
	mem[(address/4) + (kte/4)] = mem[(address/4) + (kte/4)] + dado32;

	for(i=1;i<=pos_word;i++){
		mem[(address/4) + (kte/4)] = mem[(address/4) + (kte/4)] << 8;
		mem[(address/4) + (kte/4)] = mem[(address/4) + (kte/4)]+dado_aux[pos_word-i];
	}
}

/*---------------------------------------------------------------------------------------------------------------------------------*/							
/*-------------------------------------LEITURA E VALIDAÇÂO DE PARAMETROS DAS INSTRUÇÔES--------------------------------------------*/

void get_parameters(param *parametros, char Tipo, int Tam){ 
/*Inicialização dos incremento e da base do endereço de memória para que os loops possam ser iniciados*/	
	(*parametros).add_incr =1;
	(*parametros).add_base =1;
	
/*Coletando o endereço base da memória*/
	while ((*parametros).add_base % 4 !=0){ /*O endereço base deve ser sempre múltiplo de 4 Bytes*/
		printf("Digite a base do endereço de memória:  ");
		scanf("%u", &(*parametros).add_base);
		while(getchar() != '\n');
		if((*parametros).add_base % 4 !=0)
			printf("\n posição inválida,digite um número múltiplo de 4 Bytes ! \n  ");
	}	
		printf("\n Digite a posição em bytes em relação à base do endereço de memória:  ");
		
/*Coleta da posição de memória em relação à base do endereço*/
	switch(Tam){

/*Caso essa posição tenha de ser dada em words*/	
		case 32:  
			while ((*parametros).add_incr % 4 !=0){
				scanf("%hi" , &(*parametros).add_incr);
				while(getchar() != '\n');
				if((*parametros).add_incr % 4 != 0)
					printf("\n posição inválida,deve ser digitado um número múltiplo de 4 Bytes!\n");
			}
		break;
		
/*Caso deva ser dada em half words*/		
		case 16: 
			while ((*parametros).add_incr % 2 !=0){
				scanf("%hi" , &(*parametros).add_incr);
				while(getchar() != '\n');
				if((*parametros).add_incr % 2 !=0)
					printf("\n posição inválida,digite um número múltiplo de 2 Bytes !");
			}
		break;
		
/*Caso deva ser dada em Bytes*/		
		case 8:
			scanf("%hi" , &(*parametros).add_incr);
			while(getchar() != '\n');
		break;
	}
	
/*Caso a intrução seja um store, é preciso coletar o dado a ser armazenado*/
/*Esse dado pode ter 8, 16 ou 32 bits*/	
		if(Tipo == 's'){
			printf("\n Digite o dado a ser armazenado:");
			if(Tam == 32){
				scanf("%i", &(*parametros).dado_32);
				getchar();
			}
			if(Tam == 16){
				scanf("%hi", &(*parametros).dado_16);
				getchar();
			}
			if(Tam == 8){
				scanf("%hhi", &(*parametros).dado_8);
				getchar();
			}
		}	
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------FUNÇÂO PRINCIPAL---------------------------------------------------------*/

int main(){

	int m_size;
	int op_choose=0;
	m_size=sizeof(mem);
	param parametros;
	char new_page;
	int32_t registrador;
	uint32_t registradorU;

	
	 
	
	printf("tamanho da memória = %d Bytes \n\n",m_size);
/*Chamada da função de escolha da instrução a ser executada*/
	while(op_choose != 10){
		op_choose = choose_option();
		switch(op_choose){
		
			case 1:
				get_parameters(&parametros,'l',32);
				registrador=lw(parametros.add_base,parametros.add_incr); 
				printf("\n\nO conteúdo atual do registrador é: %i em hexa %08x \n\n", registrador, registrador);
				break;
			
			case 2:
				get_parameters(&parametros,'l',16);
				registrador=lh(parametros.add_base,parametros.add_incr); 
				printf("\n\nO conteúdo atual do registrador é: %i em hexa %04x \n\n", registrador, registrador);
				break;
			
			case 3:
				get_parameters(&parametros,'l',16);
				registradorU=lhu(parametros.add_base,parametros.add_incr); 
				printf("\n\nO conteúdo atual do registrador é: %u \n\n", registradorU);
				break;
			
			case 4:
				get_parameters(&parametros,'l',8);
				registrador=lb(parametros.add_base,parametros.add_incr); 
				printf("\n\nO conteúdo atual do registrador é: %i em hexa %2hhx \n\n", registrador, registrador);
				break;	
			
			case 5:
				get_parameters(&parametros,'l',8);
				registradorU=lbu(parametros.add_base,parametros.add_incr);
				printf("\n\nO conteúdo atual do registrador é: %i \n\n", registradorU); 
				break;
			
			case 6:
				get_parameters(&parametros,'s',32);
				sw(parametros.add_base, parametros.add_incr, parametros.dado_32);
				break;
			case 7:
				get_parameters(&parametros,'s',16);
				sh(parametros.add_base, parametros.add_incr, parametros.dado_16);
				break;
			
			case 8:
				get_parameters(&parametros,'s',8);
				sb(parametros.add_base, parametros.add_incr, parametros.dado_8);
				break;
			
			case 9:
				get_parameters(&parametros,'d',32);
				dump_mem(parametros.add_base,parametros.add_incr);
				break;
		}
		
	if(op_choose != 10){
		printf("Instrução realizada, pressione qualquer tecla + ENTER para continuar \n\n");
		scanf("%c", &new_page);
		getchar();
	}
	}	
return(0);
}

/*-------------------------------------------------FIM DO PROGRAMA------------------------------------------------------------------*/
