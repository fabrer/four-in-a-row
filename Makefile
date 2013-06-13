LIB=`sdl-config --cflags --libs`
all:client

client:	Main.o Jeu.o Moteur.o Objet.o Menu.o Ia.o 
	g++ -o jeu.exe Main.o Jeu.o Moteur.o Objet.o Menu.o Ia.o $(LIB)  
 
Main.o: Main.h Main.cpp 
	g++ -c Main.cpp $(LIB)
Jeu.o: Jeu.h Jeu.cpp 
	g++ -c Jeu.cpp $(LIB)
Moteur.o: Moteur.h Moteur.cpp 
	g++ -c Moteur.cpp $(LIB)
Objet.o: Objet.h Objet.cpp 
	g++ -c Objet.cpp $(LIB)
Menu.o: Menu.h Menu.cpp 
	g++ -c Menu.cpp $(LIB)
Ia.o: Ia.h Ia.cpp 
	g++ -c Ia.cpp $(LIB)

clean:
	rm *.o
