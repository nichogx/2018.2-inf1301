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

struct VER_tgAresta {
	/* nome da aresta */
	char id;

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
	pDest->pListaAnt = LIS_CriarLista(free);
	pDest->pListaSuc = LIS_CriarLista(free);

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
                                   char id)
{
	LIS_tpCondRet retL = LIS_CondRetOK;
	LIS_tpCondRet retL2 = LIS_CondRetOK;
	VER_tpAresta *aresta;

	if (pVerticeOr == NULL || pVerticeDest == NULL)
		return VER_CondRetVerticeNaoExiste;

	aresta = (VER_tpAresta *)malloc(sizeof(VER_tpAresta));
	if (aresta == NULL)
		return VER_CondRetFaltouMemoria;

	aresta->id =  id;
	aresta->pAnterior = pVerticeOr;
	aresta->pApontado = pVerticeDest;

	retL = LIS_InserirElementoApos(pVerticeOr->pListaSuc, aresta);
	retL2 = LIS_InserirElementoApos(pVerticeDest->pListaAnt, aresta);
	if (retL != LIS_CondRetOK || retL2 != LIS_CondRetOK)
		return VER_CondRetErroModuloLista;

	return VER_CondRetOK;
} /* fim função: VER Adicionar ligação */

/***************************************************************************
*
*  Função: VER Remover ligação
*  ****/

VER_tpCondRet VER_RemoverLigacao(VER_tpVertice *pVerticeOr,
                                 char id)
{
	LIS_tpCondRet retL = LIS_CondRetOK;
	LIS_tpCondRet retL2 = LIS_CondRetOK;
	VER_tpAresta *aresta;
	VER_tpVertice *pVerticeDest;

	if (pVerticeOr == NULL)
		return VER_CondRetVerticeNaoExiste;

	IrInicioLista(pVerticeOr->pListaSuc); /* encontrar na lista de sucessores */
	aresta = (VER_tpAresta *)LIS_ObterValor(pVerticeOr->pListaSuc);
	while (aresta->id == id && retL == LIS_CondRetOK) {
		retL = LIS_AvancarElementoCorrente(pVerticeOr->pListaSuc, 1);
		aresta = (VER_tpAresta *)LIS_ObterValor(pVerticeOr->pListaSuc);
	}
	pVerticeDest = aresta->pVerticeDest;
	
	if (pVerticeDest == NULL)
		return VER_CondRetVerticeNaoExiste;

	IrInicioLista(pVerticeDest->pListaAnt); 
	while (aresta->id == id && retL2 == LIS_CondRetOK) {
		retL2 = LIS_AvancarElementoCorrente(pVerticeDest->pListaAnt, 1);
		aresta = (VER_tpAresta *)LIS_ObterValor(pVerticeDest->pListaAnt);
	}


	if (retL != LIS_CondRetOK || retL2 !=LIS_CondRetOK)
		return VER_LigacaoNaoEncontrada;

	retL = LIS_ExcluirElemento(pVerticeOr->pListaSuc);
	retL2 = LIS_ExcluirElemento(pVerticeDest->pListaAnt);
	if (retL != LIS_CondRetOK || retL2 !=LIS_CondRetOK)
		return VER_CondRetErroModuloLista;

	return VER_CondRetOK;
} /* fim função: VER Remover ligação */

VER_tpCondRet VER_obtemIDaresta(VER_tgAresta *aresta, char *id)
{
	if (aresta == NULL){
		return VER_CondRetArestaNaoExiste;
	}
	*id = aresta->id;
	return VER_CondRetOK;
}

VER_tpCondRet VER_obtemAnteriorAresta(VER_tgAresta *aresta, *pVerticeDest sucessor)
{
	if (aresta == NULL){
		return VER_CondRetArestaNaoExiste;
	}
	sucessor = aresta->pVerticeDest;
	
	return VER_CondRetOK;
}

VER_tpCondRet VER_obtemSucessorAresta(VER_tpAresta *aresta, *pVerticeOr antecessor)
{
	if (aresta == NULL){
		return VER_CondRetArestaNaoExiste;
	}
	antecessor = aresta->pVerticeOr;

	return VER_CondRetOK;
}

VER_tpCondRet VER_buscaArestaID(char id, VER_tgVertice *pVerticeOr)
{
	LIS_tpCondRet retL = LIS_CondRetOK;
	VER_tpAresta *aresta;
	IrInicioLista(pVerticeOr->pListaSuc);
	aresta = (VER_tpAresta *)LIS_ObterValor(pVerticeOr->pListaSuc); 
	while ( aresta->id != NULL && retL == LIS_CondRetOK) {
		retL = LIS_AvancarElementoCorrente(pVerticeOr->pListaSuc, 1);
		if (aresta->id == id){
			return aresta;
		}
	}
}
/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Vértice **********/
