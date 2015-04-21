a.out: main.o read.o write.o generator.o ngram.o
	$(CC) $^

main.o: main.c 
read.o: read.h struct.h 
write.o: write.h write.c
generator.o: generator.h generator.c
ngram.o: ngram.h ngram.c