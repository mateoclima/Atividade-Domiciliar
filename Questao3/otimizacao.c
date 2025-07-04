/*
    c) Proponha e implemente uma otimização para a função de remoção que permita remover todos 
    os empréstimos de um usuário (não apenas o primeiro encontrado) mantendo a eficiência adequada. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declaração da estrutura 
typedef struct emprestimo {
    char* usuario;
    char* isbn;
    struct emprestimo* prox;
} Emprestimo;


//Função modificada que remove todos os empréstimos de um usuário específico
void removeTodosEmprestimos(Emprestimo** lista, const char* user) {
    // Verifica se os ponteiros são válidos.
    if (lista == NULL || *lista == NULL || user == NULL) {
        return;
    }

    Emprestimo* atual = *lista;
    Emprestimo* anterior = NULL;

    // Percorre a lista inteira do início ao fim.
    while (atual != NULL) {

        // Verifica se o nó atual pertence ao usuário a ser removido.
        if (strcmp(atual->usuario, user) == 0) {
            Emprestimo* no_a_remover = atual; // Guarda o nó a ser removido.

            // Avança o ponteiro 'atual' para o próximo antes de remover o nó atual da memória. Isso evita o uso de
            //    ponteiro inválido.
            atual = atual->prox;

            // Desconecta o nó da lista.
            if (anterior == NULL) {
                // Caso especial: o nó a ser removido é o primeiro da lista.
                // O início da lista passa a ser o próximo nó.
                *lista = atual;
            } else {
                // O nó está no meio ou fim. O nó anterior agora aponta para o sucessor do nó removido.
                anterior->prox = atual;
            }

            // Libera a memória do nó removido de forma segura.
            free(no_a_remover->usuario);
            free(no_a_remover->isbn);
            free(no_a_remover);

            // O ponteiro 'anterior' não é atualizado, pois o nó que o precede continua sendo o mesmo para o novo 'atual'.

        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}
