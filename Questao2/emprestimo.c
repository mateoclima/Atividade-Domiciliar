#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimo.h"

/*
    b) Implemente a estrutura escolhida, incluindo:
    • Definição da estrutura de dados
    • Função de criação/inicialização
    • Função de inserção ordenada por data de empréstimo
    • Função de remoção por código de usuário E ISBN
*/

// Cria e inicializa uma lista de empréstimos vazia.
ListaEmprestimos* lista_cria() {
    // Aloca memória para a estrutura que controla a lista.
    ListaEmprestimos* nova_lista = (ListaEmprestimos*) malloc(sizeof(ListaEmprestimos));

    // Se a memória foi alocada com sucesso, inicializa os campos.
    if (nova_lista != NULL) {
        nova_lista->inicio = NULL;   // A lista começa sem nenhum nó.
        nova_lista->fim = NULL;      // A lista termina sem nenhum nó.
        nova_lista->tamanho = 0;     // O tamanho inicial é zero.
    }
    // Retorna o ponteiro para a nova lista.
    return nova_lista;
}

// Insere um novo empréstimo na lista, mantendo a ordem por data.
int lista_insere_ordenado(ListaEmprestimos* lista, Emprestimo dados) {
    // Retorna falha se a lista não existir.
    if (lista == NULL) return 0;

    // Aloca memória para o "nó" que vai guardar o empréstimo.
    NoEmprestimo* novo = (NoEmprestimo*) malloc(sizeof(NoEmprestimo));
    // Retorna falha se não conseguiu alocar memória.
    if (novo == NULL) return 0;

    // Copia os dados para o novo nó. 'strdup' aloca memória e copia a string.
    novo->dados.codusuario = strdup(dados.codusuario);
    novo->dados.isbn_livro = strdup(dados.isbn_livro);
    novo->dados.dtEmprestimo = dados.dtEmprestimo;
    novo->dados.dtDevolucao = dados.dtDevolucao;
    novo->prox = NULL; // O novo nó ainda não aponta para ninguém.
    novo->ant = NULL;  // O novo nó ainda não tem ninguém antes dele.

    // Se a cópia das strings falhou, libera a memória e retorna erro.
    if (novo->dados.codusuario == NULL || novo->dados.isbn_livro == NULL) {
        free(novo->dados.codusuario);
        free(novo->dados.isbn_livro);
        free(novo);
        return 0;
    }

    // CASO 1: A lista está vazia.
    if (lista->inicio == NULL) {
        lista->inicio = novo; // O novo nó é o início.
        lista->fim = novo;    // O novo nó também é o fim.
    }
    // CASO 2: Inserir no início da lista (a data do novo é a mais antiga).
    else if (novo->dados.dtEmprestimo < lista->inicio->dados.dtEmprestimo) {
        novo->prox = lista->inicio; // O novo aponta para o antigo início.
        lista->inicio->ant = novo;  // O antigo início aponta para o novo.
        lista->inicio = novo;       // A lista agora começa no novo nó.
    }
    // CASO 3: Inserir no meio ou no fim da lista.
    else {
        NoEmprestimo* atual = lista->inicio;
        // Percorre a lista para encontrar a posição correta.
        while (atual->prox != NULL && atual->prox->dados.dtEmprestimo < novo->dados.dtEmprestimo) {
            atual = atual->prox;
        }
        
        // Insere o novo nó após o 'atual'.
        novo->prox = atual->prox;
        if (atual->prox != NULL) { // Se não for o último elemento,
            atual->prox->ant = novo; // ajusta o ponteiro 'ant' do próximo.
        } else { // Se for o último elemento,
            lista->fim = novo; // atualiza o fim da lista.
        }
        atual->prox = novo; // O 'atual' aponta para o novo.
        novo->ant = atual;  // E o novo aponta de volta para o 'atual'.
    }
    
    // Aumenta o contador de tamanho da lista.
    lista->tamanho++;
    return 1; // Retorna 1 para indicar sucesso.
}

