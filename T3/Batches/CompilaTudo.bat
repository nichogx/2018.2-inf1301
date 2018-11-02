@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del ..\produto\*.err
del ..\produto\TRAB3*.exe

del ..\objetos\*.obj
nmake /F..\composicao\TRAB3-1.make 

del ..\objetos\*.obj
copy  ..\produto\*.err  ..\produto\tudo.err

notepad ..\produto\tudo.err

popd
