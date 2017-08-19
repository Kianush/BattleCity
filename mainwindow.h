#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//================================================================================================================
#include <QMainWindow>
//================================================================================================================
namespace Ui {
class MainWindow;
}
class Labyrinth;
class GameStatistic;
//================================================================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void slotGameOver();
    void slotNewGame();
private:
    Ui::MainWindow *ui;
    Labyrinth * m_pLabyrinth;
    GameStatistic * m_pGameStatistic;
    bool m_bGameStarted;
    void SetGame();
};
//================================================================================================================
#endif // MAINWINDOW_H
