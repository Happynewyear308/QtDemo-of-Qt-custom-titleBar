#include "mainwindow.h"

#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

CustomMainWindow::CustomMainWindow(QWidget *parent)
    : QMainWindow(parent), dragging(false), lastMousePos(0, 0) {
    setWindowFlags(Qt::FramelessWindowHint); // 设置为无边框窗口

    this->setTitle("Custom MainWindow");
    this->setTitleIcon(":/image/icon_custom.png");
    main_layout = new QVBoxLayout();
    center_wdg = new QWidget(); // 中间部分
    initLayout();
    InitBorder();

    this->resize(500, 500);

    closeBtn = new QPushButton(this);
    closeBtn->setFixedSize(22, 22);
    closeBtn->setGeometry(this->width()-32, 3, 22, 22);
    QPixmap pixmap(":/image/icon_close.png");
    QPixmap scaledPixmap = pixmap.scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QIcon scaledIcon(scaledPixmap);
    closeBtn->setIcon(scaledIcon);
    closeBtn->setObjectName("closeBtn");

    maximizeBtn = new QPushButton(this);
    maximizeBtn->setFixedSize(22, 22);
    maximizeBtn->setGeometry(this->width()-60, 3, 22, 22);
    QPixmap pixmap2(":/image/icon_maximize.png");
    QPixmap scaledPixmap2 = pixmap2.scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QIcon scaledIcon2(scaledPixmap2);
    maximizeBtn->setIcon(scaledIcon2);
    maximizeBtn->setObjectName("maximizeBtn");

    minimizeBtn = new QPushButton(this);
    minimizeBtn->setFixedSize(22, 22);
    minimizeBtn->setGeometry(this->width()-88, 3, 22, 22);
    QPixmap pixmap3(":/image/icon_minimize.png");
    QPixmap scaledPixmap3 = pixmap3.scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QIcon scaledIcon3(scaledPixmap3);
    minimizeBtn->setIcon(scaledIcon3);
    minimizeBtn->setObjectName("minimizeBtn");


    connect(closeBtn, &QPushButton::clicked, this, &CustomMainWindow::on_closed);
    connect(maximizeBtn, &QPushButton::clicked, this, &CustomMainWindow::on_maximize);
    connect(minimizeBtn, &QPushButton::clicked, this, &CustomMainWindow::on_minimize);
//    QScreen *screen = QGuiApplication::primaryScreen();
//    connect(screen, &QScreen::geometryChanged, this, &CustomMainWindow::on_screenGeometryChanged);

    closeBtn->setStyleSheet("QPushButton#closeBtn {"
                            "   text-align: center;"
                            "   background-color: #F0F0F0;"
                            "   border-radius: 3px"
                            "}"
                            "QPushButton#closeBtn:hover {"
                            "   background-color: #6F2323;"
                            "}"
                            "QPushButton#closeBtn:pressed {"
                            "   background-color: #0033FF;"
                            "}");
    maximizeBtn->setStyleSheet("QPushButton#maximizeBtn {"
                               "   text-align: center;"
                               "   background-color: #F0F0F0;"
                               "   border-radius: 3px"
                               "}"
                               "QPushButton#maximizeBtn:hover {"
                               "   background-color: #003265;"
                               "}"
                               "QPushButton#maximizeBtn:pressed {"
                               "   background-color: #0033FF;"
                               "}");
    minimizeBtn->setStyleSheet("QPushButton#minimizeBtn {"
                               "   text-align: center;"
                               "   background-color: #F0F0F0;"
                               "   border-radius: 3px"
                               "}"
                               "QPushButton#minimizeBtn:hover {"
                               "   background-color: #003265;"
                               "}"
                               "QPushButton#minimizeBtn:pressed {"
                               "   background-color: #0033FF;"
                               "}");
}

void CustomMainWindow::setTitle(const QString &_title) {
    title = _title;
    update();
}

QString CustomMainWindow::getTitle() {
    return title;
}

void CustomMainWindow::setTitleIcon(const QString &_iconpath) {
    iconpath = _iconpath;
    update();
}

QMenuBar *CustomMainWindow::menuBar() const {
    if (!m_menuBar) {
//        CustomMainWindow *self = const_cast<CustomMainWindow *>(this);
//        menuBar = new QMenuBar(self);
//        self->setMenuBar(menuBar);
        return nullptr;
    }
    return m_menuBar;
}

QToolBar *CustomMainWindow::toolBar() const {
    if (!m_toolBar) {
        //        CustomMainWindow *self = const_cast<CustomMainWindow *>(this);
        //        menuBar = new QMenuBar(self);
        //        self->setMenuBar(menuBar);
        return nullptr;
    }
    return m_toolBar;
}

