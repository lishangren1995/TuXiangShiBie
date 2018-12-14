#ifndef RECORDDLG_H
#define RECORDDLG_H

#include <QDialog>

namespace Ui {
class recorddlg;
}

class recorddlg : public QDialog
{
    Q_OBJECT

public:
    explicit recorddlg(QWidget *parent = 0);
    ~recorddlg();
    void setEditData(QStringList rowData);
    void clearData();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();
    void printdata(QString msg1,QString msg2,QString msg3,QString msg4,QString msg5,QString msg6);

private:
    Ui::recorddlg *ui;
};

#endif // RECORDDLG_H
