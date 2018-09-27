/***************************************************************************
*  $MCI Módulo de implementação: Módulo Grafo
*
*  Arquivo:                 GRAFO.C
*  Letras identificadoras:  GRF
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*           gpa - Guilherme Pasqualette
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       0.30   gpa   23/09/2018 Implementação de funções
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
	VER_tpVertice *pVerCorr;

	/* ponteiro para a lista de origens do grafo */
	LIS_tppLista pListaOr;

	/* ponteiro para a lista de vértices do grafo*/
	LIS_tppLista pListaVer;
};

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor de uma aresta entre vértices
*
*
*  $ED Descrição do tipo
*     Uma aresta liga um vértice ao outro e tem um ID.
*
***********************************************************************/

typedef struct GRF_tgAresta {
	/* id da aresta */
	char id;

	/* vértice apontado */
	VER_tpVertice *vertAp;
} GRF_tpAresta;

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

	pGrafo->pVerCorr = NULL;
	pGrafo->pListaOr = LIS_CriarLista(NULL);
	pGrafo->pListaVer = LIS_CriarLista(&VER_DestruirVertice);

	if (pGrafo->pListaOr == NULL || pGrafo->pListaVer == NULL)
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

	LIS_DestruirLista(pGrafo->pListaOr);
	LIS_DestruirLista(pGrafo->pListaVer);

	free(pGrafo);
	pGrafo = NULL;

	return GRF_CondRetOK;
} /* fim função: GRF Destruir Grafo */

/**************************************************************************
*
*	Função: GRF Obter Valor Corrente
*	****/

GRF_tpCondRet GRF_ObterValorCorrente(void **conteudo)
{
	VER_tpCondRet retVer = VER_CondRetOK;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	retVer = VER_ObterConteudoVertice(pGrafo->pVerCorr, conteudo);
	if (retVer == VER_CondRetVerticeNaoExiste)
		return GRF_CondRetVerticeNaoExiste;

	return GRF_CondRetOK;
}/* Fim da Função: GRF Obter Valor Corrente */

/**************************************************************************
*
*	Função: GRF Alterar Valor Corrente
*	****/

GRF_tpCondRet GRF_AlterarValorCorrente(void *novoConteudo)
{
	VER_tpCondRet retVer = VER_CondRetOK;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	retVer = VER_AtualizarConteudoVertice(pGrafo->pVerCorr, novoConteudo);
	if (retVer == VER_CondRetVerticeNaoExiste)
		return GRF_CondRetVerticeNaoExiste;

	return GRF_CondRetOK;
}/* Fim da função: GRF Alterar Valor Corrente */

/**************************************************************************
*
*	Função: GRF Ir Vertice
*	****/

GRF_tpCondRet GRF_IrVertice(void *content)
{
	VER_tpVertice *vertDest;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;
	/* Achar o vertice Destino nas listas Suc e Ant */
	if (LIS_ProcurarValor(pGrafo->pListaVer, NULL) == LIS_CondRetOK) {}
	if (LIS_ProcurarValor(pGrafo->pListaVer, NULL) == LIS_CondRetOK) {
		pGrafo->pNoCorr = vertDest;
		return GRF_CondRetOK;
	}
	/* Não achou */
	return GRF_CondRetVerticeNaoExiste;
}/* Fim da Função: GRF Ir Vertice */

/**************************************************************************
*
*	Função: GRF Inserir Vertice
*	****/

GRF_tpCondRet GRF_InserirVertice(void *pConteudo,
                                 void(*ExcluirValor)(void *pConteudo))
{
	VER_tpVertice *insVert;
	VER_tpCondRet Ret;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	Ret = VER_CriarVertice(insVert, pConteudo, ExcluirValor);

	if (Ret == VER_CondRetFaltouMemoria)
		return GRF_CondRetFaltouMemoria;

	if (Ret == VER_CondRetErroModuloLista)
		return GRF_CondRetErroAoCriarLista;

	if (LIS_InserirElementoApos(pGrafo->pListaVer, insVert) == LIS_CondRetOK)
		return GRF_CondRetOK;
	else
		return GRF_CondRetFaltouMemoria;
}/* Fim da Função: GRF Inserir Vertice */

/**************************************************************************
*
*	Função: GRF Remover Vertice Corrente
*	****/

GRF_tpCondRet GRF_RemoverVerticeCorr()
{
	VER_tpVertice *vertDest;

	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	LIS_ProcurarValor(pGrafo->pListaVer, pGrafo->pVerCorr);
	LIS_ExcluirElemento(pGrafo->pListaVer);

	VER_DestruirVertice(pGrafo->pNoCorr);
	IrInicioLista(pGrafo->pVertices);
	pGrafo->pNoCorr = vertDest;
	return GRF_CondRetOK;
} /* Fim da função: GRF Remover Vertice Corrente */

/**************************************************************************
*
*	Função: GRF Adicionar Origem
*	****/

GRF_tpCondRet GRF_AdicionarOrigem(void *content)
{
	VER_tpVertice *vOrigem;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	if (VER_CriarVertice(vOrigem, content,
	                     vOrigem->ExcluirValor) == VER_CondRetOK) {
		if (LIS_InserirElementoApos(pGrafo->pOrigens, vOrigem) == LIS_CondRetOK
		    && LIS_InserirElementoApos(pGrafo->pVertices, vOrigem))
			return GRF_CondRetOK;
	}
	return GRF_CondRetFaltouMemoria;
}/* Fim da Função: GRF Adicionar Origem */

/**************************************************************************
*
*	Função: GRF Remover Origem
*	****/

