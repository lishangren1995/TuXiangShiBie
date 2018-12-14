#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QTreeWidget>
#include <QGraphicsView>
#include <QTableWidget>
class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = 0);
    QImage img;
    QGraphicsScene scene;//视图.存储数据
    QGraphicsView *graph;//负责窗口显示
    QTreeWidget *menuTree;
    QTableWidget *table_widget;
    void initTreeWidget();

signals:

public slots:
};

#endif // SHOWWIDGET_H
