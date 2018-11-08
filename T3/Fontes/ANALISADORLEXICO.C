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
*       1.58   ngx   08/11/2018 Continuação da implementação do analisador léxico.
*       1.52   ngx   08/11/2018 Correção de documentação e protótipo de uma das funções
*                               encapsuladas.
*       1.51   ngx   07/11/2018 Documentação e comentários.
*       1.50   ngx   06/11/2018 Recodificação da parte de análise, ainda não pronta.
*       1.41   ngx   06/11/2018 Pequenas mudanças na documentação.
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
*     Disponibiliza comandos para a configuração e utilização de um analizador
*     léxico que analiza arquivos texto.
*
*  $EIU Interface com o usuário pessoa
*     Comandos específicos para utilizar o analisador lexico:
*
*     "=criar"                         - cria o grafo para usar no analisador
*     "=destruir"                      - destroi o grafo usado
*     "=inserir" <int> <str> <int2>    - insere um estado com id, tipo e nome fornecidos
*     "=addorigem" <int> <str> <int2>  - adiciona um estado inicial com id, tipo e nome fornecidos
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

static LEX_tpCondRet LEX_MostrarResultado(int linha, int coluna,
                LIS_tppLista lista, int id, char *nome);

static int LEX_ConverteConjuntos(int c);

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

		if (idOrigem == origem.id) { /* é a origem */
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

		if (idDestino == origem.id) { /* é a origem */
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

		printf("\n"); /* formatação */

		RetObtido = LEX_Analisar(nomeArq);
		if (RetObtido == LEX_CondRetErroAbrirArquivo) {
			return TST_NotificarFalha("Erro ao abrir arquivo. Possivelmente arquivo não existe.");
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
	int printado = 1;
	int deReleitura = 0;
	int comecaCol, comecaLin;

	GRF_tpCondRet GrfRetObtido;
	LEX_tpEstado *estado;

	/* pilha - sempre inserir no início e tirar do início */
	LIS_tppLista pilhaReleit = LIS_CriarLista(NULL);

	/* fila - sempre inserir no final e tirar do início */
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
			/* não pode mais transitar com o caractere
			   disponível no fluxo */

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
			/* não é caractere em branco e não é proveniente da pilha */
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
*  $FC Função: LEX Mostrar Resultado
*
*  $ED Descrição da função
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
*  $FC Função: LEX Converte Conjuntos
*
*  $ED Descrição da função
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

/********** Fim do módulo de implementação: Módulo de teste específico **********/
