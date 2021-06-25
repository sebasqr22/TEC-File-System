/**
 * @file mainwindow.cpp
 * @title Main Window
 * @brief Class with window's methods
 * */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "disk_node.cpp"
#include "book_actions.cpp"
#include "LinkedList.cpp"
#include "controller_node.cpp"
#include <unistd.h>
#include <QDebug>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <experimental/filesystem>

using namespace std;
typedef unsigned char byte;

/**
 * @brief Main constructor
 * */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief Method to set some messages on screen
 * */
void MainWindow::contentText(QString data, int time){
    ui->content->setText("");
    ui->content->setText(data);
    sleep(time);
}
/**
 * @brief Method to add a book to the RAID
 * */
void AddToRaid(const char* directory){
    LinkedList<vector<byte>> linked;
    disk_node diskNode;
    QStringList books;
    QString aux;

    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(directory)) != NULL){
       while((ent = readdir(dir)) != NULL){
           aux = QString::fromStdString(string(ent->d_name));
           if(aux.contains("txt")){
               books.append(aux);
           }
       }
       closedir(dir);
    }
    else{
        qInfo() << "Can't open dc" << endl;
    }

    int size = books.size();
    for(int i=0; i<size; i++){
        qInfo() << books[i];
    }
    diskNode.create();
    for(int j=0; j<size; j++){
        linked = splitFile(string(directory) + "/" + books[j].toStdString());
        createBookPartitions(linked, "book");
    }

}
/**
 * @brief Method for save a new book
 **/
void MainWindow::on_guardarBoton_clicked()
{
    book_actions actions;
    QString nameB = ui->name->text();
    QString content = ui->content->toPlainText();
    qInfo() << nameB << "---" << content;

    if(nameB != "" && content != ""){
        if(nameB.contains(".txt")){
            nameB.remove(".txt");
        }
        contentText("---Inserting--" + nameB + ".txt--to--directory---", 5);
        actions.createBook(nameB.toStdString(), content.toStdString());
        contentText("---Getting--from--actual--directory---", 2);

        //AddToRaid("/home/sebas/Escritorio/ceROBOT/ceROBOT/books/");
    }
}
/**
 * @brief Method to add books to RAID
 **/
void MainWindow::on_pushButton_clicked()
{
    AddToRaid("/home/sebas/Escritorio/ceROBOT/ceROBOT/books/");
    ui->content->setText("Se partio todo");
}
