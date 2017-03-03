#include "game.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void Game::init(int argc, char ** argv, bool debug) {
    if (argc != 5) {
        cout << "Four command-line arguments are needed:\n";
        cout << "Usage: Program interactive [input_file] [computer-next/human-next] [depth]\n";
        cout << "or: Program one-move [input_file] [output_file] [depth]\n";
        exit(EXIT_SUCCESS);
    }

    setGameMode(argv[1]);
    setInputfile(argv[2]);
    if (_gamemode == INTERACTIVE) setNextPlayer(argv[3]);
    else setOutputfile(argv[3]);
    setDepthLimit(argv[4]);

    if (debug) {
        cout << "Para: " << endl;
        cout << "GameMode: ";
        if (_gamemode == INTERACTIVE) cout << "INTERACTIVE" << endl;
        else cout << "ONEMOVE" << endl;
        cout << "InputFile: " << _infilename << endl;
        if (_gamemode == INTERACTIVE) {
            cout << "NextPlayer: ";
            if (_comNext) cout << "COMPUTER" << endl;
            else cout << "PLAYER" << endl;
        }
        else cout << "OutputFile: " << _outfilename << endl;
        cout << "DepthLimit: " << _depthLim << endl;
    }
}

void Game::start() {
    readInputFile();
    cout << "MaxConnect-4 game" << endl << endl;
    cout << "game state before move:" << endl;
    printGameBoard();
    printPlayerScore();

    if (_gamemode == INTERACTIVE) startInteractive();
    else startOneMove();
}

void Game::startOneMove() {
    if (_pieceCount == 42) {
        cout << "The board is full" << endl;
        exit;
    }
    cout << "Computer is playing..." << endl;
    aiPlay();
    printGameBoard();
    printPlayerScore();
    printGameBoardToFile(_outfilename);
}

void Game::startInteractive() {
    while (_pieceCount != 42) {
        if (_comNext) {
            _comNext = false;
            cout << "Computer is playing..." << endl;
            aiPlay();
            printGameBoard();
            printPlayerScore();
            printGameBoardToFile(_comOutputFile);
        }
        else {
            _comNext = true;
            cout << "It is your turn." << " You are playing: \"" << ((_currentTurn == 1) ? "O\"" : "X\"") << endl;
            humanPlay();
            printGameBoardToFile(_humOutputFile);
        }
        _pieceCount = totalPiece(_gameData);
    }

    int winner = 0;
    if (_player1Score > _player2Score)
        winner = 1;
    else if (_player1Score < _player2Score)
        winner = 2;
    cout << "\n\n\nGAME OVER\n\n\n";
    if (winner)
        cout << "WINNER IS PLAYER " << winner << endl;
    else
        cout << "THIS IS A DRAW" << endl;
}

void Game::aiPlay() {
    aiPlayABPruning();
    if (_currentTurn == 1)
        _currentTurn = 2;
    else
        _currentTurn = 1;
}

void Game::humanPlay() {
    cout << "Which column do you want to play: ";
    int col;
    cin >> col;
    --col;
    while (!playPiece(col, _gameData, _currentTurn)) {
        cout << "That is not a valid move, retry: ";
        cin >> col;
        --col;
    }
    if (_currentTurn == 1)
        _currentTurn = 2;
    else
        _currentTurn = 1;
}
