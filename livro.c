#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h" 

/* 
    b) Implemente duas das funções projetadas no item anterior, demonstrando:
    • Tratamento de erros adequado
    • Gerenciamento correto de memória
    • Comentários explicativos 
*/

// Descrição da função: Aloca memória para um novo livro e inicializa seus campos.
Livro* criarLivro(const char* isbn, const char* titulo, const char* autor, int ano, int paginas) {
    // Gerenciamento de Memória: Aloca um único bloco de memória para toda a estrutura do livro.
    Livro* novo_livro = (Livro*) malloc(sizeof(Livro));

    // Tratamento de Erros: Verifica se a alocação de memória foi bem-sucedida.
    // Se malloc retorna NULL, significa que não há memória disponível.
    if (novo_livro == NULL) {
        printf("Erro ao alocar memoria para o livro");
        return NULL; // Encerra a função.
    }

    // Cópia Segura dos Dados: Usa-se strncpy para copiar os dados para os arrays.
    // Copia o ISBN, garantindo que o último byte seja '\0' para terminação da string.
    strncpy(novo_livro->isbn, isbn, MAX_ISBN - 1);
    novo_livro->isbn[MAX_ISBN - 1] = '\0';

    // Copia o Título
    strncpy(novo_livro->titulo, titulo, MAX_TITULO - 1);
    novo_livro->titulo[MAX_TITULO - 1] = '\0';

    // Copia o Autor
    strncpy(novo_livro->autor, autor, MAX_AUTOR - 1);
    novo_livro->autor[MAX_AUTOR - 1] = '\0';


    // Inicialização dos campos numéricos
    novo_livro->ano = ano;
    novo_livro->totalPaginas = paginas;

    // Retorna o ponteiro para a estrutura do livro pronta para ser usada.
    return novo_livro;
}

// Implementação da função de destruição
void liberarLivro(Livro** l) {
    if (l != NULL && *l != NULL) {
        // Libera apenas o bloco de memória da struct.
        free(*l);
        // Medida de segurança para evitar uso do ponteiro após liberação.
        *l = NULL;
    }
}