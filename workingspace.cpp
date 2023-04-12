#include "workingspace.h"
#include "ui_workingspace.h"


WorkingSpace::WorkingSpace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorkingSpace)
{
    ui->setupUi(this);
}

WorkingSpace::~WorkingSpace()
{
    delete ui;
}

void WorkingSpace::loading(QSqlDatabase& db){
    tm = new QSqlTableModel(this, db);
    tm->setTable("all_storages");
    tm->select();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(tm);
    for (int i = 0; i < tm->rowCount(); ++i) {
        QString name = tm->record(i).value("name").toString();
        _local_stor.insert(name);
    }
}

void WorkingSpace::on_addStorage_clicked()
{
    bool ok;
    QString input = QInputDialog::getText(this, tr("Создание нового склада"),
                                            tr("Введите название:"), QLineEdit::Normal, QString(),
                                            &ok);

    if(ok && !input.isEmpty() && _local_stor.find(input) == _local_stor.end()){

        QSqlQuery query;
        query.exec("insert into all_storages values('" + input + "')");
        //    query.exec("create table " + input + " (name varchar, amount REAL, cost INTEGER,
        //                                                              notification_if INTEGER, is_notific BOOL)");
        tm->select();
    }
}

void WorkingSpace::on_deleteChoosenStore_clicked()
{
    tm->removeRow(row);
}

void WorkingSpace::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void WorkingSpace::on_saveChanges_clicked()
{
    tm->submitAll();
}

void WorkingSpace::on_updateAllStorages_clicked()
{
    tm->select();
}

void WorkingSpace::on_chooseCurrStorage_clicked()
{
    notifications *note = new notifications();
    QString mes = "Storage was opened";
    note->post(mes);
}
