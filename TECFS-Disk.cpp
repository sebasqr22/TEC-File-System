#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <dirent.h>
#include <filesystem>
#include <unistd.h>

using namespace std;

class TECFS_Disk{
    private:
        string route = "./RAID";
        string todo;
        fstream prueba;
        
        
    public:
        void setRoute(string routeA){
            route = routeA;
        }
        int FileSize(string routeA){
            ifstream o(routeA, ifstream::ate | ifstream::binary);
            int size = o.tellg();
            return size;
        }
        void todos(){
            string todo;
            
        }
        void DiskNodeSize(){
            DIR * dir; struct dirent *diread;
            vector<string> files;
            if ((dir = opendir("./NUEVA")) != nullptr){
                while ((diread = readdir(dir)) != nullptr){
                    if (string(diread->d_name).find(".txt") != string::npos)
                        files.push_back(diread->d_name);
                }
                closedir(dir);
            }
            int a;
            for (auto file : files){
                cout << "file name: " << file << endl; 
                a += FileSize("./NUEVA" + file);
                cout << "Suma parcial: " << FileSize("./NUEVA" + file) << endl;
                sleep(3);
            }
            cout << "Total Size: " << a << endl;


        }
        
};