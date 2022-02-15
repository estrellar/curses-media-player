#include <string>
#include "Media.hpp"
using namespace std;

#ifndef TRACK_HPP
#define TRACK_HPP

class Track : public Media
{
  public:
    Track(string path);
    ~Track();

    string getName();
    int getTrackNum();
  private:
    string path;
};
#endif //TRACK_HPP
