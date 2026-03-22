#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct no{

    int ra;

    char nome[20];

    struct no *next;

} no;

no *inicio = NULL, *corrente = NULL, *auxiliar = NULL;

//carregar arquivo

void carregarArquivo() {

    FILE *fp = fopen("dados.dat", "rb");

    if(fp == NULL) return;

    no temp;

    while(fread(&temp, sizeof(no), 1, fp) == 1){

        no *novo = (no*)malloc(sizeof(no));

        *novo = temp;

        novo->next = NULL;

        if(inicio == NULL){

            inicio = novo;

            auxiliar = novo;

        } else {

            auxiliar->next = novo;

            auxiliar = novo;

        }

    }

    fclose(fp);

}

// salvar dados

void salvarArquivo() {

    FILE *fp = fopen("dados.dat", "wb");

    if(fp == NULL){

        printf("Erro ao abrir arquivo para gravar!\n");

        return;

    }

    corrente = inicio;

    while(corrente != NULL){

        fwrite(corrente, sizeof(no), 1, fp);

        corrente = corrente->next;

    }

    fclose(fp);

}

//novo registro

void inserir() {

    corrente = (no*)malloc(sizeof(no));

    corrente->next = NULL;

    printf("\nInforme o RA: ");

    scanf("%d", &corrente->ra);

    printf("Informe o nome: ");

    scanf("%s", corrente->nome);

    if(inicio == NULL){

        inicio = corrente;

        auxiliar = corrente;

    } else {

        auxiliar->next = corrente;

        auxiliar = corrente;

    }

    printf("\nElemento inserido com sucesso!\n");

}

// Exibir lista

void exibir() {

    if(inicio == NULL){

        printf("\nLista vazia!\n");

        return;

    }

    corrente = inicio;

    printf("\n--- Lista completa ---\n");

    while(corrente != NULL){

        printf("\nRA: %d", corrente->ra);

        printf("\nNome: %s", corrente->nome);

        printf("\n---------------------");

        corrente = corrente->next;

    }

}

// Pesquisar RA

void pesquisa() {

    if(inicio == NULL){

        printf("\nLista vazia!\n");

        return;

    }

    int ra_procurado, encontrado = 0;

    printf("\nInforme o RA para pesquisar: ");

    scanf("%d", &ra_procurado);

    corrente = inicio;

    while(corrente != NULL){

        if(corrente->ra == ra_procurado){

            printf("\n--- Registro encontrado ---");

            printf("\nRA: %d", corrente->ra);

            printf("\nNome: %s", corrente->nome);

            printf("\n--------------------------");

            encontrado = 1;

            break;

        }

        corrente = corrente->next;

    }

    if(!encontrado){

        printf("\nRA %d nao encontrado na lista!\n", ra_procurado);

    }

}

// Remover RA

void remover() {

    if(inicio == NULL){

        printf("\nLista vazia!\n");

        return;

    }

    int ra_remover, encontrado = 0;

    no *anterior = NULL;

    printf("\nInforme o RA para remover: ");

    scanf("%d", &ra_remover);

    corrente = inicio;

    while(corrente != NULL){

        if(corrente->ra == ra_remover){

            if(anterior == NULL){

                inicio = corrente->next;

                if(inicio == NULL) auxiliar = NULL;

            } else {

                anterior->next = corrente->next;

                if(corrente->next == NULL) auxiliar = anterior;

            }

            printf("\n--- Registro removido ---");

            printf("\nRA: %d", corrente->ra);

            printf("\nNome: %s", corrente->nome);

            printf("\n------------------------\n");

            free(corrente);

            encontrado = 1;

            break;

        }

        anterior = corrente;

        corrente = corrente->next;

    }

    if(!encontrado){

        printf("\nRA %d nao encontrado na lista!\n", ra_remover);

    }

}

int main() {

    int opcao, continuar = 1;

    carregarArquivo(); // Carrega dados existentes do arquivo

    while(continuar){

        system("cls");

        printf("\n\n=== MENU ===");

        printf("\n1 - Inserir");

        printf("\n2 - Exibir lista");

        printf("\n3 - Pesquisar por RA");

        printf("\n4 - Remover por RA");

        printf("\n5 - Sair");

        printf("\nEscolha uma opcao: ");

        scanf("%d", &opcao);

        switch(opcao){

            case 1:

                inserir();

                system("pause");

                break;

            case 2:

                exibir();

                system("pause");

                break;

            case 3:

                pesquisa();

                system("pause");

                break;

            case 4:

                remover();

                system("pause");

                break;

            case 5:

                salvarArquivo(); // Salva dados antes de sair

                printf("\nSaindo e salvando dados...\n");

                continuar = 0;

                system("pause");

                break;

            default:

                printf("\nOpcao invalida!\n");

                system("pause");

        }

    }

}


