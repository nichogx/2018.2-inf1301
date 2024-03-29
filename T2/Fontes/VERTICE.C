/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo V�rtice
*
*  Arquivo:                 VERTICE.C
*  Letras identificadoras:  VER
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.01   ngx   01/10/2018 Coment�rios.
*       1.00   ngx   30/09/2018 Vers�o de entrega.
*       0.55   ngx   28/09/2018 Separar libera��o e destrui��o do v�rtice
*       0.50   ngx   28/09/2018 M�dulo funciona como esperado
*       0.40   ngx   27/09/2018 Continua��o da codifica��o do m�dulo.
*                               Modifica��es na estrutura.
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
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
*  $TC Tipo de dados: VER Descritor de um v�rtice
*
*
*  $ED Descri��o do tipo
*     Um v�rtice gen�rico que cont�m conte�do, lista de antecessores e
*     sucessores.
*
***********************************************************************/

struct VER_tgVertice {
	/* conte�do do v�rtice */
	void *pConteudo;

	/* ponteiro para uma fun��o que dest�i pConteudo */
	void(*ExcluirValor)(void *pConteudo);

	/* lista de antecessores */
	LIS_tppLista pListaAnt;

	/* lista de sucessores */
	LIS_tppLista pListaSuc;
};

/*****  Dados encapsulados no m�dulo  *****/

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: VER Criar v�rtice
*  ****/

VER_tpCondRet VER_CriarVertice(VER_tpVertice **pDest, void *pConteudo,
                               void(*ExcluirValor)(void *pConteudo))
{
	(*pDest) = (VER_tpVertice *) malloc(sizeof(VER_tpVertice));
	if ((*pDest) == NULL) {
		return VER_CondRetFaltouMemoria;
	} /* if */

	(*pDest)->pConteudo = pConteudo;
	(*pDest)->ExcluirValor = ExcluirValor;
	(*pDest)->pListaAnt = LIS_CriarLista(NULL);
	(*pDest)->pListaSuc = LIS_CriarLista(NULL);

	if ((*pDest)->pListaAnt == NULL || (*pDest)->pListaSuc == NULL) {
		return VER_CondRetFaltouMemoria;
	} /* if */

	return VER_CondRetOK;
} /* fim fun��o: VER Criar v�rtice */

/***************************************************************************
*
*  Fun��o: VER Destruir v�rtice
*  ****/

void VER_DestruirVertice(VER_tpVertice **pVertice)
{
	(*pVertice) = NULL;
} /* fim fun��o: VER Destruir v�rtice */

/***************************************************************************
*
*  Fun��o: VER Liberar v�rtice
*  ****/

void VER_LiberarVertice(VER_tpVertice *pVertice)
{
	if (pVertice != NULL) {
		LIS_DestruirLista(pVertice->pListaAnt);
		LIS_DestruirLista(pVertice->pListaSuc);
		if (pVertice->ExcluirValor != NULL) { /* foi passada fun��o para destruir valor */
			pVertice->ExcluirValor(pVertice->pConteudo); /* chamar essa fun��o */
		} /* if */

		free(pVertice);
	} /* if */
} /* fim fun��o: VER Liberar v�rtice */

/***************************************************************************
*
*  Fun��o: VER Obter Conteudo Vertice
*  ****/

VER_tpCondRet VER_ObterConteudoVertice(VER_tpVertice *pVertice, void **conteudo)
{
	if (pVertice == NULL) {
		return VER_CondRetVerticeNaoExiste;
	} /* if */

	*conteudo = pVertice->pConteudo;

	return VER_CondRetOK;
} /* fim fun��o: VER Obter Conteudo Vertice */

/***************************************************************************
*
*  Fun��o: VER Atualizar Conteudo Vertice
*  ****/

VER_tpCondRet VER_AtualizarConteudoVertice(VER_tpVertice *pVertice,
                void *conteudo)
{
	if (pVertice == NULL) {
		return VER_CondRetVerticeNaoExiste;
	} /* if */

	if (pVertice->ExcluirValor != NULL) { /* foi passada fun��o para destruir valor */
		pVertice->ExcluirValor(pVertice->pConteudo); /* chamar essa fun��o */
	} /* if */
	pVertice->pConteudo = conteudo;

	return VER_CondRetOK;
} /* fim fun��o: VER Atualizar Conteudo Vertice */

/***************************************************************************
*
*  Fun��o: VER Obter Antecessores e Sucessores
*  ****/

VER_tpCondRet VER_ObterListasAntSuc(VER_tpVertice *pVertice,
                                    LIS_tppLista *antecessores, LIS_tppLista *sucessores)
{
	if (pVertice == NULL) {
		return VER_CondRetVerticeNaoExiste;
	} /* if */

	if (antecessores != NULL) { /* foi passado um ponteiro para depositar essa lista */
		*antecessores = pVertice->pListaAnt;
	} /* if */

	if (sucessores != NULL) { /* foi passado um ponteiro para depositar essa lista */
		*sucessores = pVertice->pListaSuc;
	} /* if */

	return VER_CondRetOK;
} /* fim fun��o: VER Obter Antecessores e Sucessores */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/********** Fim do m�dulo de implementa��o: M�dulo V�rtice **********/
