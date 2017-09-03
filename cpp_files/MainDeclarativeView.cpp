#include "MainDeclarativeView.h"
//================================================================================================================
MainDeclarativeView::MainDeclarativeView(QWidget *pParent) : QDeclarativeView(pParent)
{

}
//================================================================================================================
MainDeclarativeView::~MainDeclarativeView()
{

}
//================================================================================================================
void MainDeclarativeView::keyPressEvent(QKeyEvent * pKeyEvent)
{
    bool bIsKeyToGame = false;
    int iKey = pKeyEvent->key();
    if (iKey == Qt::Key_Space) {
        if (!pKeyEvent->isAutoRepeat()) {
            bIsKeyToGame = true;
        }
    }
    if (iKey == Qt::Key_Up) {
        bIsKeyToGame = true;
    }
    if(iKey == Qt::Key_Down) {
        bIsKeyToGame = true;
    }
    if(iKey == Qt::Key_Left) {
        bIsKeyToGame = true;
    }
    if(iKey == Qt::Key_Right) {
        bIsKeyToGame = true;
    }
    if (bIsKeyToGame) {
        emit sigKeyPress(iKey);
    }
    QDeclarativeView::keyPressEvent(pKeyEvent);
}
//================================================================================================================
void MainDeclarativeView::keyReleaseEvent(QKeyEvent * pKeyEvent)
{
    bool bIsKeyToGame = false;
    int iKey = pKeyEvent->key();
    if (iKey == Qt::Key_Up || iKey == Qt::Key_Down || iKey == Qt::Key_Left || iKey == Qt::Key_Right) {
        bIsKeyToGame = true;
    }
    else if (iKey == Qt::Key_Space) {
        if (!pKeyEvent->isAutoRepeat()) {
            bIsKeyToGame = true;
        }
    }
    else {}
    if (bIsKeyToGame) {
        emit sigKeyRelease(iKey);
    }
    QDeclarativeView::keyReleaseEvent(pKeyEvent);
}
//================================================================================================================
