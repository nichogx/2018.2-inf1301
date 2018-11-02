/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Analisador Lexico
*
*  Arquivo:                  ANALISADORLEXICO.C
*  Letras identificadoras:   LEX
*
*  Projeto: Disciplina 1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.40   ngx   02/11/2018 Primeira vers�o do analisador l�xico.
*       1.10   ngx   02/11/2018 In�cio da adapta��o do m�dulo para o analisador l�xico.
*       1.00   ngx   30/09/2018 Vers�o de entrega. Adi��o de mais comandos de teste.
*                               Atualiza��o da documenta��o.
*       0.30   ngx   28/09/2018 Adicionar comandos de teste para as novas
*                               fun��es de acesso codificadas.
*       0.20   ngx   28/09/2018 Adi��o de mais comandos de teste.
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     // TODO
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos espec�ficos para utilizar o analisador lexico:
*
*     "=criar"                         - cria o grafo para usar no analisador
*     "=destruir"                      - destroi o grafo usado
*     "=inserir" <int> <str> <int2>    - insere um estado com id, nome e tipo fornecidos
*     "=addorigem" <int> <str> <int2>  - adiciona um estado inicial com id, nome e tipo fornecidos
*     "=addtrans" <char> <int> <int2>  - adiciona uma transi��o de rotulo <char> indo do estado
*                                        com id <int> para o estado com conte�do <int2>
*     "=iniciar" <str>                 - inicia a leitura do arquivo texto de nome <str>
*     "=finalizar"                     - finaliza a leitura e libera os espa�os de mem�ria utilizados.
*                                        dever� constar no final de todos os scripts do analisador.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"
#include    "VERTICE.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "grafo.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_GRF_CMD        "=criar"
#define     DESTRUIR_GRF_CMD     "=destruir"
#define     INSERIR_GRF_CMD      "=inserir"
#define     ADICIONAR_OR_GRF_CMD "=addorigem"
#define     ADICIONAR_AR_GRF_CMD "=addtrans"
#define     INICIAR_LEX_CMD      "=iniciar"
#define     FINALIZAR_LEX_CMD    "=finalizar"

/***********************************************************************
*
*  $TC Tipo de dados: LEX Condi��o de Retorno
*
*
***********************************************************************/

typedef enum {
	/* executou corretamente */
	LEX_CondRetOK = 0,

	/* faltou memoria */
	LEX_CondRetFaltouMemoria = 1,

	/* erro ao abrir arquivo */
	LEX_CondRetErroAbrirArquivo = 2,

	/* arquivo n�o est� conforme analisador configurado */
	LEX_CondRetErroSintaxeArquivo = 3,

	/* erro em outro modulo */
	LEX_CondRetErroModuloExt = 4,

	/* erro na configura��o do analisador
	por exemplo, n�o foi inserida uma origem
	ou n�o foi criado o grafo */
	LEX_CondRetErroConfiguracao = 5

} LEX_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: LEX Tipo de Estado
*
*
***********************************************************************/

typedef enum {
	/* estado inicial */
	LEX_TipoEstadoInicial = 0,

	/* estado intermedi�rio */
	LEX_TipoEstadoIntermediario = 1,

	/* estado final */
	LEX_TipoEstadoFinal = 2

} LEX_tpTipoEstado;

/***********************************************************************
*
*  $TC Tipo de dados: LEX Descritor de um estado
*
*
*  $ED Descri��o do tipo
*     Um estado do analisador que cont�m id, nome e tipo
*
***********************************************************************/

typedef struct LEX_tgEstado {
	/* id do estado */
	int id;

	/* nome do estado */
	char nome[51];

	/* tipo do estado */
	LEX_tpTipoEstado tipo;

} LEX_tpEstado;

/* Dados encapsulados no m�dulo */
static LEX_tpEstado origem;
static LIS_tppLista endEstados = NULL;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static LEX_tpCondRet LEX_Analisar(char *nomeArq);

