#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QWidget>
#include <QMainWindow>
#include "usermanager.h"
#include "imagemanager.h"
#include "arcmanager.h"
#include "processmanager.h"
#include "createdb.h"
#include "adduserdlg.h"
#include "laserwelddlg.h"
#include "recorddlg.h"
#include "arcdlg.h"
#include "quanju.h"


namespace Ui {
class datamanager;
}

class datamanager :  public QMainWindow
{
    Q_OBJECT


public:

    explicit datamanager(QWidget *parent = 0);
    ~datamanager();
   QString wps;
signals:
    void GetUdpLogMsg(QString msg);
private slots:
    void onBtnAdd();

    void onBtnEdit();

    void onBtnDel();

    void onBtnRefresh();

    void ExecAddSql(QVariantMap stuInfo);

    void ExecEditSql(QVariantMap stuInfo);

    void ExecDelSql(QString id);



    void on_pshuaixin_clicked();

    void on_pushButton_kaishi_clicked();

private:
    Ui::datamanager *ui;

    void initUi();

    void setTabCornerBtn();

    void initAddDlg();

private:
    UserManager *m_UserManager;
    ImageManager *m_ImageManager;
    ArcManager *m_ArcManager;
    ProcessManager *m_ProcessManager;

    createdb *m_createDB;
    adduserdlg * m_pAddStuDlg;
    laserwelddlg *m_laserwelddlg;
    recorddlg *a_recorddlg;
    arcdlg *m_arcdlg;


};

#endif // DATAMANAGER_H
