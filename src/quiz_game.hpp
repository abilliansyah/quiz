// quiz_game.hpp
#ifndef QUIZ_GAME_HPP
#define QUIZ_GAME_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

// Struktur untuk menyimpan pertanyaan
struct Question {
    string question;     // Pertanyaan
    string answer;       // Jawaban
    string hint;        // Petunjuk
    string explanation; // Penjelasan
    int difficulty;     // Tingkat kesulitan (1-3)
};

// Struktur untuk menyimpan statistik pemain
struct PlayerStats {
    string playerName;
    int totalScore = 0;
    int gamesPlayed = 0;
    int questionsAnswered = 0;
    int correctAnswers = 0;
    double averageScore = 0.0;
    time_t lastPlayed = 0;
};

class QuizGame {
private:
    vector<Question> questions;              // Daftar pertanyaan
    map<string, PlayerStats> playerRecords;  // Record pemain
    PlayerStats currentPlayer;               // Pemain saat ini
    int currentDifficulty;                   // Tingkat kesulitan saat ini

    // Private helper methods
    void loadQuestions();
    void loadPlayerStats();
    void savePlayerStats();
    string cleanInput(string input);
    bool isValidPlayerName(const string& name);
    int calculateScore(bool correct, int difficulty, int timeSpent);
    void displayAnswerFeedback(bool isCorrect, int score, const Question& q);
    void updatePlayerStats(int totalScore, int correctAnswers, int numQuestions);

public:
    // Constructor
    QuizGame();

    // Getter dan Setter
    void setPlayerName(const string& name);
    void setDifficulty(int diff);
    int getDifficulty() const { return currentDifficulty; }
    const PlayerStats& getCurrentPlayer() const { return currentPlayer; }

    // Core gameplay methods
    void displayMenu();
    void clearScreen();
    int askQuestion(const Question& q);
    void runQuiz(int numQuestions);
    
    // Display methods
    void displayStatistics();
    void displayQuizResults(int totalScore, int correctAnswers, int numQuestions, double duration);

    // Constants
    static constexpr int MIN_DIFFICULTY = 1;
    static constexpr int MAX_DIFFICULTY = 3;
    static constexpr int MAX_QUESTIONS = 10;
    static constexpr int MIN_NAME_LENGTH = 1;
    static constexpr int MAX_NAME_LENGTH = 30;

    // Exception classes
    class QuizGameException : public runtime_error {
    public:
        QuizGameException(const string& message) : runtime_error(message) {}
    };

    class InvalidInputException : public QuizGameException {
    public:
        InvalidInputException(const string& message) : QuizGameException(message) {}
    };

    class FileOperationException : public QuizGameException {
    public:
        FileOperationException(const string& message) : QuizGameException(message) {}
    };
};

#endif // QUIZ_GAME_HPP