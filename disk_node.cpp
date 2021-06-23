#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

using namespace std;

class disk_node{
    private:
        int maxTotal;
    public:
    void create(int size){
        if (size <= 5 && size >= 3){
            for(int i=0; i<size; i++){
                string directory = "./RAID/disk" + to_string(i);
                mkdir(directory.c_str(), 0777);
            }
        }
    }
};