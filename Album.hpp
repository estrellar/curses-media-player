#include <string>
#include <vector>
#include "Track.hpp"
#include "Media.hpp"

using namespace std;

#ifndef ALBUM_HPP
#define ALBUM_HPP



class Album : public Media
{
public:
  Album(const string path);
  ~Album();
  ifstream getAlbumArt();
  vector<Track*> getTracks();
private:
  vector<Track*> _tracks;
  void parseTracks();

};
#endif //ALBUM_HPP
