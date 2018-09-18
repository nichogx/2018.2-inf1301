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
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar grafos.
*     O grafo possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore. // TODO CHANGE
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

	/* faltou memória ao alocar dados */
	GRF_CondRetFaltouMemoria = 1,

	/* grafo está vazio */
	GRF_CondRetGrafoVazio = 2,

	/* não há grafo, não é possível realizar operação */
	GRF_CondRetGrafoNaoExiste = 3,

	/* erro decorrente da função do módulo lista */
	GRF_CondRetErroAoCriarLista = 4,

	/* grafo já existe, não é possível criar outro */
	GRF_CondRetGrafoJaExiste = 5

} GRF_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabeça de um grafo
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
*  $FC Função: GRF Destruir Grafo
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

#undef GRAFO_EXT

/********** Fim do módulo de definição: Módulo Grafo **********/

#else
#endif
