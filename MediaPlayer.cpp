#include "MediaPlayer.hpp"
#include <iostream>

#define HEADER_HEIGHT 3

using namespace std;

MediaPlayer::MediaPlayer(string media_path)
{
    this->_media_path = media_path;
    //TODO: load albums in ^path

    this->loadMedia();
    //init and clear screen
    initscr();
    clear();
    
    // calc partitions and print history+media
    this->handleScreenResize();

}

void MediaPlayer::handleScreenResize()
{
    getmaxyx(stdscr, this->_maxy, this->_maxx);
    this->_animate_divider = this->_maxy/2;
    this->_history_divider = this->_maxx/2;
    this->drawDividers();
    this->printHistory();
    this->printMedia();
}

void MediaPlayer::drawDividers()
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

void MediaPlayer::printHistory()
{
    mvprintw(1, 0, "| HISTORY");

    for(int i = 0; i <  this->_animate_divider && i < this->_history.size(); i++){
        mvprintw(HEADER_HEIGHT + i, 0, 
            this->_history.at(i)
            .getName()
            .substr(0, this->_history_divider-1)
            .c_str()
        );
    }
}

void MediaPlayer::printMedia(int offset)
{
    mvprintw(1, this->_history_divider + 1, " MEDIA");
    int j = 0;
    for(int i = offset; i < this->_animate_divider && i < this->_albums.size(); i++){
        mvprintw(HEADER_HEIGHT + j++, this->_animate_divider + 1,
            this->_albums.at(j)
            .getName()
            .substr(0, this->_history_divider -1 )
            .c_str()
        );
    }   
}

MediaPlayer::~MediaPlayer()
{
    endwin();
}