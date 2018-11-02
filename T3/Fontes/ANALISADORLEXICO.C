/***************************************************************************
*  $MCI Módulo de implementação: Módulo Analisador Lexico
*
*  Arquivo:                  ANALISADORLEXICO.C
*  Letras identificadoras:   LEX
*
*  Projeto: Disciplina 1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.40   ngx   02/11/2018 Primeira versão do analisador léxico.
*       1.10   ngx   02/11/2018 Início da adaptação do módulo para o analisador léxico.
*       1.00   ngx   30/09/2018 Versão de entrega. Adição de mais comandos de teste.
*                               Atualização da documentação.
*       0.30   ngx   28/09/2018 Adicionar comandos de teste para as novas
*                               funções de acesso codificadas.
*       0.20   ngx   28/09/2018 Adição de mais comandos de teste.
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     // TODO
*
*  $EIU Interface com o usuário pessoa
*     Comandos específicos para utilizar o analisador lexico:
*
*     "=criar"                         - cria o grafo para usar no analisador
*     "=destruir"                      - destroi o grafo usado
*     "=inserir" <int> <str> <int2>    - insere um estado com id, nome e tipo fornecidos
*     "=addorigem" <int> <str> <int2>  - adiciona um estado inicial com id, nome e tipo fornecidos
*     "=addtrans" <char> <int> <int2>  - adiciona uma transição de rotulo <char> indo do estado
*                                        com id <int> para o estado com conteúdo <int2>
*     "=iniciar" <str>                 - inicia a leitura do arquivo texto de nome <str>
*     "=finalizar"                     - finaliza a leitura e libera os espaços de memória utilizados.
*                                        deverá constar no final de todos os scripts do analisador.
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

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_GRF_CMD        "=criar"
#define     DESTRUIR_GRF_CMD     "=destruir"
#define     INSERIR_GRF_CMD      "=inserir"
#define     ADICIONAR_OR_GRF_CMD "=addorigem"
#define     ADICIONAR_AR_GRF_CMD "=addtrans"
#define     INICIAR_LEX_CMD      "=iniciar"
#define     FINALIZAR_LEX_CMD    "=finalizar"

/***********************************************************************
*
*  $TC Tipo de dados: LEX Condição de Retorno
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

	/* arquivo não está conforme analisador configurado */
	LEX_CondRetErroSintaxeArquivo = 3,

	/* erro em outro modulo */
	LEX_CondRetErroModuloExt = 4,

	/* erro na configuração do analisador
	por exemplo, não foi inserida uma origem
	ou não foi criado o grafo */
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

	/* estado intermediário */
	LEX_TipoEstadoIntermediario = 1,

	/* estado final */
	LEX_TipoEstadoFinal = 2

} LEX_tpTipoEstado;

/***********************************************************************
*
*  $TC Tipo de dados: LEX Descritor de um estado
*
*
*  $ED Descrição do tipo
*     Um estado do analisador que contém id, nome e tipo
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

/* Dados encapsulados no módulo */
static LEX_tpEstado origem;
static LIS_tppLista endEstados = NULL;

/***** Protótipos das funções encapuladas no módulo *****/

static LEX_tpCondRet LEX_Analisar(char *nomeArq);

static LEX_tpCondRet LEX_MostrarResultado(int linha, int coluna, int id,
                char *nome);

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

		if (idOrigem == origem.id) { /* é a origem */
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

		if (idDestino == origem.id) { /* é a origem */
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

} /* Fim função: TGRF Efetuar operações de teste específicas para grafo */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: LEX Analisar
*
*  $ED Descrição da função
*     Analisa um arquivo do início ao fim
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
					ungetc(ant, fp); /* desfaz o fgetc no início do if
							 que checava o próximo caractere */
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
*  $FC Função: LEX Mostrar Resultado
*
*  $ED Descrição da função
*     Mostra o resultado de um lexema
*
***********************************************************************/
LEX_tpCondRet LEX_MostrarResultado(int linha, int coluna, int id, char *nome)
{
	printf("LINHA: %3d COLUNA: %3d ID: %3d NOME: %s\n", linha, coluna, id, nome);
	return LEX_CondRetOK;
}

/********** Fim do módulo de implementação: Módulo de teste específico **********/
