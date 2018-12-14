#ifndef ARCDLG_H
#define ARCDLG_H

#include <QDialog>
#include "quanju.h"
namespace Ui {
class arcdlg;
}

class arcdlg : public QDialog
{
    Q_OBJECT

public:
    explicit arcdlg(QWidget *parent = 0);
    ~arcdlg();

    void setEditData(QStringList rowData);
    void clearData();
signals:
    void signalStuInfo();
private slots:


    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

private:
    Ui::arcdlg *ui;
};

#endif // ARCDLG_H
