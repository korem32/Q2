Q2_run : Q2.o
	gcc -o Q2_run Q2.o

Q2.o : Q2.c
	gcc -c -o Q2.o Q2.c

clean :
	rm *.0 Q2_run
