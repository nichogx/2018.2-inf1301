/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico (analisador léxico)
*
*  Arquivo:                  TESTLEX.C
*  Letras identificadoras:   TLEX
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
*     módulo analisador lexico.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo analisador lexico:
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "analisador_lex.h"

/* Tabela dos nomes dos comandos de teste específicos */

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLEX Efetuar operações de teste específicas para 
*              analisador lexico
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     analisador lexico sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	LEX_tpCondRet CondRetObtido   = LEX_CondRetOK;
	LEX_tpCondRet CondRetEsperada = LEX_CondRetFaltouMemoria;
                                      /* inicializa para qualquer coisa */

	int  NumLidos = -1;

	TST_tpCondRet Ret;

	return TST_CondRetNaoConhec;

   } /* Fim função: TLEX Efetuar operações de teste específicas para analisador lexico */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

