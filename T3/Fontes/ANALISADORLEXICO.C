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
*       1.58   ngx   08/11/2018 Continua��o da implementa��o do analisador l�xico.
*       1.52   ngx   08/11/2018 Corre��o de documenta��o e prot�tipo de uma das fun��es
*                               encapsuladas.
*       1.51   ngx   07/11/2018 Documenta��o e coment�rios.
*       1.50   ngx   06/11/2018 Recodifica��o da parte de an�lise, ainda n�o pronta.
*       1.41   ngx   06/11/2018 Pequenas mudan�as na documenta��o.
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
*     Disponibiliza comandos para a configura��o e utiliza��o de um analizador
*     l�xico que analiza arquivos texto.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos espec�ficos para utilizar o analisador lexico:
*
*     "=criar"                         - cria o grafo para usar no analisador
*     "=destruir"                      - destroi o grafo usado
*     "=inserir" <int> <str> <int2>    - insere um estado com id, tipo e nome fornecidos
*     "=addorigem" <int> <str> <int2>  - adiciona um estado inicial com id, tipo e nome fornecidos
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

/* Tabela dos nomes dos comandos */

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

static LEX_tpCondRet LEX_MostrarResultado(int linha, int coluna,
                LIS_tppLista lista, int id, char *nome);

static int LEX_ConverteConjuntos(int c);

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
		estado->tipo = (LEX_tpTipoEstado) tipo;
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
		origem.tipo = (LEX_tpTipoEstado) tipo;
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
				estOrigem = (LEX_tpEstado*) LIS_ObterValor(endEstados);
				if (estOrigem == NULL) {
					return TST_CondRetNaoExecutou;
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
					return TST_CondRetNaoExecutou;
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

		printf("\n"); /* formata��o */

		RetObtido = LEX_Analisar(nomeArq);
		if (RetObtido == LEX_CondRetErroAbrirArquivo) {
			return TST_NotificarFalha("Erro ao abrir arquivo. Possivelmente arquivo n�o existe.");
		} else if (RetObtido == LEX_CondRetErroSintaxeArquivo) {
			return TST_NotificarFalha("Erro na sintaxe do arquivo.");
		}

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
	int printado = 1;
	int deReleitura = 0;
	int comecaCol, comecaLin;

	GRF_tpCondRet GrfRetObtido;
	LEX_tpEstado *estado;

	/* pilha - sempre inserir no in�cio e tirar do in�cio */
	LIS_tppLista pilhaReleit = LIS_CriarLista(NULL);

	/* fila - sempre inserir no final e tirar do in�cio */
	LIS_tppLista strReconhecida = LIS_CriarLista(free);

	if ((fp = fopen(nomeArq, "r")) == NULL) {
		return LEX_CondRetErroAbrirArquivo;
	} /* if */

	if (GRF_IrVertice(&origem) != GRF_CondRetOK) {
		return LEX_CondRetErroConfiguracao;
	} /* if */

	comecaCol = coluna;
	comecaLin = linha;

	c = fgetc(fp);
	while (c != EOF) {
		int *cRec = (int *)malloc(sizeof(int));
		if (cRec == NULL) {
			return LEX_CondRetFaltouMemoria;
		}

		*cRec = c;

		if (c == '\n' && !deReleitura) {
			coluna = 1;
			linha++;
		} else {
			coluna++;
		}

		printado = 0;

		GRF_ObterValorCorrente(&estado);

		c = LEX_ConverteConjuntos(c);
		GrfRetObtido = GRF_Andar((unsigned char) c);

		GRF_ObterValorCorrente(&estado);
		if (estado->tipo == LEX_TipoEstadoInicial) {
			comecaCol = coluna;
			comecaLin = linha;
		}

		if (GrfRetObtido == GRF_CondRetErroEstrutura) {
			return LEX_CondRetErroModuloExt;
		} else if (GrfRetObtido == GRF_CondRetArestaNaoExiste) {
			/* tratar caso caractere 'outros' */
			GrfRetObtido = GRF_Andar((unsigned char) '\v');
		} /* if */

		if (GrfRetObtido != GRF_CondRetOK) {
			/* n�o pode mais transitar com o caractere
			   dispon�vel no fluxo */

			IrInicioLista(pilhaReleit);
			LIS_InserirElementoAntes(pilhaReleit, cRec);

			GrfRetObtido = GRF_ObterValorCorrente(&estado);
			if (GrfRetObtido != GRF_CondRetOK) {
				return LEX_CondRetErroConfiguracao;
			} /* if */

			if (estado->tipo == LEX_TipoEstadoFinal) {
				printado = 1;

				LEX_MostrarResultado(comecaLin, comecaCol, strReconhecida, estado->id,
				                     estado->nome);
				GRF_IrVertice(&origem);
				comecaCol = coluna;
				comecaLin = linha;
			} /* if */

		} /* if */

		if (LEX_ConverteConjuntos(*cRec) != '\x2' && !deReleitura) {
			/* n�o � caractere em branco e n�o � proveniente da pilha */
			LIS_InserirElementoApos(strReconhecida, cRec);
		}

		IrInicioLista(pilhaReleit);
		if (LIS_ObterValor(pilhaReleit) != NULL) {
			c = *(int *) LIS_ObterValor(pilhaReleit);
			deReleitura++;
			LIS_ExcluirElemento(pilhaReleit);
		} else {
			deReleitura = 0;
			c = fgetc(fp);
		}
	} /* while */

	if (!printado) {
		GRF_ObterValorCorrente(&estado);
		LEX_MostrarResultado(comecaLin, comecaCol, strReconhecida, estado->id,
		                     estado->nome);
	}

	LIS_DestruirLista(strReconhecida);
	LIS_DestruirLista(pilhaReleit);

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
LEX_tpCondRet LEX_MostrarResultado(int linha, int coluna, LIS_tppLista lista,
                                   int id, char *nome)
{
	printf("LINHA: %3d COLUNA: %3d ID: %3d NOME: %20s STRING:  ", linha, coluna,
	       id, nome);

	IrInicioLista(lista);
	do {
		char *c = (char *) LIS_ObterValor(lista);
		if (c != NULL) {
			printf("%c", *c);
		} /* if */
	} while (LIS_AvancarElementoCorrente(lista, 1) == LIS_CondRetOK);
	printf("\n");

	LIS_EsvaziarLista(lista);

	return LEX_CondRetOK;
}

/***********************************************************************
*
*  $FC Fun��o: LEX Converte Conjuntos
*
*  $ED Descri��o da fun��o
*     Trata os conjuntos de caracteres disponibilizados.
*
***********************************************************************/
int LEX_ConverteConjuntos(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		return '\a';
	} else if (c >= '0' && c <= '9') {
		return '\x1';
	} else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
		return '\x2';
	} /* if */

	return c;
}

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
