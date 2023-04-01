#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


void MainWindow::on_entry_button_clicked()
{
//    QString login = ui->login_for_user->displayText();
//    QString pass = ui->pass_for_user->displayText();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("./sam_main.db");
    db.setUserName("root");
    db.setPassword("");
    if(!db.open()){
        QMessageBox::information(this, "SAM", "Не удалось подключиться к базе данных.");
    }else{
        WorkingSpace *ws = new WorkingSpace();
        try{
            ws->loading(db);
        }catch(...){
            QMessageBox::information(this, "SAM", "Не удалось подключиться к базе данных.");
        }
        MainWindow::hide();
        ws->show();
    }
}
