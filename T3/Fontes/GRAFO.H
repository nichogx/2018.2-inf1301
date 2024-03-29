#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo Grafo
*
*  Arquivo:                 GRAFO.H
*  Letras identificadoras:  GRF
*
*  Projeto: Disciplina INF1301
*  Autores: ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   ngx   30/09/2018 Vers�o de entrega. 
*                               Atualiza��o da documenta��o.
*                               Adicionar assertivas de entrada e sa�da na documenta��o.
*       0.52   ngx   29/09/2018 Atualiza��o da documenta��o.
*       0.51   ngx   28/09/2018 Erros corrigidos.
*                               Atualiza��o da documenta��o e nomea��o de par�metros.
*       0.50   ngx   28/09/2018 Novas fun��es de acesso para caminhar sobre as arestas.
*       0.42   ngx   28/09/2018 Pequenas modifica��es nos par�metros das fun��es
*                               de acesso.
*       0.40   ngx   27/09/2018 Continua��o e recodifica��o do m�dulo e suas fun��es.
*                               Modifica��es na estrutura.
*       0.10   ngx   13/09/2018 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar um grafo.
*     A cada momento o m�dulo admite no m�ximo um �nico grafo.
*     Ao iniciar a execu��o do programa n�o existe grafo.
*     O grafo poder� estar vazio. Neste caso o v�rtice corrente
*     ser� nulo, embora a cabe�a esteja definida.
*     O v�rtice corrente ser� nulo se e somente se o grafo estiver vazio.
*
***************************************************************************/

#if defined (GRAFO_OWN)
#define GRAFO_EXT
#else
#define GRAFO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: GRF Condicoes de retorno
*
*
***********************************************************************/

typedef enum {
	/* executou corretamente */
	GRF_CondRetOK = 0,

	/* faltou mem?ria ao alocar dados */
	GRF_CondRetFaltouMemoria = 1,

	/* grafo est? vazio */
	GRF_CondRetGrafoVazio = 2,

	/* n?o h? grafo, n?o ? poss?vel realizar opera??o */
	GRF_CondRetGrafoNaoExiste = 3,

	/* erro decorrente da fun??o do m?dulo lista */
	GRF_CondRetErroAoCriarLista = 4,

	/* grafo j? existe, n?o ? poss?vel criar outro */
	GRF_CondRetGrafoJaExiste = 5,

	/* grafo j? existente, por?m algum vertice nao existe */
	GRF_CondRetVerticeNaoExiste = 6,

	/* grafo ja existente, porem nao existe uma suposta aresta */
	GRF_CondRetArestaNaoExiste = 7,

	/* erro na estrutura */
	GRF_CondRetErroEstrutura = 8

} GRF_tpCondRet;

/***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabe?a de um grafo
*
*
***********************************************************************/

typedef struct GRF_tgGrafo GRF_tpGrafo;

/***********************************************************************
*
*  $FC Fun��o: GRF Criar Grafo
*
*  $ED Descri��o da fun��o
*     Cria um novo grafo vazio.
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoJaExiste
*     GRF_CondRetFaltouMemoria
*     GRF_CondRetErroAoCriarLista
*
*  $AE Assertivas de Entrada
*     Ainda n�o existe grafo.
*
*  $AS Assertivas de Sa�da
*     O grafo foi criado e est� vazio.
*
***********************************************************************/

GRF_tpCondRet GRF_CriarGrafo(void);

/***********************************************************************
*
*  $FC Fu���o: GRF Destruir Grafo
*
*  $ED Descri��o da fun��o
*     Destr�i o grafo.
*
*  $FV Valor retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*
*  $AE Assertivas de Entrada
*     O grafo est� criado.
*
*  $AS Assertivas de Sa�da
*     O grafo foi esvaziado e destru�do. N�o existe mais grafo.
*
***********************************************************************/

GRF_tpCondRet GRF_DestruirGrafo(void);

/************************************************************************
*
*  $FC Fun��o: GRF Obter Valor Corrente
*
*  $ED Descri��o da fun��o
*     Obtem o conteudo do vertice corrente.
*
*  $EP Par�metros
*     conteudo - endere�o do ponteiro que apontar� o valor corrente
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*
*  $AS Assertivas de Sa�da
*     O par�metro recebido por refer�ncia agora aponta o conte�do do
*     v�rtice corrente.
*
*************************************************************************/

