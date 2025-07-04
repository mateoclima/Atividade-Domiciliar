#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "emprestimo.h" 

/*
 a) Projete a função principal (main) que demonstre a integração entre o TAD Livro e a Lista de Empréstimos. 
 Sua implementação deve mostrar:
    • Criação de pelo menos 3 livros
    • Cadastro de pelo menos 5 empréstimos
    • Consulta de empréstimos por usuário
    • Remoção de um empréstimo
    • Liberação adequada de toda a memória
*/

// Função auxiliar para imprimir a lista
void consultar_por_usuario(ListaEmprestimos* lista, const char* codigo_usuario) {
    if (lista == NULL || codigo_usuario == NULL) return;

    printf("\n>>> Consultando emprestimos para o usuario: %s\n", codigo_usuario);
    int encontrados = 0;
    // O tipo NoEmprestimo foi definido em emprestimo.h
    NoEmprestimo* atual = lista->inicio;

    while (atual != NULL) {
        // O campo 'codusuario' foi definido na struct Emprestimo
        // E a função strcmp foi declarada em <string.h>, incluída em emprestimo.c
        if (strcmp(atual->dados.codusuario, codigo_usuario) == 0) {
            printf("  - Livro (ISBN: %s), Devolucao: %d\n",
                   atual->dados.isbn_livro, atual->dados.dtDevolucao);
            encontrados++;
        }
        atual = atual->prox;
    }

    if (encontrados == 0) {
        printf("  Nenhum emprestimo encontrado para este usuario.\n");
    }
}

int main() {
    printf("--- Iniciando Sistema de Gerenciamento da Biblioteca ---\n\n");

    printf("1. Criando acervo de livros...\n");
    // A função criarLivro foi definida em livro.h e implementada em livro.c
    Livro* livro1 = criarLivro("978-85-7608-952-8", "Use a Cabeca! C", "David Griffiths", 2016, 608);
    Livro* livro2 = criarLivro("978-85-7393-360-1", "Estruturas de Dados", "Lilian Markenzon", 2011, 264);
    Livro* livro3 = criarLivro("978-01-3449-416-6", "C How to Program", "Paul Deitel", 2018, 928);

    if (livro1 == NULL || livro2 == NULL || livro3 == NULL) {
        printf("Erro fatal ao criar livros. Encerrando.\n");
        return 1;
    }
    printf("   -> 3 livros criados com sucesso!\n\n");


    printf("2. Cadastrando novos emprestimos...\n");
    // A função lista_cria foi definida em emprestimo.h e implementada em emprestimo.c
    ListaEmprestimos* lista_de_emprestimos = lista_cria();

    // A struct Emprestimo foi definida em emprestimo.h
    Emprestimo emp1 = { "user001", livro1->isbn, 20250701, 20250715 };
    Emprestimo emp2 = { "user002", livro3->isbn, 20250702, 20250716 };
    Emprestimo emp3 = { "user001", livro2->isbn, 20250703, 20250717 }; // user001 pegou outro livro
    Emprestimo emp4 = { "user003", livro1->isbn, 20250620, 20250704 }; // Data mais antiga
    Emprestimo emp5 = { "user001", livro3->isbn, 20250704, 20250718 }; // user001 pegou um terceiro livro

    // A função lista_insere_ordenado foi definida em emprestimo.h e implementada em emprestimo.c
    lista_insere_ordenado(lista_de_emprestimos, emp4);
    lista_insere_ordenado(lista_de_emprestimos, emp1);
    lista_insere_ordenado(lista_de_emprestimos, emp2);
    lista_insere_ordenado(lista_de_emprestimos, emp3);
    lista_insere_ordenado(lista_de_emprestimos, emp5);

    printf("   -> 5 emprestimos cadastrados.\n");
    lista_imprime(lista_de_emprestimos);


    consultar_por_usuario(lista_de_emprestimos, "user001");
    consultar_por_usuario(lista_de_emprestimos, "user004"); // Um usuário que não existe


    printf("\n>>> Removendo o emprestimo do usuario 'user001' com o livro ISBN '%s'...\n", livro2->isbn);
    // A função lista_remove foi definida em emprestimo.h e implementada em emprestimo.c
    lista_remove(lista_de_emprestimos, "user001", livro2->isbn);
    printf("   -> Emprestimo removido.\n");
    lista_imprime(lista_de_emprestimos);


    printf("5. Encerrando o sistema e liberando toda a memoria...\n");

    // Primeiro, libera a memória da lista de empréstimos.
    // A função lista_destroi percorre todos os nós e libera as strings e o próprio nó.
    lista_destroi(&lista_de_emprestimos);
    printf("   -> Memoria da lista de emprestimos liberada.\n");

    // Em seguida, libera a memória dos livros que foram criados no início.
    liberarLivro(&livro1);
    liberarLivro(&livro2);
    liberarLivro(&livro3);
    printf("   -> Memoria dos livros liberada.\n");

    printf("\n--- Sistema encerrado com sucesso. Toda a memoria foi liberada. ---\n");

    return 0;
}
/*
 b) Avalie criticamente sua arquitetura respondendo:
    • Quais seriam as limitações do sistema atual para uma biblioteca com 100.000 livros e 10.000 usuários ativos?
    • Como você modificaria a implementação para melhorar a escalabilidade?
    • Que outras estruturas de dados poderiam ser utilizadas para otimizar operações específicas?
*/

