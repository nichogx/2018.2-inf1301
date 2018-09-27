/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Grafo
*
*  Arquivo:                 GRAFO.C
*  Letras identificadoras:  GRF
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*			gpa - Guilherme Pasqualette
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
*		0.30   gpa   23/09/2018	Implementação de funções
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
*  $TC Tipo de dados: GRF Descritor da cabe�a de um grafo
*
*
*  $ED Descri��o do tipo
*     A cabe�a do grafo � o ponto de acesso para um determinado grafo.
*
***********************************************************************/

struct GRF_tgGrafo {
	/* ponteiro para o v�rtice corrente do grafo */
	VER_tpVertice *pNoCorr;

	/* ponteiro para a lista de origens do grafo */
	LIS_tppLista pOrigens;

	/* ponteiro para a lista de v�rtices do grafo*/
	LIS_tppLista pVertices;
};

/*****  Dados encapsulados no m�dulo  *****/

static GRF_tpGrafo *pGrafo = NULL;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: GRF Criar grafo
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
} /* fim fun��o: GRF Criar Grafo */

/***************************************************************************
*
*  Fun��o: GRF Destruir Grafo
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
} /* fim fun��o: GRF Destruir Grafo */

/**************************************************************************
*
*	Fun��o: GRF Obter Valor Corrente
*	****/

