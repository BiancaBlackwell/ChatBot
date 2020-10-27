all:
	gcc main.c input.c -c
	gcc -pthread main.o input.o list.o -o chatbot
clean:
	rm -f main.o input.o chatbot