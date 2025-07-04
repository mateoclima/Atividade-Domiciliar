#ifndef LIVRO_H
#define LIVRO_H

/* 
    a) Projete completamente o TAD Livro seguindo as boas práticas estudadas. Sua resposta deve incluir:
    • Arquivo de interface (.h) com comentários adequados
    • Estrutura de dados escolhida e justificativa
    • Protótipos de pelo menos 6 funções essenciais 
*/

//Variaveis Globais
#define MAX_TITULO 100 //Define valor da variavel que representa o número máximo de caracteres para o titulo do Livro
#define MAX_AUTOR 100 //Define valor da variavel que representa o número máximo de caracteres para o nome do autor do Livro
#define MAX_ISBN 14 //Define valor da variavel que representa o número máximo de caracteres para o codigo isbn do Livro


/*Resposta: Para o desenvolvimento de programas mais complexos, surge
uma maior nescessidade de abstração para a representação de "objetos" em dados.
Na linguagem C, esse tipo de representação é permitido definir um tipo de dado cujos campos
são compostos por diversos tipos de dados mais simples (int, char, float, string, entre outros),
sendo este tipo de dado chamado struct (em português, estrutura) cuja sua função é
basicamente agrupar diversas variáveis dentro de um único contexto.*/


typedef struct livro_struct {
    char titulo[MAX_TITULO]; //Variavel responsável por guardar o nome/titulo do Livro
    char autor[MAX_AUTOR]; //Variavel responsável por guardar o nome do autor do Livro
    int ano; //Variavel responsável por guardar o de publicação do Livro
    char isbn[MAX_ISBN]; //Variavel responsável por guardar o código ISBN do Livro
    int totalPaginas; //Variavel responsável por guardar o número total de páginas do Livro
} Livro;



// Prototipos das funções:
//Função que cria uma nova instância de um Livro.
Livro* criarLivro(const char* isbn, const char* titulo, const char* autor, int ano, int paginas);

//Função que libera toda a memória associada a um Livro.
void liberarLivro(Livro** l);

//Função que imprime as informações de um livro de forma formatada.
void exibirLivro(Livro* l);

//Função que obtém o ano de publicação de um livro.
int consultarAno(Livro* l);

//Função que obtém o título de um livro
void consultarTitulo(Livro* l, char* buffer);

//Função que compara o isbn de um livro com uma string fornecida.
int compararIsbn(Livro* l, const char* comparar);

/*
    c) Explique detalhadamente como o princípio do encapsulamento é aplicado em sua
    implementação e quais benefícios isso traz para:
    • Manutenibilidade do código
    • Reutilização em outros projetos
    • Proteção contra uso inadequado 
*/

/* Resposta: O princípio do encapsulamento é aplicado na implementação do TAD 

• Ficheiro: O arquivo livro.h serve como a interface, definindo a estrutura de dados Livro e os protótipos das funções que podem manipulá-la, 
como criarLivro e liberarLivro. Ele descreve o que o TAD pode fazer. Já o arquivo livro.c contém a implementação privada, ou seja, o código 
que de fato executa as operações, como a alocação de memória em criarLivro. Ele esconde como o TAD funciona.

Isso traz os seguintes benefícios:
• Manutenibilidade do código: As manutenções, como a correção de um bug ou a otimização de uma função, são feitas apenas no ficheiro livro.c. 
Desde que a interface em livro.h não mude, as outras partes do sistema que usam o TAD não precisam ser alteradas, o que centraliza e 
simplifica o processo.

• Reutilização em outros projetos: O conjunto livro.h e livro.c forma um componente de "Livro" autossuficiente. Ele pode ser facilmente 
transportado e reutilizado em qualquer outro projeto que necessite manipular livros, evitando a reescrita de código e acelerando o desenvolvimento.

• Proteção contra uso inadequado: As funções da interface atuam como "guardiãs" dos dados. A função criarLivro garante que toda instância 
de Livro seja criada corretamente, com a memória devidamente alocada. A função liberarLivro garante que a memória seja liberada de forma segura,
protegendo o programador de erros comuns como vazamentos de memória ou tentativas de liberar memória de forma incorreta. Isso impede a
manipulação direta e insegura dos dados, garantindo a integridade da estrutura.
*/

// Referências para respostas:
// Introdução a Estrutura de Dados (Celes, Cerqueira e Dangel) páginas 64 a 67, 98 a 104 e 123 a 126.
// Guia didático "Aula1-Tipos-Abstratos-Dados-Modularização-C" disponíbilizado pelo Prof. MsC. Helcio.
// Atividade "Implementações de Listas" disponíbilizado pelo Prof. MsC. Helcio.
#endif
