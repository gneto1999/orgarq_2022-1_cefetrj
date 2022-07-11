#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2){
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char**argv){
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, metade;
	char nomeArquivo [20];

	f = fopen("cep.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	metade = qtd/N;
	printf("qtd: %ld, metade: %ld\n", qtd, metade);

	rewind(f);
	for(int i = 1; i < N; i++){
		e = (Endereco*) malloc(metade*sizeof(Endereco));
		if(fread(e,sizeof(Endereco),metade,f) == metade){
			printf("Lido = OK\n");
		}
		qsort(e,metade,sizeof(Endereco),compara);
		printf("Ordenado = OK\n");
		sprintf(nomeArquivo, "Cep__%d.dat", i);
		saida = fopen(nomeArquivo,"wb");
		fwrite(e,sizeof(Endereco),metade,saida);
		printf("Escrito = OK\n");
		fclose(saida);
		free(e);
	}

	long restante = qtd - metade * 3; 

	e = (Endereco*) malloc((restante)*sizeof(Endereco));
	if(fread(e,sizeof(Endereco),restante,f) == metade){
		printf("Lido = OK\n");
	}
	qsort(e,restante,sizeof(Endereco),compara);
	printf("Ordenado = OK\n");
	sprintf(nomeArquivo, "Cep__%d.dat", N);
	saida = fopen(nomeArquivo,"wb");
	fwrite(e,sizeof(Endereco),restante,saida);
	fclose(saida);
	printf("Escrito = OK\n");
	free(e);

	fclose(f);
}