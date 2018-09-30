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
*       1.00   ngx   30/09/2018 Versão de entrega.
*                               Fix de bugs e atualização da documentação.
*       0.60   ngx   29/09/2018 Corrigir funções remover aresta e esvaziar grafo.
*       0.51   ngx   28/09/2018 Erros corrigidos.
*       0.50   ngx   28/09/2018 Novas funções de acesso para caminhar sobre as arestas.
*       0.42   ngx   28/09/2018 Pequenas modificações nos parâmetros das funções
*                               de acesso.
*       0.40   ngx   27/09/2018 Continuação e recodificação do módulo e suas funções.
*                               Modificações na estrutura.
*       0.30   gpa   23/09/2018 Implementação de funções
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
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
	if (pGrafo != NULL) {
		return GRF_CondRetGrafoJaExiste;
	}

	pGrafo = (GRF_tpGrafo *) malloc(sizeof(GRF_tpGrafo));
	if (pGrafo == NULL) {
		return GRF_CondRetFaltouMemoria;
	}

	pGrafo->pVerCorr = NULL;
	pGrafo->pListaOr = LIS_CriarLista(NULL);
	pGrafo->pListaVer = LIS_CriarLista(&VER_LiberarVertice);

	if (pGrafo->pListaOr == NULL || pGrafo->pListaVer == NULL) {
		return GRF_CondRetErroAoCriarLista;
	}

	return GRF_CondRetOK;
} /* fim função: GRF Criar Grafo */

/***************************************************************************
*
*  Função: GRF Destruir Grafo
*  ****/

GRF_tpCondRet GRF_DestruirGrafo(void)
{
	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}
	if (pGrafo->pVerCorr != NULL) {
		GRF_EsvaziarGrafo();
	}

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
	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}

	retVer = VER_ObterConteudoVertice(pGrafo->pVerCorr, conteudo);
	if (retVer == VER_CondRetVerticeNaoExiste) {
		return GRF_CondRetGrafoVazio;
	}

	return GRF_CondRetOK;
}/* Fim da Função: GRF Obter Valor Corrente */

/**************************************************************************
*
*	Função: GRF Alterar Valor Corrente
*	****/

GRF_tpCondRet GRF_AlterarValorCorrente(void *novoConteudo)
{
	VER_tpCondRet retVer = VER_CondRetOK;
	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}

	retVer = VER_AtualizarConteudoVertice(pGrafo->pVerCorr, novoConteudo);
	if (retVer == VER_CondRetVerticeNaoExiste) {
		return GRF_CondRetGrafoVazio;
	}

	return GRF_CondRetOK;
}/* Fim da função: GRF Alterar Valor Corrente */

/**************************************************************************
*
*	Função: GRF Ir Vertice
*	****/

GRF_tpCondRet GRF_IrVertice(void *conteudoBuscado)
{
	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}
	if (pGrafo->pVerCorr == NULL) {
		return GRF_CondRetGrafoVazio;
	}

	IrInicioLista(pGrafo->pListaVer);
	do {
		void *conteudo;
		VER_tpVertice *verticeAt = LIS_ObterValor(pGrafo->pListaVer);

		if (VER_ObterConteudoVertice(verticeAt,
		                             &conteudo) != GRF_CondRetOK) {
			return GRF_CondRetErroEstrutura;
		}

		if (conteudo == conteudoBuscado) {
			pGrafo->pVerCorr = verticeAt;
			return GRF_CondRetOK;
		}
	} while (LIS_AvancarElementoCorrente(pGrafo->pListaVer,
	                                     1) != LIS_CondRetFimLista);
	return GRF_CondRetVerticeNaoExiste;
}/* Fim da Função: GRF Ir Vertice */

/**************************************************************************
*
*	Função: GRF Inserir Vertice
*	****/

GRF_tpCondRet GRF_InserirVertice(void *pConteudo,
                                 void(*ExcluirValor)(void *pConteudo))
{
	VER_tpVertice *insVert = NULL;
	VER_tpCondRet Ret;
	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}

	Ret = VER_CriarVertice(&insVert, pConteudo, ExcluirValor);

	if (Ret == VER_CondRetFaltouMemoria) {
		return GRF_CondRetFaltouMemoria;
	}

	if (Ret == VER_CondRetErroModuloLista) {
		return GRF_CondRetErroAoCriarLista;
	}

	if (LIS_InserirElementoApos(pGrafo->pListaVer, insVert) == LIS_CondRetOK) {
		pGrafo->pVerCorr = insVert;
		return GRF_CondRetOK;
	} else {
		return GRF_CondRetFaltouMemoria;
	}
}/* Fim da Função: GRF Inserir Vertice */

/**************************************************************************
*
*	Função: GRF Remover Vertice Corrente
*	****/

