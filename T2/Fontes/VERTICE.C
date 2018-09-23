/***************************************************************************
*  $MCI Módulo de implementação: Módulo Vártice
*
*  Arquivo:                 VERTICE.C
*  Letras identificadoras:  VER
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LISTA.H"

#define VERTICE_OWN
#include "VERTICE.H"
#undef VERTICE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor de um vértice
*
*
*  $ED Descrição do tipo
*     Um vértice genérico que contém conteúdo, lista de antecessores e
*     sucessores.
*
***********************************************************************/

struct VER_tgVertice {
	/* conteúdo do vértice */
	void *pConteudo;

	/* ponteiro para uma função que destói pConteudo */
	void(*ExcluirValor)(void *pConteudo);

	/* lista de antecessores */
	LIS_tppLista pListaAnt;

	/* lista de sucessores */
	LIS_tppLista pListaSuc;
};

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor de uma aresta
*
*
*  $ED Descrição do tipo
*     Uma aresta que liga dois vértices. É o conteúdo das listas
*     de antecessores e sucessores no vértice. Tem um nome de até 5
*     caracteres.
*
***********************************************************************/

typedef struct VER_tgAresta VER_tpAresta;
struct VER_tgAresta {
	/* nome da aresta */
	char nome[11];

	/* vertice apontado */
	VER_tpVertice *pApontado;

	/* vertice origem */
	VER_tpVertice *pAnterior;
};

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER Criar vértice
*  ****/

VER_tpCondRet VER_CriarVertice(VER_tpVertice *pDest, void *pConteudo,
                               void(*ExcluirValor)(void *pConteudo))
{
	pDest = (VER_tpVertice *) malloc(sizeof(VER_tpVertice));
	if (pDest == NULL)
		return VER_CondRetFaltouMemoria;

	pDest->pConteudo = pConteudo;
	pDest->ExcluirValor = ExcluirValor;
	pDest->pListaAnt = LIS_CriarLista(NULL);
	pDest->pListaSuc = LIS_CriarLista(NULL);

	if (pDest->pListaAnt == NULL || pDest->pListaSuc == NULL)
		return VER_CondRetErroModuloLista;

	return VER_CondRetOK;
} /* fim função: VER Criar vértice */

/***************************************************************************
*
*  Função: VER Destruir vértice
*  ****/

void VER_DestruirVertice(VER_tpVertice *pVertice)
{
	if (pVertice != NULL) {
		LIS_DestruirLista(pVertice->pListaAnt);
		LIS_DestruirLista(pVertice->pListaSuc);

		if (pVertice->ExcluirValor != NULL)
			pVertice->ExcluirValor(pVertice->pConteudo);

		free(pVertice);
		pVertice = NULL;
	} /* if */
} /* fim função: VER Destruir vértice */

/***************************************************************************
*
*  Função: VER Adicionar ligação
*  ****/

VER_tpCondRet VER_AdicionarLigacao(VER_tpVertice *pVerticeOr,
                                   VER_tpVertice *pVerticeDest,
                                   char *nome)
{
	LIS_tpCondRet retL = LIS_CondRetOK;
	VER_tpAresta *aresta;

	if (pVerticeOr == NULL || pVerticeDest == NULL)
		return VER_CondRetVerticeNaoExiste;

	aresta = (VER_tpAresta *)malloc(sizeof(VER_tpAresta));
	if (aresta == NULL)
		return VER_CondRetFaltouMemoria;

	strcpy(aresta->nome, nome);
	aresta->pAnterior = pVerticeOr;
	aresta->pApontado = pVerticeDest;

	retL = LIS_InserirElementoApos(pVerticeOr->pListaSuc, aresta);
	if (retL != LIS_CondRetOK)
		return VER_CondRetErroModuloLista;

	return VER_CondRetOK;
} /* fim função: VER Adicionar ligação */

/***************************************************************************
*
*  Função: VER Remover ligação
*  ****/

VER_tpCondRet VER_RemoverLigacao(VER_tpVertice *pVerticeOr,
                                 char *nome)
{
	LIS_tpCondRet retL = LIS_CondRetOK;
	VER_tpAresta *aresta = (VER_tpAresta *) LIS_ObterValor(pVerticeOr->pListaSuc);

	if (pVerticeOr == NULL)
		return VER_CondRetVerticeNaoExiste;

	IrInicioLista(pVerticeOr->pListaSuc);
	while (strcmp(aresta->nome, nome) && retL == LIS_CondRetOK) {
		retL = LIS_AvancarElementoCorrente(pVerticeOr->pListaSuc, 1);
		aresta = (VER_tpAresta *)LIS_ObterValor(pVerticeOr->pListaSuc);
	}

	if (retL != LIS_CondRetOK)
		return VER_LigacaoNaoEncontrada;

	retL = LIS_ExcluirElemento(pVerticeOr->pListaSuc);
	if (retL != LIS_CondRetOK)
		return VER_CondRetErroModuloLista;

	return VER_CondRetOK;
} /* fim função: VER Remover ligação */

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Vértice **********/
