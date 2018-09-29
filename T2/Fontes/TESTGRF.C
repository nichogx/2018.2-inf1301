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
*       0.30   ngx   28/09/2018 Adicionar comandos de teste para as novas
*                               funções de acesso codificadas.
*       0.20   ngx   28/09/2018 Adição de mais comandos de teste.
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
#define     ANDAR_GRF_CMD        "=andar"
#define     VOLTAR_GRF_CMD       "=voltar"
#define     REMOVER_AR_GRF_CMD   "=remaresta"
#define     ESVAZIAR_GRF_CMD     "=esvaziar"

/* Dados encapsulados no módulo */
#define MAX_STRGS 5
static char *strTestes[MAX_STRGS] = {
	"primeira string de teste",
	"segunda string de teste",
	"terceira string de teste",
	"quarta string de teste",
	"quinta string de teste"
};

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

	char *valorObtido = strTestes[0];

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

		if (NumLidos != 2 || strTesteEsperada < 1 || strTesteEsperada > MAX_STRGS) {
			return TST_CondRetParm;
		}


		CondRetObtido = GRF_ObterValorCorrente(&valorObtido);

		Ret = TST_CompararInt(CondRetEsperada, CondRetObtido,
		                      "Retorno errado ao obter valor corrente do grafo.");

		if (Ret != TST_CondRetOK) {
			return Ret;
		}

		return TST_CompararString(strTestes[strTesteEsperada - 1], valorObtido,
		                          "Valor esperado difere do obtido ao obter valor corrente do grafo.");
	} else if (strcmp(ComandoTeste, ALTERAR_GRF_CMD) == 0) {
		int strAColocar = 0;
		NumLidos = LER_LerParametros("ii", &strAColocar, &CondRetEsperada);

		if (NumLidos != 2 || strAColocar < 1 || strAColocar > MAX_STRGS) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_AlterarValorCorrente(strTestes[strAColocar - 1]);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao alterar valor corrente do grafo.");
	} else if (strcmp(ComandoTeste, IR_VERT_GRF_CMD) == 0) {
		int strVer = 0;
		NumLidos = LER_LerParametros("ii", &strVer, &CondRetEsperada);

		if (NumLidos != 2 || strVer < 1 || strVer > MAX_STRGS) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_IrVertice(strTestes[strVer - 1]);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao ir para o vertice do grafo.");
	} else if (strcmp(ComandoTeste, INSERIR_GRF_CMD) == 0) {
		int strVer = 0;
		NumLidos = LER_LerParametros("ii", &strVer, &CondRetEsperada);

		if (NumLidos != 2 || strVer < 1 || strVer > MAX_STRGS) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_InserirVertice(strTestes[strVer - 1], NULL);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao inserir vertice no grafo.");
	} else if (strcmp(ComandoTeste, REMOVER_GRF_CMD) == 0) {
		NumLidos = LER_LerParametros("i", &CondRetEsperada);

		if (NumLidos != 1) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_RemoverVerticeCorr();

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao remover vertice corrente.");
	} else if (strcmp(ComandoTeste, ADICIONAR_OR_GRF_CMD) == 0) {
		int strVer = 0;
		NumLidos = LER_LerParametros("ii", &strVer, &CondRetEsperada);

		if (NumLidos != 2 || strVer < 1 || strVer > MAX_STRGS) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_AdicionarOrigem(strTestes[strVer - 1], NULL);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao adicionar vertice origem no grafo.");
	} else if (strcmp(ComandoTeste, ADICIONAR_AR_GRF_CMD) == 0) {
		char id = 0;
		int contVerOrigem = 0;
		int contVerDestino = 0;
		NumLidos = LER_LerParametros("ciii", &id, &contVerOrigem, &contVerDestino,
		                             &CondRetEsperada);

		if (NumLidos != 4 || contVerOrigem < 1 || contVerOrigem > MAX_STRGS
		    || contVerDestino < 1 || contVerDestino > MAX_STRGS) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_AdicionarAresta(id, strTestes[contVerOrigem - 1],
		                                    strTestes[contVerDestino - 1]);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao adicionar aresta no grafo.");
	} else if (strcmp(ComandoTeste, ANDAR_GRF_CMD) == 0) {
		char id = 0;
		NumLidos = LER_LerParametros("ci", &id, &CondRetEsperada);

		if (NumLidos != 2) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_Andar(id);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao andar pelas arestas do grafo.");
	} else if (strcmp(ComandoTeste, VOLTAR_GRF_CMD) == 0) {
		char id = 0;
		NumLidos = LER_LerParametros("ci", &id, &CondRetEsperada);

		if (NumLidos != 2) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_Voltar(id);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao voltar pelas arestas do grafo.");
	} else if (strcmp(ComandoTeste, REMOVER_AR_GRF_CMD) == 0) {
		char id = 0;
		NumLidos = LER_LerParametros("ci", &id, &CondRetEsperada);

		if (NumLidos != 2) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_RemoverAresta(id);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao remover aresta do grafo.");
	} else if (strcmp(ComandoTeste, ESVAZIAR_GRF_CMD) == 0) {
		NumLidos = LER_LerParametros("i", &CondRetEsperada);

		if (NumLidos != 1) {
			return TST_CondRetParm;
		}

		CondRetObtido = GRF_EsvaziarGrafo();

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao esvaziar grafo.");
	}

	return TST_CondRetNaoConhec;

} /* Fim função: TGRF Efetuar operações de teste específicas para grafo */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
