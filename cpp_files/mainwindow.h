#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//================================================================================================================
#include <QMainWindow>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QtGui>
#include <QDeclarativeContext>
//================================================================================================================
namespace Ui {
class MainWindow;
}
class Labyrinth;
class GameStatistic;
class MainDeclarativeView;
class AudioDelegate;
class GameAudioThread;
//================================================================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Q_INVOKABLE void NewGameButtonQmlClick();
private slots:
    void slotGameOver();
    void slotNewGame();
private:
    QObject * m_pRoot;
    //Ui::MainWindow *ui;
    QDeclarativeView * m_pqdvUi;
    Labyrinth * m_pLabyrinth;
    GameStatistic * m_pGameStatistic;
    bool m_bGameStarted;
    void SetGame();
    AudioDelegate * m_pAudioDelegate;
    GameAudioThread * m_pGameAudioThread;
};
//================================================================================================================
#endif // MAINWINDOW_H
