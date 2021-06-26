#include "widget.h"
#include "ui_widget.h"
#include "tictactoecore.h"
#include <QDebug>
#include "unistd.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Крестики-нолики");
    pushButtons[0] = ui->button_1_1;
    pushButtons[1] = ui->button_1_2;
    pushButtons[2] = ui->button_1_3;
    pushButtons[3] = ui->button_2_1;
    pushButtons[4] = ui->button_2_2;
    pushButtons[5] = ui->button_2_3;
    pushButtons[6] = ui->button_3_1;
    pushButtons[7] = ui->button_3_2;
    pushButtons[8] = ui->button_3_3;

    updateGUI();
    for (int i = 0; i < 9; ++i)
    {
        connect(pushButtons[i], SIGNAL (clicked()), this, SLOT (userPlayed()));
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateGUI()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            QPushButton *button = pushButtons[i * 3 + j];
            button->setText(QString(TTT.table[i][j]));

            switch (TTT.table[i][j])
            {
            case 'X':
                button->setDisabled(true);
                button->setStyleSheet("background-color: rgb(0, 255, 255);color: red;");
                break;
            case 'O':
                button->setDisabled(true);
                button->setStyleSheet("background-color: rgb(0, 255, 255);color: green;");
                break;
            case ' ':
                button->setEnabled(true);
                button->setStyleSheet("background-color: rgb(0, 255, 255);");
                break;
            }

        }
    }
    ui->labelScorePlayer->setStyleSheet("color: red;");
    ui->labelScoreTie->setStyleSheet("color: gray;");
    ui->labelScoreComputer->setStyleSheet("color: green;");
    this->repaint();
}

void Widget::gameFinishedPlayerWon()
{
    m_score.player++;
    ui->labelScorePlayer->setNum(m_score.player);
    ui->labelScorePlayer->setStyleSheet("color: red;font-weight:bold;font-size:30px;");
    this->repaint();
    usleep(1 * 1000000);
    TTT.clearBoard();
    updateGUI();
}

void Widget::gameFinishedTieWon()
{
    m_score.tie++;
    ui->labelScoreTie->setNum(m_score.tie);
    ui->labelScoreTie->setStyleSheet("color: gray;font-weight:bold;font-size:30px;");
    this->repaint();
    usleep(1 * 1000000);
    TTT.clearBoard();
    updateGUI();
}

void Widget::gameFinishedComputerWon()
{
    m_score.computer++;
    ui->labelScoreComputer->setNum(m_score.computer);
    ui->labelScoreComputer->setStyleSheet("color: green;font-weight:bold;font-size:30px;");
    this->repaint();
    usleep(1 * 1000000);
    TTT.clearBoard();
    updateGUI();
}

void Widget::userPlayed()
{
    {
        int i = sender()->objectName().split("_")[1].toInt();
        int j = sender()->objectName().split("_")[2].toInt();
        TTT.table[i - 1][j - 1] = 'X';
    }
    updateGUI();

    switch (TTT.gameStatus())
    {
    case gameState::FINISHED:
        gameFinishedPlayerWon();
        break;
    case gameState::TIE:
        gameFinishedTieWon();
        break;
    case gameState::CONTINUES:
        break;
    }

    TTT.computerPlay();
    updateGUI();
    switch (TTT.gameStatus())
    {
    case gameState::FINISHED:
        gameFinishedComputerWon();
        break;
    case gameState::TIE:
        gameFinishedTieWon();
        break;
    case gameState::CONTINUES:
        break;
    }
    updateGUI();
}

