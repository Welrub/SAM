#ifndef WORKINGSPACE_H
#define WORKINGSPACE_H

#include <QMainWindow>
#include "currentchoosenstore.h"

namespace Ui {
class WorkingSpace;
}

class WorkingSpace : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorkingSpace(QSqlDatabase* db, QWidget *parent = nullptr);
    ~WorkingSpace();

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
    QSet<QString> local_store;
    uint32_t row;
};

#endif // WORKINGSPACE_H
