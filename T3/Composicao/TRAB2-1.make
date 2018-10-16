##################################################
###
### Diretivas de MAKE para o construto: TRAB2-1
### Gerado a partir de: TRAB2-1.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TRAB2-1


### Nomes de paths

Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\testgrf.obj   $(Fobj)\grafo.obj   $(Fobj)\vertice.obj \
   $(Fobj)\lista.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\testgrf.obj :  {$(Pc)}\testgrf.c \
    {$(Ph)}generico.h           {$(Ph)}grafo.h              {$(Ph)}lerparm.h            \
    {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\grafo.obj :  {$(Pc)}\grafo.c \
    {$(Ph)}grafo.h              {$(Ph)}lista.h              {$(Ph)}vertice.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\vertice.obj :  {$(Pc)}\vertice.c \
    {$(Ph)}lista.h              {$(Ph)}vertice.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\testgrf.obj   $(Fobj)\grafo.obj   $(Fobj)\vertice.obj \
   $(Fobj)\lista.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TRAB2-1
###
##################################################

