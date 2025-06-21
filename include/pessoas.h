#ifndef PESSOAS.H
#define PESSOAS.H

typedef struct{
	int cpf;
	char nome[100];
	char data[11]; // dd/MM/yyyy
}Pessoa;

void incluir_pessoa();
void remover_pessoa();
void listar_pessoas();
void ordenar_pessoas();
void buscar_pessoas();

#endif
