if exist .\TestaTudo.bat.txt ren .\TestaTudo.bat.txt TestaTudo.bat
if exist ..\Produto\TRAB4-1.exe.txt ren ..\Produto\TRAB4-1.exe.txt TRAB4-1.exe
if exist ..\Produto\TRAB4-2.exe.txt ren ..\Produto\TRAB4-2.exe.txt TRAB4-2.exe
call TestaTudo.bat
notepad ..\Produto\resultado.txt
