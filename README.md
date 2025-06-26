# Documentação Completa do Projeto: Sistema de Gerenciamento de Pessoas em C

**Versão:** 1.0
**Autor:** (Substitua pelo seu nome)

## 1. Visão Geral do Projeto

Este documento detalha a arquitetura e as funcionalidades do "Sistema de Gerenciamento de Pessoas", um programa desenvolvido em linguagem C. A aplicação permite realizar operações de cadastro, remoção, listagem, busca e ordenação de registros de pessoas, além de oferecer persistência de dados através de arquivos no formato CSV.

## 2. Estrutura dos Arquivos

O projeto é modularizado em três arquivos principais para garantir organização e manutenibilidade:

* **`pessoas.h`**: O arquivo de cabeçalho. Declara as estruturas de dados e os protótipos de todas as funções, atuando como um "contrato" que os outros arquivos seguem.
* **`main.c`**: O ponto de entrada da aplicação. É responsável pelo menu principal e pelo fluxo de navegação do usuário.
* **`pessoas.c`**: O coração do projeto. Contém a implementação (o código) de todas as funcionalidades do sistema.

## 3. Explicação das Funções

### Arquivo de Cabeçalho: `pessoas.h`

Este arquivo centraliza as definições e declarações que são compartilhadas entre os diferentes arquivos `.c`.

* **Estrutura `Pessoa`**: Define o formato dos dados para cada pessoa cadastrada.
* **Protótipos de Funções**: Listam todas as funções disponíveis no sistema, permitindo que o `main.c` as chame mesmo que sua implementação esteja em `pessoas.c`.

### Arquivo Principal: `main.c`

* **`main()`**: É a primeira função a ser executada. Suas responsabilidades são:
    1.  **`setlocale()`**: Configura a localidade para Português.
    2.  **`ler_csv()`**: Tenta carregar dados salvos no início do programa.
    3.  **Loop Principal (`do-while`)**: Mantém o menu principal ativo.
    4.  **`switch (option)`**: Direciona o programa para a função correta com base na escolha do usuário.

### Arquivo de Funcionalidades: `pessoas.c`

**Grupo 1: Funções Auxiliares e Utilitárias**
* **`comparar_strings_sem_case()`**: Compara duas strings ignorando maiúsculas/minúsculas.
* **`calcular_idade()`**: Calcula a idade a partir da data de nascimento e da data atual do sistema.
* **`print_pessoa_detalhes()`**: Imprime os dados de uma única pessoa, evitando repetição de código.

**Grupo 2: Funções Principais (CRUD)**
* **`incluir_pessoa()`**: Adiciona um novo registro de pessoa ao sistema.
* **`listar_pessoas()`**: Exibe todos os registros de pessoas na tela.
* **`remover_pessoa()`**: Remove um registro de pessoa escolhido pelo usuário.

**Grupo 3: Funções de Ordenação**
* **`menu_ordenar()`**: Apresenta a interface para o usuário escolher o critério e o algoritmo de ordenação.
* **`comparar_por_nome()`, `comparar_por_cpf()`, `comparar_por_idade()`**: Funções especializadas que determinam a ordem entre duas pessoas com base em um critério.
* **`bubble_sort_pessoas()`, `selection_sort_pessoas()`, `insertion_sort_pessoas()`**: Implementações dos algoritmos de ordenação, que recebem uma função de comparação como parâmetro para se manterem genéricos.

**Grupo 4: Funções de Busca**
* **`menu_buscar()`**: Apresenta a interface para o usuário escolher o critério, o termo e o algoritmo de busca.
* **Lógica de Busca Linear**: Implementada dentro do menu, percorre toda a lista e pode encontrar múltiplos resultados.
* **Lógica de Busca Binária**: Implementada dentro do menu, é mais eficiente, mas requer que a lista esteja pré-ordenada.

**Grupo 5: Funções de Persistência (CSV)**
* **`menu_csv()`**: Interface para salvar ou carregar dados.
* **`gravar_csv()`**: Salva a lista de pessoas em memória para o arquivo `pessoas.csv`.
* **`ler_csv()`**: Carrega os dados do arquivo `pessoas.csv` para a memória.

---
---

## 4. Código-Fonte Completo

### ARQUIVO 1: `pessoas.h`
```c
#ifndef PESSOAS_H
#define PESSOAS_H

// Estrutura para armazenar os dados de uma pessoa
typedef struct {
    char nome[100];
    char cpf[15];
    char data[11]; // Formato "dd/mm/aaaa"
    int idade;
} Pessoa;


// --- PROTÓTIPOS DAS FUNÇÕES PRINCIPAIS ---
void incluir_pessoa();
void remover_pessoa();
void listar_pessoas();
void menu_ordenar();
void menu_buscar();
void menu_csv();


// --- PROTÓTIPOS DAS FUNÇÕES DE ORDENAÇÃO ---
void bubble_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*));
void selection_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*));
void insertion_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*));


// --- PROTÓTIPOS DAS FUNÇÕES DE COMPARAÇÃO ---
int comparar_por_nome(const Pessoa* a, const Pessoa* b);
int comparar_por_cpf(const Pessoa* a, const Pessoa* b);
int comparar_por_idade(const Pessoa* a, const Pessoa* b);


// --- PROTÓTIPOS DAS FUNÇÕES AUXILIARES ---
int calcular_idade(const char* data_nascimento_str);
int comparar_strings_sem_case(const char* str1, const char* str2);
void print_pessoa_detalhes(int indice);
void ler_csv();
void gravar_csv();

#endif //PESSOAS_H
