#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "pessoas.h"
#include "clean.h"

Pessoa pessoas[100];
int totalPessoas = 0;

// --- FUNÇÕES AUXILIARES ---

int comparar_strings_sem_case(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        int diff = tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
        if (diff != 0) return diff;
        str1++;
        str2++;
    }
    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}

int calcular_idade(const char* data_nascimento_str) {
    int dia_nasc, mes_nasc, ano_nasc;
    if (sscanf(data_nascimento_str, "%d/%d/%d", &dia_nasc, &mes_nasc, &ano_nasc) != 3) {
        return -1; // Formato inválido
    }
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int idade = (tm.tm_year + 1900) - ano_nasc;
    if ((tm.tm_mon + 1) < mes_nasc || ((tm.tm_mon + 1) == mes_nasc && tm.tm_mday < dia_nasc)) {
        idade--;
    }
    return idade;
}

void print_pessoa_detalhes(int indice) {
    printf("\n--- Pessoa Encontrada ---\n");
    printf("Nome: %s\n", pessoas[indice].nome);
    printf("CPF: %s\n", pessoas[indice].cpf);
    printf("Data de Nasc.: %s\n", pessoas[indice].data);
    printf("Idade: %d anos\n", pessoas[indice].idade);
    printf("-------------------------\n");
}


// --- FUNÇÕES DE CADASTRO, REMOÇÃO E LISTAGEM ---

void incluir_pessoa() {
    printf("==========================\n|   Cadastro de pessoa   |\n==========================\n\n");
    Pessoa nova_pessoa;
    printf("Digite o nome da pessoa: ");
    fgets(nova_pessoa.nome, sizeof(nova_pessoa.nome), stdin);
    nova_pessoa.nome[strcspn(nova_pessoa.nome, "\n")] = '\0';
    printf("Digite o CPF da pessoa: ");
    fgets(nova_pessoa.cpf, sizeof(nova_pessoa.cpf), stdin);
    nova_pessoa.cpf[strcspn(nova_pessoa.cpf, "\n")] = '\0';
    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    fgets(nova_pessoa.data, sizeof(nova_pessoa.data), stdin);
    nova_pessoa.data[strcspn(nova_pessoa.data, "\n")] = '\0';
    nova_pessoa.idade = calcular_idade(nova_pessoa.data);
    pessoas[totalPessoas++] = nova_pessoa;
    printf("\nPessoa registrada com sucesso! (Idade calculada: %d anos)\n", nova_pessoa.idade);
    printf("Pressione ENTER para continuar...");
    getchar();
    clean_window();
}

void remover_pessoa() {
    printf("=========================\n|   Remoção de pessoa   |\n=========================\n\n");
    if (totalPessoas == 0) {
        printf("Nenhuma pessoa encontrada.\n");
    } else {
        printf("Qual pessoa você quer remover?\n");
        for (int i = 0; i < totalPessoas; i++) printf("%d - %s\n", i + 1, pessoas[i].nome);
        int resposta;
        printf("\nDigite o número correspondente: ");
        scanf("%d", &resposta);
        getchar();
        if (resposta < 1 || resposta > totalPessoas) {
            printf("\nOpção inválida!\n");
        } else {
            for (int i = resposta - 1; i < totalPessoas - 1; i++) pessoas[i] = pessoas[i + 1];
            totalPessoas--;
            printf("\nPessoa removida com sucesso!\n");
        }
    }
    printf("Pressione ENTER para continuar...");
    getchar();
    clean_window();
}

void listar_pessoas() {
    printf("========================\n|   Lista de pessoas   |\n========================\n\n");
    if (totalPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
    } else {
        for (int i = 0; i < totalPessoas; i++) {
            printf("%d. Nome: %s | CPF: %s | Nasc: %s | Idade: %d\n", i + 1, pessoas[i].nome, pessoas[i].cpf, pessoas[i].data, pessoas[i].idade);
        }
    }
    printf("\nPressione ENTER para sair...");
    getchar();
    clean_window();
}


// --- FUNÇÕES DE COMPARAÇÃO PARA ORDENAÇÃO ---

