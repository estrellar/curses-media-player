#include "Media.hpp"


vector<string> Media::readPath()
{
    vector<string> items;
    DIR* dirp = opendir(this->_path.c_str());
    struct dirent * dp;
    while((dp = readdir(dirp)) != NULL){
        if(dp->d_name != "." && dp->d_name != ".."){
            items.push_back(dp->d_name);
        }
    }
    closedir(dirp);
    return items;
}