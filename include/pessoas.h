#ifndef PESSOAS_H
#define PESSOAS_H

// Estrutura para armazenar os dados de uma pessoa
typedef struct {
    char nome[100];
    char cpf[15];
    char data[11]; // Formato "dd/mm/aaaa"
    int idade;
} Pessoa;


// --- PROT�TIPOS DAS FUN��ES PRINCIPAIS ---
void incluir_pessoa();
void remover_pessoa();
void listar_pessoas();
void menu_ordenar();
void menu_buscar();
void menu_csv();


// --- PROT�TIPOS DAS FUN��ES DE ORDENA��O ---

void bubble_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*));
void selection_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*));
void insertion_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*));


// --- PROT�TIPOS DAS FUN��ES DE COMPARA��O ---
int comparar_por_nome(const Pessoa* a, const Pessoa* b);
int comparar_por_cpf(const Pessoa* a, const Pessoa* b);
int comparar_por_idade(const Pessoa* a, const Pessoa* b);


// --- PROT�TIPOS DAS FUN��ES AUXILIARES ---
int calcular_idade(const char* data_nascimento_str);
int comparar_strings_sem_case(const char* str1, const char* str2);
void print_pessoa_detalhes(int indice);

#endif 