int comparar_por_nome(const Pessoa* a, const Pessoa* b) {
    return comparar_strings_sem_case(a->nome, b->nome);
}
int comparar_por_cpf(const Pessoa* a, const Pessoa* b) {
    return strcmp(a->cpf, b->cpf);
}
int comparar_por_idade(const Pessoa* a, const Pessoa* b) {
    return a->idade - b->idade;
}


// --- ALGORITMOS DE ORDENAÇÃO ---

void bubble_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*)) {
    int i, j; Pessoa temp;
    for (i = 0; i < totalPessoas - 1; i++) {
        for (j = 0; j < totalPessoas - i - 1; j++) {
            if (comparador(&pessoas[j], &pessoas[j + 1]) > 0) {
                temp = pessoas[j]; pessoas[j] = pessoas[j + 1]; pessoas[j + 1] = temp;
            }
        }
    }
}

void selection_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*)) {
    int i, j, min_idx; Pessoa temp;
    for (i = 0; i < totalPessoas - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < totalPessoas; j++) {
            if (comparador(&pessoas[j], &pessoas[min_idx]) < 0) min_idx = j;
        }
        if (min_idx != i) {
            temp = pessoas[min_idx]; pessoas[min_idx] = pessoas[i]; pessoas[i] = temp;
        }
    }
}

void insertion_sort_pessoas(int (*comparador)(const Pessoa*, const Pessoa*)) {
    int i, j; Pessoa chave;
    for (i = 1; i < totalPessoas; i++) {
        chave = pessoas[i]; j = i - 1;
        while (j >= 0 && comparador(&pessoas[j], &chave) > 0) {
            pessoas[j + 1] = pessoas[j]; j--;
        }
        pessoas[j + 1] = chave;
    }
}


// --- MENUS DE ORDENAÇÃO E BUSCA ---

void menu_ordenar() {
    if (totalPessoas < 2) { printf("É necessário ter pelo menos duas pessoas para ordenar.\n"); getchar(); clean_window(); return; }
    int crit_opcao, alg_opcao;
    int (*comparador_escolhido)(const Pessoa*, const Pessoa*) = NULL;

    printf("Ordenar por qual critério?\n1-Nome | 2-CPF | 3-Idade | 4-Cancelar\nOpção: ");
    scanf("%d", &crit_opcao); getchar();
    switch (crit_opcao) {
        case 1: comparador_escolhido = comparar_por_nome; break;
        case 2: comparador_escolhido = comparar_por_cpf; break;
        case 3: comparador_escolhido = comparar_por_idade; break;
        default: return;
    }

    printf("\nQual algoritmo usar?\n1-Bubble | 2-Selection | 3-Insertion | 4-Cancelar\nOpção: ");
    scanf("%d", &alg_opcao); getchar();
    char* nome_algoritmo = "";
    switch (alg_opcao) {
        case 1: bubble_sort_pessoas(comparador_escolhido); nome_algoritmo = "Bubble Sort"; break;
        case 2: selection_sort_pessoas(comparador_escolhido); nome_algoritmo = "Selection Sort"; break;
        case 3: insertion_sort_pessoas(comparador_escolhido); nome_algoritmo = "Insertion Sort"; break;
        default: return;
    }
    printf("\nLista ordenada com %s!\nPressione ENTER...", nome_algoritmo);
    getchar();
    clean_window();
}

