#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2){
	return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

int main(int argc, char** argv){
	FILE *a, *b, *c, *d, *saida, *AeBinterc;
	Endereco ea, eb, ec, ed;
	char nomeArquivo [11], nomeArquivo2 [11], novo_nomeArquivo[11];
	int count = N;

	// saida = fopen("Cep__Intercalado.dat","w");

	for(int i = 1; i <= (N+1); i += 2){
		sprintf(nomeArquivo, "Cep__%d.dat", i);
		sprintf(nomeArquivo2, "Cep__%d.dat", i+1);
		printf("nomeArquivo: %s\n", nomeArquivo);
		printf("nomeArquivo2: %s\n", nomeArquivo2);
		a = fopen(nomeArquivo,"r");
		b = fopen(nomeArquivo2,"r");	
		fread(&ea, sizeof(Endereco), 1, a);
		fread(&eb, sizeof(Endereco), 1, b);
		if(i <= (N-1)){
			sprintf(novo_nomeArquivo, "Cep__%d.dat", (count+1));
			printf("novo_nomeArquivo: %s\n", novo_nomeArquivo);
			AeBinterc = fopen(novo_nomeArquivo, "w");
			printf("\n");
		} else {
			AeBinterc = fopen("Cep__Intercalado.dat", "w");
			printf("Arquivo Final: Cep__Intercalado.dat");
			printf("\n");
		}

		while(!feof(a) && !feof(b)){
			if(compara(&ea, &eb) < 0){
				fwrite(&ea, sizeof(Endereco), 1, AeBinterc);
				fread(&ea, sizeof(Endereco), 1, a);
			} else {
				fwrite(&eb, sizeof(Endereco), 1, AeBinterc);
				fread(&eb, sizeof(Endereco), 1, b);
			}
		}

		while(!feof(a)){
			fwrite(&ea, sizeof(Endereco), 1, AeBinterc);
			fread(&ea, sizeof(Endereco), 1, a);		
		}

		while(!feof(b)){
			fwrite(&eb, sizeof(Endereco), 1, AeBinterc);
			fread(&eb, sizeof(Endereco), 1, b);		
		}

		count++;
		fclose(a);
		fclose(b);
		fclose(AeBinterc);

		remove(nomeArquivo);
		remove(nomeArquivo2);
	}
	// printf("retorno: %d\n", remove("./Cep__Intercalado.dat"));

	printf("FIM");
}