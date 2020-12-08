#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../DasDatabaseManager/dasexport.h"
#include <QDebug>
#include "Util/utils.h"
#include <QLibrary>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //testDatabase();
    const char *host = "127.0.0.1";

    int port = 3306;
    const char *user = "root";
    const char *pwd = "ajdts";
    const char *dbname = "das_database";

    initDatabaseConnection(host,port,user,pwd,dbname);
}

void MainWindow::on_pushButton_2_clicked()
{
    //selectTest();
    int *pCount = new int;
    int result = getUserCount(pCount);

    //qDebug()<<"result = "<<result <<"  count = "<<*pCount;

    for(int i = 0;i<*pCount;i++){
        USER *puser = new USER;
        int nRet = getUser(puser,i);
        qDebug()<<"user = "<<puser->username<<"   "<<puser->password<<"  "<<puser->userType;

        if(puser)
        {
            delete puser;
            puser = nullptr;
        }
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    int *pCount = new int;
    int result = getUserCount(pCount);

    qDebug()<<"result = "<<result <<"  count = "<<*pCount;

    delete pCount;
    pCount = nullptr;
}

void MainWindow::on_pushButton_4_clicked()
{
    USER *puser = new USER;

    strcpy(puser->username,"admin");
    strcpy(puser->password,"123");

    int type = -1;

    int result = userLogin(puser,&type);

    qDebug()<<"result = "<<result<<"   type="<<type;

    delete puser;
    puser = nullptr;
}

void MainWindow::on_pushButton_5_clicked()
{
    USER *puser = new USER;

    strcpy(puser->username,"gaopy");
    strcpy(puser->password,"666");
    puser->userType = 1;

    qDebug()<<"ret ="<<insertUser(puser);

    delete puser;
    puser = nullptr;
}

void MainWindow::on_pushButton_6_clicked()
{
    USER *puser = new USER;

    strcpy(puser->username,"gaopy");
    strcpy(puser->password,"666");
    puser->userType = 1;

    qDebug()<<"ret ="<<deleteUser(puser);

    delete puser;
    puser = nullptr;
}
