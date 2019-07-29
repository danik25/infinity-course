myexe : main3.o b3.o a3.o
	cc -o myexe main3.o a3.o b3.o

main3.o : main3.c b3.h 
	cc -c main3.c

b3.o : b3.c a3.h b3.h
	cc -c b3.c

a3.o : a3.c a3.h
	cc -c a3.c

.PHONY : clean
clean : 
	rm main3.o b3.o a3.o ./myexe