GRF_tpCondRet GRF_RemoverVerticeCorr(void)
{
	LIS_tpCondRet Ret = LIS_CondRetOK;
	LIS_tppLista ListaAnt;
	LIS_tppLista ListaSuc;

	GRF_tpAresta *aresta;

	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}
	if (pGrafo->pVerCorr == NULL) {
		return GRF_CondRetGrafoVazio;
	}

	Ret = LIS_ProcurarValor(pGrafo->pListaVer,
	                        pGrafo->pVerCorr); /* remover da lista de vertices */
	if (Ret == LIS_CondRetOK) {
		LIS_ExcluirElemento(pGrafo->pListaVer);
	} else {
		return GRF_CondRetErroEstrutura;
	}

	if (LIS_ProcurarValor(pGrafo->pListaOr,
	                      pGrafo->pVerCorr) == LIS_CondRetOK) { /* remover da lista de origens */
		LIS_ExcluirElemento(pGrafo->pListaOr);
	}

	if (VER_ObterListasAntSuc(pGrafo->pVerCorr, &ListaAnt,
	                          &ListaSuc) == VER_CondRetVerticeNaoExiste) {
		return GRF_CondRetErroEstrutura;
	}

	IrInicioLista(ListaAnt);
	IrInicioLista(ListaSuc);
	while ((aresta = LIS_ObterValor(ListaAnt)) !=
	       NULL) { /* remover da lista de sucessores dos antecessores dele */
		LIS_tppLista ListaAux;
		VER_ObterListasAntSuc(aresta->vertAp, NULL, &ListaAux);
		IrInicioLista(ListaAux);
		while (((GRF_tpAresta *)LIS_ObterValor(ListaAux))->vertAp != pGrafo->pVerCorr) {
			if (LIS_ObterValor(ListaAux) == NULL) {
				return GRF_CondRetErroEstrutura;
			}

			LIS_AvancarElementoCorrente(ListaAux, 1);
		}
		LIS_ExcluirElemento(ListaAux);

		VER_ObterListasAntSuc(aresta->vertAp, &ListaAux, NULL);
		IrInicioLista(ListaAux);
		while (((GRF_tpAresta *)LIS_ObterValor(ListaAux))->vertAp != pGrafo->pVerCorr) {
			if (LIS_ObterValor(ListaAux) == NULL) {
				return GRF_CondRetErroEstrutura;
			}

			LIS_AvancarElementoCorrente(ListaAux, 1);
		}
		LIS_ExcluirElemento(ListaAux);



		LIS_AvancarElementoCorrente(ListaAnt, 1);
	}

	while ((aresta = LIS_ObterValor(ListaSuc)) !=
	       NULL) { /* remover da lista de antecessores dos sucessores dele */
		LIS_tppLista ListaAux;
		VER_ObterListasAntSuc(aresta->vertAp, NULL, &ListaAux);
		IrInicioLista(ListaAux);
		while (((GRF_tpAresta *)LIS_ObterValor(ListaAux))->vertAp != pGrafo->pVerCorr) {
			if (LIS_AvancarElementoCorrente(ListaAux, 1) != GRF_CondRetOK) {
				return GRF_CondRetErroEstrutura;
			}
		}
		LIS_ExcluirElemento(ListaAux);

		VER_ObterListasAntSuc(aresta->vertAp, &ListaAux, NULL);
		IrInicioLista(ListaAux);
		while (((GRF_tpAresta *)LIS_ObterValor(ListaAux))->vertAp != pGrafo->pVerCorr) {
			if (LIS_AvancarElementoCorrente(ListaAux, 1) != GRF_CondRetOK) {
				return GRF_CondRetErroEstrutura;
			}
		}
		LIS_ExcluirElemento(ListaAux);



		LIS_AvancarElementoCorrente(ListaSuc, 1);
	}

	VER_DestruirVertice(&pGrafo->pVerCorr);
	IrInicioLista(pGrafo->pListaOr);
	if (LIS_ObterValor(pGrafo->pListaOr) != NULL) { /* lista não vazia */
		pGrafo->pVerCorr = LIS_ObterValor(pGrafo->pListaOr);
	}


	return GRF_CondRetOK;
} /* Fim da função: GRF Remover Vertice Corrente */

/**************************************************************************
*
*	Função: GRF Adicionar Origem
*	****/

GRF_tpCondRet GRF_AdicionarOrigem(void *pConteudo,
                                  void(*ExcluirValor)(void *pConteudo))
{
	GRF_tpCondRet Ret;

	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}

	Ret = GRF_InserirVertice(pConteudo, ExcluirValor);

	if (Ret != GRF_CondRetOK) {
		return Ret;
	}

	if (LIS_InserirElementoApos(pGrafo->pListaOr,
	                            pGrafo->pVerCorr) == LIS_CondRetOK) {
		return GRF_CondRetOK;
	} else {
		return GRF_CondRetFaltouMemoria;
	}
}/* Fim da Função: GRF Adicionar Origem */

