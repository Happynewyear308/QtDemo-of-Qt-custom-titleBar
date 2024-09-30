#include "customborder.h"

#include <QMouseEvent>
#include <QDebug>

CustomBorder::CustomBorder(QWidget *parent)
    :m_bKeepDrag(false)
{
    this->setParent(parent);
    this->setObjectName("ui_border");
    this->setStyleSheet(QString(R"(
        QWidget#ui_border {
            background-color: blue;
        }
    )"));
}

void CustomBorder::setScaleCursor(int nshape) {
    if(nshape == 1) {
        setCursor(Qt::SizeHorCursor);
    }
    else if(nshape == 2) {
        setCursor(Qt::SizeVerCursor);
    }
    else if(nshape == 3) {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(nshape == 4) {
        setCursor(Qt::SizeBDiagCursor);
    }
    else {
        setCursor(Qt::ArrowCursor);
    }
}

void CustomBorder::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton) {
        m_bKeepDrag = true;
        m_mousePointOld = ev->globalPos();
        qDebug()<<this->objectName();
    }
}

void CustomBorder::mouseMoveEvent(QMouseEvent *ev) {
    if(m_bKeepDrag) {
        const QPoint position = ev->globalPos() - m_mousePointOld;
        emit moveEventSig(position);
        m_mousePointOld = ev->globalPos();
    }
}

void CustomBorder::mouseReleaseEvent(QMouseEvent *ev) {
    if(m_bKeepDrag) {
        Q_UNUSED(ev);
        m_bKeepDrag = false;
        emit mouseReleaseSig();
    }
}
