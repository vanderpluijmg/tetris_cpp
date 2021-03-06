// MIT License
//
// Copyright (c) 2022 Andrew SASSOYE, Constantin GUNDUZ, Gregory VAN DER PLUIJM,
// Thomas LEUTSCHER
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "game_window.hpp"

#include <QFontDatabase>
#include <QKeyEvent>

namespace tetris::client::window {

GameWindow::GameWindow(QWidget* parent)
    : QGraphicsView(parent), gameScene_{nullptr} {
  setFrameStyle(QFrame::NoFrame);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scale(0.2, 0.2);
  int id = QFontDatabase::addApplicationFont(":/font/nes.otf");
}

void GameWindow::start(std::string playerName, unsigned long highScore,
                       std::string opponentName,
                       unsigned long opponentHighScore, unsigned long seed,
                       Socket_Client* socket) {
  player_ = new model::game::Player{playerName, highScore};
  player2_ = new model::game::Player{opponentName, opponentHighScore};

  gameScene_ =
      new scene::MultiplayerScene{player_, player2_, seed, socket, this};
  setScene(gameScene_);
}

GameWindow::~GameWindow() {
  if (player_ != nullptr) {
    delete player_;
    player_ = nullptr;
  }
}

}  // namespace tetris::client::window
