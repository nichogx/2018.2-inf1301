#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo V�rtice
*
*  Arquivo:                 VERTICE.H
*  Letras identificadoras:  VER
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   ngx   30/09/2018 Vers�o de entrega.
*       0.58   ngx   29/09/2018 Atualiza��o da documenta��o e adi��o de
*                               assertivas de entrada e sa�da.
*       0.55   ngx   28/09/2018 Separar libera��o e destrui��o do v�rtice
*       0.50   ngx   28/09/2018 M�dulo funciona como esperado
*       0.40   ngx   27/09/2018 Continua��o da codifica��o do m�dulo.
*                               Modifica��es na estrutura.
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     modificar vertices.
*     Um v�rtice possui conte�do, uma lista de antecessores e uma lista de
*     sucessores.
*     Um v�rtice tem seu conte�do e listas adicionados na cria��o.
*
***************************************************************************/

#if defined (VERTICE_OWN)
#define VERTICE_EXT
#else
#define VERTICE_EXT extern
#endif

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: VER Condicoes de retorno
*
*
***********************************************************************/

typedef enum {
	/* executou corretamente */
	VER_CondRetOK = 0,

	/* faltou mem�ria ao alocar dados */
	VER_CondRetFaltouMemoria = 1,

	/* n�o h� v�rtice, n�o � poss�vel realizar opera��o */
	VER_CondRetVerticeNaoExiste = 2,

	/* erro decorrente da fun��o do m�dulo lista */
	VER_CondRetErroModuloLista = 3,

	/* ligacao a ser removida nao foi encontrada */
	VER_LigacaoNaoEncontrada = 4,

	/*aresta nao foi encontrada */
	VER_CondRetArestaNaoExiste = 5

} VER_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor de um v�rtice
*
*
***********************************************************************/

typedef struct VER_tgVertice VER_tpVertice;

/***********************************************************************
*
*  $FC Fun��o: VER Criar v�rtice
*
*  $ED Descri��o da fun��o
*     Cria um novo v�rtice vazio e guarda em um ponteiro recebido.
*     O endere�o que esse ponteiro guardava anteriormente ser� perdido.
*
*  $EP Par�metros
*     pDest - endere�o do ponteiro onde ser� guardado o v�rtice criado.
*     pConteudo - conte�do a colocar no v�rtice.
*     ExcluirValor - ponteiro para fun��o que libera pConteudo. Pode ser NULL se
*                    n�o for necess�rio liberar.
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido n�o aponta outro v�rtice j� criado.
*     A fun��o ExcluirValor recebida libera a mem�ria de pConteudo.
*     O ponteiro pConteudo � um ponteiro para o conte�do que ser� inserido.
*
*  $AS Assertivas de Sa�da
*     O v�rtice foi criado e preenchido com o conte�do recebido.
*     As listas de antecessores e sucessores foram criadas e est�o vazias.
*
***********************************************************************/

VER_tpCondRet VER_CriarVertice(VER_tpVertice **pDest, void *pConteudo,
                               void(*ExcluirValor)(void *pConteudo));

/***********************************************************************
*
*  $FC Fun��o: VER Destruir v�rtice
*
*  $EP Par�metros
*     pVertice - endere�o do ponteiro que cont�m o v�rtice
*
*  $ED Descri��o da fun��o
*     Anula o ponteiro para v�rtice recebido, destruindo-o.
*     As outras fun��es reconhecer�o esse ponteiro como um v�rtice que n�o existe.
*     N�o libera o espa�o de mem�ria.
*     O espa�o de mem�ria deve ser liberado antes com VER_LiberarVertice.
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um v�rtice j� liberado.
*
*  $AS Assertivas de Sa�da
*     O ponteiro recebido agora � NULO.
*     As outras fun��es reconhecer�o esse ponteiro como um v�rtice inexistente.
*
***********************************************************************/

void VER_DestruirVertice(VER_tpVertice **pVertice);

/***********************************************************************
*
*  $FC Fun��o: VER Liberar v�rtice
*
*  $EP Par�metros
*     pVertice - ponteiro que cont�m o v�rtice
*
*  $ED Descri��o da fun��o
*     Libera espa�o de mem�ria do v�rtice recebido, por�m n�o o anula.
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um v�rtice j� criado e ainda n�o liberado.
*
*  $AS Assertivas de Sa�da
*     O v�rtice foi liberado e a �rea apontada pelo ponteiro recebido 
*     n�o � mais de controle do programa.
*
***********************************************************************/

void VER_LiberarVertice(VER_tpVertice *pVertice);

/***********************************************************************
*
*  $FC Fun��o: VER Obter Conteudo Vertice
*
*  $ED Descri��o da fun��o
*     O ponteiro recebido por refer�ncia passa a apontar o conte�do do v�rtice recebido.
*
*  $EP Par�metros
*     pVertice - ponteiro para v�rtice a extrair conte�do
*     conteudo - endere�o do ponteiro que apontar� o conte�do do v�rtice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeNaoExiste
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um v�rtice j� criado.
*
*  $AS Assertivas de Sa�da
*     O ponteiro conteudo recebido por refer�ncia agora aponta o 
*     conte�do do v�rtice recebido.
*
***********************************************************************/

VER_tpCondRet VER_ObterConteudoVertice(VER_tpVertice *pVertice,
                                       void **conteudo);

/***********************************************************************
*
*  $FC Fun��o: VER Atualiar Conteudo Vertice
*
*  $ED Descri��o da fun��o
*     O conte�do recebido substituir� o conte�do do v�rtice recebido.
*
*  $EP Par�metros
*     pVertice - ponteiro para v�rtice a modificar conte�do
*     conteudo - conte�do que substituir�
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeNaoExiste
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um v�rtice j� criado.
*
*  $AS Assertivas de Sa�da
*     O conte�do antigo do v�rtice foi exclu�do, e agora o conte�do � o 
*     que foi recebido.
*
***********************************************************************/

VER_tpCondRet VER_AtualizarConteudoVertice(VER_tpVertice *pVertice,
                void *conteudo);

/***********************************************************************
*
*  $FC Fun��o: VER Atualiar Conteudo Vertice
*
*  $ED Descri��o da fun��o
*     Os ponteiros recebidos por refer�ncia apontar�o as listas de antecessores
*     e sucessores do v�rtice recebido. Esses ponteiros podem ser nulos caso
*     n�o seja desejada uma das listas.
*
*  $EP Par�metros
*     pVertice - ponteiro para v�rtice a modificar conte�do
*     antecessores - endere�o do ponteiro que apontar� a lista de antecessores
*     sucessores - endere�o do ponteiro que apontar� a lista de sucessores
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeNaoExiste
*
*  $AE Assertivas de Entrada
*     O ponteiro recebido aponta um v�rtice j� criado.
*     Os par�metros antecessores e sucessores s�o ponteiros para lista 
*     recebidos por refer�ncia, ou NULL.
*
*  $AS Assertivas de Sa�da
*     O(s) ponteiro(s) para lista recebidos por refer�ncia agora apontam
*     as listas de antecessores ou sucessores.
*
***********************************************************************/

VER_tpCondRet VER_ObterListasAntSuc(VER_tpVertice *pVertice,
                                    LIS_tppLista *antecessores, LIS_tppLista *sucessores);

#undef VERTICE_EXT

/********** Fim do m�dulo de defini��o: M�dulo V�rtice **********/

#else
#endif
