all:
	gcc main.c input.c sender.c receiver.c -c
	gcc -pthread main.o input.o list.o sender.o receiver.o -o chatbot
clean:
	rm -f main.o input.o sender.o receiver.o chatbot