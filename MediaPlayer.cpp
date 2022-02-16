#include "MediaPlayer.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

#define HEADER_HEIGHT 3

using namespace std;

MediaPlayer::MediaPlayer(string media_path)
{
    this->_media_path = media_path;
    this->loadMedia();

    //init and clear screen
    initscr();
    clear();
    
    // calc partitions and print history+media
    this->handleScreenResize();
    getch();
}

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
            ->getName()
            .substr(0, this->_history_divider-1)
            .c_str()
        );
    }
}

void MediaPlayer::printMedia(int offset)
{
    mvprintw(1, this->_history_divider + 1, " MEDIA");
    int j = 0;
    Album* a;
    for(int i = offset; i < this->_animate_divider && i < this->_albums.size(); i++){
        a = &this->_albums.at(i);
        mvprintw(HEADER_HEIGHT + j++, this->_animate_divider + 1,
            a->getName()
            .substr(0, this->_history_divider - 1)
            .c_str()
        );
        for(int k = 0; k < a->getTracks().size(); k++)
        {
            mvprintw(HEADER_HEIGHT + j++, this->_animate_divider + 1,
                a->getTracks().at(k)
                .getName()
                .substr(0, this->_history_divider - 1)
                .c_str()
            );
        }
    }   
}

MediaPlayer::~MediaPlayer()
{
    endwin();
}