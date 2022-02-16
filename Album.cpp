#include "Album.hpp"
#include <iostream> 
#include <string.h>

Album::Album(string path)
{
  this->_path = path;
  auto split = this->_path.find('-');
  if(split != string::npos){
    this->_artist = this->_path.substr(0, split-1);
    this->_name = this->_path.substr(split + 1, this->_path.length());
  }
  this->loadTracks(path);
}

Album::~Album()
{

}

vector<Track> Album::getTracks()
{
  return this->_tracks;
}

void Album::loadTracks(string path)
{
  DIR* dirp = opendir(path.c_str());
  struct dirent * dp;
  while((dp = readdir(dirp)) != NULL){
    string album_path = path;
    if(!strcmp(dp->d_name, "cover.ascii")){
      this->_album_art_path = album_path.append(dp->d_name);
    }
    else if(!strcmp(dp->d_name, ".") 
      || !strcmp(dp->d_name, "..") 
      || !strcmp(dp->d_name, "cover.jpg")){

    }
    else{
      album_path.append(dp->d_name);
      cout << album_path << endl;
      Track a = Track(album_path);
      this->_tracks.push_back(a);
    }
  }
  closedir(dirp);
}