#include "workingspace.h"
#include "ui_workingspace.h"


WorkingSpace::WorkingSpace(QSqlDatabase* db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorkingSpace)
{    
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    tm = new QSqlTableModel(this, *db);
    tm->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
    tm->setTable("all_storages");
    tm->select();

    ui->tableView->setModel(tm);
    ui->tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i = 0; i < tm->rowCount(); ++i) {
        QString name = tm->record(i).value("name").toString();
        local_store.insert(name);
    }
}

WorkingSpace::~WorkingSpace()
{
    delete ui;
}

void WorkingSpace::on_addStorage_clicked()
{
    bool ok;
    QString input = QInputDialog::getText(this, tr("Creating new"),
                                            tr("Input name:"), QLineEdit::Normal, QString(),
                                            &ok);

    if(ok && !input.isEmpty() && local_store.find(input) == local_store.end()){
        QSqlQuery query;
        query.exec("insert into all_storages values('" + input + "')");
        query.exec("create table if not exists " + input + " (name TEXT, amount REAL, cost INTEGER, is_notific INTEGER, notification_if INTEGER)");
        local_store.insert(input);
        tm->select();
    }
}

void WorkingSpace::on_deleteChoosenStore_clicked()
{
    QString name = tm->record(row).value("name").toString();
    QSqlQuery query;
    query.exec("drop table " + name);
    query.exec("delete from all_storages where name='" + name + "'");
    local_store.remove(name);
    tm->select();
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
    QString name = tm->record(row).value("name").toString();
    currentChoosenStore *ccs = new currentChoosenStore(name, tm);
    ccs->show();
}
