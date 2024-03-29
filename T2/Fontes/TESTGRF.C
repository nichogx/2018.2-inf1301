/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico (grafo)
*
*  Arquivo:                  TESTGRF.C
*  Letras identificadoras:   TGRF
*
*  Projeto: Disciplina 1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   ngx   30/09/2018 Vers�o de entrega. Adi��o de mais comandos de teste.
*                               Atualiza��o da documenta��o.
*       0.30   ngx   28/09/2018 Adicionar comandos de teste para as novas
*                               fun��es de acesso codificadas.
*       0.20   ngx   28/09/2018 Adi��o de mais comandos de teste.
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo grafo.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo grafo:
*
*     "=criar"           - chama a fun��o GRF_CriarGrafo( )
*     "=destruir"        - chama a fun��o GRF_DestruirGrafo( )
*     "=obter" <int>     - obtem o conte�do do corrente e compara com a string <int>
*     "=alterar" <int>   - altera o conteudo do corrente para a string <int>
*     "=ir" <int>        - vai para o v�rtice que tem o conteudo da string <int>
*     "=inserir" <int>   - insere um v�rtice com o conte�do da string <int>
*     "=remover"         - remove o corrente
*     "=addorigem" <int> - adiciona um v�rtice origem com o conte�do da string <int>
*     "=addaresta" <char> <int> <int2> - adiciona uma aresta de id <char> indo do v�rtice
*                                        com conte�do <int> para o v�rtice com conte�do <int2>
*     "=andar" <char>    - andar pela aresta <char> do vertice corrente
*     "=voltar" <char>   - voltar pela aresta < char> do vertice corrente
*     "=remaresta" <char> - remove a aresta <char>
*     "=esvaziar"        - esvazia o grafo.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "grafo.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

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

/* Dados encapsulados no m�dulo */
#define MAX_STRGS 5
static char *strTestes[MAX_STRGS] = {
	"primeira string de teste",
	"segunda string de teste",
	"terceira string de teste",
	"quarta string de teste",
	"quinta string de teste"
};

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TGRF Efetuar opera��es de teste espec�ficas para grafo
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     grafo sendo testado.
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

} /* Fim fun��o: TGRF Efetuar opera��es de teste espec�ficas para grafo */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
