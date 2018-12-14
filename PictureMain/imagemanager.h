#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QWidget>

namespace Ui {
class ImageManager;
}

class ImageManager : public QWidget
{
    Q_OBJECT

public:
    explicit ImageManager(QWidget *parent = 0);
    ~ImageManager();
    void appendRowData(QStringList rowData); //添加一行数据

    void clearTableData(); //清除表格数据

    QStringList getCurrentRowData();

    QString getCurrentID();
private:
    Ui::ImageManager *ui;
};

#endif // IMAGEMANAGER_H
