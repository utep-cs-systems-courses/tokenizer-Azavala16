#compile all files
tokenizer: history.o tokenizer.o main.o
	gcc -o tokenizer history.o tokenizer.o main.o

#compile main
main.o: main.c

#compile history files
history.o: history.c history.h

#compile tojenizer files
tokenizer.o: tokenizer.c tokenizer.h

#target to run program
run: ./tokenizer

#target to clean object files
clean:
	rm -f *.o tokenizer
