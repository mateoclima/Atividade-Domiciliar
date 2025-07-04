#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

/* 
 A biblioteca relatou que frequentemente precisa:
    • Consultar empréstimos de um usuário específico
    • Remover empréstimos quando os livros são devolvidos
    • Navegar pela lista em ambas as direções para relatórios

 a) Considerando os requisitos apresentados, justifique qual tipo de lista seria mais adequado:
    • Lista simplesmente encadeada
    • Lista duplamente encadeada
    • Lista com nó cabeçalho
    • Lista circular

 Resposta: A lista duplamente encadeada, pois nela há cada elemento tem um ponteiro para o próximo
 elemento e um ponteiro para o elemento anterior.Assim, dado um elemento, роdemos acessar os dois elementos 
 adjacentes: o próximo e o anterior. Possibilitando a busca/navegamento bilateral pelos elementos com 
 complexidade O(1) para cada passo. Além de deixar a remoção também mais eficiente, pois, uma vez que o nó 
 a ser removido é encontrado, não precisamos de um ponteiro auxiliar para o "anterior", pois o próprio nó já o possui.

 A lista simplementes encadeada permite inserção e remoção eficientes, mas só se pode navegar para a frente (ponteiro->próximo). 
 Nesse contexto, navegar para trás exigiria percorrer a lista desde o início, o que é muito ineficiente (complexidade O(n)). 
 Portanto, é uma opção menos viavel de acordo com os requisitos.

 Ademais, a lista com nó cabeçalho simplifica a inserção e remoção (eliminando casos especiais para o início da lista),
 mas não resolve o problema da navegação para trás.

 Já a lista circular é útil para tarefas cíclicas, mas uma lista circular simples também não permite navegar para trás de forma eficiente.
*/

// Definição do tipo de dados para o empréstimo
typedef struct {
    char* codusuario;
    char* isbn_livro;
    int dtEmprestimo; // Data de emprestimo 
    int dtDevolucao;   // Data de emprestimo 
} Emprestimo;

// Nó da lista duplamente encadeada
typedef struct no_emprestimo {
    Emprestimo dados;
    struct no_emprestimo* prox;
    struct no_emprestimo* ant;
} NoEmprestimo;

// Estrutura da lista
typedef struct {
    NoEmprestimo* inicio;
    NoEmprestimo* fim;
    int tamanho;
} ListaEmprestimos;

// Protótipos das funções
ListaEmprestimos* lista_cria();
void lista_destroi(ListaEmprestimos** lista);
int lista_insere_ordenado(ListaEmprestimos* lista, Emprestimo dados); 
int lista_remove(ListaEmprestimos* lista, const char* codigo_usuario, const char* isbn);
void lista_imprime(ListaEmprestimos* lista);

// Referências para respostas:
// Introdução a Estrutura de Dados (Celes, Cerqueira e Dangel) páginas 134 a 151 e 185 a 195.
// Guia didático "Aula 2 Listas Estáticas e Listas Dinâmicas" disponíbilizado pelo Prof. MsC. Helcio.
#endif