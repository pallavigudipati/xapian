#include "/home/pallavi/POSE/xapian/xapian-core/include/xapian.h"
#include "/home/pallavi/POSE/xapian/xapian-core/api/trie.cc"
// #include "/home/pallavi/POSE/xapian/xapian-core/api/omdatabase.cc"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Xapian::Trie t;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
