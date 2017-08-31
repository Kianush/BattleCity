#ifndef MAINDECLARATIVEVIEW_H
#define MAINDECLARATIVEVIEW_H
//================================================================================================================
#include <QtWidgets>
#include <QtDeclarative>
//================================================================================================================
class MainDeclarativeView : public QDeclarativeView
{
Q_OBJECT
public:
    MainDeclarativeView(QWidget *pParent = 0);
    virtual ~MainDeclarativeView();
signals:
    void sigKeyPress(const int &iKey);
    void sigKeyRelease(const int &iKey);
protected:
    virtual void keyPressEvent(QKeyEvent * pKeyEvent);
    virtual void keyReleaseEvent(QKeyEvent * pKeyEvent);
};
//================================================================================================================
#endif // MAINDECLARATIVEVIEW_H
