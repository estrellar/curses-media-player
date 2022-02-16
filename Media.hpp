#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <vector>

using namespace std;

#ifndef MEDIA_HPP
#define MEDIA_HPP

class Media {
    public:
        string getName();
    protected:
        string _name;
        string _path;
};

#endif