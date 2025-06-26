#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "clean.h"
#include "pessoas.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "pt_bt.UTF-8");
	if (setlocale(LC_ALL, "pt_BR.UTF-8") == NULL) {
    	setlocale(LC_ALL, "Portuguese_Brazil.1252");  
	}
	
	ler_csv();
	
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
		clean_buffer();
		clean_window();
		
		switch (option){
			case 1:
				incluir_pessoa();
				break;
			case 2:
				remover_pessoa();
				break;
			case 3:
				listar_pessoas();
				break;
			case 4:
				menu_ordenar();
				break;
			case 5:
				menu_buscar(); 
                break;
			case 6:
				menu_csv();
				break;
			case 7:
				printf("\n Saindo do programa. Até logo!");	
				break;
			default:
				printf("\nOpção inválida!");
				getchar();
				break;	
		}
	} while (option != 7);
	
	return 0;
}
