mourya:  main.o echo.o cd.o pwd.o
	gcc echo.o cd.o pwd.o main.o -o mourya
main.o: echo.h cd.h pwd.h shell2.c
	gcc shell2.c -c -o main.o
echo.o: echo.c
	gcc echo.c -c -o echo.o
pwd.o: pwd.c
	gcc pwd.c -c -o pwd.o
cd.o: cd.c
	gcc cd.c -c -o cd.o