QStatusBar *CustomMainWindow::statusBar() const {
    if (!m_statusBar) {
        //        CustomMainWindow *self = const_cast<CustomMainWindow *>(this);
        //        menuBar = new QMenuBar(self);
        //        self->setMenuBar(menuBar);
        return nullptr;
    }
    return m_statusBar;
}

void CustomMainWindow::setLayout(QLayout *_layout) {
    center_wdg->setLayout(_layout);
}

QWidget* CustomMainWindow::takeCenterWdg() {
    return center_wdg;
}

QLayout* CustomMainWindow::layout() const {
    return center_wdg->layout();
}

void CustomMainWindow::setMenuBar(QMenuBar *_menuBar) {
    qDebug()<<"CustomMainWindow::setMenuBar";
    if (main_layout->menuBar() && m_menuBar != _menuBar) {
        // Reparent corner widgets before we delete the old menu bar.
        QMenuBar *oldMenuBar = qobject_cast<QMenuBar *>(main_layout->menuBar());
        if (_menuBar) {
            // TopLeftCorner widget.
            QWidget *cornerWidget = oldMenuBar->cornerWidget(Qt::TopLeftCorner);
            if (cornerWidget)
                _menuBar->setCornerWidget(cornerWidget, Qt::TopLeftCorner);
            // TopRightCorner widget.
            cornerWidget = oldMenuBar->cornerWidget(Qt::TopRightCorner);
            if (cornerWidget)
                _menuBar->setCornerWidget(cornerWidget, Qt::TopRightCorner);
        }
        oldMenuBar->hide();
        oldMenuBar->setParent(nullptr);
        oldMenuBar->deleteLater();
    }
    m_menuBar = _menuBar;
    if(m_menuBar->sizePolicy().verticalPolicy() != QSizePolicy::Fixed) {
//        qDebug()<<25;
        m_menuBar->setFixedHeight(25);
    }
    main_layout->insertWidget(0, m_menuBar);
}

void CustomMainWindow::setToolBar(QToolBar *_toolBar) {
    if (m_toolBar) {
        qWarning()<<"toolBar already exits, cannot add toolBar for window";
        return;
    }
    if(!_toolBar)
        m_toolBar = new QToolBar(centralWidget);
    else
        m_toolBar = _toolBar;
    if(m_toolBar->sizePolicy().verticalPolicy() != QSizePolicy::Fixed) {
        m_toolBar->setFixedHeight(40);
    }
    else if(m_toolBar->height()<30 || m_toolBar->height()>50){
        m_toolBar->setFixedHeight(40);
    }
    if(!menuBar()) {
        main_layout->insertWidget(0, m_toolBar);
    }
    else {
        main_layout->insertWidget(1, m_toolBar);
    }
}

void CustomMainWindow::setStatusBar(QStatusBar *_statusBar) {
    if (m_statusBar) {
        qWarning()<<"statusBar already exits, cannot add toolBar for window";
        return;
    }
    if(!_statusBar)
        m_statusBar = new QStatusBar(centralWidget);
    else
        m_statusBar = _statusBar;
    if(m_statusBar->sizePolicy().verticalPolicy() != QSizePolicy::Fixed) {
        m_statusBar->setFixedHeight(40);
    }
    else if(m_statusBar->height()<30 || m_statusBar->height()>50){
        m_statusBar->setFixedHeight(40);
    }
//    main_layout->addStretch();
    main_layout->addWidget(m_statusBar);
}

void CustomMainWindow::paintEvent(QPaintEvent *event)  {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制自定义边框和标题栏
    painter.setBrush(Qt::lightGray);
    painter.drawRect(0, 0, width(), height());

    QRect rect = this->rect().adjusted(6, 6, -6, -6);  // 矩形区域，留出边距
    int radius = 3;  // 圆角半径
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(rect, radius, radius);

    painter.setBrush(Qt::darkGray);
    painter.drawRect(0, 0, width(), 30); // 绘制标题栏

    // 加载并绘制 PNG 图标
    QPixmap icon(iconpath);
    painter.drawPixmap(5, 5, 20, 20, icon);

    painter.setPen(Qt::white);
    painter.drawText(35, 20, title); // 绘制标题

    QMainWindow::paintEvent(event);
}

void CustomMainWindow::mousePressEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        if (event->y() < 30) { // 点击在标题栏
            dragging = true;
            lastMousePos = event->pos();
        }
    }
}

void CustomMainWindow::mouseMoveEvent(QMouseEvent *event)  {
    if (dragging) {
        QPoint tem =  pos() + event->pos() - lastMousePos;
        move(tem.x(), tem.y()); // 拖拽窗口
    }
}

void CustomMainWindow::mouseReleaseEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        dragging = false;
    }
}

void CustomMainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    closeBtn->setGeometry(this->width()-32, 3, 22, 22);
    maximizeBtn->setGeometry(this->width()-60, 3, 22, 22);
    minimizeBtn->setGeometry(this->width()-88, 3, 22, 22);
    DarwBorder();
}

void CustomMainWindow::InitBorder()
{
    minWindowWidth = 200;   //最小窗口宽度
    minWindowHeight = 100;  //最小窗口高度


    //上下左右的label，为了控制界面能够拖动拉伸
    labelLft = new CustomBorder(this);
    labelLft->setObjectName("labelLft");
    labelLft->raise();
    labelLft->setScaleCursor(1);


    labelRit = new CustomBorder(this);
    labelRit->raise();
    labelRit->setScaleCursor(1);//设置为左右拉升光标


    labelBot = new CustomBorder(this);
    labelBot->raise();
    labelBot->setScaleCursor(2);//设置为上下拉升光标


    labelTop = new CustomBorder(this);
    labelTop->setScaleCursor(2);//设置为上下拉升光标

    labelRB = new CustomBorder(this);
    labelRB->setScaleCursor(3);//设置为右下拉升光标

    labelRT = new CustomBorder(this);
    labelRT->setScaleCursor(4);//设置为右上拉升光标

    labelLB = new CustomBorder(this);
    labelLB->setScaleCursor(4);//设置为左下拉升光标

    labelLT = new CustomBorder(this);
    //    labelLT->setStyleSheet("QWidget {background-color: transparent;}");//设置背景透明
    labelLT->setScaleCursor(3);//设置为左上拉升光标


    labelRit->setObjectName("labelRit");
    labelBot->setObjectName("labelBot");
    labelTop->setObjectName("labelTop");
    labelRB->setObjectName("labelRB");
    labelRT->setObjectName("labelRT");
    labelLB->setObjectName("labelLB");
    labelLT->setObjectName("labelLT");


    this->setMinimumWidth(minWindowWidth);
    this->setMinimumHeight(minWindowHeight);
    //绘制边框
    DarwBorder();

    //关联回调函数
    connect(labelLft, SIGNAL(moveEventSig(QPoint)), this, SLOT(getLeftScaleEvent(QPoint)));
    connect(labelRit, SIGNAL(moveEventSig(QPoint)), this, SLOT(getRightScaleEvent(QPoint)));
    connect(labelBot, SIGNAL(moveEventSig(QPoint)), this, SLOT(getBottomScaleEvent(QPoint)));
    connect(labelTop, SIGNAL(moveEventSig(QPoint)), this, SLOT(getTopScaleEvent(QPoint)));
    connect(labelRB, SIGNAL(moveEventSig(QPoint)), this, SLOT(getRBScaleEvent(QPoint)));
    connect(labelRT, SIGNAL(moveEventSig(QPoint)), this, SLOT(getRTScaleEvent(QPoint)));
    connect(labelLB, SIGNAL(moveEventSig(QPoint)), this, SLOT(getLBScaleEvent(QPoint)));
    connect(labelLT, SIGNAL(moveEventSig(QPoint)), this, SLOT(getLTScaleEvent(QPoint)));

    this->setObjectName("custom_mainwindow");
}


void CustomMainWindow::initLayout() {
    centralWidget = new QWidget(this);
    QMainWindow::setCentralWidget(centralWidget);
    centralWidget->setObjectName("central_wdg");
//    QWidget *test = new QWidget();
//    test->setObjectName("test");
    main_layout->addWidget(center_wdg);

    main_layout->setContentsMargins(7, 31, 7, 7);
//    main_layout->setAlignment(Qt::AlignTop);

    main_layout->setSpacing(0);
//    main_layout->addWidget(test);
    centralWidget->QMainWindow::setLayout(main_layout);

//    centralWidget->setStyleSheet(QString(R"(
//        QWidget#central_wdg {
//            background-color:transparent;
//        }
//    )"));
}

void CustomMainWindow::DarwBorder()
{
    labelLft->setGeometry(0,10,5,this->height()-15);
    labelRit->setGeometry(this->width()-5,10,5,this->height()-15);
    labelBot->setGeometry(5,this->height()-5,this->width()-10,5);
    labelTop->setGeometry(5,0,this->width()-10,5);
    labelRB->setGeometry(this->width()-6,this->height()-6,6,6);
    labelRT->setGeometry(this->width()-6,0,6,6);
    labelLB->setGeometry(0,this->height()-6,6,6);
    labelLT->setGeometry(0,0,6,6);
}

