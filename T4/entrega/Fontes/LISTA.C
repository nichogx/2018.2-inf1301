/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*           ngx - Nicholas Godoy
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     5.00    ngx   01/dez/2018 adiconado verificador. A princ�pio, � a vers�o de entrega.
*     4.40    ngx   29/nov/2018 adicionada fun��o de deturpa��o e modos de deturpa��o
*     4.30    ngx   27/nov/2018 utiliza��o do m�dulo conta, novos casos de teste
*     4.10    ngx   25/nov/2018 in�cio da transforma��o em estrutura auto verificadora
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
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
               /* Tamanho do conte�do apontado, em bytes */

         char tipoApontado[11];
               /* Cadeia de caracteres que indica o tipo apontado */

         struct LIS_tagLista * pCabeca;
               /* Ponteiro para a cabe�a a qual o elemento pertence */
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
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
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
               /* N�mero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

   } LIS_tpLista ;

/*****  Prot�tipos das fun��es encapuladas no m�dulo  *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

   #ifdef _DEBUG

      static int VerificarCabeca( LIS_tppLista pLista ) ;

      static int VerificarElementos( LIS_tppLista pLista ) ;

   #endif

/*****  Dados encapsulados no m�dulo  *****/

   #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espa�o de dados lixo usado ao testar */

   #endif

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
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

   } /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
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

   } /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
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

   } /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
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

      /* Criar elemento a inerir ap�s */

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

      /* Encadear o elemento ap�s o elemento */

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

   } /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
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

      /* Desencadeia � esquerda */

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

      /* Desencadeia � direita */

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

   } /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
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

   } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
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

      /* Tratar avan�ar para frente */

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

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

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

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
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

   } /* Fim fun��o: LIS  &Procurar elemento contendo valor */

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Deturpar lista
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

            /* Desencadeia � esquerda */

               if ( pElem->pAnt != NULL )
               {
                  pElem->pAnt->pProx   = pElem->pProx ;
               } else {
                  pLista->pOrigemLista = pElem->pProx ;
               } /* if */

            /* Desencadeia � direita */

               if ( pElem->pProx != NULL )
               {
                  pElem->pProx->pAnt = pElem->pAnt ;
               } else
               {
                  pLista->pFimLista = pElem->pAnt ;
               } /* if */

            break ;

         } /* fim ativa: elimina o elemento corrente da lista */

      /* desencadeia n� sem liber�-lo com free */

         case DeturpaTiraSemLiberar :
         {

            if ( pLista->pElemCorr == NULL )
            {
               return ;
            } /* if */

            pElem = pLista->pElemCorr ;

            /* Desencadeia � esquerda */

               if ( pElem->pAnt != NULL )
               {
                  pElem->pAnt->pProx   = pElem->pProx ;
                  pLista->pElemCorr    = pElem->pAnt ;
               } else {
                  pLista->pElemCorr    = pElem->pProx ;
                  pLista->pOrigemLista = pLista->pElemCorr ;
               } /* if */

            /* Desencadeia � direita */

               if ( pElem->pProx != NULL )
               {
                  pElem->pProx->pAnt = pElem->pAnt ;
               } else
               {
                  pLista->pFimLista = pElem->pAnt ;
               } /* if */

            break ;

         } /* fim ativa: desencadeia n� sem liber�-lo com free */

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

      /* modifica o tipo de estrutura na cabe�a */

         case DeturpaTipoCabeca :
         {

            strncpy( pLista->tipoApontado , "xxxxxxxxxx" , 10 ) ;

            break ;

         } /* fim ativa: modifica o tipo de estrutura na cabe�a */

      /* Deturpa n� */

         default :

         if ( pLista->pElemCorr != NULL )
         {

            switch ( ModoDeturpar ) {

            /* atribui NULL ao ponteiro para o pr�ximo n� */

               case DeturpaProxNULL :
               {

                  pLista->pElemCorr->pProx = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro para o pr�ximo n� */

            /* atribui NULL ao ponteiro para o n� anterior */

               case DeturpaAntNULL :
               {

                  pLista->pElemCorr->pAnt = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro para o n� anterior */

            /* atribui lixo ao ponteiro para o pr�ximo n� */

               case DeturpaProxLixo :
               {

                  pLista->pElemCorr->pProx = ( tpElemLista * ) ( EspacoLixo ) ;

                  break ;

               } /* fim ativa: atribui lixo ao ponteiro para o pr�ximo n� */

            /* atribui lixo ao ponteiro para o n� anterior */

               case DeturpaAntLixo :
               {

                  pLista->pElemCorr->pAnt = ( tpElemLista * ) ( EspacoLixo ) ;

                  break ;

               } /* fim ativa: atribui lixo ao ponteiro para o n� anterior */

            /* atribui NULL ao ponteiro para o conte�do do n� */

               case DeturpaConteudoNULL :
               {

                  pLista->pElemCorr->pValor = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro para o conte�do do n� */

            /* altera o tipo de estrutura apontado no n� */

               case DeturpaTipoNo :
               {

                  strncpy( pLista->pElemCorr->tipoApontado , "xxxxxxxxxx" , 10 ) ;

                  break ;

               } /* fim ativa: altera o tipo de estrutura apontado no n� */

            /* atribui NULL ao ponteiro cabe�a */

               case DeturpaCabecaNULL :
               {

                  pLista->pElemCorr->pCabeca = NULL ;

                  break ;

               } /* fim ativa: atribui NULL ao ponteiro cabe�a */

            /* atribui lixo ao ponteiro cabe�a */

               case DeturpaCabecaLixo :
               {

                  pLista->pElemCorr->pCabeca = ( LIS_tpLista * ) ( EspacoLixo ) ;

                  break ;

               } /* fim ativa: atribui lixo ao ponteiro cabe�a */

            /* modifica o tamanho do conte�do apontado no corrente para um a mais */

               case DeturpaTamanho :
               {

                  pLista->pElemCorr->tamApontado = pLista->pElemCorr->tamApontado + 1 ;

                  break ;

               } /* fim ativa: modifica o tamanho do conte�do apontado no corrente para um a mais */

            } /* switch */

          } /* if */

      } /* switch */

   } /* Fim fun��o: LIS  &Deturpar lista */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: LIS  &Verificar lista
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

   } /* Fim fun��o: LIS  &Verificar lista */