/**************************************************************************
*
*	Função: GRF Adicionar Aresta
*	****/

GRF_tpCondRet GRF_AdicionarAresta(char idAresta, void *contOrigem,
                                  void *contDestino)
{
	/* existem duas arestas com mesmo id: a que vai de um vértice para o outro
	e a que volta */

	LIS_tppLista sucOrigem;
	LIS_tppLista antDestino;
	GRF_tpAresta *apOrigem; /* aponta para origem */
	GRF_tpAresta *apDestino; /* aponta para destino */
	VER_tpVertice *origem;
	VER_tpVertice *destino;
	int flag = 0;

	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}
	if (pGrafo->pVerCorr == NULL) {
		return GRF_CondRetGrafoVazio;
	}

	IrInicioLista(pGrafo->pListaVer);
	if (LIS_ObterValor(pGrafo->pListaVer) == NULL) {
		return GRF_CondRetErroEstrutura;
	}

	do {
		void *conteudo;
		if (VER_ObterConteudoVertice(LIS_ObterValor(pGrafo->pListaVer),
		                             &conteudo) != GRF_CondRetOK) {
			return GRF_CondRetErroEstrutura;
		}
		if (conteudo == contOrigem) {
			flag = 1;
			break;
		}
	} while (LIS_AvancarElementoCorrente(pGrafo->pListaVer,
	                                     1) != LIS_CondRetFimLista);
	if (!flag) {
		return GRF_CondRetVerticeNaoExiste;
	}
	origem = LIS_ObterValor(pGrafo->pListaVer);

	flag = 0;
	do {
		void *conteudo;
		if (VER_ObterConteudoVertice(LIS_ObterValor(pGrafo->pListaVer),
		                             &conteudo) != GRF_CondRetOK) {
			return GRF_CondRetErroEstrutura;
		}
		if (conteudo == contDestino) {
			flag = 1;
			break;
		}
	} while (LIS_AvancarElementoCorrente(pGrafo->pListaVer,
	                                     1) != LIS_CondRetFimLista);

	if (!flag) {
		return GRF_CondRetVerticeNaoExiste;
	}
	destino = LIS_ObterValor(pGrafo->pListaVer);

	apOrigem = (GRF_tpAresta *)malloc(sizeof(GRF_tpAresta));
	apDestino = (GRF_tpAresta *)malloc(sizeof(GRF_tpAresta));

	if (apOrigem == NULL || apDestino == NULL) {
		return GRF_CondRetFaltouMemoria;
	}

	apOrigem->id = idAresta;
	apOrigem->vertAp = origem;
	apDestino->id = idAresta;
	apDestino->vertAp = destino;

	if (VER_ObterListasAntSuc(origem, NULL, &sucOrigem) != VER_CondRetOK
	    || VER_ObterListasAntSuc(destino, &antDestino, NULL) != VER_CondRetOK)

	{
		return GRF_CondRetVerticeNaoExiste;
	}

	if (LIS_InserirElementoApos(sucOrigem, apDestino) != LIS_CondRetOK) {
		return GRF_CondRetFaltouMemoria;
	}
	if (LIS_InserirElementoApos(antDestino, apOrigem) != LIS_CondRetOK) {
		return GRF_CondRetFaltouMemoria;
	}

	return GRF_CondRetOK;
}/* Fim da Função: GRF Adicionar Aresta */

/**************************************************************************
*
*	Função: GRF Andar
*	****/

GRF_tpCondRet GRF_Andar(char idAresta)
{
	LIS_tppLista ListaSucessores;
	GRF_tpAresta *aresta;
	int encontrou = 1;

	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}
	if (pGrafo->pVerCorr == NULL) {
		return GRF_CondRetGrafoVazio;
	}

	if (VER_ObterListasAntSuc(pGrafo->pVerCorr, NULL,
	                          &ListaSucessores) != VER_CondRetOK) {
		return GRF_CondRetErroEstrutura;
	}

	IrInicioLista(ListaSucessores);
	aresta = LIS_ObterValor(ListaSucessores);
	if (aresta == NULL) {
		return GRF_CondRetArestaNaoExiste;
	}

	while (aresta->id != idAresta && encontrou != 0) {
		if (LIS_AvancarElementoCorrente(ListaSucessores, 1) != GRF_CondRetOK) {
			encontrou = 0;
		}
		aresta = LIS_ObterValor(ListaSucessores);
	}

	if (!encontrou) {
		return GRF_CondRetArestaNaoExiste;
	}

	pGrafo->pVerCorr = ((GRF_tpAresta *)LIS_ObterValor(ListaSucessores))->vertAp;
	return GRF_CondRetOK;
} /*Fim Função: GRF Andar */