GRF_tpCondRet GRF_ObterValorCorrente(void **conteudo);

/************************************************************************
*
*  $FC Fun��o: GRF Alterar Valor Corrente
*
*  $ED Descri��o da fun��o
*     Altera o conteudo do vertice corrente.
*
*  $EP Par�metros
*     novoConteudo - conte�do que ser� o novo do corrente
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*
*  $AS Assertivas de Sa�da
*     O par�metro recebido agora � o novo conte�do do v�rtice corrente.
*     O antigo conte�do foi liberado.
*
*************************************************************************/

GRF_tpCondRet GRF_AlterarValorCorrente(void *novoConteudo);

/************************************************************************
*
*  $FC Fun��o: GRF Ir Vertice
*
*  $ED Descri��o da fun��o
*     O vertice corrente vira o vertice que cont�m o conteudo.
*     A fun��o compara ponteiros, n�o conte�do apontado.
*
*  $EP Par�metros
*     conteudoBuscado - conte�do que ser� comparado
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetVerticeNaoExiste
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*     O conte�do recebido j� foi inserido no grafo em algum momento.
*
*  $AS Assertivas de Sa�da
*     O v�rtice que possui o conte�do recebido agora � o corrente.
*
*************************************************************************/

GRF_tpCondRet GRF_IrVertice(void *conteudoBuscado);

/************************************************************************
*
*  $FC Fun��o: GRF Inserir Vertice
*
*  $ED Descri��o da fun��o
*     Insere um vertice na lista de vertices do grafo.
*     O v�rtice inserido passa a ser o corrente.
*
*  $EP Par�metros
*     pConteudo - conteudo do novo v�rtice a ser inserido
*     ExcluirValor - ponteiro para fun��o que destr�i (libera espa�o de mem�ria)
*                    o conte�do.
*                    pode ser NULL caso n�o seja necess�rio liberar
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetFaltouMemoria
*     GRF_CondRetErroAoCriarLista
*     GRF_CondRetErroEstrutura
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*     A fun��o recebida libera o valor recebido.
*
*  $AS Assertivas de Sa�da
*     Um novo v�rtice foi criado e inserido na lista de v�rtices
*     com o valor recebido.
*
*************************************************************************/

GRF_tpCondRet GRF_InserirVertice(void *pConteudo,
                                 void(*ExcluirValor)(void *pConteudo));

/************************************************************************
*
*  $FC Fun��o: GRF Remover Corrente
*
*  $ED Descri��o da fun��o
*     Remove o vertice corrente
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*
*  $AS Assertivas de Sa�da
*     O v�rtice corrente foi liberado e n�o existe mais. O corrente agora
*     � a primeira origem, ou o grafo ficar� vazio se n�o houverem mais
*     origens.
*
*************************************************************************/

GRF_tpCondRet GRF_RemoverVerticeCorr(void);

/************************************************************************
*
*  $FC Fun��o: GRF Adicionar Origem
*
*  $ED Descri��o da fun��o
*     Adiciona um vertice e tamb�m torna-o origem.
*     O v�rtice inserido passa a ser o corrente.
*
*  $EP Par�metros
*     pConteudo - conteudo do novo v�rtice a ser inserido
*     ExcluirValor - ponteiro para fun��o que destr�i (libera espa�o de mem�ria)
*                    o conte�do.
*                    pode ser NULL caso n�o seja necess�rio liberar
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetFaltouMemoria
*     GRF_CondRetErroEstrutura
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*     A fun��o recebida libera o valor recebido.
*
*  $AS Assertivas de Sa�da
*     Um novo v�rtice foi criado e inserido na lista de v�rtices
*     com o valor recebido. Ele tamb�m foi inserido na lista de origens.
*
*************************************************************************/

GRF_tpCondRet GRF_AdicionarOrigem(void *pConteudo,
                                  void(*ExcluirValor)(void *pConteudo));

