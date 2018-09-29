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
*       0.58   ngx   29/09/2018 Atualização da documentação e adição de
*                               assertivas de entrada e saída.
*       0.55   ngx   28/09/2018 Separar liberação e destruição do vértice
*       0.50   ngx   28/09/2018 Módulo funciona como esperado
*       0.40   ngx   27/09/2018 Continuação da codificação do módulo.
*                               Modificações na estrutura.
*       0.10   ngx   13/09/2018 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     modificar vertices.
*     Um vértice possui conteúdo, uma lista de antecessores e uma lista de
*     sucessores.
*     Um vértice tem seu conteúdo e listas adicionados na criação.
*
***************************************************************************/

#if defined (VERTICE_OWN)
#define VERTICE_EXT
#else
#define VERTICE_EXT extern
#endif

#include "LISTA.H"

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
	VER_LigacaoNaoEncontrada = 4,

	/*aresta nao foi encontrada */
	VER_CondRetArestaNaoExiste = 5

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
*     pDest - endereço do ponteiro onde será guardado o vértice criado.
*     pConteudo - conteúdo a colocar no vértice.
*     ExcluirValor - ponteiro para função que libera pConteudo. Pode ser NULL se
*                    não for necessário liberar.
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetFaltouMemoria
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido não aponta outro vértice já criado.
*     A função ExcluirValor recebida libera a memória de pConteudo.
*     O ponteiro pConteudo é um ponteiro para o conteúdo que será inserido.
*
*  $AS Assertivas de Saída
*     O vértice foi criado e preenchido com o conteúdo recebido.
*     As listas de antecessores e sucessores foram criadas e estão vazias.
*
***********************************************************************/

VER_tpCondRet VER_CriarVertice(VER_tpVertice **pDest, void *pConteudo,
                               void(*ExcluirValor)(void *pConteudo));

/***********************************************************************
*
*  $FC Função: VER Destruir vértice
*
*  $EP Parâmetros
*     pVertice - endereço do ponteiro que contém o vértice
*
*  $ED Descrição da função
*     Anula o ponteiro para vértice recebido, destruindo-o.
*     As outras funções reconhecerão esse ponteiro como um vértice que não existe.
*     Não libera o espaço de memória.
*     O espaço de memória deve ser liberado antes com VER_LiberarVertice.
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um vértice já liberado.
*
*  $AS Assertivas de Saída
*     O ponteiro recebido agora é NULO.
*     As outras funções reconhecerão esse ponteiro como um vértice inexistente.
*
***********************************************************************/

void VER_DestruirVertice(VER_tpVertice **pVertice);

/***********************************************************************
*
*  $FC Função: VER Liberar vértice
*
*  $EP Parâmetros
*     pVertice - ponteiro que contém o vértice
*
*  $ED Descrição da função
*     Libera espaço de memória do vértice recebido, porém não o anula.
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um vértice já criado e ainda não liberado.
*
*  $AS Assertivas de Saída
*     O vértice foi liberado e a área apontada pelo ponteiro recebido 
*     não é mais de controle do programa.
*
***********************************************************************/

void VER_LiberarVertice(VER_tpVertice *pVertice);

/***********************************************************************
*
*  $FC Função: VER Obter Conteudo Vertice
*
*  $ED Descrição da função
*     O ponteiro recebido por referência passa a apontar o conteúdo do vértice recebido.
*
*  $EP Parâmetros
*     pVertice - ponteiro para vértice a extrair conteúdo
*     conteudo - endereço do ponteiro que apontará o conteúdo do vértice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeNaoExiste
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um vértice já criado.
*
*  $AS Assertivas de Saída
*     O ponteiro conteudo recebido por referência agora aponta o 
*     conteúdo do vértice recebido.
*
***********************************************************************/

VER_tpCondRet VER_ObterConteudoVertice(VER_tpVertice *pVertice,
                                       void **conteudo);

/***********************************************************************
*
*  $FC Função: VER Atualiar Conteudo Vertice
*
*  $ED Descrição da função
*     O conteúdo recebido substituirá o conteúdo do vértice recebido.
*
*  $EP Parâmetros
*     pVertice - ponteiro para vértice a modificar conteúdo
*     conteudo - conteúdo que substituirá
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeNaoExiste
*
*  $AE Assertivas de Entrada
*     O ponteiro pVertice recebido aponta um vértice já criado.
*
*  $AS Assertivas de Saída
*     O conteúdo antigo do vértice foi excluído, e agora o conteúdo é o 
*     que foi recebido.
*
***********************************************************************/

VER_tpCondRet VER_AtualizarConteudoVertice(VER_tpVertice *pVertice,
                void *conteudo);

/***********************************************************************
*
*  $FC Função: VER Atualiar Conteudo Vertice
*
*  $ED Descrição da função
*     Os ponteiros recebidos por referência apontarão as listas de antecessores
*     e sucessores do vértice recebido. Esses ponteiros podem ser nulos caso
*     não seja desejada uma das listas.
*
*  $EP Parâmetros
*     pVertice - ponteiro para vértice a modificar conteúdo
*     antecessores - endereço do ponteiro que apontará a lista de antecessores
*     sucessores - endereço do ponteiro que apontará a lista de sucessores
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeNaoExiste
*
*  $AE Assertivas de Entrada
*     O ponteiro recebido aponta um vértice já criado.
*     Os parâmetros antecessores e sucessores são ponteiros para lista 
*     recebidos por referência, ou NULL.
*
*  $AS Assertivas de Saída
*     O(s) ponteiro(s) para lista recebidos por referência agora apontam
*     as listas de antecessores ou sucessores.
*
***********************************************************************/

VER_tpCondRet VER_ObterListasAntSuc(VER_tpVertice *pVertice,
                                    LIS_tppLista *antecessores, LIS_tppLista *sucessores);

#undef VERTICE_EXT

/********** Fim do módulo de definição: Módulo Vértice **********/

#else
#endif
