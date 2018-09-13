#if ! defined( ANALISADOR_LEX_ )
#define ANALISADOR_LEX_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Analisador Léxico
*
*  Arquivo:                 ANALISADOR_LEX.H
*  Letras identificadoras:  LEX
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar grafos.
*     O grafo possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore. // TODO CHANGE
*     A cada momento o módulo admite no máximo uma única árvore.
*     Ao iniciar a execução do programa não existe grafo.
*     O grafo poderá estar vazio. Neste caso o nó corrente
*     será nulo, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se o grafo estiver vazio.
*
***************************************************************************/

#if defined (ANALISADOR_LEX_OWN)
#define ANALISADOR_LEX_EXT
#else
#define ANALISADOR_LEX_EXT extern
#endif // NÃO MEXER!! DEIXAR NO INICIO!! // TODO remover comentário

/***********************************************************************
*
*  $TC Tipo de dados: LEX Condicoes de retorno
*
*
***********************************************************************/

typedef enum {
	/* executou corretamente */
	LEX_CondRetOK = 0,

	/* faltou memória ao alocar dados */
	LEX_CondRetFaltouMemoria = 1
} LEX_tpCondRet;

#undef ANALISADOR_LEX_EXT // NÃO MEXER!! DEIXAR NO FINAL!! // TODO remover comentário

/********** Fim do módulo de definição: Módulo Grafo **********/

#else
#endif
