#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>

#include "customborder.h"

class CustomMainWindow : public QMainWindow {
    Q_OBJECT

public:
    CustomMainWindow(QWidget *parent = nullptr);

    void setTitle(const QString &_title);
    QString getTitle();
    void setTitleIcon(const QString &_iconpath);

    QWidget *takeCenterWdg();   // 中心内容
    QLayout* layout() const;
    void setMenuBar(QMenuBar *_menuBar);
    QMenuBar *menuBar() const;
    void setToolBar(QToolBar *_toolBar); // 使用setUnifiedTitleAndToolBarOnMac会发生布局错乱，没想到解决方案
    QToolBar *toolBar() const;
    void setStatusBar(QStatusBar *_statusBar);
    QStatusBar *statusBar() const;

    void setLayout(QLayout *_layout);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *ev) override;

private:
    void initLayout();  // 创建

    void DarwBorder();
    void InitBorder();

private slots:
    void getLeftScaleEvent(QPoint movPoint);
    void getRightScaleEvent(QPoint movPoint);
    void getBottomScaleEvent(QPoint movPoint);
    void getTopScaleEvent(QPoint movPoint);
    void getRBScaleEvent(QPoint movPoint);
    void getRTScaleEvent(QPoint movPoint);
    void getLTScaleEvent(QPoint movPoint);
    void getLBScaleEvent(QPoint movPoint);

    void on_closed();
    void on_maximize();
    void on_minimize();
//    void on_screenGeometryChanged(const QRect &geometry);

private:
    bool dragging; // 是否拖拽窗口
    QPoint lastMousePos; // 最后鼠标位置

    uint16_t minWindowHeight; //最小窗口高度
    uint16_t minWindowWidth;   //最小窗口宽度

    CustomBorder *labelLft;
    CustomBorder *labelRit;
    CustomBorder *labelBot;
    CustomBorder *labelTop;
    CustomBorder *labelRB;
    CustomBorder *labelRT;
    CustomBorder *labelLB;
    CustomBorder *labelLT;

    QString iconpath;
    QString title;

    QPushButton *closeBtn = nullptr;
    QPushButton *maximizeBtn = nullptr;
    QPushButton *minimizeBtn = nullptr;

    QWidget *centralWidget = nullptr;
    QVBoxLayout* main_layout = nullptr;

    QMenuBar *m_menuBar = nullptr;
    QToolBar *m_toolBar = nullptr;
    QWidget *center_wdg = nullptr;
    QStatusBar *m_statusBar = nullptr;
};


#endif // MAINWINDOW_H
