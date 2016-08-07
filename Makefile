CPP=gcc    #Commande du compilateur
CFLAGS=-O3 #Option d'optimisation du programme
LDFLAGS=`sdl-config --cflags --libs` #Linker
EXEC=test  #Nom du programme à modifier
FILE=test.c

all:
	gcc -o exec -Wall -Wextra -Werror -I includes/ -I libft/ libft/libft.a srcs/*.c `sdl-config --cflags --libs`

clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}
