#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*           ngx - Nicholas Godoy
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5.00    ngx   01/dez/2018 adiconado verificador. A princípio, é a versão de entrega.
*     4.40    ngx   29/nov/2018 adicionada função de deturpação e modos de deturpação
*     4.10    ngx   25/nov/2018 início da transformação em estrutura auto verificadora
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;

#ifdef _DEBUG

/***********************************************************************
*
*  $TC Tipo de dados: LIS Modos de deturpar
*
*
***********************************************************************/

   typedef enum {

         DeturpaElimCorrente = 1 ,
               /* elimina o elemento corrente da lista */

         DeturpaProxNULL = 2 ,
               /* atribui NULL ao ponteiro para o próximo nó */

         DeturpaAntNULL = 3 ,
               /* atribui NULL ao ponteiro para o nó anterior */

         DeturpaProxLixo = 4 ,
               /* atribui lixo ao ponteiro para o próximo nó */

         DeturpaAntLixo = 5 ,
               /* atribui lixo ao ponteiro para o nó anterior */

         DeturpaConteudoNULL = 6 ,
               /* atribui NULL ao ponteiro para o conteúdo do nó */

         DeturpaTipoNo = 7 ,
               /* altera o tipo de estrutura apontado no nó */

         DeturpaTiraSemLiberar = 8 ,
               /* desencadeia nó sem liberá-lo com free */

         DeturpaCorrenteNULL = 9 ,
               /* atribui NULL ao ponteiro corrente */

         DeturpaOrigemNULL = 10 ,
               /* atribui NULL ao ponteiro de origem */

         DeturpaFinalNULL = 11 ,
               /* atribui NULL ao ponteiro de fim da lista */

         DeturpaTipoCabeca = 12 ,
               /* modifica o tipo de estrutura na cabeça */

         DeturpaCabecaNULL = 13 ,
               /* atribui NULL ao ponteiro cabeça */

         DeturpaCabecaLixo = 14 ,
               /* atribui lixo ao ponteiro cabeça */

         DeturpaTamanho = 15 ,
               /* modifica o tamanho do conteúdo apontado no corrente para um a mais */

         DeturpaCorrenteLixo = 16 ,
               /* atribui lico ao ponteiro corrente */

         DeturpaOrigemLixo = 17 ,
               /* atribui lixo ao ponteiro de origem */

         DeturpaFinalLixo = 18 ,
               /* atribui lixo ao ponteiro de fim da lista */

   } LIS_tpModosDeturpacao ;

#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado )
             #ifdef _DEBUG
             , char *tipo
             #endif
   );


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor
                                           #ifdef _DEBUG
                                           , int tamBytes,
                                             char * tipoApontado
                                           #endif
    );


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor
                                          #ifdef _DEBUG
                                          , int tamBytes,
                                            char * tipoApontado
                                          #endif
    );


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Deturpar lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Corrompe elementos específicos da estrutura da lista.
*     Essa função destina-se a preparar os cenários de teste dos
*     casos de teste utilizados ao testar os verificadores estruturais
*     da lista.
*     Esta função não tem proteção contra erros de uso, consequentemente
*     poderá levar o programa a ser cancelado pelo sistema operacional.
*
*  $EP Parâmetros
*     pLista       - ponteiro para a lista a ser deturpada
*     ModoDeturpar - identifica como deve ser feita a deturpação
*                    LIS_tpModosDeturpacao identifica os modos de
*                    deturpação conhecidos
*
***********************************************************************/

   void LIS_Deturpar( LIS_tppLista pLista ,
                      LIS_tpModosDeturpacao ModoDeturpar ) ;

#endif

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Verificar lista
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica completamente uma determinada lista.
*     Também marca ativo todos os espaços por ela ocupados.
*
*     Se a quantidade de falhas verificadas for zero,
*     não houveram falhas e a quantidade é confiável. Caso a quantidade
*     seja maior do que zero, esta não é totalmente confiável pois algumas
*     falhas podem impedir a verificação de outras, sabe-se somente
*     que houveram uma ou mais falhas.
*     Se houverem falhas na cabeça, estas serão acusadas, e não será
*     percorrido o resto da lista.
*
*  $EP Parâmetros
*     pLista       - ponteiro para a lista a ser verificada
*
*  $FV Valor retornado
*     Quantidade de falhas verificadas.
*
***********************************************************************/

   int LIS_VerificarLista( LIS_tppLista pLista ) ;

#endif

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
