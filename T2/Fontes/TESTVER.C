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
#define     CRIAR_VER_CMD       "=criar"
#define     DESTRUIR_VER_CMD    "=destruir"

/* Dados encapsulados no módulo */
static VER_tpVertice *pVert = NULL;
static char *strTeste = "eu sou uma string de teste";

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

	int  NumLidos = -1;

	TST_tpCondRet Ret;

	/* Testar VER Criar vértice */

	if (strcmp(ComandoTeste, CRIAR_VER_CMD) == 0) {
		NumLidos = LER_LerParametros("i", &CondRetEsperada);
		if (NumLidos != 1)
			return TST_CondRetParm;

		CondRetObtido = VER_CriarVertice(pVert, &strTeste, NULL);

		return TST_CompararInt(CondRetEsperada, CondRetObtido,
		                       "Retorno errado ao criar vertice.");
	} else if (strcmp(ComandoTeste, DESTRUIR_VER_CMD) == 0) {
		VER_DestruirVertice(pVert);

		return TST_CondRetOK;
	}

	return TST_CondRetNaoConhec;

} /* Fim função: TVER Efetuar operações de teste específicas para vértice */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
