#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo Grafo
*
*  Arquivo:                 GRAFO.H
*  Letras identificadoras:  GRF
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar grafos.
*     O grafo possui uma cabe�a que cont�m uma refer�ncia para a ra�z da
*     �rvore e outra para um n� corrente da �rvore. // TODO CHANGE
*     A cada momento o m�dulo admite no m�ximo um �nico grafo.
*     Ao iniciar a execu��o do programa n�o existe grafo.
*     O grafo poder� estar vazio. Neste caso o n� corrente
*     ser� nulo, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se o grafo estiver vazio.
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

	/* faltou mem�ria ao alocar dados */
	GRF_CondRetFaltouMemoria = 1,

	/* grafo est� vazio */
	GRF_CondRetGrafoVazio = 2,

	/* n�o h� grafo, n�o � poss�vel realizar opera��o */
	GRF_CondRetGrafoNaoExiste = 3,

	/* erro decorrente da fun��o do m�dulo lista */
	GRF_CondRetErroAoCriarLista = 4,

	/* grafo j� existe, n�o � poss�vel criar outro */
	GRF_CondRetGrafoJaExiste = 5,

	/* grafo j� existente, por�m algum vertice nao existe */
	GRF_CondRetVerticeNaoExiste = 6,

	/* grafo ja existente, porem nao existe uma suposta aresta */
	GRF_CondRetArestaNaoExiste = 7

} GRF_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabe�a de um grafo
*
*
***********************************************************************/

typedef struct GRF_tgGrafo GRF_tpGrafo;

/***********************************************************************
*
*  $FC Fun��o: GRF Criar Grafo
*
*  $ED Descri��o da fun��o
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
*  $FC Fun��o: GRF Destruir Grafo
*
*  $ED Descri��o da fun��o
*     Destr�i o grafo.
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*
***********************************************************************/

GRF_tpCondRet GRF_DestruirGrafo(void);

/************************************************************************
*
*	$FC Função: GRF Obter Valor Corrente
*
*	$ED Descrição da função
*		Obtem o conteudo do vertice corrente.
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*
*************************************************************************/

GRF_tpCondRet GRF_ObterValorCorrente(void);

/************************************************************************
*
*	$FC Função: GRF Alterar Valor Corrente
*
*	$ED Descrição da função
*		Altera o conteudo do vertice corrente.
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*
*************************************************************************/

GRF_tpCondRet GRF_AlterarValorCorrente(void *newContent);

/************************************************************************
*
*	$FC Função: GRF Ir Vertice
*
*	$ED Descrição da função
*		O vertice corrente vira o vertice contendo o conteudo.
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*		GRF_CondRetVerticeNaoExiste
*
*************************************************************************/

GRF_tpCondRet GRF_IrVertice(void *content);

/************************************************************************
*
*	$FC Função: GRF Inserir Vertice
*
*	$ED Descrição da função
*		Insere um vertice na lista de vertices do grafo.
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*		GRF_CondRetFaltouMemoria
*
*************************************************************************/

GRF_tpCondRet GRF_InserirVertice(void * content);

/************************************************************************
*
*	$FC Função: GRF Remover Corrente
*
*	$ED Descrição da função
*		Remove o vertice corrente que contem o conteudo 
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*		GRF_CondRetVerticeNaoExiste
*
*************************************************************************/

GRF_tpCondRet GRF_RemoverVertice(void *contentDestino);

/************************************************************************
*
*	$FC Função: GRF Adicionar Origem
*
*	$ED Descrição da função
*		Adiciona um vertice origem com o conteudo void no grafo
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*		GRF_CondRetFaltouMemoria
*
*************************************************************************/

GRF_tpCondRet GRF_AdicionarOrigem(void * contentOrigem);

/************************************************************************
*
*	$FC Função: GRF Remover Origem
*
*	$ED Descrição da função
*		Remove o vertice origem corrente que contem o conteudo do grafo 
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*		GRF_CondRetVerticeNaoExiste
*
*************************************************************************/

GRF_tpCondRet GRF_RemoverOrigem(void *contentOrigem, char destino);

/************************************************************************
*
*	$FC Função: GRF Adicionar Aresta
*
*	$ED Descrição da função
*		Adiciona uma aresta ao vertice corrente 
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*		GRF_CondRetVerticeNaoExiste
*		GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_AdicionarAresta(char nomeAresta);

/************************************************************************
*
*	$FC Função: GRF Remover Aresta
*
*	$ED Descrição da função
*		Remove uma aresta corrente do vertice corrente 
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoNaoExiste
*		GRF_CondRetVerticeNaoExiste
*		GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_RemoverAresta(char nomeAresta);

/************************************************************************
*
*	$FC Função: GRF Esvaziar Grafo
*
*	$ED Descrição da função
*		Esvazia as listas e destroi o vertice corrente do grafo 
*
*	$FV Valor Retornado
*		GRF_CondRetOK
*		GRF_CondRetGrafoVazio	
*
*************************************************************************/

GRF_tpCondRet GRF_EsvaziarGrafo(void);

#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: M�dulo Grafo **********/

#else
#endif