static LEX_tpCondRet LEX_MostrarResultado(int linha, int coluna, int id,
                char *nome);

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

	int  NumLidos = -1;

	if (endEstados == NULL) {
		endEstados = LIS_CriarLista(NULL);
	}

	/* Efetuar Comando */

	if (strcmp(ComandoTeste, CRIAR_GRF_CMD) == 0) {
		CondRetObtido = GRF_CriarGrafo();

		return TST_CompararInt(GRF_CondRetOK, CondRetObtido, "Erro ao criar grafo.");
	} else if (strcmp(ComandoTeste, DESTRUIR_GRF_CMD) == 0) {
		CondRetObtido = GRF_DestruirGrafo();

		return TST_CompararInt(GRF_CondRetOK, CondRetObtido, "Erro ao destruir grafo.");
	} else if (strcmp(ComandoTeste, INSERIR_GRF_CMD) == 0) {
		char nome[51];
		int id, tipo;

		LEX_tpEstado *estado = (LEX_tpEstado *) malloc(sizeof(LEX_tpEstado));
		if (estado == NULL) {
			return TST_CondRetMemoria;
		}

		NumLidos = LER_LerParametros("iis", &id, &tipo, nome);

		if (tipo == LEX_TipoEstadoFinal && (NumLidos != 3 || strlen(nome) > 50) ||
		    tipo != LEX_TipoEstadoFinal && (NumLidos != 2)) {
			return TST_CondRetParm;
		} /* if */

		estado->id = id;
		estado->tipo = tipo;
		if (tipo == LEX_TipoEstadoFinal) {
			strcpy(estado->nome, nome);
		}

		CondRetObtido = GRF_InserirVertice(estado, free);
		LIS_InserirElementoApos(endEstados, estado);

		return TST_CompararInt(GRF_CondRetOK, CondRetObtido, "Erro ao inserir estado.");
	} else if (strcmp(ComandoTeste, ADICIONAR_OR_GRF_CMD) == 0) {
		char nome[51];
		int id, tipo;
		NumLidos = LER_LerParametros("iis", &id, &tipo, nome);

		if (tipo == LEX_TipoEstadoFinal && (NumLidos != 3 || strlen(nome) > 50) ||
			tipo != LEX_TipoEstadoFinal && (NumLidos != 2)) {
			return TST_CondRetParm;
		} /* if */

		origem.id = id;
		origem.tipo = tipo;
		if (tipo == LEX_TipoEstadoFinal) {
			strcpy(origem.nome, nome);
		}

		CondRetObtido = GRF_AdicionarOrigem(&origem, NULL);

		return TST_CompararInt(GRF_CondRetOK, CondRetObtido,
		                       "Erro ao inserir estado origem.");
	} else if (strcmp(ComandoTeste, ADICIONAR_AR_GRF_CMD) == 0) {
		char trans;
		int idOrigem, idDestino;
		LEX_tpEstado *estOrigem, *estDestino;
		NumLidos = LER_LerParametros("cii", &trans, &idOrigem, &idDestino);

		if (NumLidos != 3) {
			return TST_CondRetParm;
		} /* if */

		if (idOrigem == origem.id) { /* � a origem */
			estOrigem = &origem;
		} else { /* pesquisar na lista de estados */
			IrInicioLista(endEstados);
			do {
				estOrigem = LIS_ObterValor(endEstados);
				if (estOrigem == NULL) {
					return LEX_CondRetErroConfiguracao;
				}
			} while (LIS_AvancarElementoCorrente(endEstados, 1) != LIS_CondRetFimLista
			         && estOrigem->id != idOrigem);
		} /* if */

		if (idDestino == origem.id) { /* � a origem */
			estDestino = &origem;
		} else { /* pesquisar na lista de estados */
			IrInicioLista(endEstados);
			do {
				estDestino = LIS_ObterValor(endEstados);
				if (estDestino == NULL) {
					return LEX_CondRetErroConfiguracao;
				}
			} while (LIS_AvancarElementoCorrente(endEstados, 1) != LIS_CondRetFimLista
			         && estDestino->id != idDestino);
		} /* if */

		CondRetObtido = GRF_AdicionarAresta(trans, estOrigem, estDestino);

		return TST_CompararInt(GRF_CondRetOK, CondRetObtido,
		                       "Erro ao criar transicao.");
	} else if (strcmp(ComandoTeste, INICIAR_LEX_CMD) == 0) {
		char nomeArq[51];
		LEX_tpCondRet RetObtido;
		NumLidos = LER_LerParametros("s", nomeArq);

		if (NumLidos != 1) {
			return TST_CondRetParm;
		}

		RetObtido = LEX_Analisar(nomeArq);

		return TST_CompararInt(LEX_CondRetOK, RetObtido,
		                       "Retorno errado ao analisar arquivo.");
	} else if (strcmp(ComandoTeste, FINALIZAR_LEX_CMD) == 0) {
		LIS_DestruirLista(endEstados);
		return TST_CondRetOK;
	}

	return TST_CondRetNaoConhec;

} /* Fim fun��o: TGRF Efetuar opera��es de teste espec�ficas para grafo */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: LEX Analisar
*
*  $ED Descri��o da fun��o
*     Analisa um arquivo do in�cio ao fim
*
***********************************************************************/
LEX_tpCondRet LEX_Analisar(char *nomeArq)
{
	FILE *fp;
	int c;
	int coluna = 1;
	int linha  = 1;

	GRF_tpCondRet GrfRetObtido;

	if ((fp = fopen(nomeArq, "r")) == NULL) {
		return LEX_CondRetErroAbrirArquivo;
	} /* if */

	while ((c = fgetc(fp)) != EOF) {
		LEX_tpEstado *estado;

		/* trata custom eof */
		if (c == '\f') {
			break;
		}

		/* trata os conjuntos */
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			c = '\a';
		} else if (c >= '0' && c <= '9') {
			c = '\x1';
		} else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
			c = '\x2';
		} /* if */

		GrfRetObtido = GRF_Andar((unsigned char) c);

		if (GrfRetObtido == GRF_CondRetErroEstrutura) {
			return LEX_CondRetErroModuloExt;
		} else if (GrfRetObtido == GRF_CondRetArestaNaoExiste) {
			c = '\v'; /* tratar caso caractrere 'outros' */
			GrfRetObtido = GRF_Andar((unsigned char) c);
		} /* if */

		if (GrfRetObtido != GRF_CondRetOK) {
			return LEX_CondRetErroSintaxeArquivo;
		} /* if */

		GrfRetObtido = GRF_ObterValorCorrente(&estado);
		if (estado->tipo == LEX_TipoEstadoFinal) {
			int ant = c;
			c = fgetc(fp);
			GrfRetObtido = GRF_Andar((unsigned char) c);

			if (GrfRetObtido == GRF_CondRetErroEstrutura) {
				return LEX_CondRetErroModuloExt;
			} else if (GrfRetObtido == GRF_CondRetArestaNaoExiste) {
				c = '\v'; /* tratar caso caractrere 'outros' */
				GrfRetObtido = GRF_Andar((unsigned char) c);
				if (GrfRetObtido == GRF_CondRetArestaNaoExiste) {
					LEX_MostrarResultado(linha, coluna, estado->id, estado->nome);
					ungetc(ant, fp); /* desfaz o fgetc no in�cio do if
							 que checava o pr�ximo caractere */
					if (GRF_IrVertice(&origem) != GRF_CondRetOK) {
						return LEX_CondRetErroConfiguracao;
					}
				} else if (GrfRetObtido != GRF_CondRetOK) {
					return LEX_CondRetErroSintaxeArquivo;
				} /* if */
			} else if (GrfRetObtido != GRF_CondRetOK) {
				return LEX_CondRetErroSintaxeArquivo;
			} /* if */
		} /* if */

		if (c == '\n') {
			coluna = 1;
			linha++;
		} else {
			coluna++;
		} /* if */
	} /* while */

	return LEX_CondRetOK;
}

/***********************************************************************
*
*  $FC Fun��o: LEX Mostrar Resultado
*
*  $ED Descri��o da fun��o
*     Mostra o resultado de um lexema
*
***********************************************************************/
LEX_tpCondRet LEX_MostrarResultado(int linha, int coluna, int id, char *nome)
{
	printf("LINHA: %3d COLUNA: %3d ID: %3d NOME: %s\n", linha, coluna, id, nome);
	return LEX_CondRetOK;
}

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/