/* 
 a) Analise o código a seguir e identifique todos os problemas relacionados ao gerenciamento de memória:

    • Falta de verificação de malloc: A linha "Emprestimo* novo = malloc(sizeof(Emprestimo))" não verifica se malloc retornou NULL, 
    o que levaria a uma falha de segmentação se a memória estiver esgotada,assim, travando o programa.

    • Vazamento de memória: A linha "free(atual)" libera apenas a memória da estrutura "nó" mas NÃO libera 
    a memória alocada para as strings 'atual->usuario' e 'atual->isbn'.

    • Cópia rasa de ponteiros: As linhas "novo->usuario = user" e "novo->isbn = book" apenas copiam os endereços de memória, 
    e não o conteúdo das strings.
*/

/*
 b) Reescreva o código corrigindo todos os problemas identificados. Sua solução deve incluir:
    • Verificação adequada de alocação de memória
    • Liberação correta de todos os recursos
    • Tratamento de casos extremos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados original
typedef struct emprestimo {
    char* usuario;
    char* isbn;
    struct emprestimo* prox;
} Emprestimo;


Emprestimo* adiciona_emprestimo_corrigido(Emprestimo* lista, const char* user, const char* book) {
    // Tratamento de casos extremos: não faz nada se os dados de entrada forem nulos.
    if (user == NULL || book == NULL) {
        return lista;
    }

    // Aloca memória para a estrutura do novo empréstimo.
    Emprestimo* novo = (Emprestimo*) malloc(sizeof(Emprestimo));

    // Verificação adequada de alocação de memória para o nó.
    if (novo == NULL) {
        perror("Falha ao alocar memoria para novo emprestimo");
        return lista; // Retorna a lista original sem modificação em caso de falha.
    }

    // Inicializa ponteiros para garantir que não contenham lixo.
    novo->usuario = NULL;
    novo->isbn = NULL;

    // Alocação de memória para as strings, criando cópias independentes (cópia profunda).
    // strdup aloca memória e copia a string de uma só vez.
    novo->usuario = strdup(user);
    novo->isbn = strdup(book);

    // Verificação adequada de alocação de memória para as strings internas.
    if (novo->usuario == NULL || novo->isbn == NULL) {
        perror("Falha ao alocar memoria para dados do emprestimo");
        // Liberação correta de todos os recursos em caso de falha parcial.
        free(novo->usuario); // É seguro chamar free em um ponteiro NULL.
        free(novo->isbn);
        free(novo); // Libera o nó que foi parcialmente criado.
        return lista;
    }

    // Se tudo deu certo, liga o novo nó no início da lista.
    novo->prox = lista;
    return novo; // Retorna o novo início da lista.
}

void remove_usuario_corrigido(Emprestimo** lista, const char* user) {
    // Tratamento de casos extremos: verifica se os ponteiros são válidos.
    if (lista == NULL || *lista == NULL || user == NULL) {
        return;
    }

    Emprestimo* atual = *lista;
    Emprestimo* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->usuario, user) == 0) {
            // Desconecta o nó da lista
            if (anterior == NULL) { // O nó a ser removido é o primeiro.
                *lista = atual->prox;
            } else { // O nó está no meio ou no fim.
                anterior->prox = atual->prox;
            }

            // Liberação correta de todos os recursos:
            // 1. Libera a memória das strings internas.
            free(atual->usuario);
            free(atual->isbn);
            // 2. Libera a memória da própria estrutura do nó.
            free(atual);

            break; // Sai do loop após remover o primeiro encontrado.
        }
        anterior = atual;
        atual = atual->prox;
    }
}