#include "quiz_game.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

int main() {
    try {
        QuizGame quiz;
        string playerName;
        int choice;

        cout << "Selamat datang di Kuis Interaktif!\n";
        cout << "Masukkan nama Anda: ";
        getline(cin, playerName);
        quiz.setPlayerName(playerName);

        do {
            quiz.displayMenu();
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: {
                    int numQuestions;
                    cout << "Masukkan jumlah pertanyaan (1-10): ";
                    do {
                        cin >> numQuestions;
                        if (cin.fail() || numQuestions < 1 || numQuestions > 10) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Input tidak valid. Masukkan angka 1-10: ";
                        }
                    } while (numQuestions < 1 || numQuestions > 10);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    quiz.runQuiz(numQuestions);
                    break;
                }
                case 2:
                    quiz.displayStatistics();
                    break;
                case 3: {
                    int diff;
                    cout << "Atur kesulitan (1-3): ";
                    do {
                        cin >> diff;
                        if (cin.fail() || diff < 1 || diff > 3) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Input tidak valid. Masukkan angka 1-3: ";
                        }
                    } while (diff < 1 || diff > 3);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    quiz.setDifficulty(diff);
                    break;
                }
                case 4: {
                    char confirm;
                    cout << "Anda yakin ingin keluar? (y/n): ";
                    cin >> confirm;
                    if (tolower(confirm) != 'y') {
                        choice = 0;
                    }
                    break;
                }
                default:
                    cout << "Pilihan tidak valid!\n";
                    break;
            }
        } while (choice != 4);

        cout << "Terima kasih telah bermain!" << endl;
        return 0;
    }
    catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}