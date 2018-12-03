if exist ..\Produto\resultado.txt del ..\Produto\resultado.txt
if exist ..\scripts\*_acum.cont del ..\scripts\*_acum.cont

(
..\produto\TRAB4-1        /s..\scripts\testelista    /l..\produto\testelista
..\produto\TRAB4-2        /s..\scripts\testelistadebug    /l..\produto\testelistadebug
..\produto\TRAB4-2        /s..\scripts\testelistadeturpacoes    /l..\produto\testelistadeturpacoes

type ..\scripts\todos_acum.cont
) > "..\Produto\resultado.txt"