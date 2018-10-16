if exist .\TestaTudo.bat.txt ren .\TestaTudo.bat.txt TestaTudo.bat
if exist ..\Objetos\ArcaboucoTeste.lib.txt ren ..\Objetos\ArcaboucoTeste.lib.txt ArcaboucoTeste.lib
if exist ..\Produto\TRAB2-1.exe.txt ren ..\Produto\TRAB2-1.exe.txt TRAB2-1.exe
if exist ..\Produto\TRAB2-2.exe.txt ren ..\Produto\TRAB2-2.exe.txt TRAB2-2.exe
cmd /k TestaTudo.bat
