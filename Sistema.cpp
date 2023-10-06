#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

#include "I-NodeTAD.h"
#include "funcaoSecretaNaoOlha.h"


void inicializaSistemaBlocos(Disco disco[], int quantidadeBlocosTotais){
    int quantidadeBlocosNecessariosListaLivre = quantidadeBlocosTotais / QUANTIDADE_LIMITE_ENDERECO_LISTA_BLOCO_LIVRE;
    
    for(int j=0; j<quantidadeBlocosNecessariosListaLivre; j++)
    {
        initDisco(disco[j]);
        initListaBlocosLivre(disco[j].lbl);
        
    }

    for(int i = quantidadeBlocosNecessariosListaLivre; i < quantidadeBlocosTotais; i++) 
    {
        initDisco(disco[i]);
        pushListaBlocoLivre(disco, i);
    }

    // exibeListaBlocoLivre(disco);
}

void execucaoSistema(Disco disco[], int quantidadeBlocosTotais, int enderecoInodeRaiz){
    char diretorioAtual[300];
    char comando[200];
    strcpy(comando, "init");
    // system("cls");
    fflush(stdin);

    int enderecoAtual = enderecoInodeRaiz;
    strcpy(diretorioAtual, "/");

    do
    {
        printf("\nroot@localhost:%s$ ", (strcmp(diretorioAtual, "/") == 0 ? "~" : diretorioAtual));
		
        if (strcmp(comando, "ls") == 0)
        {
            printf("\n");
            listDirectory(disco, enderecoAtual, comando+3, comando+4);
            // if (strcmp(comando+3, "-l") == 0)
            // {

            // }
            // else
            // {

            // }
            
        }
        else if (strcmp(comando, "mkdir") == 0)
        {
        	printf("\n");
            printf("receba o diretorio\n");
            
        }
        else if (strcmp(comando, "trace disk") == 0)
        {
            printf("\n");
            exibirDisco(disco, quantidadeBlocosTotais, quantidadeBlocosTotais / QUANTIDADE_LIMITE_ENDERECO_LISTA_BLOCO_LIVRE);
        }
        else if (strcmp(comando, "clear") == 0)
        {
            system("cls");
        }
        
		gets(comando);
		printf("\n");
    } while(strcmp(comando, "exit") != 0);
}

void inicializaSistema(Disco disco[], int quantidadeBlocosTotais)
{
    inicializaSistemaBlocos(disco, quantidadeBlocosTotais);
    int enderecoInodeRaiz = criaDiretorioRaiz(disco);
    // printf("endereco raiz: %d\n", enderecoRaiz);
    // exibeListaBlocoLivre(disco);

    execucaoSistema(disco, quantidadeBlocosTotais, enderecoInodeRaiz);
}

int QuantidadeBlocosTotais() {

    char charQuantidadeBlocosTotais[10];
	int quantidadeBlocosTotais;
    char flag = 1;

    printf("Informe a Quantidade de blocos no disco desejada[ENTER p/ ignorar]:\n");
    while(flag) {

        fflush(stdin);
        gets(charQuantidadeBlocosTotais);

        flag = 0;

        if(strcmp(charQuantidadeBlocosTotais,"") == 0) {
			quantidadeBlocosTotais = 100;
		}
		else {
			quantidadeBlocosTotais = atoi(charQuantidadeBlocosTotais); 
			if(quantidadeBlocosTotais <= 10) {
				printf("A quantidade deve ser maior que 10!\n");
                flag = 1;
			}
		}
    }
	return quantidadeBlocosTotais;
}

int main()
{
    int quantidadeBlocosTotais;
    /*no início do sistema, deve ser informado pelo usuário a quantidade total de discos que haverá */
    /*deve ser possível executar o comando ls -l*/
    iniciarAParada();
    getch();
    system("cls");
    
    quantidadeBlocosTotais = QuantidadeBlocosTotais();
    
    printf("Quantidade de blocos selecionada: %d\n",quantidadeBlocosTotais);
    
    Disco disco[quantidadeBlocosTotais];
    inicializaSistema(disco, quantidadeBlocosTotais);
    
    return 0;
}
