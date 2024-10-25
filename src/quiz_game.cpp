// quiz_game.cpp
#include "quiz_game.hpp"
#include <random>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <cctype>

QuizGame::QuizGame() {
    try {
        loadQuestions();
        loadPlayerStats();
        currentDifficulty = 1;
    }
    catch (const exception& e) {
        cerr << "Error initializing game: " << e.what() << endl;
        throw;
    }
}

void QuizGame::loadQuestions() {
    try {
        questions = {
            // Mudah (Difficulty: 1)
            {"Apa ibu kota Indonesia?", "Jakarta", "Ibu kota di Pulau Jawa", 
             "Jakarta adalah ibu kota dan kota terbesar di Indonesia.", 1},
            {"Berapa jumlah warna dalam pelangi?", "7", "Jumlah antara 5 dan 10", 
             "Pelangi memiliki tujuh warna: merah, jingga, kuning, hijau, biru, nila, ungu.", 1},
            {"Apa simbol kimia untuk air?", "H2O", "Terdiri dari 2 unsur", 
             "Air adalah senyawa kimia dengan rumus H2O.", 1},
            
            // Sedang (Difficulty: 2)
            {"Siapa penemu lampu pijar?", "Thomas Edison", "Seorang penemu asal Amerika", 
             "Thomas Edison menemukan lampu pijar yang praktis pada tahun 1879.", 2},
            {"Planet apa yang terdekat dengan matahari?", "Merkurius", "Bukan Venus atau Bumi", 
             "Merkurius adalah planet terdekat dengan Matahari di tata surya.", 2},
            
            // Sulit (Difficulty: 3)
            {"Berapa kecepatan cahaya dalam kilometer per detik?", "299792", "Hampir 300.000", 
             "Kecepatan cahaya adalah 299.792 kilometer per detik dalam ruang hampa.", 3}
        };

        if (questions.empty()) {
            throw runtime_error("Tidak ada pertanyaan yang dimuat");
        }
    }
    catch (const exception& e) {
        cerr << "Error loading questions: " << e.what() << endl;
        throw;
    }
}

void QuizGame::loadPlayerStats() {
    ifstream inFile("player_stats.txt");
    if (!inFile) {
        cerr << "Warning: Tidak dapat membuka file player_stats.txt\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        try {
            PlayerStats stats;
            size_t pos = line.find(',');
            if (pos != string::npos) {
                stats.playerName = line.substr(0, pos);
                // Parse other stats here
                playerRecords[stats.playerName] = stats;
            }
        }
        catch (const exception& e) {
            cerr << "Error parsing player stats: " << e.what() << endl;
        }
    }
    inFile.close();
}

void QuizGame::savePlayerStats() {
    ofstream outFile("player_stats.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Tidak dapat menyimpan statistik pemain\n";
        return;
    }

    outFile << currentPlayer.playerName << ","
           << currentPlayer.totalScore << ","
           << currentPlayer.gamesPlayed << ","
           << currentPlayer.questionsAnswered << ","
           << currentPlayer.correctAnswers << ","
           << fixed << setprecision(2) << currentPlayer.averageScore << ","
           << currentPlayer.lastPlayed << endl;
    outFile.close();
}