#endif

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
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

   } /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
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

   } /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS  -Verificar a cabe�a da lista
*
***********************************************************************/

   int VerificarCabeca( LIS_tppLista pLista )
   {

      int falhas = 0 ;

      /* Verifica o tipo do espa�o */

         if ( pLista == NULL )
         {
            CNT_CONTAR( "VerificarCabeca pLista_NULL" ) ;
            TST_NotificarFalha( "Tentou verificar cabe�a inexistente." ) ;
            falhas ++ ;
            return falhas ;
         } /* if */

         if ( LIS_TipoEspacoCabeca != CED_ObterTipoEspaco( pLista )
              || ! CED_VerificarEspaco( pLista , NULL ) )
         {
            CNT_CONTAR( "VerificarCabeca cabeca_tipo_errado" ) ;
            TST_NotificarFalha( "cabe�a n�o � cabe�a de lista." ) ;
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
               TST_NotificarFalha( "Origem � nula mas lista n�o � vazia." ) ;
               falhas ++ ;
            } /* if */
            return falhas ;
         } /* if */

            if ( CED_ObterTipoEspaco( pLista->pOrigemLista ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pOrigemLista , NULL ) )
            {
               CNT_CONTAR( "VerificarCabeca origem_lixo" ) ;
               TST_NotificarFalha( "origem da lista n�o � um n�." ) ;
               falhas ++ ;
            } /* if */

      /* Verifica final */

         if ( pLista->pFimLista == NULL )
         {
            if ( pLista->pElemCorr != NULL || pLista->pOrigemLista != NULL 
                 || pLista->numElem != 0 )
            {
               CNT_CONTAR( "VerificarCabeca fim_null" ) ;
               TST_NotificarFalha( "Fim � nulo mas lista n�o � vazia." ) ;
               falhas ++ ;
            } /* if */
            return falhas ;
         } /* if */

            if ( CED_ObterTipoEspaco( pLista->pFimLista ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pFimLista , NULL ) )
            {
               CNT_CONTAR( "VerificarCabeca fim_lixo" ) ;
               TST_NotificarFalha( "fim da lista n�o � um n�." ) ;
               falhas ++ ;
            } /* if */

      /* Verifica corrente */

         if ( pLista->pElemCorr == NULL )
         {
            if ( pLista->pFimLista != NULL || pLista->pOrigemLista != NULL 
                 || pLista->numElem != 0 )
            {
               CNT_CONTAR( "VerificarCabeca corrente_null" ) ;
               TST_NotificarFalha( "Corrente � nulo mas lista n�o � vazia." ) ;
               falhas ++ ;
            } /* if */
            return falhas ;
         } /* if */

            if ( CED_ObterTipoEspaco( pLista->pElemCorr ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pElemCorr , NULL ) )
            {
               CNT_CONTAR( "VerificarCabeca corrente_lixo" ) ;
               TST_NotificarFalha( "elemento corrente n�o � um n�." ) ;
               falhas ++ ;
            } /* if */

      return falhas ;

   } /* Fim fun��o: LIS  -Verificar a cabe�a da lista */

