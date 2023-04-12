#ifndef WORKINGSPACE_H
#define WORKINGSPACE_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include <QInputDialog>
#include <QSet>
#include "notifications.h"

namespace Ui {
class WorkingSpace;
}

class WorkingSpace : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorkingSpace(QWidget *parent = nullptr);
    ~WorkingSpace();
    void loading(QSqlDatabase& db);

private slots:
    void on_addStorage_clicked();

    void on_deleteChoosenStore_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_saveChanges_clicked();

    void on_updateAllStorages_clicked();

    void on_chooseCurrStorage_clicked();

private:
    Ui::WorkingSpace *ui;
    QSqlTableModel *tm;
    QTableView *view;
    QSet<QString> _local_stor;
    int32_t row;
};

#endif // WORKINGSPACE_H
