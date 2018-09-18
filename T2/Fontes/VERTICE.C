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
	/* conteúdo do vértice */
	char nome[6];

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
	LIS_tppLista listaAnt = NULL;
	LIS_tppLista listaSuc = NULL;

	pDest = (VER_tpVertice *) malloc(sizeof(VER_tpVertice));
	if (pDest == NULL)
		return VER_CondRetFaltouMemoria;

	pDest->pConteudo = pConteudo;
	listaAnt = LIS_CriarLista(NULL);
	listaSuc = LIS_CriarLista(NULL);

	if (listaAnt == NULL || listaSuc == NULL)
		return VER_CondRetErroAoCriarLista;

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

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Vértice **********/
