#include <curses.h>
#include <vector>
#include <list>
#include <string>
#include "Album.hpp"
#include "Track.hpp"

using namespace std;


#ifndef MEDIA_PLAYER_HPP
#define MEDIA_PLAYER_HPP
 
class MediaPlayer
{
  
  public:

    MediaPlayer(string media_path = "./media/");
    ~MediaPlayer();
    vector<Track*> history();
    bool setTrack(Track track);
    bool nextTrack();
    void handleScreenResize();
    
    //bool changeAnimation(Animation anime);

  private:
    void loadMedia();
    void printHistory();
    void printMedia(int offset = 0);
    void drawDividers();
    string _media_path;
    list<Track> _q;
    vector<Track> _history;
    vector<Album> _albums;
    Track _now_playing;
    int _maxx, _maxy, _cursor_x, _cursor_y, _animate_divider, _history_divider;

};

#endif //MEDIA_PLAYER_HPP
