#ifndef ADDUSERDLG_H
#define ADDUSERDLG_H

#include <QDialog>
#include <QVariantMap>
namespace Ui {
class adduserdlg;
}

class adduserdlg : public QDialog
{
    Q_OBJECT

public:
    explicit adduserdlg(QWidget *parent = 0);
    ~adduserdlg();

    void setEditData(QStringList rowData);

private slots:
    void on_buttonBox_4_accepted();

    void on_buttonBox_4_rejected();

private:
    void clearData();
signals:
    void signalStuInfo(QVariantMap stuInfo);

private:
    Ui::adduserdlg *ui;
};

#endif // ADDUSERDLG_H
