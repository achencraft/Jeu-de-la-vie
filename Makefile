OBJDIR = obj/
SRCDIR = src/
INCDIR = include/
BINDIR = bin/
LIBDIR = lib/


CFILES = $(wildcard $(SRCDIR)*.c)
OFILES = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(CFILES))
EXEC = main

vpath %.c src
vpath %.o obj
vpath %.h include
vpath main bin

MODE = rien
TARNAME = projet_LETT.tar.xz

CPPFLAGS = -Iinclude -I/usr/include/cairo
LDFLAGS = -lcairo -lm -lX11
MYLIB = -L$(LIBDIR) -ljeu


main : obj/main.o obj/io.o obj/ioCairo.o obj/mainCairo.o lib/libjeu.a
	mkdir -p ./bin
ifeq ($(MODE),TEXTE)
	gcc -o bin/main obj/main.o obj/io.o $(MYLIB)
else
	gcc -o bin/main obj/mainCairo.o obj/io.o obj/ioCairo.o $(CPPFLAGS) $(LDFLAGS) $(MYLIB)
endif


#main : obj/main.o obj/io.o obj/ioCairo.o obj/mainCairo.o obj/jeu.o obj/grille.o 
#	mkdir -p ./bin
#ifeq ($(MODE),TEXTE)
#	gcc -o bin/main obj/main.o obj/io.o obj/jeu.o obj/grille.o
#else
#	gcc -o bin/main obj/mainCairo.o obj/io.o obj/jeu.o obj/grille.o obj/ioCairo.o $(CPPFLAGS) $(LDFLAGS) 
#endif



$(LIBDIR)libjeu.a : $(OBJDIR)jeu.o  $(OBJDIR)grille.o
	mkdir -p $(LIBDIR)
	ar -crv $(LIBDIR)libjeu.a $(OBJDIR)jeu.o $(OBJDIR)grille.o
	ranlib $(LIBDIR)libjeu.a


$(OBJDIR)%.o : $(SRCDIR)%.c
	gcc -c $^ -o $@  $(CPPFLAGS) $(LDFLAGS) 



clean :
	rm -f $(BINDIR)*	
	rm -f $(OBJDIR)*
	rm -f $(LIBDIR)*


dist :
	tar -J -c $(SRCDIR)* Makefile Doxyfile -f $(TARNAME)
	
	

.PHONY:doc
doc :
	doxygen


