#include "testwindow.h"

TestWindow::TestWindow(QWidget *parent)
    : CustomMainWindow(parent)
{
    m_menubar = new QMenuBar(this);
    tem_act1 = new QAction(m_menubar);
    tem_act1->setText("act 1");
    m_menubar->addAction(tem_act1);
    this->setMenuBar(m_menubar); // 设置菜单栏
    m_menubar->setStyleSheet(QString(R"(
        QMenuBar {
            background-color: red;
        }
    )"));


    m_toolbar = new QToolBar();
//    m_toolbar->setFixedHeight(35);
    this->setToolBar(m_toolbar);
    m_toolbar->setFixedHeight(50);

    m_toolbar->setStyleSheet(QString(R"(
        QToolBar {
            background-color: blue;
        }
    )"));

    m_statusBar = new QStatusBar();
    this->setStatusBar(m_statusBar);
    m_statusBar->setStyleSheet(QString(R"(
        QStatusBar {
            background-color: green;
        }
    )"));

//    test1 = new QWidget(this);
//    test2 = new QWidget(this);
//    test3 = new QWidget(this);
//    test1->setObjectName("test1");
//    test2->setObjectName("test2");
//    test3->setObjectName("test3");

//    test1->setStyleSheet(QString(R"(
//        QWidget#test1 {
//            background-color: lightgray;
//        }
//    )"));
//    test2->setStyleSheet(QString(R"(
//        QWidget#test2 {
//            background-color: orange;
//        }
//    )"));
//    test3->setStyleSheet(QString(R"(
//        QWidget#test3 {
//            background-color: yellow;
//        }
//    )"));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
//    layout->addWidget(test1);
//    layout->addWidget(test2);
//    layout->addWidget(test3);
    this->setLayout(layout);

    toolbar_act1 = new QAction("toolitem1", m_toolbar);
    toolbar_act2 = new QAction("toolitem2", m_toolbar);
    m_toolbar->addAction(toolbar_act1);
    m_toolbar->addAction(toolbar_act2);

}