/************************************************************************
*
*  $FC Fun��o: GRF Adicionar Aresta
*
*  $ED Descri��o da fun��o
*     Adiciona uma aresta ao vertice corrente.
*     N�o � feita verifica��o se j� existe uma aresta com esse ID.
*     Recomenda-se manter os IDs de aresta �nicos.
*
*     Os conte�dos recebidos ser�o comparados com todos os v�rtices do grafo.
*     Caso eles sejam encontrados, adiciona-se uma aresta.
*     O conte�do de cada v�rtice � comparado por ponteiros, n�o conte�do apontado.
*
*  $EP Par�metros
*     idAresta - caractere que ser� o ID da aresta
*     contOrigem - conte�do do v�rtice que ser� a origem da aresta (esse ser� buscado)
*     contOrigem - conte�do do v�rtice que ser� o destino da aresta (esse ser� buscado)
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetVerticeNaoExiste
*     GRF_CondRetErroEstrutura
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*     O conte�do de origem e o conte�do de destino recebidos existem em
*     algum v�rtice do grafo.
*
*  $AS Assertivas de Sa�da
*     Aresta com o id recebido foi criada e inserida tanto na lista de 
*     sucessores do origem quanto na lista de antecessores do destino.
*
*************************************************************************/

GRF_tpCondRet GRF_AdicionarAresta(char idAresta, void *contOrigem,
                                  void *contDestino);

/************************************************************************
*
*  $FC Fun��o: GRF Andar
*
*  $ED Descri��o da fun��o
*     Avan�a o v�rtice corrente pela aresta com ID recebido.
*     A aresta precisa estar na lista de sucessores do v�rtice corrente.
*
*     Caso haja mais de uma aresta com o mesmo ID, opera na primeira
*     encontrada com esse ID.
*     Recomenda-se manter os IDs de aresta �nicos.
*
*  $EP Par�metros
*     idAresta - caractere que � o ID da aresta
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetArestaNaoExiste
*     GRF_CondRetErroEstrutura
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*     A aresta recebida existe na lista de sucessores do v�rtice corrente.
*
*  $AS Assertivas de Sa�da
*     O v�rtice corrente agora � o que � apontado pela aresta de id recebido.
*
*************************************************************************/

GRF_tpCondRet GRF_Andar(char idAresta);

/************************************************************************
*
*  $FC Fun��o: GRF Voltar
*
*  $ED Descri��o da fun��o
*     Volta o v�rtice corrente pela aresta com ID recebido.
*     A aresta precisa estar na lista de antecessores do v�rtice corrente.
*
*     Caso haja mais de uma aresta com o mesmo ID, opera na primeira
*     encontrada com esse ID.
*     Recomenda-se manter os IDs de aresta �nicos.
*
*  $EP Par�metros
*     idAresta - caractere que � o ID da aresta
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetGrafoVazio
*     GRF_CondRetArestaNaoExiste
*     GRF_CondRetErroEstrutura
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*     A aresta recebida existe na lista de antecessores do v�rtice corrente.
*
*  $AS Assertivas de Sa�da
*     O v�rtice corrente agora � o que � apontado pela aresta de id recebido.
*
*************************************************************************/

GRF_tpCondRet GRF_Voltar(char idAresta);

/************************************************************************
*
*  $FC Fun��o: GRF Remover Aresta
*
*  $ED Descri��o da fun��o
*     Remove aresta com o ID recebido
*     N�o importa se essa aresta est� ligada ao v�rtice corrente ou n�o.
*
*     Caso haja mais de uma aresta com o mesmo ID, opera na primeira
*     encontrada com esse ID.
*     Recomenda-se manter os IDs de aresta �nicos.
*
*  $EP Par�metros
*     idAresta - caractere que � o ID da aresta
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoNaoExiste
*     GRF_CondRetVerticeNaoExiste
*     GRF_CondRetErroEstrutura
*
*************************************************************************/

GRF_tpCondRet GRF_RemoverAresta(char nomeAresta);

/************************************************************************
*
*  $FC Fun��o: GRF Esvaziar Grafo
*
*  $ED Descri��o da fun��o
*     Esvazia o grafo, liberando espa�os de mem�ria e deixando-o
*     como se tivesse acabado de ser criado.
*
*  $FV Valor Retornado
*     GRF_CondRetOK
*     GRF_CondRetGrafoVazio
*     GRF_CondRetGrafoNaoExiste
*
*  $AE Assertivas de Entrada
*     Existe um grafo e este n�o � vazio.
*
*  $AS Assertivas de Sa�da
*     O grafo agora est� vazio.
*
*************************************************************************/

GRF_tpCondRet GRF_EsvaziarGrafo(void);

#undef GRAFO_EXT

/********** Fim do m?dulo de defini??o: M?dulo Grafo **********/

#else
#endif