// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    quiz = new QuizGame();
    setupUI();
}

void MainWindow::setupUI()
{
    // Set window properties
    setWindowTitle("Quiz Game");
    setMinimumSize(800, 600);

    // Create stacked widget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Add pages
    stackedWidget->addWidget(createLoginPage());
    stackedWidget->addWidget(createMainMenuPage());
    stackedWidget->addWidget(createQuizPage());
    stackedWidget->addWidget(createStatsPage());

    // Set initial page
    stackedWidget->setCurrentIndex(0);
}

QWidget* MainWindow::createLoginPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    // Add welcome label
    QLabel *welcomeLabel = new QLabel("Welcome to Quiz Game!");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; margin: 20px;");

    // Add name input
    QLineEdit *nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter your name");
    nameInput->setMaximumWidth(300);

    // Add start button
    QPushButton *startBtn = new QPushButton("Start");
    startBtn->setMaximumWidth(200);

    connect(startBtn, &QPushButton::clicked, [=]() {
        QString name = nameInput->text();
        if (!name.isEmpty()) {
            try {
                quiz->setPlayerName(name.toStdString());
                stackedWidget->setCurrentIndex(1); // Go to main menu
            } catch (const std::exception& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        } else {
            QMessageBox::warning(this, "Error", "Please enter your name");
        }
    });

    // Add widgets to layout
    layout->addWidget(welcomeLabel);
    layout->addWidget(nameInput, 0, Qt::AlignCenter);
    layout->addWidget(startBtn, 0, Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);

    return page;
}

QWidget* MainWindow::createMainMenuPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(page);

    // Create menu buttons
    QPushButton *startQuizBtn = new QPushButton("Start Quiz");
    QPushButton *statsBtn = new QPushButton("Statistics");
    QPushButton *difficultyBtn = new QPushButton("Change Difficulty");
    QPushButton *exitBtn = new QPushButton("Exit");

    // Style buttons
    QString buttonStyle = "QPushButton {"
                         "    padding: 10px;"
                         "    font-size: 16px;"
                         "    min-width: 200px;"
                         "    margin: 5px;"
                         "}";
    startQuizBtn->setStyleSheet(buttonStyle);
    statsBtn->setStyleSheet(buttonStyle);
    difficultyBtn->setStyleSheet(buttonStyle);
    exitBtn->setStyleSheet(buttonStyle);

    // Connect buttons
    connect(startQuizBtn, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(statsBtn, &QPushButton::clicked, this, &MainWindow::showStatistics);
    connect(difficultyBtn, &QPushButton::clicked, this, &MainWindow::changeDifficulty);
    connect(exitBtn, &QPushButton::clicked, this, &QMainWindow::close);

    // Add buttons to layout
    layout->addWidget(startQuizBtn, 0, Qt::AlignCenter);
    layout->addWidget(statsBtn, 0, Qt::AlignCenter);
    layout->addWidget(difficultyBtn, 0, Qt::AlignCenter);
    layout->addWidget(exitBtn, 0, Qt::AlignCenter);

    return page;
}

// Implementasi method lainnya...