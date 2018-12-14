#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QWidget>

namespace Ui {
class ProcessManager;
}

class ProcessManager : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessManager(QWidget *parent = 0);
    ~ProcessManager();
    void appendRowData(QStringList rowData); //添加一行数据

    void clearTableData(); //清除表格数据

    QStringList getCurrentRowData();

    QString getCurrentID();
private:
    Ui::ProcessManager *ui;
};

#endif // PROCESSMANAGER_H
