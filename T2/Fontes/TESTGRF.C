/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico (grafo)
*
*  Arquivo:                  TESTGRF.C
*  Letras identificadoras:   TGRF
*
*  Projeto: Disciplina 1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo grafo.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo grafo:
*
*     "=criar"      - chama a função GRF_CriarGrafo( )
*     "=destruir"   - chama a função GRF_DestruirGrafo( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "grafo.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_GRF_CMD        "=criar"
#define     DESTRUIR_GRF_CMD     "=destruir"
#define     OBTER_GRF_CMD        "=obter"
#define     ALTERAR_GRF_CMD      "=alterar"
#define     IR_VERT_GRF_CMD      "=ir"
#define     INSERIR_GRF_CMD      "=inserir"
#define     REMOVER_GRF_CMD      "=remover"
#define     ADICIONAR_OR_GRF_CMD "=addorigem"
#define     ADICIONAR_AR_GRF_CMD "=addaresta"
#define     REMOVER_AR_GRF_CMD   "=remaresta"
#define     ESVAZIAR_GRF_CMD     "=esvaziar"

/* Dados encapsulados no módulo */
static char *strTeste = "eu sou uma string de teste";
static char *strTeste2 = "segunda string de teste";

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRF Efetuar operações de teste específicas para grafo
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     grafo sendo testado.
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
	GRF_tpCondRet CondRetObtido   = GRF_CondRetOK;
	GRF_tpCondRet CondRetEsperada = GRF_CondRetFaltouMemoria;

	char *valorObtido = "ALO";

	int  NumLidos = -1;

	TST_tpCondRet Ret;

	/* Testar GRF Criar grafo */

	if (strcmp(ComandoTeste, CRIAR_GRF_CMD) == 0) {
		NumLidos = LER_LerParametros("i", &CondRetEsperada);
		if (NumLidos != 1) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_CriarGrafo();

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao criar grafo.");
	} else if (strcmp(ComandoTeste, DESTRUIR_GRF_CMD) == 0) {
		NumLidos = LER_LerParametros("i", &CondRetEsperada);
		if (NumLidos != 1) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_DestruirGrafo();

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao criar grafo.");
	} else if (strcmp(ComandoTeste, OBTER_GRF_CMD) == 0) {
		int strTesteEsperada = 0;
		NumLidos = LER_LerParametros("ii", &strTesteEsperada, &CondRetEsperada);

		if (NumLidos != 2 || strTesteEsperada < 1 || strTesteEsperada > 2) {
			return TST_CondRetParm;
		}


		CondRetObtido = GRF_ObterValorCorrente(&valorObtido);

		Ret = TST_CompararInt(CondRetEsperada, CondRetObtido,
		                      "Retorno errado ao obter valor corrente do grafo.");

		if (Ret != TST_CondRetOK) {
			return Ret;
		}

		if (strTesteEsperada == 1) {
			return TST_CompararString(strTeste, valorObtido,
			                          "Valor esperado difere do obtido ao obter valor corrente do grafo.");
		} else {
			return TST_CompararString(strTeste2, valorObtido,
			                          "Valor esperado difere do obtido ao obter valor corrente do grafo.");
		}
	} else if (strcmp(ComandoTeste, ALTERAR_GRF_CMD) == 0) {
		int strAColocar = 0;
		NumLidos = LER_LerParametros("ii", &strAColocar, &CondRetEsperada);

		if (NumLidos != 2 || strAColocar < 1 || strAColocar > 2) {
			return TST_CondRetParm;
		}

		if (strAColocar == 1) {
			CondRetObtido = GRF_AlterarValorCorrente(strTeste);
		} else {
			CondRetObtido = GRF_AlterarValorCorrente(strTeste2);
		}

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao alterar valor corrente do grafo.");
	}

	return TST_CondRetNaoConhec;

} /* Fim função: TGRF Efetuar operações de teste específicas para grafo */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
