#pragma once

#include <string>

enum game_mode {
    INTERACTIVE,
    ONEMOVE,
    NOTSET,
};

class Game
{
public:
    // constructor
    Game();
   
    void init(int argc, char ** argv, bool debug = false);
    void start();
    
private:
    const int ASCII_0 = 48;
    const int ASCII_9 = 57;
    const char * _comOutputFile = "computer.txt";
    const char * _humOutputFile = "human.txt";

    int * _gameBoard[6];
    int _gameData[42];
    int _currentTurn;
    int _pieceCount;
    int _player1Score;
    int _player2Score;
    int _depth;

    char * _infilename = NULL;
    char * _outfilename = NULL;



    game_mode _gamemode;
    bool _comNext;

    void setGameMode(char * mode);
    void setInputfile(char * infile);
    void setOutputfile(char * outfile);
    void setNextPlayer(char * next);
    void setDepthLimit(char * depth);

    void printGameBoard();
    void printGameBoardToFile(const char * outfilename);
    void printPlayerScore();
    bool playPiece(int column);
    void aiPlay();
    void humanPlay();
    void countScore();
    void startOneMove();
    void startInteractive();
    void readInputFile();
};
