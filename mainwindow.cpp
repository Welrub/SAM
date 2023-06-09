#include "mainwindow.h"
#include "authorizationinterface.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    loadPlugins();
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
        QMessageBox::information(this, "SAM", "Fail.");
    }else{
        WorkingSpace *ws = new WorkingSpace(&db);
        MainWindow::hide();
        ws->show();
    }
}

void MainWindow::loadPlugins()
{
    const auto staticInstances = QPluginLoader::staticInstances();
    for (QObject *plugin : staticInstances){
        auto IAuthorization = qobject_cast<AuthorizationInterface*>(plugin);
        if(IAuthorization){
            addOptions(IAuthorization); //TODO
        }
    }
    pluginsDir = QDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");

    const auto entryList = pluginsDir.entryList(QDir::Files);
        for (const QString &fileName : entryList) {
            QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = loader.instance();
            if (plugin) {                
                auto IAuthorization = qobject_cast<AuthorizationInterface*>(plugin);
                if(IAuthorization){
                    addOptions(IAuthorization); //TODO
                }
                pluginFileNames += fileName;
            }
        }
}
