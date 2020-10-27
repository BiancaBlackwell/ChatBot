all:
	gcc main.c input.c sender.c -c
	gcc -pthread main.o input.o list.o sender.o -o chatbot
clean:
	rm -f main.o input.o sender.o chatbot