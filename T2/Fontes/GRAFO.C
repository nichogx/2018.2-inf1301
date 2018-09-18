/***************************************************************************
*  $MCI Módulo de implementação: Módulo Grafo
*
*  Arquivo:                 GRAFO.C
*  Letras identificadoras:  GRF
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
#include "VERTICE.H"

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabeça de um grafo
*
*
*  $ED Descrição do tipo
*     A cabeça do grafo é o ponto de acesso para um determinado grafo.
*
***********************************************************************/

struct GRF_tgGrafo {
	/* ponteiro para o vértice corrente do grafo */
	VER_tpVertice *pNoCorr;

	/* ponteiro para a lista de origens do grafo */
	LIS_tppLista *pOrigens;

	/* ponteiro para a lista de vértices do grafo*/
	LIS_tppLista *pVertices;
};

/*****  Dados encapsulados no módulo  *****/

static GRF_tpGrafo *pGrafo = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF Criar grafo
*  ****/

GRF_tpCondRet GRF_CriarGrafo(void)
{
	if (pGrafo != NULL)
		return GRF_CondRetGrafoJaExiste;

	pGrafo = (GRF_tpGrafo *) malloc(sizeof(GRF_tpGrafo));
	if (pGrafo == NULL)
		return GRF_CondRetFaltouMemoria;

	pGrafo->pNoCorr = NULL;
	pGrafo->pOrigens = LIS_CriarLista(&VER_DestruirVertice);
	pGrafo->pVertices = LIS_CriarLista(&VER_DestruirVertice);

	if (pGrafo->pOrigens == NULL || pGrafo->pVertices == NULL)
		return GRF_CondRetErroAoCriarLista;

	return GRF_CondRetOK;
} /* fim função: GRF Criar Grafo */

/***************************************************************************
*
*  Função: GRF Destruir Grafo
*  ****/

GRF_tpCondRet GRF_DestruirGrafo(void)
{
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	LIS_DestruirLista(pGrafo->pVertices);
	LIS_DestruirLista(pGrafo->pOrigens);

	free(pGrafo);
	pGrafo = NULL;

	return GRF_CondRetOK;
} /* fim função: GRF Destruir Grafo */

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Grafo **********/
