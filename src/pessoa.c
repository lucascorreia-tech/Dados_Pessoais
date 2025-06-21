#include <stdio.h>
#include <string.h>
#include "pessoas.h"
#include "clean.h"

Pessoa pessoa;
Pessoa pessoas[100];
int totalPessoas = 0;

void incluir_pessoa(){
	printf("==========================\n");
	printf("|   Cadastro de pessoa   |\n");
	printf("==========================\n\n");
	
	printf("Digite o nome da pessoa: ");
	fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
	pessoa.nome[strcspn(pessoa.nome,"\n")] = '\0'; // Removendo o \n
	
	printf("Digite o cpf da pessoa: ");
	scanf("%d", &pessoa.cpf);
	clean_buffer();
	
	printf("Digite a data de nascimento da pessoa: ");
	scanf(" %10s", &pessoa.data);
	clean_buffer();
	
	pessoas[totalPessoas++] = pessoa;
	printf("\nPessoa registrada com sucesso");
	getchar();
	clean_window();
}

void remover_pessoa(){
	printf("=========================\n");
	printf("|   Remoção de pessoa   |\n");
	printf("=========================\n\n");
	
	
	if(totalPessoas == 0){
		printf("Nenhuma pessoa encontrada. Registre uma pessoa primeiro!!");
		getchar();
		clean_window();
		return;
	}
	
	printf("Qual dessas pessoas você quer remover ?\n");
	for (int i = 0; i < totalPessoas; i++){
		printf("%d - %s\n", i + 1, pessoas[i].nome);
	}
	
	int resposta;
	printf("Digite o número correspondente a pessoa: ");
	scanf("%d", &resposta);
	clean_buffer();
	
	if (resposta < 1 || resposta > totalPessoas){
		printf("\nOpção inválida!\n");
		getchar();
		clean_window();
		return;
	}
	
	for(int i = resposta - 1; i < totalPessoas - 1; i++){
		pessoas[i] = pessoas[i+1];
	}
	
	totalPessoas--;
	
	printf("\nPessoa removida com sucesso!\n");
	getchar();
	clean_window();
}

void listar_pessoas(){
	printf("========================\n");
	printf("|   Listas de pessoas  |\n");
	printf("========================\n\n");
	
	printf("Abaixo está a lista de pessoas cadastradas até agora:\n\n");
	
	for (int i = 0; i < totalPessoas; i++){
		printf("%d. Nome: %s CPF: %d Data de nascimento: %s\n", i + 1, pessoas[i].nome, pessoas[i].cpf, pessoas[i].data);
	}
	
	printf("Aperte ENTER para sair...");
	getchar();
	clean_window();
}
