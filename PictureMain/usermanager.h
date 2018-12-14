#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QWidget>

namespace Ui {
class UserManager;
}

class UserManager : public QWidget
{
    Q_OBJECT

public:
    explicit UserManager(QWidget *parent = 0);
    ~UserManager();
    void appendRowData(QStringList rowData); //添加一行数据

    void clearTableData(); //清除表格数据

    QStringList getCurrentRowData();

    QString getCurrentID();
private:
    Ui::UserManager *ui;
};

#endif // USERMANAGER_H
