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

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor do nó do grafo
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

typedef struct tgNoGrafo tpNoGrafo;
struct tgNoGrafo {
	char valor; /* valor do nó */
};

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabeça de um grafo
*
*
*  $ED Descrição do tipo
*     A cabeça do grafo é o ponto de acesso para um determinado grafo.
*
***********************************************************************/

typedef struct tgGrafo tpGrafo;
struct tgGrafo {
	tpNoGrafo *pNoCorr; /* ponteiro para o nó corrente do grafo */
};

/*****  Dados encapsulados no módulo  *****/

static tpGrafo *pGrafo = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF Criar grafo
*  ****/

GRF_tpCondRet GRF_CriarGrafo()
{
	if (pGrafo != NULL)
		return GRF_CondRetGrafoJaExiste;

	pGrafo = (tpGrafo *) malloc(sizeof(tpGrafo));
	if (pGrafo == NULL)
		return GRF_CondRetFaltouMemoria;

	pGrafo->pNoCorr = NULL;

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

	// TODO continuar
} /* fim função: GRF Destruir Grafo

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Grafo **********/