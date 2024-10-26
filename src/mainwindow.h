// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStackedWidget>
#include "quiz_game.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startGame();
    void showStatistics();
    void changeDifficulty();
    void submitAnswer();
    void showMainMenu();

private:
    Ui::MainWindow *ui;
    QuizGame *quiz;
    QStackedWidget *stackedWidget;
    
    // Pages
    QWidget *createLoginPage();
    QWidget *createMainMenuPage();
    QWidget *createQuizPage();
    QWidget *createStatsPage();
    
    void setupUI();
    void updateScore(int score);
};

#endif // MAINWINDOW_H