GRF_tpCondRet GRF_RemoverOrigem(void *content, char destino)
{
	VER_tpVertice *dest;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;
	/* Se o vertice corrente eh uma origem ou nao */

	if (LIS_ProcurarValor(pGrafo->pOrigens, content) == LIS_CondRetOK)
		if (LIS_ExcluirElemento(pGrafo->pOrigens) == LIS_CondRetOK) {
			VER_DestruirVertice(pGrafo->pNoCorr);
			if (LIS_ProcurarValor(pGrafo->pVertices, destino) && pGRafo->pOrigens == NULL)
				pGrafo->pNoCorr = dest;
			return GRF_CondRetOK;
		}
	return GRF_CondRetVerticeNaoExiste;
}/* Fim da Função: GRF Remover Origem */

/**************************************************************************
*
*	Função: GRF Adicionar Aresta
*	****/

GRF_tpCondRet GRF_AdicionarAresta(char nomeAresta)
{
	LIS_CondRet x, y, z;
	VER_tpVertice *inicio;
	VER_tpAresta *arestaAdd;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	if (LIS_ProcurarValor(pGrafo->pVertice, inicio) != LIS_CondRetOK
	    || inicio == NULL)
		return GRF_CondRetVerticeNaoExiste;
	// if's servem para checar se a aresta a ser criada nao existe
	if (LIS_ProcurarValor(pGrafo->pNoCorr->pListaAnt, inicio) != LIS_CondRet
	    && LIS_ProcurarValor(inicio->pListaSuc, pGrafo->pNoCorr) != LIS_CondRet) {
		x = LIS_InserirElementoApos(pGrafo->pNoCorr->pListaAnt, inicio);
		y = LIS_InserirElementoApos(inicio->pListaSuc, pGrafo->pNoCorr);
		arestaAdd->pApontado = pGrafo->pNoCorr;
		arestaAdd->pAnterior = inicio;
		arestaAdd->id = nomeAresta;
		z = LIS_InserirElementoApos(inicio->pListaArestas, arestaAdd);
		return GRF_CondRetOK;

	} else if (LIS_ProcurarValor(pGrafo->pNoCorr->pListaSuc, inicio) != LIS_CondRet
	           && LIS_ProcurarValor(inicio->pListaAnt, pGrafo->pNoCorr) != LIS_CondRet) {
		x = LIS_InserirElementoApos(pGrafo->pNoCorr->pListaSuc, inicio);
		y = LIS_InserirElementoApos(inicio->pListaAnt, pGrafo->pNoCorr);
		arestaAdd->pApontado = inicio;
		arestaAdd->pAnterior = pGrafo->pNoCorr;
		arestaAdd->id = nomeAresta;
		z = LIS_InserirElementoApos(inicio->pListaArestas, arestaAdd);
		return GRF_CondRetOK;
	}
	return GRF_CondRetErroEstrutura;
}/* Fim da Função: GRF Adicionar Aresta */

/**************************************************************************
*
*	Função: GRF Remover Aresta
*	****/

GRF_tpCondRet GRF_RemoverAresta(char nomeAresta)
{
	VER_tpVertice *Vert;
	LIS_tpCondRet x, y, z, a;
	if (pGrafo == NULL)
		return GRF_CondRetGrafoVazio;

	if (LIS_ProcurarValor(pGrafo->pVertices, Vert) != LIS_CondRetOK || Vert == NULL)
		return GRF_CondRetVerticeNaoExiste;


	// if's servem para checar se a aresta a ser criada, ja existe
	if (LIS_ProcurarValor(pGrafo->pNoCorr->pListaSuc, Vert) == LIS_CondRetOK
	    && LIS_ProcurarValor(Vert->pListaAnt, pGrafo->pNoCorr) == LIS_CondRetOK) {
		if (LIS_ProcurarValor(pGrafo->pNoCorr->pListaArestas,
		                      nomeAresta) == LIS_CondRetOK
		    && LIS_ProcurarValor(Vert->pListaArestas, nomeAresta))
			x = LIS_ExcluirElemento(pGrafo->pNoCorr->pListaSuc);
		y = LIS_ExcluirElemento(Vert->pListaAnt);
		z = LIS_ExcluirElemento(pGrafo->pNoCorr->pListaArestas);
		a = LIS_ExcluirElemento(Vert->pListaArestas);
		return GRF_CondRetOK;
	} else if (LIS_ProcurarValor(pGrafo->pNoCorr->pListaAnt, Vert) == LIS_CondRetOK
	           && LIS_ProcurarValor(Vert->pListaSuc, pGrafo->pNoCorr) == LIS_CondRetOK) {
		if (LIS_ProcurarValor(pGrafo->pNoCorr->pListaArestas,
		                      nomeAresta) == LIS_CondRetOK
		    && LIS_ProcurarValor(Vert->pListaArestas, nomeAresta))
			x = LIS_ExcluirElemento(pGrafo->pNoCorr->pListaAnt);
		y = LIS_ExcluirElemento(Vert->pListaSuc);
		z = LIS_ExcluirElemento(pGrafo->pNoCorr->pListaArestas);
		a = LIS_ExcluirElemento(Vert->pListaArestas);
		return GRF_CondRetOK;
	}
	return GRF_CondRetErroEstrutura;
}/* Fim da função: GRF Remover Aresta */

/**************************************************************************
*
*	Função: GRF Esvaziar Grafo
*	****/

GRF_tpCondRet GRF_EsvaziarGrafo(void)
{
	if (pGrafo == NULL)
		return GRF_CondRetGrafoVazio;

	LIS_EsvaziarLista(tpGrafo->pOrigens);
	LIS_EsvaziarLista(tpGrafo->pVertices);
	VER_DestruirVertice(tpGrafo->pNoCorr);

	return GRF_CondRetOK;
}/* Fim da função: GRF Esvaziar Grafo */

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Grafo **********/