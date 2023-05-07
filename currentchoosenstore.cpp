#include "currentchoosenstore.h"
#include "ui_currentchoosenstore.h"

currentChoosenStore::currentChoosenStore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::currentChoosenStore)
{
    ui->setupUi(this);
}

currentChoosenStore::currentChoosenStore(QString name, QSqlTableModel *tm, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::currentChoosenStore)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->storageName->setText(name);
    name_of_this_store = name;
    tm_for_this_store = tm;
    tm_for_this_store->setTable(name);
    ui->tableView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(tm_for_this_store);
    tm_for_this_store->select();
}

currentChoosenStore::~currentChoosenStore()
{
    tm_for_this_store->setTable("all_storages");
    delete ui;
}

void currentChoosenStore::on_addItem_clicked()
{
    const int max_border = 2000000000;
    bool ok;
    QString name                    =    QInputDialog::getText(this, tr("Add new"),
                                                                                     tr("Name:"), QLineEdit::Normal, QString(), &ok);
    uint32_t amount               =    QInputDialog::getInt(this, tr("Add new"),
                                                                                     tr("Amount:"), 0, 0, max_border, 1, &ok);
    uint32_t cost                    =    QInputDialog::getInt(this, tr("Add new"),
                                                                                     tr("Cost:"), 0, 0, max_border, 1, &ok);
    QMessageBox::StandardButton is_notific = QMessageBox::question(this, tr("Add new"),
                                                                       tr("Send notificatoin?"), QMessageBox::Yes | QMessageBox::No);
    uint32_t notification_if = 0;
    if(is_notific == QMessageBox::Yes){
        notification_if   =   QInputDialog::getInt(this, tr("Add new"),
                                                                                     tr("Send notificatoin if:"), 0, 0, max_border, 1, &ok);
    }
    if(ok && !name.isEmpty()){
       QSqlQuery query;
       uint32_t is_note_bool = (is_notific == QMessageBox::Yes);
       QString q = "insert into " + name_of_this_store + " (name, amount, cost, is_notific, notification_if) "
                          "values('" + name + "' , " + QString::number(amount) + ", " + QString::number(cost) + ", " +
                           QString::number(is_note_bool) + ", " + QString::number(notification_if) + ")";
       query.exec(q);
       local_store.insert(name);
    }
    tm_for_this_store->select();
}

void currentChoosenStore::on_deleteItem_clicked()
{
    QString name = tm_for_this_store->record(row).value("name").toString();
    QSqlQuery query;
    query.exec("delete from " + name_of_this_store + " "
                      "where name='" + name + "'");
    local_store.remove(name);
}

void currentChoosenStore::on_findItem_clicked()
{
    bool ok;
    QString name   =   QInputDialog::getText(this, tr("Search"),
                                                                             tr("Input name:"), QLineEdit::Normal, QString(), &ok);
    if(ok && !name.isEmpty()){
        tm_for_this_store->setFilter("name='" + name + "'");
        tm_for_this_store->select();
    }
}

void currentChoosenStore::on_saveChanges_clicked()
{
    tm_for_this_store->submitAll();
}

void currentChoosenStore::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

