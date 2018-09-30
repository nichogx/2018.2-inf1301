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
*       1.00   ngx   30/09/2018 Versão de entrega.
*       0.55   ngx   28/09/2018 Separar liberação e destruição do vértice
*       0.50   ngx   28/09/2018 Módulo funciona como esperado
*       0.40   ngx   27/09/2018 Continuação da codificação do módulo.
*                               Modificações na estrutura.
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

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER Criar vértice
*  ****/

VER_tpCondRet VER_CriarVertice(VER_tpVertice **pDest, void *pConteudo,
                               void(*ExcluirValor)(void *pConteudo))
{
	(*pDest) = (VER_tpVertice *) malloc(sizeof(VER_tpVertice));
	if ((*pDest) == NULL) {
		return VER_CondRetFaltouMemoria;
	}

	(*pDest)->pConteudo = pConteudo;
	(*pDest)->ExcluirValor = ExcluirValor;
	(*pDest)->pListaAnt = LIS_CriarLista(NULL);
	(*pDest)->pListaSuc = LIS_CriarLista(NULL);

	if ((*pDest)->pListaAnt == NULL || (*pDest)->pListaSuc == NULL) {
		return VER_CondRetFaltouMemoria;
	}

	return VER_CondRetOK;
} /* fim função: VER Criar vértice */

/***************************************************************************
*
*  Função: VER Destruir vértice
*  ****/

void VER_DestruirVertice(VER_tpVertice **pVertice)
{
	(*pVertice) = NULL;
} /* fim função: VER Destruir vértice */

/***************************************************************************
*
*  Função: VER Liberar vértice
*  ****/

void VER_LiberarVertice(VER_tpVertice *pVertice)
{
	if (pVertice != NULL) {
		LIS_DestruirLista(pVertice->pListaAnt);
		LIS_DestruirLista(pVertice->pListaSuc);
		if (pVertice->ExcluirValor != NULL) {
			pVertice->ExcluirValor(pVertice->pConteudo);
		}

		free(pVertice);
	} /* if */
} /* fim função: VER Liberar vértice */

/***************************************************************************
*
*  Função: VER Obter Conteudo Vertice
*  ****/

VER_tpCondRet VER_ObterConteudoVertice(VER_tpVertice *pVertice, void **conteudo)
{
	if (pVertice == NULL) {
		return VER_CondRetVerticeNaoExiste;
	}

	*conteudo = pVertice->pConteudo;

	return VER_CondRetOK;
} /* fim função: VER Obter Conteudo Vertice */

/***************************************************************************
*
*  Função: VER Atualizar Conteudo Vertice
*  ****/

VER_tpCondRet VER_AtualizarConteudoVertice(VER_tpVertice *pVertice,
                void *conteudo)
{
	if (pVertice == NULL) {
		return VER_CondRetVerticeNaoExiste;
	}

	if (pVertice->ExcluirValor != NULL) {
		pVertice->ExcluirValor(pVertice->pConteudo);
	}
	pVertice->pConteudo = conteudo;

	return VER_CondRetOK;
} /* fim função: VER Atualizar Conteudo Vertice */

/***************************************************************************
*
*  Função: VER Obter Antecessores e Sucessores
*  ****/

VER_tpCondRet VER_ObterListasAntSuc(VER_tpVertice *pVertice,
                                    LIS_tppLista *antecessores, LIS_tppLista *sucessores)
{
	if (pVertice == NULL) {
		return VER_CondRetVerticeNaoExiste;
	}

	if (antecessores != NULL) {
		*antecessores = pVertice->pListaAnt;
	}

	if (sucessores != NULL) {
		*sucessores = pVertice->pListaSuc;
	}

	return VER_CondRetOK;
} /* fim função: VER Obter Antecessores e Sucessores */

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Vértice **********/
