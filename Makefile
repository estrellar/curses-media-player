GCC = g++
OUT = player.out
FLAGS = -g -lncurses

player.out : Player.o Track.o album.o MediaPlayer.o
	$(GCC) -g -o $(OUT) Track.o Album.o MediaPlayer.o Player.o $(FLAGS)
player.o: Player.cpp MediaPlayer.hpp
	$(GCC) -g -c Player.cpp

mediaplayer.o : Track.hpp Album.hpp MediaPlayer.hpp MediaPlayer.cpp
	$(GCC) -g -c MediaPlayer.cpp
album.o : Track.hpp Album.hpp Album.cpp
	$(GCC) -g -c Album.cpp
track.o : Track.hpp Track.cpp
	$(GCC) -g -c Track.cpp
clean:
	rm -f $(OUT) *.gch *.o
