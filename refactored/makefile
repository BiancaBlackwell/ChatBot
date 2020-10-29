all:
	gcc main.c input.c sender.c receiver.c screen.c -c
	gcc -pthread main.o input.o list.o sender.o receiver.o screen.o -o s-talk
clean:
	rm -f main.o input.o sender.o receiver.o screen.o s-talk