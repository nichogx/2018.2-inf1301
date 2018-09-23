#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Vértice
*
*  Arquivo:                 VERTICE.H
*  Letras identificadoras:  VER
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
*     modificar vertices.
*     Um vértice possui conteúdo, uma lista de antecessores e uma lista de
*     sucessores.
*     O grafo poderá estar vazio. Neste caso o nó corrente
*     será nulo, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se o grafo estiver vazio. // TODO change
*
***************************************************************************/

#if defined (VERTICE_OWN)
#define VERTICE_EXT
#else
#define VERTICE_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: VER Condicoes de retorno
*
*
***********************************************************************/

typedef enum {
	/* executou corretamente */
	VER_CondRetOK = 0,

	/* faltou memória ao alocar dados */
	VER_CondRetFaltouMemoria = 1,

	/* não há vértice, não é possível realizar operação */
	VER_CondRetVerticeNaoExiste = 2,

	/* erro decorrente da função do módulo lista */
	VER_CondRetErroModuloLista = 3,

	/* ligacao a ser removida nao foi encontrada */
	VER_LigacaoNaoEncontrada = 4

} VER_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor de um vértice
*
*
***********************************************************************/

typedef struct VER_tgVertice VER_tpVertice;

/***********************************************************************
*
*  $FC Função: VER Criar vértice
*
*  $ED Descrição da função
*     Cria um novo vértice vazio e guarda em um ponteiro recebido.
*     O endereço que esse ponteiro guardava anteriormente será perdido.
*
*  $EP Parâmetros
*     pDest - ponteiro onde será guardado o vértice criado.
*     pConteudo - conteúdo a colocar no vértice.
*     ExcluirValor - função que libera pConteudo. Pode ser NULL se
*                    não for necessário liberar.
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*     VER_CondRetErroAoCriarLista
*
***********************************************************************/

VER_tpCondRet VER_CriarVertice(VER_tpVertice *pDest, void *pConteudo,
                               void(*ExcluirValor)(void *pConteudo));

/***********************************************************************
*
*  $FC Função: VER Destruir vértice
*
*  $ED Descrição da função
*     Destroi vértice recebido, liberando espaço de memória e anulando
*     o ponteiro recebido.
*
***********************************************************************/

void VER_DestruirVertice(VER_tpVertice *pVertice);

/***********************************************************************
*
*  $FC Função: VER Adicionar ligação
*
*  $ED Descrição da função
*     Adiciona ligação entre os dois vértices recebidos, o primeiro
*     é a origem e o segundo o destino (primeiro será antecessor,
*     segundo será sucessor).
*
*  $EP Parâmetros
*     pVerticeOr - ponteiro para o vértice onde será originada a ligação.
*     pVerticeDest - ponteiro para o vértice que será o destino da ligação.
*     nome - nome (ID) da ligação.
*
*  $FV Valor retornado
*     VER_CondRetVerticeNaoExiste - se um dos vertices recebidos for NULL
*     VER_CondRetFaltouMemoria - se não houver memória suficiente
*     VER_CondRetErroModuloLista - se houver um erro no módulo lista
*     VER_CondRetOK - se ocorreu tudo como esperado
*
***********************************************************************/

VER_tpCondRet VER_AdicionarLigacao(VER_tpVertice *pVerticeOr,
                                   VER_tpVertice *pVerticeDest,
                                   char *nome);

/***********************************************************************
*
*  $FC Função: VER Remover ligação
*
*  $ED Descrição da função
*     Busca ligação que o vértice tem (sendo esse a origem) pelo nome,
*     e remove-a, se encontrada;
*
*  $EP Parâmetros
*     pVerticeOr - ponteiro para o vértice onde é originada a ligação.
*     nome - nome (ID) da ligação.
*
*  $FV Valor retornado
*     VER_CondRetVerticeNaoExiste - se o ve'rtice recebido for NULL
*     VER_LigacaoNaoEncontrada - se não for encontrado uma ligação com esse nome
*     VER_CondRetErroModuloLista - se houver um erro no módulo lista
*     VER_CondRetOK - se ocorreu tudo como esperado
*
***********************************************************************/

VER_tpCondRet VER_RemoverLigacao(VER_tpVertice *pVerticeOr,
                                 char *nome);

#undef VERTICE_EXT

/********** Fim do módulo de definição: Módulo Vértice **********/

#else
#endif