string QuizGame::cleanInput(string input) {
    // Hapus spasi di awal dan akhir
    while (!input.empty() && isspace(input.front())) input.erase(0, 1);
    while (!input.empty() && isspace(input.back())) input.pop_back();
    
    // Ubah ke lowercase
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

void QuizGame::clearScreen() {
    cout << string(50, '\n');
}

bool QuizGame::isValidPlayerName(const string& name) {
    if (name.empty() || name.length() > 30) return false;
    return all_of(name.begin(), name.end(), [](char c) {
        return isalnum(c) || isspace(c);
    });
}

void QuizGame::setPlayerName(const string& name) {
    if (!isValidPlayerName(name)) {
        throw invalid_argument("Nama pemain tidak valid");
    }
    currentPlayer.playerName = name;
    if (playerRecords.find(name) != playerRecords.end()) {
        currentPlayer = playerRecords[name];
    }
}

void QuizGame::setDifficulty(int diff) {
    if (diff < 1 || diff > 3) {
        throw invalid_argument("Level kesulitan tidak valid");
    }
    currentDifficulty = diff;
}

void QuizGame::displayMenu() {
    cout << "\n╔═══════════════════════╗\n";
    cout << "║      QUIZ GAME        ║\n";
    cout << "╠═══════════════════════╣\n";
    cout << "║ 1. Mulai Quiz        ║\n";
    cout << "║ 2. Lihat Statistik   ║\n";
    cout << "║ 3. Atur Kesulitan (" << currentDifficulty << ") ║\n";
    cout << "║ 4. Keluar            ║\n";
    cout << "╚═══════════════════════╝\n";
    cout << "Pilihan Anda: ";
}

int QuizGame::calculateScore(bool correct, int difficulty, int timeSpent) {
    if (!correct) return 0;
    if (difficulty < 1 || difficulty > 3) {
        cerr << "Warning: Invalid difficulty level\n";
        return 0;
    }
    
    int baseScore = 10 * difficulty;
    
    // Bonus berdasarkan waktu
    if (timeSpent < 5) baseScore += 5;      // Bonus cepat
    else if (timeSpent < 10) baseScore += 3; // Bonus sedang
    else if (timeSpent < 15) baseScore += 1; // Bonus lambat
    
    return baseScore;
}

void QuizGame::displayAnswerFeedback(bool isCorrect, int score, const Question& q) {
    cout << "\n" << string(40, '-') << "\n";
    if (isCorrect) {
        cout << "✓ Benar! +" << score << " poin\n";
    } else {
        cout << "✗ Salah.\n";
        cout << "Jawaban yang benar: " << q.answer << "\n";
        cout << "Penjelasan: " << q.explanation << "\n";
    }
    cout << string(40, '-') << "\n";
}

int QuizGame::askQuestion(const Question& q) {
    string userAnswer;
    auto start = steady_clock::now();
    bool usedHint = false;

    cout << "\nPertanyaan: " << q.question << endl;
    if (currentDifficulty > 1) {
        cout << "(Ketik 'hint' untuk petunjuk, -2 poin)" << endl;
    }

    do {
        cout << "Jawaban: ";
        getline(cin, userAnswer);
        
        if (userAnswer.empty ()) {
            cout << "Jawaban tidak boleh kosong!\n";
            continue;
        }

        if (userAnswer == "hint" && currentDifficulty > 1 && !usedHint) {
            cout << "Petunjuk: " << q.hint << endl;
            usedHint = true;
            continue;
        }
        
        break;
    } while (true);

    auto end = steady_clock::now();
    auto duration = duration_cast<seconds>(end - start).count();

    userAnswer = cleanInput(userAnswer);
    string correctAnswer = cleanInput(q.answer);

    bool isCorrect = (userAnswer == correctAnswer);
    int score = calculateScore(isCorrect, q.difficulty, duration);
    
    if (usedHint && score > 0) {
        score -= 2; // Pengurangan poin untuk penggunaan hint
    }

    displayAnswerFeedback(isCorrect, score, q);
    return score;
}

void QuizGame::runQuiz(int numQuestions) {
    if (numQuestions <= 0) {
        cerr << "Error: Jumlah pertanyaan tidak valid\n";
        return;
    }

    vector<Question> currentQuestions;
    copy_if(questions.begin(), questions.end(), back_inserter(currentQuestions),
            [this](const Question& q) { return q.difficulty == currentDifficulty; });
    
    if (currentQuestions.empty()) {
        cout << "Tidak ada pertanyaan tersedia untuk tingkat kesulitan ini.\n";
        return;
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(currentQuestions.begin(), currentQuestions.end(), g); // Lebih baik dari random_shuffle

    numQuestions = min(numQuestions, (int)currentQuestions.size());
    int totalScore = 0;
    int correctAnswers = 0;

    for (int i = 0; i < numQuestions; i++) {
        clearScreen();
        cout << "Pertanyaan " << (i + 1) << "/" << numQuestions << "\n";
        cout << string(30, '-') << endl;

        int score = askQuestion(currentQuestions[i]);
        if (score > 0) correctAnswers++;
        totalScore += score;

        cout << "\nSkor: " << totalScore << endl;
        cout << "\nTekan Enter untuk lanjut... ";
        cin.get();
    }

    displayQuizResults(totalScore, correctAnswers, numQuestions, 0);
    updatePlayerStats(totalScore, correctAnswers, numQuestions);
}

void QuizGame::displayStatistics() {
    clearScreen();
    cout << "╔════════════════════════════════╗\n";
    cout << "║       STATISTIK PEMAIN         ║\n";
    cout << "╠════════════════════════════════╣\n";
    cout << "║ Nama: " << setw(23) << left << currentPlayer.playerName << "║\n";
    cout << "║ Total Permainan: " << setw(14) << currentPlayer.gamesPlayed << "║\n";
    cout << "║ Rata-rata Skor: " << fixed << setprecision(2) 
         << setw(14) << currentPlayer.averageScore << "║\n";
    cout << "║ Jawaban Benar: " << setw(15) 
         << to_string(currentPlayer.correctAnswers) + "/" + 
            to_string(currentPlayer.questionsAnswered) << "║\n";
    cout << "╚════════════════════════════════╝\n";
    
    cout << "\nTekan Enter untuk kembali... ";
    cin.get();
}

void QuizGame::displayQuizResults(int totalScore, int correctAnswers, int numQuestions, double duration) {
    clearScreen();
    cout << "╔════════════════════════════════╗\n";
    cout << "║       HASIL QUIZ             ║\n";
    cout << "╠════════════════════════════════╣\n";
    cout << "║ Skor Total: " << setw(14) << totalScore << "║\n";
    cout << "║ Jawaban Benar: " << setw(15) 
         << to_string(correctAnswers) + "/" + 
            to_string(numQuestions) << "║\n";
    cout << "║ Waktu yang dibutuhkan: " << fixed << setprecision(2) 
         << setw(14) << duration << " detik║\n";
    cout << "╚════════════════════════════════╝\n";
    
    cout << "\n Tekan Enter untuk kembali... ";
    cin.get();
}

void QuizGame::updatePlayerStats(int totalScore, int correctAnswers, int numQuestions) {
    currentPlayer.totalScore += totalScore;
    currentPlayer.gamesPlayed++;
    currentPlayer.questionsAnswered += numQuestions;
    currentPlayer.correctAnswers += correctAnswers;
    currentPlayer.averageScore = (double)currentPlayer.totalScore / currentPlayer.gamesPlayed;
    currentPlayer.lastPlayed = time(0);
    savePlayerStats();
}