#include "MediaPlayer.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <chrono>

#define HEADER_HEIGHT 3

using namespace std;

MediaPlayer::MediaPlayer(string media_path)
{
  this->_media_path = media_path;
  this->loadMedia();

  //init, clear screen, hide input, hide cursor
  initscr();
  clear();
  noecho();
  curs_set(0);

  // calc partitions and print history+media
  this->handleScreenResize();


  this->_msecs_rewind = 0;
}

/**
 * @brief 
 * loop to listen for input
 */
void MediaPlayer::listen()
{
  int c;
  bool state = 0;
  while(1){
    c = getch();
    switch(c){
      case KEY_W:
        //move cursor up
        this->moveUp();
        break;
      case KEY_S:
        this->moveDown();
        //move cursor down
        break;
        //forward
      //case KEY_TAB:
      case KEY_D:
        this->next();
        break;
        //back
      case KEY_A:
        this->rewind();
        break;
        //play
      case KEY_RESUME:
      case KEY_SPACE:
        this->play();
        break;
    }
  }
}

/**
 * @brief 
 * load media from this->_media_path
 */
void MediaPlayer::loadMedia()
{
  DIR* dirp = opendir(this->_media_path.c_str());
  struct dirent * dp;
  while((dp = readdir(dirp)) != NULL){
    string path = this->_media_path;
    if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")){}
    else{
      Album a = Album(path.append(dp->d_name).append("/"));
      this->_albums.push_back(a);
    }
  }
  closedir(dirp);
}

/**
 * @brief 
 * recalc dividers + call prints
 */
void MediaPlayer::handleScreenResize()
{
  getmaxyx(stdscr, this->_maxy, this->_maxx);
  this->_animate_divider = this->_maxy/2;
  this->_history_divider = this->_maxx/2;
  this->printDividers();
  this->printHistory();
  this->printMedia(0);
  move(this->_min_media, this->_history_divider + 1);
  this->printSelector(0, true);
}
/**
 * @brief 
 * print separators between sections
 */
void MediaPlayer::printDividers()
{
  //draw horizontal line
  for (int i = 0; i < this->_maxx; i++){
    move(this->_animate_divider, i);
    addch('-');
    move(0, i);
    addch('-');
    move(2, i);
    addch('-');
  }
  for(int i = 0; i < this->_animate_divider; i++){
    move(i, this->_history_divider);
    addch('|');
  }
}

/**
 * @brief 
 * print a list of recently played songs 
 *
 */
void MediaPlayer::printHistory()
{
  mvprintw(1, 0, "| HISTORY");

  for(int i = 0; i <  this->_animate_divider && i < this->_history.size(); i++){
    mvprintw(HEADER_HEIGHT + i, 0,
	     this->_history.at(i)
	     ->getName()
	     .substr(0, this->_history_divider-1)
	     .c_str()
	     );
  }
}

/**
 * @brief 
 *  print tracks in "Media" section
 *  creates list of available tracks for indexing
 * @param a_offset 
 */
void MediaPlayer::printMedia(int a_offset)
{

  mvprintw(1, this->_history_divider + 1, " MEDIA");
  int j = 0;
  Album* a;
  //loop through albums
  for(int i = a_offset; i < this->_animate_divider && i < this->_albums.size(); i++){
    a = &this->_albums.at(i);
    //print album name
    // mvprintw(HEADER_HEIGHT + j++, this->_history_divider + 1,
    // 	     a->getName()
    // 	     .substr(0, this->_history_divider - 1)
    // 	     .c_str()
    // 	     );
    vector<Track> t = a->getTracks();
    //print track names in album
    for(int k = 0; k < t.size() && HEADER_HEIGHT + j < this->_animate_divider; k++){
      //dont print tracks past animation divider
      if(HEADER_HEIGHT + j < this->_animate_divider){
        move(HEADER_HEIGHT + j++, this->_history_divider + 4);
        t[k];
        printw(
          t.at(k)
          .getName()
          .substr(0, this->_history_divider - 1)
          .c_str()
          );
      }
      
      this->_all_tracks.push_back(&t[k]);
    }
  }

  this->_max_media = HEADER_HEIGHT + j - 1;
  this->_min_media = HEADER_HEIGHT;
  this->_cursor_x = this->_history_divider + 1;
  this->_cursor_y =  this->_min_media;
}

void MediaPlayer::printSelector(int val, bool first)
{
  move(this->_cursor_y, this->_history_divider + 1);
  if(first){
    printw("->");
  }else{
    printw("  ");
    this->_cursor_y = (this->_min_media + (this->_cursor_y + val)) % (this->_max_media);
    move(this->_cursor_y, this->_history_divider + 1);
    printw("->");
  }
}

/*************Music Navigation***********/
void MediaPlayer::moveUp()
{
  this->printSelector(1);
}

void MediaPlayer::moveDown()
{
  this->printSelector(-1);
}

void MediaPlayer::next()
{
  this->printSelector(-1);
  this->play();
}

void MediaPlayer::rewind()
{
  if(this->_msecs_rewind == 0){
    this->_msecs_rewind = MediaPlayer::getMsSinceEpoch();
    this->play();
  }else{
    unsigned long since = MediaPlayer::getMsSinceEpoch() - this->_msecs_rewind;
    cout << "rewind" << since << endl;
  }
}

void MediaPlayer::play()
{
  
}

/**
 * @brief Get MS Since Epoch
 * 
 * @return unsigned long 
 */
const unsigned long MediaPlayer::getMsSinceEpoch()
{
  return chrono::system_clock::now().time_since_epoch() / chrono::milliseconds(1);
}


MediaPlayer::~MediaPlayer()
{
  endwin();
}

