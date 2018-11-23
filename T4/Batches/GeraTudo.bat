@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

gmake  /b..\composicao  /cTRAB4-1
gmake  /b..\composicao  /cTRAB4-2

popd
