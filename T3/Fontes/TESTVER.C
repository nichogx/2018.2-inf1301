/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico (v�rtice)
*
*  Arquivo:                  TESTVER.C
*  Letras identificadoras:   TVER
*
*  Projeto: Disciplina 1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   ngx   30/09/2018 Vers�o de entrega. Adi��o de mais comandos de teste.
*                               Atualiza��o da documenta��o.
*       0.31   ngx   28/09/2018 Pequena altera��o para refletir mudan�a em vertice.c/.h
*       0.30   ngx   28/09/2018 Finaliza��o do m�dulo te teste
*       0.20   ngx   27/09/2018 Adi��o de mais comandos de teste
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo v�rtice.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo v�rtice:
*
*     "=criar"            - chama a fun��o VER_CriarVertice e preenche com ponteiro
*                           para uma cadeia de caracteres
*     "=destruir"         - chama a fun��o VER_DestruirVertice
*     "=free"             - chama a fun��o VER_LiberarVertice
*     "=obter" <int>      - obt�m o conte�do do v�rtice corrente e compara com a string
*                           <int> definida
*     "=atualizar" <int>  - atualiza o conte�do do v�rtice corrente com a string <int>
*     "=obterlistas"      - chama a fun��o que obt�m as listas
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "vertice.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */
#define     CRIAR_VER_CMD        "=criar"
#define     DESTRUIR_VER_CMD     "=destruir"
#define     LIBERAR_VER_CMD      "=free"
#define     OBTER_VER_CMD        "=obter"
#define     ATUALIZAR_VER_CMD    "=atualizar"
#define     OBTER_LISTAS_VER_CMD "=obterlistas"

/* Dados encapsulados no m�dulo */
static VER_tpVertice *pVert = NULL;
static char *strTeste = "eu sou uma string de teste";
static char *strTeste2 = "segunda string de teste";

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TVER Efetuar opera��es de teste espec�ficas para v�rtice
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     v�rtice sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char *ComandoTeste)
{
	/* inicializa para qualquer coisa */
	VER_tpCondRet CondRetObtido   = VER_CondRetOK;
	VER_tpCondRet CondRetEsperada = VER_CondRetFaltouMemoria;

	TST_tpCondRet Ret = TST_CondRetOK;

	int  NumLidos = -1;

	char *strObtida = strTeste;

	/* Testar VER Criar v�rtice */

	if (strcmp(ComandoTeste, CRIAR_VER_CMD) == 0) {
		NumLidos = LER_LerParametros("i", &CondRetEsperada);
		if (NumLidos != 1) {
			return TST_CondRetParm;
		}

		CondRetObtido = VER_CriarVertice(&pVert, strTeste, NULL);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao criar vertice.");
	} else if (strcmp(ComandoTeste, DESTRUIR_VER_CMD) == 0) {
		VER_DestruirVertice(&pVert);

		return TST_CondRetOK;
	} else if (strcmp(ComandoTeste, LIBERAR_VER_CMD) == 0) {
		VER_LiberarVertice(pVert);

		return TST_CondRetOK;
	} else if (strcmp(ComandoTeste, OBTER_VER_CMD) == 0) {
		int strTesteEsperada = 0;
		NumLidos = LER_LerParametros("ii", &strTesteEsperada, &CondRetEsperada);
		if (NumLidos != 2) {
			return TST_CondRetParm;
		}

		CondRetObtido = VER_ObterConteudoVertice(pVert, &strObtida);

		Ret = TST_CompararInt(CondRetEsperada, CondRetObtido,
		                      "Retorno errado ao obter conteudo do vertice.");

		if (Ret != TST_CondRetOK) {
			return Ret;
		}

		if (strTesteEsperada == 1)
			return TST_CompararString(strTeste, strObtida,
			                          "Conteudo obtido difere do esperado ao obter conteudo do vertice.");
		else if (strTesteEsperada == 2)
			return TST_CompararString(strTeste2, strObtida,
			                          "Conteudo obtido difere do esperado ao obter conteudo do vertice.");
		else {
			return TST_CondRetParm;
		}


	} else if (strcmp(ComandoTeste, ATUALIZAR_VER_CMD) == 0) {
		int strAColocar = 0;
		NumLidos = LER_LerParametros("ii", &strAColocar, &CondRetEsperada);
		if (NumLidos != 2 || strAColocar < 1 || strAColocar > 2) {
			return TST_CondRetParm;
		}

		if (strAColocar == 1) {
			CondRetObtido = VER_AtualizarConteudoVertice(pVert, strTeste);
		} else if (strAColocar == 2) {
			CondRetObtido = VER_AtualizarConteudoVertice(pVert, strTeste2);
		}

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao atualizar conteudo do vertice.");
	} else if (strcmp(ComandoTeste, OBTER_LISTAS_VER_CMD) == 0) {
		NumLidos = LER_LerParametros("i", &CondRetEsperada);
		if (NumLidos != 1) {
			return TST_CondRetParm;
		}

		CondRetObtido = VER_ObterListasAntSuc(pVert, NULL, NULL);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao obter listas do vertice.");
	}

	return TST_CondRetNaoConhec;

} /* Fim fun��o: TVER Efetuar opera��es de teste espec�ficas para v�rtice */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
