#include <iostream>
#include <string>
using namespace std;

int main() {
    string rep;
    
    do {
        cout << "==============================" <<;
        cout << "   КРЕСТИКИ-НОЛИКИ" <<;
        cout << "==============================" <<;
        cout << "Вводите числа 1-9 для хода" <<;
        cout << "Поле выглядит так:" <<;
        cout << " 1 | 2 | 3 " <<;
        cout << "-----------" <<;
        cout << " 4 | 5 | 6 " <<;
        cout << "-----------" <<;
        cout << " 7 | 8 | 9 " <<;
        cout << "==============================" <<;
        
        char brd[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // board -> brd
        char cur = 'X';
        bool ovr = false;
        int mvv; 
        
        while (!ovr) {
            cout << "\n=============================="; // это типо разделитель, вдруг непонятнго
            cout << "Сейчас ходит: " << cur;
            cout << "\n " << brd[0] << " | " << brd[1] << " | " << brd[2] << " ";
            cout << "-----------" <<;
            cout << " " << brd[3] << " | " << brd[4] << " | " << brd[5] << " ";
            cout << "-----------" <<;
            cout << " " << brd[6] << " | " << brd[7] << " | " << brd[8] << " ";while (!ovr) {
            cout << "\n=============================="
                 << "\nСейчас ходит: " << cur
                 << "\n " << brd[0] << " | " << brd[1] << " | " << brd[2]
                 << "\n-----------"
                 << "\n " << brd[3] << " | " << brd[4] << " | " << brd[5]
                 << "\n-----------"
                 << "\n " << brd[6] << " | " << brd[7] << " | " << brd[8];

            cout << "\n\nИгрок " << cur << ", ваш ход (1-9): ";
            cin >> mvv;

            if (mvv < 1  mvv > 9) {
                cout << "Только числа от 1 до 9!\n";
                continue;
            }
            if (brd[mvv - 1] != ' ') {
                cout << "Здесь уже занято! Выберите другое место.\n";
                continue;
            }

            brd[mvv - 1] = cur;

            char win = 0;
            int lines[8][3] = {
                {0,1,2}, {3,4,5}, {6,7,8}, 
                {0,3,6}, {1,4,7}, {2,5,8}, 
                {0,4,8}, {2,4,6}           
            };
            for (int i = 0; i < 8; ++i)
                if (brd[lines[i][0]] != ' ' &&
                    brd[lines[i][0]] == brd[lines[i][1]] &&
                    brd[lines[i][1]] == brd[lines[i][2]])
                    win = brd[lines[i][0]];

           bool full = true;
            for (int i = 0; i < 9; ++i)
                if (brd[i] == ' ') { full = false; break; }

            if (win) {
                cout << "\n=============================="
                     << "\nИгра окончена!"
                     << "\n " << brd[0] << " | " << brd[1] << " | " << brd[2]
                     << "\n-----------"
                     << "\n " << brd[3] << " | " << brd[4] << " | " << brd[5]
                     << "\n-----------"
                     << "\n " << brd[6] << " | " << brd[7] << " | " << brd[8]
                     << "\n\nПобедил игрок " << win << "!\n";
                ovr = true;
            }
            else if (full) {
                cout << "\n=============================="
                     << "\nИгра окончена!"
                     << "\n " << brd[0] << " | " << brd[1] << " | " << brd[2]
                     << "\n-----------"
                     << "\n " << brd[3] << " | " << brd[4] << " | " << brd[5]
                     << "\n-----------"
                     << "\n " << brd[6] << " | " << brd[7] << " | " << brd[8]
                     << "\n\nНичья! Все клетки заполнены.\n";
                ovr = true;
            }
            else
                cur = (cur == 'X') ? 'O' : 'X';  
        }

        cout << "\n=============================="
             << "\nСыграем еще? (да/нет): ";
        cin >> rep;

    } while (rep == "да"  rep == "yes"  rep == "д"  rep == "y");

    cout << "\nСпасибо за игру! До встречи!\n";
    return 0;
}
    
#include <cstdlib>  // для rand() и srand()
#include <ctime>    // для time()
int getCellScore(int position) {
    // position от 0 до 8, как в массиве поля
    // карта важности: центр (4) → 5, углы → 3, остальное → 1
    if (position == 4) return 5;           // центр
    if (position % 2 == 0) return 3;       // чётные — это углы
    return 1;                               // бока (1,3,5,7) — невыгодные ходы
}


// Возвращает номер клетки (0-8) для лучшего хода
int getComputerMove(char brd[9], char computerSymbol, char playerSymbol) {
    // Сначала ищем свой выигрышный ход
    for (int i = 0; i < 9; i++) {
        if (brd[i] == ' ') {
            brd[i] = computerSymbol;
            if (checkWinner(brd) == computerSymbol) {
                brd[i] = ' ';  // откатываем
                return i;      // нашли победный ход
            }
            brd[i] = ' ';
        }
    }
    
    // Если нет своего выигрыша — баним выигрыш игрока
    for (int i = 0; i < 9; i++) {
        if (brd[i] == ' ') {
            brd[i] = playerSymbol;
            if (checkWinner(brd) == playerSymbol) {
                brd[i] = ' ';  // откатываем
                return i;      // блокируем игрока
            }
            brd[i] = ' ';
        }
    }
    int bestMove = -1;
    int bestScore = -1;
    for (int i = 0; i < 9; i++) {
        if (brd[i] == ' ') {
            int score = getCellScore(i);
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;  // может быть -1, если нет свободных клеток
}

// Выбор сложности
int getDifficulty() {
    int diff;
    cout << "\nВыберите сложность:\n";
    cout << "1 - Легко ( ходит случайно)\n";
    cout << "2 - Сложно ( думает)\n";
    cout << "Ваш выбор: ";
    cin >> diff;
    
    while (diff != 1 && diff != 2) {
        cout << "Ошибка! Введите 1 или 2: ";
        cin >> diff;
    }
    return diff;
}

void computerMove(char brd[9], char computerSymbol, char playerSymbol, int difficulty) {
    int move;
    
    if (difficulty == 1) {
        // Лёгкий режим: случайный ход среди свободных клеток
        do {
            move = rand() % 9;  // случайное число 0-8
        } while (brd[move] != ' ');
    } 
    else {
        // Сложный: типо умный ход
        move = getComputerMove(brd, computerSymbol, playerSymbol);
        if (move == -1) return;  // нет свободных клеток (защита)
    }
    
    brd[move] = computerSymbol;
    cout << "Компьютер сходил в клетку " << move + 1 << endl;
}

int main() {
    srand(time(0));  // генератор случайных чисел (нужно для rand())
    
    string rep;
    char brd[9];
    int statsPlayer = 0, statsComputer = 0, statsDraw = 0;  // статистика побед
    
    do {
        showRules();
        
        // Выбор режима игры
        int gameMode;
        cout << "\nВыберите режим:\n";
        cout << "1 - Игрок против игрока\n";
        cout << "2 - Игрок против компьютера\n";
        cout << "Ваш выбор: ";
        cin >> gameMode;
        
        int difficulty = 1;  // сложность 
        char computerSymbol = 'O';  // компьютер будет играть за O
        
        if (gameMode == 2) {
            difficulty = getDifficulty();
            cout << "Вы играете за X. Компьютер за O.\n";
        }
        
        resetBoard(brd);
        
        char cur = 'X';      // X ходит первым всегда
        bool ovr = false;
        int move;
        
        while (!ovr) {
            cout << "\n==============================\n";
            if (gameMode == 2 && cur == computerSymbol) {
                cout << "Ходит компьютер (" << computerSymbol << ")" << endl;
            } else {
                cout << "Сейчас ходит: " << cur << endl;
            }
            drawBoard(brd);
            
            // --- ХОД ИГРОКА ИЛИ КОМПЬЮТЕРА ---
            if (gameMode == 2 && cur == computerSymbol) {
                // Ход компьютера
                computerMove(brd, computerSymbol, 'X', difficulty);
            } 
            else {
                // Ход человека
                cout << "\nИгрок " << cur << ", ваш ход (1-9): ";
                cin >> move;
                
                if (move < 1 || move > 9) {
                    cout << "Ошибка! Только числа от 1 до 9!\n";
                    continue;
                }
                
                if (brd[move - 1] != ' ') {
                    cout << "Ошибка! Здесь уже занято! Выберите другое место.\n";
                    continue;
                }
                brd[move - 1] = cur;
            }
            
            
            char winner = checkWinner(brd);
            bool full = isFull(brd);
            
            if (winner) {
                cout << "\n==============================\nИгра окончена!\n";
                drawBoard(brd);
                cout << "\nПоздравляем! Победил ";
                
                if (winner == 'X') {
                    cout << "игрок X!\n";
                    if (gameMode == 2) statsPlayer++;  // человек победил 
                    else statsPlayer++;
                } 
                else if (winner == 'O') {
                    cout << "игрок O!\n";
                    if (gameMode == 2) statsComputer++;  // компьютер победил
                    else statsPlayer++;  // в режиме считаем победу второго игрока как победу противника
                }
                
                ovr = true;
            }
            else if (full) {
                cout << "\n==============================\nИгра окончена!\n";
                drawBoard(brd);
                cout << "\nНичья! Все клетки заполнены.\n";
                statsDraw++;
                ovr = true;
            }
            else {
                // Меняем игрока
                cur = (cur == 'X') ? 'O' : 'X';
            }
        }
        if (gameMode == 2) {
            cout << "\n======= СТАТИСТИКА =======\n";
            cout << "Побед человека (X): " << statsPlayer << endl;
            cout << "Побед компьютера (O): " << statsComputer << endl;
            cout << "Ничьих: " << statsDraw << endl;
            cout << "==========================\n";
        }
        
        cout << "\nСыграем еще? (да/нет): ";
        cin >> rep;
        
    } while (isYesAnswer(rep));
    
    cout << "\nСпасибо за игру! До встречи!\n";
    return 0;
}
