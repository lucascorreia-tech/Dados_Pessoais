#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "clean.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "pt_bt.UTF-8");
	if (setlocale(LC_ALL, "pt_BR.UTF-8") == NULL) {
    	setlocale(LC_ALL, "Portuguese_Brazil.1252");  
	}
	
	int option;
	do{
		printf("=============================\n");
		printf("|     Bem vindo Ao Menu     |\n");
		printf("=============================\n\n");
		
		printf("1 - Incluir pessoa\n");
		printf("2 - Remover pessoa\n");
		printf("3 - Listar pessoas\n");
		printf("4 - Ordenar\n");
		printf("5 - Buscar pessoa\n");
		printf("6 - Ler/Gravar CSV\n");
		printf("7 - sair\n");
		
		printf("\nEscolha uma das opções: ");
		scanf("%d", &option);
		
		switch (option){
			case 1:
				printf(" incluirPessoa()...");
			case 2:
				printf(" removePessoa()...");
			case 3:
				printf(" listarPessoa()...");
			case 4:
				printf(" ordenarPessoa()...");
			case 5:
				printf(" buscaPessoa()...");
			case 6:
				printf(" lerGravarPessoa()...");
			default:
				printf("\nOpção inválida!");
				clean_window();		
		}
	} while (option != 7);
}
