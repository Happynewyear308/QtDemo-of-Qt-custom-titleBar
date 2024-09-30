#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include "mainwindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>

class TestWindow : public CustomMainWindow
{
    Q_OBJECT
public:
    TestWindow(QWidget *parent = nullptr);

private:
    QMenuBar *m_menubar = nullptr;
    QAction *tem_act1 = nullptr;
    QToolBar *m_toolbar = nullptr;
    QStatusBar *m_statusBar = nullptr;

    QWidget *test1 = nullptr;
    QWidget *test2 = nullptr;
    QWidget *test3 = nullptr;

    QAction *toolbar_act1 = nullptr;
    QAction *toolbar_act2 = nullptr;
};

#endif // TESTWINDOW_H
