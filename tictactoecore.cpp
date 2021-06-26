#include "tictactoecore.h"
#include <QDebug>
#include "unistd.h"

TicTacToeCore::TicTacToeCore()
{

}

void TicTacToeCore::computerPlay() // Кто ходит первый
{
    switch (m_gameDifficulty)
    {
    case 0:
        computerPlayRandom();
        break;
    case 1:
        computerPlaySmart();
        break;
    }
}


gameState TicTacToeCore::gameStatus() const
{
    for (int i = 0; i < 3; ++i)
    {
        if ((table[i][0] != ' ') && (table[i][0] == table[i][1]) && (table[i][1] == table[i][2])) // Проверка строки
        {
            return gameState::FINISHED;
        }
        if ((table[0][i] != ' ') && (table[0][i] == table[1][i]) && (table[1][i] == table[2][i]))// Проверка столбца
        {
            return gameState::FINISHED;
        }
    }


    if ((table[0][0] != ' ') && (table[0][0] == table[1][1]) && (table[1][1] == table[2][2])) // Проверка диагонали; Левый верхний
    {
        return gameState::FINISHED;
    }

    if ((table[0][2] !=  ' ' ) && (table[0][2] == table[1][1] ) && (table[1][1] == table[2][0])) // Проверка диагонали; Правый верхний
    {
        return gameState::FINISHED;
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (table[i][j] == ' ') // Есть свободные строки
            {
                return gameState::CONTINUES;
            }
        }
    }
    return gameState::TIE;
}

void TicTacToeCore::clearBoard() // Очистка таблицы
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            table[i][j] = ' ';
        }
    }
}

void TicTacToeCore::changeGameDifficulty(int gameDifficulty)
{
    m_gameDifficulty = gameDifficulty;
}

void TicTacToeCore::computerPlayRandom()
{
    usleep(0.5 * 1000000);// Задержка
    //while (1)
   // {
    /*Постановка правильного нолика при имеющихся двух ноликов*/
        for (int k = 0; k < 3; ++k)
        {
                if ((table[k][0] == 'O') && (table[k][0] == table[k][1]) &&(table[k][2] != 'X' )) // Проверка первой строки
                {
                    table[k][2] = 'O';
                    return;
                }
                if ((table[k][1] == 'O') && (table[k][1] == table[k][2]) &&(table[k][0] != 'X' )) // Проверка второй строки
                {
                    table[k][0] = 'O';
                    return;
                }
                if ((table[k][2] == 'O') && (table[k][0] == table[k][2]) &&(table[k][1] != 'X' )) // Проверка третьей строки
                {
                    table[k][1] = 'O';
                    return;
                }
                if ((table[0][k] == 'O') && (table[0][k] == table[1][k]) &&(table[2][k] != 'X' )) // Проверка первого столбца
                {
                    table[2][k] = 'O';
                    return;
                }
                if ((table[1][k] == 'O') && (table[1][k] == table[2][k]) &&(table[0][k] != 'X' )) // Проверка второго столбца
                {
                    table[0][k] = 'O';
                    return;
                }
                if ((table[2][k] == 'O') && (table[0][k] == table[2][k]) &&(table[1][k] != 'X' )) // Проверка третьего столбца
                {
                    table[1][k] = 'O';
                    return;
                }
        }
            /*Постановка нолика на диагоналях, при двух крестиках*/
                if ((table[0][0] == 'O') && (table[0][0] == table[1][1]) &&(table[2][2] != 'X' )) // Проверка левой диагонали
                {
                    table[2][2] = 'O';
                    return;
                }
                if ((table[1][1] == 'O') && (table[2][2] == table[1][1]) &&(table[0][0] != 'X' )) // Проверка левой диагонали
                {
                    table[0][0] = 'O';
                    return;
                }
                if ((table[2][2] == 'O') && (table[0][0] == table[2][2]) &&(table[1][1] != 'X' )) // Проверка левой диагонали
                {
                    table[1][1] = 'O';
                    return;
                }
                if ((table[0][2] == 'O') && (table[0][2] == table[1][1]) &&(table[2][0] != 'X' )) // Проверка правой диагонали
                {
                    table[2][0] = 'O';
                    return;
                }
                if ((table[1][1] == 'O') && (table[2][0] == table[1][1]) &&(table[0][2] != 'X' )) // Проверка правой диагонали
                {
                    table[0][2] = 'O';
                    return;
                }
                if ((table[2][0] == 'O') && (table[2][0] == table[0][2]) &&(table[1][1] != 'X' )) // Проверка правой диагонали
                {
                    table[1][1] = 'O';
                    return;
                }
    /*Постановка правильного нолика, при двух крестиках*/
        for (int k = 0; k < 3; ++k)
        {
                if ((table[k][0] == 'X') && (table[k][0] == table[k][1]) &&(table[k][2] != 'O' )) // Проверка первой строки
                {
                    table[k][2] = 'O';
                    return;
                }
                if ((table[k][1] == 'X') && (table[k][1] == table[k][2]) &&(table[k][0] != 'O' )) // Проверка второй строки
                {
                    table[k][0] = 'O';
                    return;
                }
                if ((table[k][2] == 'X') && (table[k][0] == table[k][2]) &&(table[k][1] != 'O' )) // Проверка третьей строки
                {
                    table[k][1] = 'O';
                    return;
                }
                if ((table[0][k] == 'X') && (table[0][k] == table[1][k]) &&(table[2][k] != 'O' )) // Проверка первого столбца
                {
                    table[2][k] = 'O';
                    return;
                }
                if ((table[1][k] == 'X') && (table[1][k] == table[2][k]) &&(table[0][k] != 'O' )) // Проверка второго столбца
                {
                    table[0][k] = 'O';
                    return;
                }
                if ((table[2][k] == 'X') && (table[0][k] == table[2][k]) &&(table[1][k] != 'O' )) // Проверка третьего столбца
                {
                    table[1][k] = 'O';
                    return;
                }
        }
            /*Постановка нолика на диагоналях, при двух крестиках*/
                if ((table[0][0] == 'X') && (table[0][0] == table[1][1]) &&(table[2][2] != 'O' )) // Проверка левой диагонали
                {
                    table[2][2] = 'O';
                    return;
                }
                if ((table[1][1] == 'X') && (table[2][2] == table[1][1]) &&(table[0][0] != 'O' )) // Проверка левой диагонали
                {
                    table[0][0] = 'O';
                    return;
                }
                if ((table[2][2] == 'X') && (table[0][0] == table[2][2]) &&(table[1][1] != 'O' )) // Проверка левой диагонали
                {
                    table[1][1] = 'O';
                    return;
                }
                if ((table[0][2] == 'X') && (table[0][2] == table[1][1]) &&(table[2][0] != 'O' )) // Проверка правой диагонали
                {
                    table[2][0] = 'O';
                    return;
                }
                if ((table[1][1] == 'X') && (table[2][0] == table[1][1]) &&(table[0][2] != 'O' )) // Проверка правой диагонали
                {
                    table[0][2] = 'O';
                    return;
                }
                if ((table[2][0] == 'X') && (table[2][0] == table[0][2]) &&(table[1][1] != 'O' )) // Проверка правой диагонали
                {
                    table[1][1] = 'O';
                    return;
                }
        /*Рандомная постановка нолика*/
    while(1)
    {
        int i = rand() % 3;
        int j = rand() % 3;
        if (table[i][j] == ' ')
        {
            table[i][j] = 'O';
            return;
        }
    }
}

void TicTacToeCore::computerPlaySmart()
{
    usleep(0.2 * 1000000);// Задержка
    computerPlayRandom();
}

\

