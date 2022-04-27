#include <curses.h>
#include <vector>
#include <list>
#include <string>
#include "Album.hpp"
#include "Track.hpp"
#include "fmod.hpp"

using namespace std;

//navigation keys
#define KEY_SPACE 0x20
#define KEY_W 0x77
#define KEY_A 0x61
#define KEY_S 0x73
#define KEY_D 0x64
#define KEY_TAB 0x09


#ifndef MEDIA_PLAYER_HPP
#define MEDIA_PLAYER_HPP

 
class MediaPlayer
{
public:
  MediaPlayer(string media_path = "./media/");
  ~MediaPlayer();
  //vector<Track> history();
  // bool setTrack(Track track);
  // bool nextTrack();
  void handleScreenResize();
  void listen();

  
  //bool changeAnimation(Animation anime);

private:
  void loadMedia();
  void printHistory();
  void printMedia(int offset = 0);
  void printDividers();
  void printSelector(int val, bool first=false);
  void moveUp();
  void moveDown();
  void next();
  void rewind();
  void play();
  const unsigned long getMsSinceEpoch();

  string _media_path;
  list<Track*> _q;
  vector<Track*> _history;
  vector<Track*> _all_tracks; 
  vector<Album> _albums;
  Track* _now_playing;
  FMOD::System* _system;
  

  int _maxx, _maxy, _cursor_x, _cursor_y, _animate_divider, _history_divider, _max_media, _min_media;
  unsigned long _msecs_rewind;
};

#endif //MEDIA_PLAYER_HPP
