#ifndef LASERWELDDLG_H
#define LASERWELDDLG_H

#include <QWidget>
#include <QDialog>
#include <QPrintDialog>

namespace Ui {
class laserwelddlg;
}

//class laserwelddlg : public QWidget
class laserwelddlg : public QDialog
{
    Q_OBJECT

public:
    void setEditData(QStringList rowData);

    void clearData();
    explicit laserwelddlg(QWidget *parent = 0);
    ~laserwelddlg();
private:



private slots:
    //void on_buttonBox_accepted();
   // void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::laserwelddlg *ui;
};

#endif // LASERWELDDLG_H