/**************************************************************************
*
*	Função: GRF Voltar
*	****/

GRF_tpCondRet GRF_Voltar(char idAresta)
{
	LIS_tppLista ListaAntecessores;
	GRF_tpAresta *aresta;
	int encontrou = 1;

	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}
	if (pGrafo->pVerCorr == NULL) {
		return GRF_CondRetGrafoVazio;
	}

	if (VER_ObterListasAntSuc(pGrafo->pVerCorr, &ListaAntecessores,
	                          NULL) != VER_CondRetOK) {
		return GRF_CondRetErroEstrutura;
	}

	IrInicioLista(ListaAntecessores);
	aresta = LIS_ObterValor(ListaAntecessores);
	if (aresta == NULL) {
		return GRF_CondRetArestaNaoExiste;
	}

	while (aresta->id != idAresta && encontrou != 0) {
		if (LIS_AvancarElementoCorrente(ListaAntecessores, 1) != GRF_CondRetOK) {
			encontrou = 0;
		}
		aresta = LIS_ObterValor(ListaAntecessores);
	}

	if (!encontrou) {
		return GRF_CondRetArestaNaoExiste;
	}

	pGrafo->pVerCorr = ((GRF_tpAresta *)LIS_ObterValor(ListaAntecessores))->vertAp;
	return GRF_CondRetOK;
} /*Fim Função: GRF Voltar */

/**************************************************************************
*
*	Função: GRF Remover Aresta
*	****/

GRF_tpCondRet GRF_RemoverAresta(char idProc)
{
	/* existem duas arestas com mesmo id: a que vai de um vértice para o outro
	   e a que volta */
	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}

	if (LIS_ObterValor(pGrafo->pListaVer) == NULL) {
		return GRF_CondRetGrafoVazio;
	}

	IrInicioLista(pGrafo->pListaVer);

	do {
		/* andar pela lista de vertices do grafo */

		VER_tpVertice *vertAt;
		GRF_tpAresta *arestaSuc;
		LIS_tppLista ListaSucs;

		vertAt = LIS_ObterValor(pGrafo->pListaVer);
		if (vertAt == NULL) {
			return GRF_CondRetErroEstrutura;
		}

		VER_ObterListasAntSuc(vertAt, NULL, &ListaSucs);

		if (ListaSucs == NULL) {
			return GRF_CondRetErroEstrutura;
		}

		IrInicioLista(ListaSucs);
		arestaSuc = LIS_ObterValor(ListaSucs);
		if (arestaSuc == NULL) {
			continue;
		}

		do {
			/* andar pela lista de sucessores */

			arestaSuc = LIS_ObterValor(ListaSucs);
			if (arestaSuc->id == idProc) {
				/* achou sucessor, ir para ele e deletar dos antecessores */

				LIS_tppLista ListaAnts;

				GRF_tpAresta *arestaAnt;

				VER_ObterListasAntSuc(arestaSuc->vertAp, &ListaAnts, NULL);
				do {
					arestaAnt = LIS_ObterValor(ListaAnts);
					if (arestaAnt->id == idProc) {
						free(arestaAnt);
						free(arestaSuc);
						LIS_ExcluirElemento(ListaAnts);
						LIS_ExcluirElemento(ListaSucs);
						return GRF_CondRetOK;
					}

				} while ((LIS_AvancarElementoCorrente(ListaAnts, 1) == LIS_CondRetOK));

				/* nao achou na lista de antecessores do apontado */
				return GRF_CondRetErroEstrutura;
			}

		} while ((LIS_AvancarElementoCorrente(ListaSucs, 1) == LIS_CondRetOK));

	} while (LIS_AvancarElementoCorrente(pGrafo->pListaVer, 1) == LIS_CondRetOK);

	return GRF_CondRetArestaNaoExiste;
}/* Fim da função: GRF Remover Aresta */

/**************************************************************************
*
*	Função: GRF Esvaziar Grafo
*	****/

GRF_tpCondRet GRF_EsvaziarGrafo(void)
{
	unsigned char i;
	if (pGrafo == NULL) {
		return GRF_CondRetGrafoNaoExiste;
	}
	if (pGrafo->pVerCorr == NULL) {
		return GRF_CondRetGrafoVazio;
	}

	for (i = CHAR_MIN; i < CHAR_MAX; i++) {
		GRF_RemoverAresta(i);
	}

	LIS_DestruirLista(pGrafo->pListaOr);
	LIS_DestruirLista(pGrafo->pListaVer);
	VER_DestruirVertice(&pGrafo->pVerCorr); /* já liberado quando destruiu lista */

	return GRF_CondRetOK;
}/* Fim da função: GRF Esvaziar Grafo */

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: Módulo Grafo **********/