GRF_tpCondRet GRF_ObterValorCorrente(void){
	void *content;
	if(pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	content = pGrafo->pNoCorr->pConteudo;
	return GRF_CondRetOK;
}/* Fim da Fun��o: GRF Obter Valor Corrente */

/**************************************************************************
*
*	Fun��o: GRF Alterar Valor Corrente
*	****/

GRF_tpCondRet GRF_AlterarValorCorrente(void *newContent){
	if (pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	pGrafo->pNoCorr->pConteudo = newContent;

	return GRF_CondRetOK;
}/* Fim da fun��o: GRF Alterar Valor Corrente */

/**************************************************************************
*
*	Fun��o: GRF Ir Vertice
*	****/

GRF_tpCondRet GRF_IrVertice(void *content){
	VER_tpVertice *vertDest;
	if(pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;
	/* Achar o vertice Destino nas listas Suc e Ant */
	if(LIS_ProcurarValor(pGrafo->pNoCorr->pListaSuc,vertDest->content) == LIS_CondRetOK || LIS_ProcurarValor(pGrafo->pNoCorr->pListaAnt,vertDest->content) == LIS_CondRetOK){
		pGrafo->pNoCorr = vertDest;
		return GRF_CondRetOK;
	}
	/* N�o achou */
	return GRF_CondRetVerticeNaoExiste;
}/* Fim da Fun��o: GRF Ir Vertice */

/**************************************************************************
*
*	Fun��o: GRF Inserir Vertice
*	****/

GRF_tpCondRet GRF_InserirVertice(void * content){
	VER_tpVertice *insVert;
	if(pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;
		
	if(VER_CriarVertice(insVert,content,insVert->ExcluirValor) == VER_CondRetOK){	
		if(LIS_InserirElementoApos(pGrafo->pVertices,insVert) == LIS_CondRetOK)
			return GRF_CondRetOK;	
	}
	return GRF_CondRetFaltouMemoria;
}/* Fim da Função: GRF Inserir Vertice */

/**************************************************************************
*
*	Fun��o: GRF Remover Vertice
*	****/

GRF_tpCondRet GRF_RemoverVertice(void *contentDestino){ //Destruir aresta, se pertencer a alguma....
	VER_tpVertice *vertDest;

	if(pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	if(LIS_ProcurarValor(pGrafo->pVertices, contentDestino) == LIS_CondRetOK){}
		VER_DestruirVertice(pGrafo->pNoCorr);
		IrInicioLista(pGrafo->pVertices);
		pGrafo->pNoCorr = vertDest;
		return GRF_CondRetOK;
	}
	return GRF_CondRetVerticeNaoExiste;
}/* Fim da função: GRF Remover Vertice*/

/**************************************************************************
*
*	Fun��o: GRF Adicionar Origem
*	****/

GRF_tpCondRet GRF_AdicionarOrigem(void * content){
	VER_tpVertice *vOrigem;
	if(pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	if(VER_CriarVertice(vOrigem,content,vOrigem->ExcluirValor) == VER_CondRetOK){
		if(LIS_InserirElementoApos(pGrafo->pOrigens,vOrigem) == LIS_CondRetOK && LIS_InserirElementoApos(pGrafo->pVertices,vOrigem))
			return GRF_CondRetOK;
	}
	return GRF_CondRetFaltouMemoria;
}/* Fim da Função: GRF Adicionar Origem */

/**************************************************************************
*
*	Fun��o: GRF Remover Origem
*	****/

GRF_tpCondRet GRF_RemoverOrigem(void *content, char destino){
	VER_tpVertice *dest;
	if(pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;
	/* Se o vertice corrente eh uma origem ou nao */
	
	if(LIS_ProcurarValor(pGrafo->pOrigens, content) == LIS_CondRetOK)
		if(LIS_ExcluirElemento(pGrafo->pOrigens) == LIS_CondRetOK){
			VER_DestruirVertice(pGrafo->pNoCorr);
			if(LIS_ProcurarValor(pGrafo->pVertices, destino) && pGRafo->pOrigens == NULL)
				pGrafo->pNoCorr = dest;
				return GRF_CondRetOK;
		}
	return GRF_CondRetVerticeNaoExiste;
}/* Fim da Função: GRF Remover Origem */

/**************************************************************************
*
*	Fun��o: GRF Adicionar Aresta 
*	****/

GRF_tpCondRet GRF_AdicionarAresta(char nomeAresta){		
	LIS_CondRet x,y,z;
	VER_tpVertice *inicio;
	VER_tpAresta *arestaAdd;
	if(pGrafo == NULL)
		return GRF_CondRetGrafoNaoExiste;

	if(LIS_ProcurarValor(pGrafo->pVertice, inicio) != LIS_CondRetOK || inicio == NULL)
		return GRF_CondRetVerticeNaoExiste;
	// if's servem para checar se a aresta a ser criada nao existe 
	if(LIS_ProcurarValor(pGrafo->pNoCorr->pListaAnt, inicio) != LIS_CondRet && LIS_ProcurarValor(inicio->pListaSuc, pGrafo->pNoCorr) != LIS_CondRet){
		x = LIS_InserirElementoApos(pGrafo->pNoCorr->pListaAnt, inicio);
		y = LIS_InserirElementoApos(inicio->pListaSuc, pGrafo->pNoCorr);
		arestaAdd->pApontado = pGrafo->pNoCorr;
		arestaAdd->pAnterior = inicio;
		arestaAdd->id = nomeAresta;
		z = LIS_InserirElementoApos(inicio->pListaArestas, arestaAdd);
		return GRF_CondRetOK;

		}else if(LIS_ProcurarValor(pGrafo->pNoCorr->pListaSuc, inicio) != LIS_CondRet && LIS_ProcurarValor(inicio->pListaAnt, pGrafo->pNoCorr) != LIS_CondRet){
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
*	Fun��o: GRF Remover Aresta
*	****/

GRF_tpCondRet GRF_RemoverAresta(char nomeAresta){
	VER_tpVertice *Vert;
	LIS_tpCondRet x,y,z,a;
	if(pGrafo == NULL)
		return GRF_CondRetGrafoVazio;

	if(LIS_ProcurarValor(pGrafo->pVertices, Vert) != LIS_CondRetOK || Vert == NULL)
		return GRF_CondRetVerticeNaoExiste;

		
	// if's servem para checar se a aresta a ser criada, ja existe 
	if(LIS_ProcurarValor(pGrafo->pNoCorr->pListaSuc, Vert) == LIS_CondRetOK && LIS_ProcurarValor(Vert->pListaAnt, pGrafo->pNoCorr) == LIS_CondRetOK){
		if(LIS_ProcurarValor(pGrafo->pNoCorr->pListaArestas, nomeAresta) == LIS_CondRetOK && LIS_ProcurarValor(Vert->pListaArestas, nomeAresta))	
		x = LIS_ExcluirElemento(pGrafo->pNoCorr->pListaSuc);	
		y = LIS_ExcluirElemento(Vert->pListaAnt);
		z = LIS_ExcluirElemento(pGrafo->pNoCorr->pListaArestas);
		a = LIS_ExcluirElemento(Vert->pListaArestas);
		return GRF_CondRetOK;
		}else if(LIS_ProcurarValor(pGrafo->pNoCorr->pListaAnt, Vert) == LIS_CondRetOK && LIS_ProcurarValor(Vert->pListaSuc, pGrafo->pNoCorr) == LIS_CondRetOK){
			if(LIS_ProcurarValor(pGrafo->pNoCorr->pListaArestas, nomeAresta) == LIS_CondRetOK && LIS_ProcurarValor(Vert->pListaArestas, nomeAresta))
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
*	Fun��o: GRF Esvaziar Grafo
*	****/

GRF_tpCondRet GRF_EsvaziarGrafo(void){
	if(pGrafo == NULL)
		return GRF_CondRetGrafoVazio;
	
	LIS_EsvaziarLista(tpGrafo->pOrigens);
	LIS_EsvaziarLista(tpGrafo->pVertices);
	VER_DestruirVertice(tpGrafo->pNoCorr);

	return GRF_CondRetOK;
}/* Fim da função: GRF Esvaziar Grafo */

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Grafo **********/