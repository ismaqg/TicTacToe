all: Tres_en_raya_normal Tres_en_raya_extremo

	
PrepareText.o: PrepareText.cc
	g++ -c PrepareText.cc
	
Audio.o: Audio.cc
	g++ -c Audio.cc
	
Board.o: Board.cc 
	g++ -c Board.cc
	
Line.o: Line.cc
	g++ -c Line.cc
	
Piece.o: Piece.cc
	g++ -c Piece.cc
	
Tres_en_raya_normal.o: main_normal.cc
	g++ -c main_normal.cc
	
Tres_en_raya_normal: main_normal.o PrepareText.o Audio.o Board.o Line.o Piece.o
	g++ -o 3enraya_normal main_normal.o PrepareText.o Audio.o Board.o Line.o Piece.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	
Tres_en_raya_extremo.o: main_extreme.o
	g++ -c main_extreme.cc
	
Tres_en_raya_extremo: main_extreme.o PrepareText.o Audio.o Board.o Line.o Piece.o
	g++ -o 3enraya_extremo main_extreme.o PrepareText.o Audio.o Board.o Line.o Piece.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
