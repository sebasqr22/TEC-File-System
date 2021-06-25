/**
 * @file TECFS-Disk.cpp
 * @title TECFS Disk
 * @brief Class that controlls memory  managment of the disk nodes
**/

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
        string route = "./RAID/";
        string todo;
        fstream prueba;
        
        
    public:
        /**
         * @brief Method that sets the route
        **/
        void setRoute(string routeA){
            route + routeA;
        }
        /**
         * @brief Method to obtain a file's size
         * @return Size of a file
        **/
        int FileSize(string routeA){
            ifstream o(routeA, ifstream::ate | ifstream::binary);
            int size = o.tellg();
            return size;
        }
        /**
         * @brief Method for get a Disk Node
         * @return String Vector with data from a Disk Node
        **/
        vector<string> getDiskNodes(){
            vector<string> dirs;
            DIR * dir; struct dirent *diread;
            if ((dir = opendir("./RAID/")) != nullptr){
                while ((diread = readdir(dir)) != nullptr){
                    if (string(diread->d_name).length() > 2 )
                        dirs.push_back(diread->d_name); //dirs es todo el raid
                }
                closedir(dir);
            }
            return dirs;
        }
        /**
         * @brief Method to obtain the size of a Disk Node
        **/
        void DiskNodeSize(vector<string> diskNodes){
            DIR * dir; struct dirent *diread;
            for (string diskNode : diskNodes){ 
                vector<string> files;
                string directory = "./RAID/" + diskNode;
                cout << "Directorio: " << directory << endl;
                if ((dir = opendir(directory.c_str())) != nullptr){
                    while ((diread = readdir(dir)) != nullptr){
                        if (string(diread->d_name).find(".txt") != string::npos)
                            files.push_back(diread->d_name);
                    }
                    closedir(dir);
                }
                int a = 0;
                for (auto file : files){
                    cout << "file name: " << file << endl; 
                    a += FileSize(directory + "/" + string(file));
                }
                cout << "Total Size: " << a << endl;
            }
        }
        
};