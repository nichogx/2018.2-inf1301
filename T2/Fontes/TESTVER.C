/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico (vértice)
*
*  Arquivo:                  TESTVER.C
*  Letras identificadoras:   TVER
*
*  Projeto: Disciplina 1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       0.31   ngx   28/09/2018 Pequena alteração para refletir mudança em vertice.c/.h
*       0.30   ngx   28/09/2018 Finalização do módulo te teste
*       0.20   ngx   27/09/2018 Adição de mais comandos de teste
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo vértice.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo vértice:
*
*     "=criar"      - chama a função VER_CriarVertice e preenche com ponteiro
*                     para uma cadeia de caracteres
*     "=destruir"   - chama a função VER_DestruirVertice
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "vertice.h"

/* Tabela dos nomes dos comandos de teste específicos */
#define     CRIAR_VER_CMD        "=criar"
#define     DESTRUIR_VER_CMD     "=destruir"
#define     LIBERAR_VER_CMD      "=free"
#define     OBTER_VER_CMD        "=obter"
#define     ATUALIZAR_VER_CMD    "=atualizar"
#define     OBTER_LISTAS_VER_CMD "=obterlistas"

/* Dados encapsulados no módulo */
static VER_tpVertice *pVert = NULL;
static char *strTeste = "eu sou uma string de teste";
static char *strTeste2 = "segunda string de teste";

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TVER Efetuar operações de teste específicas para vértice
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     vértice sendo testado.
*
*  $EP Parâmetros
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

	/* Testar VER Criar vértice */

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

} /* Fim função: TVER Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
