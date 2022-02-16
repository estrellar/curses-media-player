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
  string getArtist();
  ifstream getAlbumArt();
  vector<Track> getTracks();
private:
  vector<Track> _tracks;
  void loadTracks(string path);
  string _artist;
  string _album_art_path;

};
#endif //ALBUM_HPP
