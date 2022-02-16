GCC = g++
OUT = player.out
FLAGS = -g -lncurses

player.out : Player.o Track.o Album.o MediaPlayer.o Media.o
	$(GCC) -g -o $(OUT) Media.o Track.o Album.o MediaPlayer.o Player.o  $(FLAGS)
Player.o: Player.cpp MediaPlayer.hpp
	$(GCC) -g -c Player.cpp
MediaPlayer.o : Media.hpp Track.hpp Album.hpp MediaPlayer.hpp MediaPlayer.cpp
	$(GCC) -g -c MediaPlayer.cpp
Album.o : Media.hpp Track.hpp Album.hpp Album.cpp
	$(GCC) -g -c Album.cpp
Track.o : Media.hpp Track.hpp Track.cpp
	$(GCC) -g -c Track.cpp
Media.o : Media.hpp Media.cpp
	$(GCC) -g -c Media.cpp
clean:
	rm -f $(OUT) *.gch *.o