#endif

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS  -Verificar elementos da lista
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
               TST_NotificarFalha( "elemento pr�ximo n�o � um n�." ) ;
               falhas ++ ;
               acusouLixo = 1 ;
            } /* if */

            if ( pLista->pElemCorr->pAnt != NULL && 
                 CED_ObterTipoEspaco( pLista->pElemCorr->pAnt ) != LIS_TipoEspacoElemento
                 || ! CED_VerificarEspaco( pLista->pElemCorr->pAnt , NULL ) )
            {
               CNT_CONTAR( "VerificarElementos anterior_lixo" ) ;
               TST_NotificarFalha( "elemento anterior n�o � um n�." ) ;
               falhas ++ ;
               acusouLixo = 1 ;
            } /* if */

            /* para o programa n�o voar */
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
               TST_NotificarFalha( "pCabeca no elemento n�o aponta para a cabe�a da lista." ) ;
               falhas ++ ;
            } /* if */

            if ( strcmp( pLista->tipoApontado , pLista->pElemCorr->tipoApontado ) != 0 )
            {
               CNT_CONTAR( "VerificarElementos tipo_errado" ) ;
               TST_NotificarFalha( "tipo do elemento n�o � mesmo tipo da lista." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pValor == NULL )
            {
               CNT_CONTAR( "VerificarElementos conteudo_null" ) ;
               TST_NotificarFalha( "conte�do do elemento � nulo." ) ;
               falhas ++ ;
            } /* if */

            if ( CED_ObterTamanhoValor( pLista->pElemCorr->pValor ) != pLista->pElemCorr->tamApontado )
            {
               CNT_CONTAR( "VerificarElementos tamanho_errado" ) ;
               TST_NotificarFalha( "tamanho do apontado n�o � o tamanho real." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pAnt == NULL && pLista->pElemCorr != pLista->pOrigemLista )
            {
               CNT_CONTAR( "VerificarElementos anterior_null_nao_primeiro" ) ;
               TST_NotificarFalha( "anterior � nulo em elemento n�o primeiro." ) ;
               falhas ++ ;
            } /* if */

            if ( pLista->pElemCorr->pProx == NULL && pLista->pElemCorr != pLista->pFimLista )
            {
               CNT_CONTAR( "VerificarElementos proximo_null_nao_primeiro" ) ;
               TST_NotificarFalha( "pr�ximo � nulo em elemento n�o �ltimo." ) ;
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

   } /* Fim fun��o: LIS  -Verificar elementos da lista */

#endif

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

