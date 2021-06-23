#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <stdlib.h>
#include <experimental/filesystem>

using namespace std;

class disk_node{
    private:
        int maxTotal;
    public:
    void create(){
        system("rm -r ./RAID");
        mkdir("./RAID", 0777);
        for(int i=0; i<4; i++){
            string directory = "./RAID/disk" + to_string(i);
            mkdir(directory.c_str(), 0777);

            for(int j=0; j<20; j++){
                string directory2 = "./RAID/disk" + to_string(i) + "/bloque" + to_string(j);
                mkdir(directory2.c_str(), 0777);
            }
        }
    }
};