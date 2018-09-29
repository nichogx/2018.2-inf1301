#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Grafo
*
*  Arquivo:                 GRAFO.H
*  Letras identificadoras:  GRF
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       0.51   ngx   28/09/2018 Erros corrigidos.
*                               Atualização da documentação e nomeação de parâmetros.
*       0.50   ngx   28/09/2018 Novas funções de acesso para caminhar sobre as arestas.
*       0.42   ngx   28/09/2018 Pequenas modificações nos parâmetros das funções
*                               de acesso.
*       0.40   ngx   27/09/2018 Continuação e recodificação do módulo e suas funções.
*                               Modificações na estrutura.
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar grafos.
*     O grafo possui uma cabeça que contém uma referência para a raíz da
*     Árvore e outra para um nó corrente da Árvore. // TODO CHANGE
*     A cada momento o módulo admite no máximo um único grafo.
*     Ao iniciar a execução do programa não existe grafo.
*     O grafo poderá estar vazio. Neste caso o nó corrente
*     será nulo, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se o grafo estiver vazio.
*
***************************************************************************/

#if defined (GRAFO_OWN)
#define GRAFO_EXT
#else
#define GRAFO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: GRF Condicoes de retorno
*
*
***********************************************************************/

typedef enum {
	/* executou corretamente */
	GRF_CondRetOK = 0,

	/* faltou mem?ria ao alocar dados */
	GRF_CondRetFaltouMemoria = 1,

	/* grafo est? vazio */
	GRF_CondRetGrafoVazio = 2,

	/* n?o h? grafo, n?o ? poss?vel realizar opera??o */
	GRF_CondRetGrafoNaoExiste = 3,

	/* erro decorrente da fun??o do m?dulo lista */
	GRF_CondRetErroAoCriarLista = 4,

	/* grafo j? existe, n?o ? poss?vel criar outro */
	GRF_CondRetGrafoJaExiste = 5,

	/* grafo j? existente, por?m algum vertice nao existe */
	GRF_CondRetVerticeNaoExiste = 6,

	/* grafo ja existente, porem nao existe uma suposta aresta */
	GRF_CondRetArestaNaoExiste = 7,

	/* erro na estrutura */
	GRF_CondRetErroEstrutura = 8

} GRF_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabe?a de um grafo
*
*
***********************************************************************/

typedef struct GRF_tgGrafo GRF_tpGrafo;

/***********************************************************************
*
*  $FC Função: GRF Criar Grafo
*
*  $ED Descrição da função
*     Cria um novo grafo vazio.
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoJaExiste
*     GRF_CondRetFaltouMemoria
*     GRF_CondRetErroAoCriarLista
*
***********************************************************************/

GRF_tpCondRet GRF_CriarGrafo(void);

/***********************************************************************
*
*  $FC Fuñção: GRF Destruir Grafo
*
*  $ED Descrição da função
*     Destrói o grafo.
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*
***********************************************************************/

GRF_tpCondRet GRF_DestruirGrafo(void);

/************************************************************************
*
*  $FC Função: GRF Obter Valor Corrente
*
*  $ED Descrição da função
*     Obtem o conteudo do vertice corrente.
*
*  $EP Parâmetros
*     conteudo - endereço do ponteiro que apontará o valor corrente
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*
*************************************************************************/

GRF_tpCondRet GRF_ObterValorCorrente(void **conteudo);

/************************************************************************
*
*  $FC Função: GRF Alterar Valor Corrente
*
*  $ED Descrição da função
*     Altera o conteudo do vertice corrente.
*
*  $EP Parâmetros
*     novoConteudo - conteúdo que será o novo do corrente
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*
*************************************************************************/

GRF_tpCondRet GRF_AlterarValorCorrente(void *novoConteudo);

/************************************************************************
*
*  $FC Função: GRF Ir Vertice
*
*  $ED Descrição da função
*     O vertice corrente vira o vertice que contém o conteudo.
*     A função compara ponteiros, não conteúdo apontado.
*
*  $EP Parâmetros
*     conteudoBuscado - conteúdo que será comparado
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetVerticeNaoExiste
*
*************************************************************************/

GRF_tpCondRet GRF_IrVertice(void *conteudoBuscado);

