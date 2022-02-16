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
    int getTrackNum();
  private:
    string _track_num;
};
#endif //TRACK_HPP
