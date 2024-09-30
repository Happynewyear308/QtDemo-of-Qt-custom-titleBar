#ifndef CUSTOMBORDER_H
#define CUSTOMBORDER_H

#include <QWidget>

class CustomBorder : public QWidget
{
    Q_OBJECT
public:
    explicit CustomBorder(QWidget *parent = nullptr);
    void setScaleCursor(int nshape = 0);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

public:
    QPoint m_mousePointOld;
    bool m_bKeepDrag;

signals:
    void moveEventSig(QPoint point);
    void mouseReleaseSig();
};

#endif // CUSTOMBORDER_H