/* Limitações para 100.000 livros e 10.000 usuários: 
    • LENTIDÃO NAS OPERAÇÕES: A lista de empréstimos ListaEmprestimos tem busca com complexidade O(n). 
    Com milhares de empréstimos, operações como remover ou consultar um usuário específico se tornam muito lentas.

    • BUSCA DE LIVROS INVIÁVEL: O sistema atual não possui uma estrutura de dados para gerenciar os 100.000 livros. 
    Encontrar um livro por ISBN para um novo empréstimo exigiria uma busca linear em todo o acervo, o que é impraticável.
*/

/* Como você modificaria a implementação para melhorar a escalabilidade?: 
    • Substituir a lista de emprestimos: Trocar a lista duplamente encadeada por uma tabela hash. 
    Isso permitiria buscar e remover empréstimos em tempo médio O(1).
    
    • Implementar um catálogo de livros: Implementar um novo TAD "Catalogo", também usando uma
    tabela hash, para indexar os livros por ISBN e permitir buscas em tempo O(1).
*/

/* Que outras estruturas de dados poderiam ser utilizadas para otimizar operações específicas?: 
    • Árvore binária de busca (balanceada): Seria ideal para os empréstimos se relatórios ordenados
    por data fossem uma necessidade frequente, garantindo operações em O(log n).
    
*/

/* 
 c) Proponha uma melhoria específica para o sistema, implementando um pequeno trecho de código que demonstre sua ideia. 
    Justifique como essa melhoria impactaria positivamente o desempenho ou a funcionalidade do sistema
    
    Resposta: A melhoria mais impactante é a criação de um TAD "Catalogo" para gerenciar o acervo de livros. 
    Internamente, este TAD usaria uma Tabela Hash onde a chave de busca seria o ISBN do livro.

    Justificativa do Impacto Positivo:
    - O desempenho: A operação de encontrar um livro no acervo, que é essencial para fazer um novo empréstimo, 
    teria seu tempo de execução reduzido de O(N)(onde N=100.000) para O(1) em média. Isso torna o sistema viável e rápido
    em uma escala real.

    - A organização: Centraliza todo o gerenciamento do acervo em um módulo coeso.

    Trecho de código demonstrativo (exemplo no main):
    "início do main"
    Catalogo* catalogo = catalogo_cria();
    catalogo_adiciona_livro(catalogo, livro1);
    catalogo_adiciona_livro(catalogo, livro2);

    "na hora de fazer um empréstimo"
    const char* isbn_desejado = "978-85-7393-360-1";
    Livro* livro_encontrado = catalogo_busca_por_isbn(catalogo, isbn_desejado);

    if (livro_encontrado != NULL) {
    // Segue com o empréstimo
    }

*/
