/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
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
*     4.30    ngx   27/nov/2018 utilização do módulo conta, novos casos de teste
*     4.10    ngx   25/nov/2018 início da transformação em estrutura auto verificadora
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#ifdef _DEBUG
   #include "GENERICO.H"
   #include "CESPDIN.H"
   #include "CONTA.H"
   #include "..\\tabelas\\IdTiposEspaco.def"
#endif

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {
         #ifdef _DEBUG
         int tamApontado;
               /* Tamanho do conteúdo apontado, em bytes */

         char tipoApontado[11];
               /* Cadeia de caracteres que indica o tipo apontado */

         struct LIS_tagLista * pCabeca;
               /* Ponteiro para a cabeça a qual o elemento pertence */
         #endif

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {
         #ifdef _DEBUG
         char tipoApontado[11];
               /* Cadeia de caracteres que indica o tipo apontado */
         #endif

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/*****  Protótipos das funções encapuladas no módulo  *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

   #ifdef _DEBUG

      static int VerificarCabeca( LIS_tppLista pLista ) ;

      static int VerificarElementos( LIS_tppLista pLista ) ;

   #endif

/*****  Dados encapsulados no módulo  *****/

   #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */

   #endif

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado )
             #ifdef _DEBUG
             , char *tipo
             #endif
   )
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista ) ) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      #ifdef _DEBUG
         strncpy(pLista->tipoApontado, tipo, 10) ;
         CED_DefinirTipoEspaco ( pLista , LIS_TipoEspacoCabeca ) ;
      #endif

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR("LIS_EsvaziarLista pElem_dif_NULL");
         #endif
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor
                                           #ifdef _DEBUG
                                           , int tamBytes,
                                             char * tipoApontado
                                           #endif
    )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inserir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

         #ifdef _DEBUG
            pElem->tamApontado = tamBytes;
            strncpy(pElem->tipoApontado, tipoApontado, 10);
            pElem->pCabeca = pLista;
         #endif

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_InserirElementoAntes lista_era_vazia");
            #endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR("LIS_InserirElementoAntes el_corrente_nao_primeiro");
               #endif
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR("LIS_InserirElementoAntes el_corrente_primeiro");
               #endif
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor
                                          #ifdef _DEBUG
                                          , int tamBytes,
                                            char * tipoApontado
                                          #endif
    )  
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

         #ifdef _DEBUG
            pElem->tamApontado = tamBytes;
            strncpy(pElem->tipoApontado, tipoApontado, 10);
            pElem->pCabeca = pLista;
         #endif

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_InserirElementoApos lista_era_vazia");
            #endif
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR("LIS_InserirElementoApos el_corrente_nao_ultimo");
               #endif
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               #ifdef _DEBUG
                  CNT_CONTAR("LIS_InserirElementoApos el_corrente_ultimo");
               #endif
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR("LIS_ExcluirElemento lista_era_vazia");
         #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_ExcluirElemento nao_era_primeiro");
            #endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_ExcluirElemento era_primeiro");
            #endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_ExcluirElemento nao_era_ultimo");
            #endif
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_ExcluirElemento era_ultimo");
            #endif
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR("LIS_ObterValor nao_tem_corrente");
         #endif
        return NULL ;
      } /* if */

      return pLista->pElemCorr->pValor ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_AvancarElementoCorrente lista_era_vazia");
            #endif

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR("LIS_AvancarElementoCorrente maior_zero_pElem_virou_NULL");
                  #endif
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR("LIS_AvancarElementoCorrente maior_zero_pElem_nao_NULL");
               #endif
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  #ifdef _DEBUG
                     CNT_CONTAR("LIS_AvancarElementoCorrente menor_zero_pElem_virou_NULL");
                  #endif
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               #ifdef _DEBUG
                  CNT_CONTAR("LIS_AvancarElementoCorrente menor_zero_pElem_nao_NULL");
               #endif
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         #ifdef _DEBUG
            CNT_CONTAR("LIS_ProcurarValor lista_era_vazia");
         #endif
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            #ifdef _DEBUG
               CNT_CONTAR("LIS_ProcurarValor achou");
            #endif
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Deturpar lista
*  ****/

   void LIS_Deturpar( LIS_tppLista pLista ,
                      LIS_tpModosDeturpacao ModoDeturpar )
   {

      tpElemLista * pElem ;

      if ( pLista == NULL )
      {
         return ;
      } /* if */

      switch ( ModoDeturpar ) {

      /* elimina o elemento corrente da lista */

         case DeturpaElimCorrente :
         {

            if ( pLista->pElemCorr == NULL )
            {
               return ;
            } /* if */

            pElem = pLista->pElemCorr ;

            /* Desencadeia à esquerda */

               if ( pElem->pAnt != NULL )
               {
                  pElem->pAnt->pProx   = pElem->pProx ;
               } else {
                  pLista->pOrigemLista = pElem->pProx ;
               } /* if */

            /* Desencadeia à direita */

               if ( pElem->pProx != NULL )
               {
                  pElem->pProx->pAnt = pElem->pAnt ;
               } else
               {
                  pLista->pFimLista = pElem->pAnt ;
               } /* if */

            break ;

         } /* fim ativa: elimina o elemento corrente da lista */

      /* desencadeia nó sem liberá-lo com free */

         case DeturpaTiraSemLiberar :
         {

            if ( pLista->pElemCorr == NULL )
            {
               return ;
            } /* if */

            pElem = pLista->pElemCorr ;

            /* Desencadeia à esquerda */

               if ( pElem->pAnt != NULL )
               {
                  pElem->pAnt->pProx   = pElem->pProx ;
                  pLista->pElemCorr    = pElem->pAnt ;
               } else {
                  pLista->pElemCorr    = pElem->pProx ;
                  pLista->pOrigemLista = pLista->pElemCorr ;
               } /* if */

            /* Desencadeia à direita */

               if ( pElem->pProx != NULL )
               {
                  pElem->pProx->pAnt = pElem->pAnt ;
               } else
               {
                  pLista->pFimLista = pElem->pAnt ;
               } /* if */

            break ;

         } /* fim ativa: desencadeia nó sem liberá-lo com free */

      /* atribui NULL ao ponteiro corrente */

         case DeturpaCorrenteNULL :
         {

            pLista->pElemCorr = NULL ;

            break ;

         } /* fim ativa: atribui NULL ao ponteiro corrente */

      /* atribui NULL ao ponteiro de origem */

         case DeturpaOrigemNULL :
         {

            pLista->pOrigemLista = NULL ;

            break ;

         } /* fim ativa: atribui NULL ao ponteiro de origem */

      /* atribui NULL ao ponteiro de fim da lista */

         case DeturpaFinalNULL :
         {

            pLista->pFimLista = NULL ;

            break ;

         } /* fim ativa: atribui NULL ao ponteiro de fim da lista */

      /* atribui lixo ao ponteiro corrente */

         case DeturpaCorrenteLixo :
         {

            pLista->pElemCorr = ( tpElemLista * ) ( EspacoLixo ) ;

            break ;

         } /* fim ativa: atribui lixo ao ponteiro corrente */

      /* atribui lixo ao ponteiro de origem */

         case DeturpaOrigemLixo :
         {

            pLista->pOrigemLista = ( tpElemLista * ) ( EspacoLixo ) ;

            break ;

         } /* fim ativa: atribui lixo ao ponteiro de origem */

      /* atribui lixo ao ponteiro de fim da lista */

         case DeturpaFinalLixo :
         {

            pLista->pFimLista = ( tpElemLista * ) ( EspacoLixo ) ;

            break ;

         } /* fim ativa: atribui lixo ao ponteiro de fim da lista */

      /* modifica o tipo de estrutura na cabeça */

         case DeturpaTipoCabeca :
         {

            strncpy( pLista->tipoApontado , "xxxxxxxxxx" , 10 ) ;

            break ;

         } /* fim ativa: modifica o tipo de estrutura na cabeça */

      /* Deturpa nó */

         default :

         if ( pLista->pElemCorr != NULL )
         {

            switch ( ModoDeturpar ) {

            /* atribui NULL ao ponteiro para o próximo nó */

               case DeturpaProxNULL :
               {

                  pLista->pElemCorr->pProx = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro para o próximo nó */

            /* atribui NULL ao ponteiro para o nó anterior */

               case DeturpaAntNULL :
               {

                  pLista->pElemCorr->pAnt = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro para o nó anterior */

            /* atribui lixo ao ponteiro para o próximo nó */

               case DeturpaProxLixo :
               {

                  pLista->pElemCorr->pProx = ( tpElemLista * ) ( EspacoLixo ) ;

                  break ;

               } /* fim ativa: atribui lixo ao ponteiro para o próximo nó */

            /* atribui lixo ao ponteiro para o nó anterior */

               case DeturpaAntLixo :
               {

                  pLista->pElemCorr->pAnt = ( tpElemLista * ) ( EspacoLixo ) ;

                  break ;

               } /* fim ativa: atribui lixo ao ponteiro para o nó anterior */

            /* atribui NULL ao ponteiro para o conteúdo do nó */

               case DeturpaConteudoNULL :
               {

                  pLista->pElemCorr->pValor = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro para o conteúdo do nó */

            /* altera o tipo de estrutura apontado no nó */

               case DeturpaTipoNo :
               {

                  strncpy( pLista->pElemCorr->tipoApontado , "xxxxxxxxxx" , 10 ) ;

                  break ;

               } /* fim ativa: altera o tipo de estrutura apontado no nó */

            /* atribui NULL ao ponteiro cabeça */

               case DeturpaCabecaNULL :
               {

                  pLista->pElemCorr->pCabeca = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro cabeça */

            /* atribui lixo ao ponteiro cabeça */

               case DeturpaCabecaLixo :
               {

                  pLista->pElemCorr->pCabeca = ( LIS_tpLista * ) ( EspacoLixo ) ;

                  break ;

               } /* fim ativa: atribui lixo ao ponteiro cabeça */

            /* modifica o tamanho do conteúdo apontado no corrente para um a mais */

               case DeturpaTamanho :
               {

                  pLista->pElemCorr->tamApontado = pLista->pElemCorr->tamApontado + 1 ;

                  break ;

               } /* fim ativa: modifica o tamanho do conteúdo apontado no corrente para um a mais */

            } /* switch */

          } /* if */

      } /* switch */

   } /* Fim função: LIS  &Deturpar lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Função: LIS  &Verificar lista
*  ****/

   int LIS_VerificarLista( LIS_tppLista pLista )
   {

      int falhas = 0 ;
      falhas += VerificarCabeca( pLista ) ;

      CED_MarcarEspacoAtivo( pLista ) ;

      if ( falhas == 0 )
      {
         falhas += VerificarElementos( pLista ) ;
      }

      return falhas ;

   } /* Fim função: LIS  &Verificar lista */

#endif

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         #ifdef _DEBUG
            CNT_CONTAR("LiberarElemento if");
         #endif
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pElem , LIS_TipoEspacoElemento ) ;
      #endif

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  -Verificar a cabeça da lista
*
***********************************************************************/

   int VerificarCabeca( LIS_tppLista pLista )
   {

      int falhas = 0 ;

      /* Verifica o tipo do espaço */

         if ( pLista == NULL )
         {
            CNT_CONTAR( "VerificarCabeca pLista_NULL" ) ;
            TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
            falhas ++ ;
            return falhas ;
         } /* if */

         if ( LIS_TipoEspacoCabeca != CED_ObterTipoEspaco( pLista )
              || ! CED_VerificarEspaco( pLista , NULL ) )
         {
            CNT_CONTAR( "VerificarCabeca cabeca_tipo_errado" ) ;
            TST_NotificarFalha( "cabeça não é cabeça de lista." ) ;
            falhas ++ ;
            return falhas ;
         } /* if */

      /* Verifica origem */

         if ( pLista->pOrigemLista == NULL )
         {
            if ( pLista->pFimLista != NULL || pLista->pElemCorr != NULL 
                 || pLista->numElem != 0 )
            {
               CNT_CONTAR( "VerificarCabeca origem_null" ) ;
               TST_NotificarFalha( "Origem é nula mas lista não é vazia." ) ;
               falhas ++ ;
            } /* if */
            return falhas ;
         } /* if */

            if ( CED_ObterTipoEspaco( pLista->pOrigemLista ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pOrigemLista , NULL ) )
            {
               CNT_CONTAR( "VerificarCabeca origem_lixo" ) ;
               TST_NotificarFalha( "origem da lista não é um nó." ) ;
               falhas ++ ;
            } /* if */

      /* Verifica final */

         if ( pLista->pFimLista == NULL )
         {
            if ( pLista->pElemCorr != NULL || pLista->pOrigemLista != NULL 
                 || pLista->numElem != 0 )
            {
               CNT_CONTAR( "VerificarCabeca fim_null" ) ;
               TST_NotificarFalha( "Fim é nulo mas lista não é vazia." ) ;
               falhas ++ ;
            } /* if */
            return falhas ;
         } /* if */

            if ( CED_ObterTipoEspaco( pLista->pFimLista ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pFimLista , NULL ) )
            {
               CNT_CONTAR( "VerificarCabeca fim_lixo" ) ;
               TST_NotificarFalha( "fim da lista não é um nó." ) ;
               falhas ++ ;
            } /* if */

      /* Verifica corrente */

         if ( pLista->pElemCorr == NULL )
         {
            if ( pLista->pFimLista != NULL || pLista->pOrigemLista != NULL 
                 || pLista->numElem != 0 )
            {
               CNT_CONTAR( "VerificarCabeca corrente_null" ) ;
               TST_NotificarFalha( "Corrente é nulo mas lista não é vazia." ) ;
               falhas ++ ;
            } /* if */
            return falhas ;
         } /* if */

            if ( CED_ObterTipoEspaco( pLista->pElemCorr ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pElemCorr , NULL ) )
            {
               CNT_CONTAR( "VerificarCabeca corrente_lixo" ) ;
               TST_NotificarFalha( "elemento corrente não é um nó." ) ;
               falhas ++ ;
            } /* if */

      return falhas ;

   } /* Fim função: LIS  -Verificar a cabeça da lista */

#endif

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  -Verificar elementos da lista
*
***********************************************************************/

   int VerificarElementos( LIS_tppLista pLista )
   {

      int falhas = 0 ;

      /* Verifica elementos da lista */

         if ( pLista->pElemCorr != NULL )
         {
            if ( pLista->pElemCorr->pProx != NULL 
                 && pLista->pElemCorr->pProx->pAnt != pLista->pElemCorr )
            {
               CNT_CONTAR( "VerificarElementos falha_encadeamento_direita" ) ;
               TST_NotificarFalha( "falha no encadeamento (direita)." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pAnt != NULL 
                 && pLista->pElemCorr->pAnt->pProx != pLista->pElemCorr )
            {
               CNT_CONTAR( "VerificarElementos falha_encadeamento_esquerda" ) ;
               TST_NotificarFalha( "falha no encadeamento (esquerda)." ) ;
               falhas ++ ;
            } /* if */
         }

         IrInicioLista( pLista ) ;
         if ( pLista->pElemCorr != NULL ) 
         do 
         {
            int acusouLixo = 0 ;

            if ( pLista->pElemCorr->pProx != NULL && 
                 CED_ObterTipoEspaco( pLista->pElemCorr->pProx ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pElemCorr->pProx , NULL ) )
            {
               CNT_CONTAR( "VerificarElementos proximo_lixo" ) ;
               TST_NotificarFalha( "elemento próximo não é um nó." ) ;
               falhas ++ ;
               acusouLixo = 1 ;
            } /* if */

            if ( pLista->pElemCorr->pAnt != NULL && 
                 CED_ObterTipoEspaco( pLista->pElemCorr->pAnt ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pElemCorr->pAnt , NULL ) )
            {
               CNT_CONTAR( "VerificarElementos anterior_lixo" ) ;
               TST_NotificarFalha( "elemento anterior não é um nó." ) ;
               falhas ++ ;
               acusouLixo = 1 ;
            } /* if */

            /* para o programa não voar */
            if ( acusouLixo )
            {
               CNT_CONTAR( "VerificarElementos acusouLixo" ) ;
               return falhas ;
            }

            CED_MarcarEspacoAtivo( pLista->pElemCorr ) ;
            CED_MarcarEspacoAtivo( pLista->pElemCorr->pValor ) ;

            if ( pLista->pElemCorr->pCabeca != pLista )
            {
               CNT_CONTAR( "VerificarElementos pCabeca_nao_cabeca" ) ;
               TST_NotificarFalha( "pCabeca no elemento não aponta para a cabeça da lista." ) ;
               falhas ++ ;
            } /* if */

            if ( strcmp( pLista->tipoApontado , pLista->pElemCorr->tipoApontado ) != 0 )
            {
               CNT_CONTAR( "VerificarElementos tipo_errado" ) ;
               TST_NotificarFalha( "tipo do elemento não é mesmo tipo da lista." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pValor == NULL )
            {
               CNT_CONTAR( "VerificarElementos conteudo_null" ) ;
               TST_NotificarFalha( "conteúdo do elemento é nulo." ) ;
               falhas ++ ;
            } /* if */

            if ( CED_ObterTamanhoValor( pLista->pElemCorr->pValor ) != pLista->pElemCorr->tamApontado )
            {
               CNT_CONTAR( "VerificarElementos tamanho_errado" ) ;
               TST_NotificarFalha( "tamanho do apontado não é o tamanho real." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pAnt == NULL && pLista->pElemCorr != pLista->pOrigemLista )
            {
               CNT_CONTAR( "VerificarElementos anterior_null_nao_primeiro" ) ;
               TST_NotificarFalha( "anterior é nulo em elemento não primeiro." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pProx == NULL && pLista->pElemCorr != pLista->pFimLista )
            {
               CNT_CONTAR( "VerificarElementos proximo_null_nao_primeiro" ) ;
               TST_NotificarFalha( "próximo é nulo em elemento não último." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pProx != NULL 
                 && pLista->pElemCorr->pProx->pAnt != pLista->pElemCorr )
            {
               CNT_CONTAR( "VerificarElementos falha_encadeamento_direita_2" ) ;
               TST_NotificarFalha( "falha no encadeamento." ) ;
               falhas ++ ;
            } /* if */

         } while ( LIS_AvancarElementoCorrente( pLista , 1 ) == LIS_CondRetOK ) ;

         return falhas ;

   } /* Fim função: LIS  -Verificar elementos da lista */

#endif

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

