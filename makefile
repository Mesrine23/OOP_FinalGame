
game: main.cpp items.cpp spells.cpp market.cpp living.cpp fight.cpp cell.cpp
	g++ -std=c++11 -o game main.cpp items.cpp spells.cpp market.cpp living.cpp fight.cpp cell.cpp

clean:
	rm game