void menu_buscar() {
    clean_window();
    if (totalPessoas == 0) { printf("Nenhuma pessoa cadastrada.\n"); getchar(); clean_window(); return; }
    int crit_opcao, alg_opcao, encontrados = 0;
    
    printf("Buscar por qual critério?\n1-Nome | 2-CPF | 3-Idade | 4-Cancelar\nOpção: ");
    scanf("%d", &crit_opcao); getchar();
    if (crit_opcao < 1 || crit_opcao > 3) return;

    char nome_busca[100], cpf_busca[15]; int idade_busca;
    switch (crit_opcao) {
        case 1: printf("Digite o nome: "); fgets(nome_busca, 100, stdin); nome_busca[strcspn(nome_busca, "\n")] = 0; break;
        case 2: printf("Digite o CPF: "); fgets(cpf_busca, 15, stdin); cpf_busca[strcspn(cpf_busca, "\n")] = 0; break;
        case 3: printf("Digite a idade: "); scanf("%d", &idade_busca); getchar(); break;
    }

    printf("\nQual algoritmo usar?\n1-Linear | 2-Binária (lista deve estar ordenada)\nOpção: ");
    scanf("%d", &alg_opcao); getchar();

    if (alg_opcao == 1) { // Busca Linear
        for (int i = 0; i < totalPessoas; i++) {
            int achou = 0;
            if (crit_opcao == 1 && comparar_strings_sem_case(pessoas[i].nome, nome_busca) == 0) achou = 1;
            if (crit_opcao == 2 && strcmp(pessoas[i].cpf, cpf_busca) == 0) achou = 1;
            if (crit_opcao == 3 && pessoas[i].idade == idade_busca) achou = 1;
            if (achou) { print_pessoa_detalhes(i); encontrados++; }
        }
    } else if (alg_opcao == 2) { // Busca Binária
        printf("AVISO: A busca binária SÓ funciona se a lista estiver ORDENADA pelo critério da busca!\n");
        int baixo = 0, alto = totalPessoas - 1, meio, achou_indice = -1;
        while (baixo <= alto) {
            meio = baixo + (alto - baixo) / 2;
            int comp = 0;
            if (crit_opcao == 1) comp = comparar_strings_sem_case(pessoas[meio].nome, nome_busca);
            if (crit_opcao == 2) comp = strcmp(pessoas[meio].cpf, cpf_busca);
            if (crit_opcao == 3) comp = pessoas[meio].idade - idade_busca;
            if (comp == 0) { achou_indice = meio; break; }
            if (comp < 0) baixo = meio + 1; else alto = meio - 1;
        }
        if (achou_indice != -1) { print_pessoa_detalhes(achou_indice); encontrados++; }
    }
    
    if (encontrados == 0) printf("\nNenhum resultado encontrado.\n");
    printf("\nPressione ENTER para continuar...");
    getchar();
    clean_window();
}

void gravar_csv() {
    FILE* arquivo = fopen("pessoas.csv", "w"); 

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    fprintf(arquivo, "Nome,CPF,DataNascimento\n");

    for (int i = 0; i < totalPessoas; i++) {
        fprintf(arquivo, "%s,%s,%s\n",
                pessoas[i].nome,
                pessoas[i].cpf,
                pessoas[i].data);
    }

    fclose(arquivo); 
    printf("\nDados salvos com sucesso em pessoas.csv!\n");
}


void ler_csv() {
    FILE* arquivo = fopen("pessoas.csv", "r"); 

    if (arquivo == NULL) {
        return;
    }

    char buffer[200];
    fgets(buffer, sizeof(buffer), arquivo);

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        if (totalPessoas >= 100) {
            printf("Limite de pessoas atingido. Nem todos os dados do CSV foram carregados.\n");
            break;
        }

        Pessoa nova_pessoa;
        char* token = strtok(buffer, ",");
        if(token) strcpy(nova_pessoa.nome, token);

        token = strtok(NULL, ",");
        if(token) strcpy(nova_pessoa.cpf, token);

        token = strtok(NULL, "\n"); 
        if(token) strcpy(nova_pessoa.data, token);

        nova_pessoa.idade = calcular_idade(nova_pessoa.data);
        pessoas[totalPessoas++] = nova_pessoa;
    }

    fclose(arquivo);
}


void menu_csv() {
    clean_window();
    printf("======================================\n");
    printf("|     Gerenciar Dados em Arquivo     |\n");
    printf("======================================\n\n");
    printf("1 - Salvar dados no arquivo (sobrescreve o atual)\n");
    printf("2 - Carregar dados do arquivo (adiciona à lista atual)\n");
    printf("3 - Cancelar\n");

    int opcao;
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            gravar_csv();
            break;
        case 2:
            ler_csv();
            break;
        case 3:
        	clean_window();
            return;
        default:
            printf("Opção inválida!\n");
            break;
    }

    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    clean_window();
}
