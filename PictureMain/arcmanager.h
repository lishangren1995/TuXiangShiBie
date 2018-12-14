#ifndef ARCMANAGER_H
#define ARCMANAGER_H

#include <QWidget>

namespace Ui {
class ArcManager;
}

class ArcManager : public QWidget
{
    Q_OBJECT

public:
    explicit ArcManager(QWidget *parent = 0);
    ~ArcManager();
    void appendRowData(QStringList rowData); //添加一行数据

    void clearTableData(); //清除表格数据

    QStringList getCurrentRowData();

    QString getCurrentID();
private:
    Ui::ArcManager *ui;
};

#endif // ARCMANAGER_H