/************************************************************************
*
*  $FC Função: GRF Inserir Vertice
*
*  $ED Descrição da função
*     Insere um vertice na lista de vertices do grafo.
*     O vértice inserido passa a ser o corrente.
*
*  $EP Parâmetros
*     pConteudo - conteudo do novo vértice a ser inserido
*     ExcluirValor - ponteiro para função que destrói (libera espaço de memória)
*                    o conteúdo.
*                    pode ser NULL caso não seja necessário liberar
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetFaltouMemoria
*     GRF_CondRetErroAoCriarLista
*     GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_InserirVertice(void *pConteudo,
                                 void(*ExcluirValor)(void *pConteudo));

/************************************************************************
*
*  $FC Função: GRF Remover Corrente
*
*  $ED Descrição da função
*     Remove o vertice corrente
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*
*************************************************************************/

GRF_tpCondRet GRF_RemoverVerticeCorr(void);

/************************************************************************
*
*  $FC Função: GRF Adicionar Origem
*
*  $ED Descrição da função
*     Adiciona um vertice e também torna-o origem.
*     O vértice inserido passa a ser o corrente.
*
*  $EP Parâmetros
*     pConteudo - conteudo do novo vértice a ser inserido
*     ExcluirValor - ponteiro para função que destrói (libera espaço de memória)
*                    o conteúdo.
*                    pode ser NULL caso não seja necessário liberar
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetFaltouMemoria
*     GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_AdicionarOrigem(void *pConteudo,
                                  void(*ExcluirValor)(void *pConteudo));

/************************************************************************
*
*  $FC Função: GRF Adicionar Aresta
*
*  $ED Descrição da função
*     Adiciona uma aresta ao vertice corrente.
*     Não é feita verificação se já existe uma aresta com esse ID.
*     Recomenda-se manter os IDs de aresta únicos.
*
*     Os conteúdos recebidos serão comparados com todos os vértices do grafo.
*     Caso eles sejam encontrados, adiciona-se uma aresta.
*     O conteúdo de cada vértice é comparado por ponteiros, não conteúdo apontado.
*
*  $EP Parâmetros
*     idAresta - caractere que será o ID da aresta
*     contOrigem - conteúdo do vértice que será a origem da aresta (esse será buscado)
*     contOrigem - conteúdo do vértice que será o destino da aresta (esse será buscado)
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetVerticeNaoExiste
*     GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_AdicionarAresta(char idAresta, void *contOrigem,
                                  void *contDestino);

/************************************************************************
*
*  $FC Função: GRF Andar
*
*  $ED Descrição da função
*     Avança o vértice corrente pela aresta com ID recebido.
*     A aresta precisa estar na lista de sucessores do vértice corrente.
*
*     Caso haja mais de uma aresta com o mesmo ID, opera na primeira
*     encontrada com esse ID.
*     Recomenda-se manter os IDs de aresta únicos.
*
*  $EP Parâmetros
*     idAresta - caractere que é o ID da aresta
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetArestaNaoExiste
*     GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_Andar(char idAresta);

/************************************************************************
*
*  $FC Função: GRF Voltar
*
*  $ED Descrição da função
*     Volta o vértice corrente pela aresta com ID recebido.
*     A aresta precisa estar na lista de antecessores do vértice corrente.
*
*     Caso haja mais de uma aresta com o mesmo ID, opera na primeira
*     encontrada com esse ID.
*     Recomenda-se manter os IDs de aresta únicos.
*
*  $EP Parâmetros
*     idAresta - caractere que é o ID da aresta
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetArestaNaoExiste
*     GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_Voltar(char idAresta);

/************************************************************************
*
*  $FC Função: GRF Remover Aresta
*
*  $ED Descrição da função
*     Remove aresta com o ID recebido
*     Não importa se essa aresta está ligada ao vértice corrente ou não.
*
*     Caso haja mais de uma aresta com o mesmo ID, opera na primeira
*     encontrada com esse ID.
*     Recomenda-se manter os IDs de aresta únicos.
*
*  $EP Parâmetros
*     idAresta - caractere que é o ID da aresta
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetVerticeNaoExiste
*     GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_RemoverAresta(char nomeAresta);

/************************************************************************
*
*  $FC Função: GRF Esvaziar Grafo
*
*  $ED Descrição da função
*     Esvazia o grafo, liberando espaços de memória e deixando-o
*     como se tivesse acabado de ser criado.
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoVazio
*     GRF_CondRetGrafoNaoExiste
*
*************************************************************************/

GRF_tpCondRet GRF_EsvaziarGrafo(void);

#undef GRAFO_EXT

/********** Fim do m?dulo de defini??o: M?dulo Grafo **********/

#else
#endif