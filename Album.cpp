#include "Album.hpp"

Album::Album(string path)
{
  this->_path = path;
  auto split = this->_path.find('-');
  if(split != string::npos){
    this->_artist = this->_path.substr(0, split-1);
    this->_name = this->_path.substr(split + 1, this->_path.length());
    
  }
}

Album::~Album()
{

}