// Remove um empréstimo da lista, buscando por usuário e ISBN.
int lista_remove(ListaEmprestimos* lista, const char* codigo_usuario, const char* isbn) {
    // Retorna falha se a lista for nula ou estiver vazia.
    if (lista == NULL || lista->inicio == NULL) return 0;

    NoEmprestimo* atual = lista->inicio;
    // Percorre a lista procurando o empréstimo para remover.
    while (atual != NULL) {
        // 'strcmp' compara strings. Retorna 0 se forem iguais.
        if (strcmp(atual->dados.codusuario, codigo_usuario) == 0 && strcmp(atual->dados.isbn_livro, isbn) == 0) {
            
            // Se o nó a remover não é o primeiro, ajusta o ponteiro do anterior.
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else { // Se for o primeiro, o início da lista muda.
                lista->inicio = atual->prox;
            }

            // Se o nó a remover não é o último, ajusta o ponteiro do próximo.
            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            } else { // Se for o último, o fim da lista muda.
                lista->fim = atual->ant;
            }

            // Libera a memória das strings e, em seguida, do nó.
            free(atual->dados.codusuario);
            free(atual->dados.isbn_livro);
            free(atual);
            
            // Diminui o tamanho da lista.
            lista->tamanho--;
            return 1; // Retorna sucesso.
        }
        atual = atual->prox; // Continua para o próximo nó.
    }

    return 0; // Retorna 0 se não encontrou o empréstimo.
}


// Libera toda a memória usada pela lista.
void lista_destroi(ListaEmprestimos** lista) {
    // Retorna se o ponteiro da lista for nulo.
    if (lista == NULL || *lista == NULL) return;

    NoEmprestimo* atual = (*lista)->inicio;
    NoEmprestimo* proximo;

    // Percorre todos os nós da lista.
    while (atual != NULL) {
        proximo = atual->prox; // Guarda o próximo nó antes de apagar o atual.
        
        // Libera a memória das strings dentro do nó.
        free(atual->dados.codusuario);
        free(atual->dados.isbn_livro);
        // Libera a memória do nó em si.
        free(atual);
        
        atual = proximo; // Avança para o próximo nó.
    }
    // Por fim, libera a memória da estrutura de controle da lista.
    free(*lista);
    // Aponta o ponteiro original para NULL para evitar erros.
    *lista = NULL;
}

// Imprime o conteúdo da lista (função auxiliar para testes).
void lista_imprime(ListaEmprestimos* lista) {
    if (lista == NULL) {
        printf("Lista invalida.\n");
        return;
    }
    printf("--- Lista de Emprestimos (Tamanho: %d) ---\n", lista->tamanho);
    NoEmprestimo* atual = lista->inicio;
    if (atual == NULL) {
        printf("A lista esta vazia.\n");
    } else {
        // Percorre a lista e imprime os dados de cada empréstimo.
        while (atual != NULL) {
            printf("  Usuario: %s | ISBN: %s | Data Emp: %d\n",
                   atual->dados.codusuario, atual->dados.isbn_livro, atual->dados.dtEmprestimo);
            atual = atual->prox;
        }
    }
    printf("-----------------------------------------\n\n");
}

/*
    c) Analise criticamente sua implementação:

    1. Qual a complexidade de cada operação implementada?
    - lista_cria: O(1). Custo constante, não depende do tamanho da lista.
    - lista_insere_ordenado: O(n). Custo linear, pois no pior caso percorre a lista inteira para achar a posição.
    - lista_remove: O(n). Custo linear, dominado pela busca do elemento a ser removido.
    - lista_destroi: O(n). Custo linear, pois precisa visitar todos os 'n' nós para liberar a memória.
 
    2. Quais são os pontos fortes e limitações da estrutura escolhida?
    Pontos Fortes:
    - Navegação eficiente nos dois sentidos (frente/trás), conforme pedido no problema.
    - Remoção em tempo O(1) uma vez que o nó é localizado, graças ao ponteiro "ant".
    - Alocação dinâmica de memória, usando apenas o espaço necessário.

    Limitações:
    - Acesso por índice (ex: "buscar o 50º elemento") é lento, com custo O(n).
    - Consome mais memória que uma lista simples por causa do ponteiro "ant" em cada nó.
    
    3. Em que cenários sua implementação seria inadequada?
    - Cenário 1: Acesso aleatório frequente.
    Se o sistema precisasse acessar elementos por sua posição muitas vezes, um vetor (array) com acesso O(1) seria muito mais rápido.
 
    - Cenário 2: Grande volume de dados com necessidade de busca rápida.
    Para uma base com milhares de empréstimos, a busca O(n) seria um gargalo.
    Uma tabela hash (com busca O(1)) seria a estrutura idea.
 
    - Cenário 3: Consultas complexas por faixas de dados.
    Se fosse preciso buscar "todos os empréstimos de um mês", a lista seria ineficiente.
    Estruturas como árvores binária de busca (balanceadas) seriam mais adequadas.

*/
