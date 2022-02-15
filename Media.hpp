#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <vector>

using namespace std;


class Media {
    public:
        vector<string> readPath();
        void setName(string name);
        string getName();
        void setArtist(string artist_name);
        string getArtist();
    protected:
        string _name;
        string _artist;
        string _path;
};