void CustomMainWindow::getLeftScaleEvent(QPoint movPoint)
{
    if((pos().x()+movPoint.x())>(pos().x()+this->width()-minWindowWidth))
    {
        return;//保证拖动窗口左边界的时候，控件宽度至少有200
    }
    //    qDebug()<<"minimumWidth:"<<minimumWidth();
    this->setGeometry(pos().x()+movPoint.x(),pos().y(),this->width()-movPoint.x(),this->height());
//    DarwBorder();
//    closeBtn->setGeometry(this->width()-32, 3, 20, 20);
}

void CustomMainWindow::getRightScaleEvent(QPoint movPoint)
{
    if((pos().x()+this->width()+movPoint.x())<(pos().x()+minWindowWidth))
    {
        return;//保证拖动窗口右边界的时候，控件宽度至少有200
    }
    this->setGeometry(pos().x(),pos().y(),this->width()+movPoint.x(),this->height());
//    DarwBorder();
//    closeBtn->setGeometry(this->width()-32, 3, 20, 20);
}

void CustomMainWindow::getBottomScaleEvent(QPoint movPoint)
{
    if((pos().y()+this->height()+movPoint.y())<(pos().y()+minWindowHeight))
    {
        return;//保证拖动窗口下边界的时候，控件高度至少有200
    }
    this->setGeometry(pos().x(),pos().y(),this->width(),this->height()+movPoint.y());
//    DarwBorder();
}

void CustomMainWindow::getTopScaleEvent(QPoint movPoint)
{
    if((pos().y()+movPoint.y())>(pos().y()+this->height()-minWindowHeight))
    {
        return;//保证拖动窗口上边界的时候，控件高度至少有200
    }
    this->setGeometry(pos().x(),pos().y()+movPoint.y(),this->width(),this->height()-movPoint.y());
//    DarwBorder();
}

void CustomMainWindow::getRBScaleEvent(QPoint movPoint)
{
    if((pos().y()+this->height()+movPoint.y())<(pos().y()+minWindowHeight)
        || (pos().x()+this->width()+movPoint.x())<(pos().x()+minWindowWidth))
    {
        return;//保证拖动窗口上边界的时候，控件高度和宽度至少有200
    }
    this->setGeometry(pos().x(),pos().y(),this->width()+movPoint.x(),this->height());
    this->setGeometry(pos().x(),pos().y(),this->width(),this->height()+movPoint.y());
//    DarwBorder();
//    closeBtn->setGeometry(this->width()-32, 3, 20, 20);
}

void CustomMainWindow::getRTScaleEvent(QPoint movPoint)
{
    if((pos().x()+this->width()+movPoint.x())<(pos().x()+minWindowWidth)
        || (pos().y()+movPoint.y())>(pos().y()+this->height()-minWindowHeight) )
    {
        return;//保证拖动窗口上边界的时候，控件高度和宽度至少有200
    }
    this->setGeometry(pos().x(),pos().y()+movPoint.y(),this->width(),this->height()-movPoint.y());
    this->setGeometry(pos().x(),pos().y(),this->width()+movPoint.x(),this->height());
//    DarwBorder();
//    closeBtn->setGeometry(this->width()-32, 3, 20, 20);
}

void CustomMainWindow::getLTScaleEvent(QPoint movPoint)
{
    if((pos().x()+movPoint.x())>(pos().x()+this->width()-minWindowWidth)
        || (pos().y()+movPoint.y())>(pos().y()+this->height()-minWindowHeight) )
    {
        return;//保证拖动窗口上边界的时候，控件高度和宽度至少有200
    }
    this->setGeometry(pos().x()+movPoint.x(),pos().y(),this->width()-movPoint.x(),this->height());
    this->setGeometry(pos().x(),pos().y()+movPoint.y(),this->width(),this->height()-movPoint.y());
//    DarwBorder();
//    closeBtn->setGeometry(this->width()-32, 3, 20, 20);
}

void CustomMainWindow::getLBScaleEvent(QPoint movPoint)
{
    if((pos().x()+movPoint.x())>(pos().x()+this->width()-minWindowWidth)
        || (pos().y()+this->height()+movPoint.y())<(pos().y()+minWindowHeight))
    {
        return;//保证拖动窗口上边界的时候，控件高度和宽度至少有200
    }
    this->setGeometry(pos().x()+movPoint.x(),pos().y(),this->width()-movPoint.x(),this->height());
    this->setGeometry(pos().x(),pos().y(),this->width(),this->height()+movPoint.y());
//    DarwBorder();
//    closeBtn->setGeometry(this->width()-32, 3, 20, 20);
}

void CustomMainWindow::on_closed() {
    this->close();
}
void CustomMainWindow::on_maximize() {
    if (this->windowState() & Qt::WindowMaximized) {
        // 如果当前是最大化状态，则还原
        this->showNormal();
    } else {
        // 否则将窗口最大化
        this->showMaximized();
    }
}
void CustomMainWindow::on_minimize() {
    this->showMinimized();
}


