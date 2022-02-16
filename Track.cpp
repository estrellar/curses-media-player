#include "Track.hpp"

Track::Track(string path)
{
  auto split = this->_path.find('-');
  if(split != string::npos){
    this->_track_num = atoi(this->_path.substr(0, split-1).c_str());
    this->_name = this->_path.substr(split + 1, this->_path.length());
  }
}

Track::~Track()
{
  return;
}


