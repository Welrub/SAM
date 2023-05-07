#ifndef CURRENTCHOOSENSTORE_H
#define CURRENTCHOOSENSTORE_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTableView>
#include <QSet>
#include <QInputDialog>
#include <QMessageBox>
#include "notifications.h"

namespace Ui {
class currentChoosenStore;
}

class currentChoosenStore : public QMainWindow
{
    Q_OBJECT

public:
    explicit currentChoosenStore(QWidget *parent = nullptr);
    explicit currentChoosenStore(QString store, QSqlTableModel *tm, QWidget *parent = nullptr);
    ~currentChoosenStore();

private slots:
    void on_addItem_clicked();

    void on_deleteItem_clicked();

    void on_findItem_clicked();

    void on_saveChanges_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    int32_t row;
    QString name_of_this_store;
    QSqlTableModel *tm_for_this_store;
    QSet<QString> local_store;
    Ui::currentChoosenStore *ui;
};

#endif // CURRENTCHOOSENSTORE_H
