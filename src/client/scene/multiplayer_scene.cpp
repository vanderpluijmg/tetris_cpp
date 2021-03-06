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
#include "client/scene/multiplayer_scene.hpp"

#include <QKeyEvent>
#include <utility>

namespace tetris::client::scene {

MultiplayerScene::MultiplayerScene(model::game::Player *player1,
                                   model::game::Player *player2,
                                   uint_fast64_t seed, Socket_Client *socket,
                                   QObject *parent)
    : QGraphicsScene(parent),
      player1_{new component::Game{}},
      player1Game_{new model::game::OngoingGame(player1, seed)},
      player2_{new component::Game{}},
      player2Game_{new model::game::OngoingGame(player2, seed, false)} {
  connect(
      player1Game_, &model::game::OngoingGame::matrixUpdate,
      [this](MatrixArray array) { player1_->updateMatrix(std::move(array)); });

  connect(socket, &Socket_Client::score,
          [this](unsigned score) { player2_->setScore(score); });

  connect(player1Game_, &model::game::OngoingGame::nextUpdate,
          [this](model::tetrimino::Mino mino) { player1_->updateNext(mino); });

  connect(player1Game_, &model::game::OngoingGame::holdUpdate,
          [this](model::tetrimino::Mino mino) { player1_->updateHold(mino); });
  connect(
      player2Game_, &model::game::OngoingGame::matrixUpdate,
      [this](MatrixArray array) { player2_->updateMatrix(std::move(array)); });

  connect(player2Game_, &model::game::OngoingGame::nextUpdate,
          [this](model::tetrimino::Mino mino) { player2_->updateNext(mino); });

  connect(player2Game_, &model::game::OngoingGame::holdUpdate,
          [this](model::tetrimino::Mino mino) { player2_->updateHold(mino); });

  connect(player1Game_, &model::game::OngoingGame::holdUpdate, socket,
          &Socket_Client::slot_Hold);
  connect(player1Game_, &model::game::OngoingGame::moveUpdate, socket,
          &Socket_Client::slot_Move);

  connect(player1Game_, &model::game::OngoingGame::rotateUpdate, socket,
          &Socket_Client::slot_Rotate);

  connect(player1Game_, &model::game::OngoingGame::lockUpdate, socket,
          &Socket_Client::slot_Lock);
  connect(player1Game_, &model::game::OngoingGame::hardDropUpdate, socket,
          &Socket_Client::slot_HardDrop);
  connect(player1Game_, &model::game::OngoingGame::scoreUpdate, socket,
          &Socket_Client::slot_Score);

  connect(player1Game_, &model::game::OngoingGame::matrixUpdate,
          [this](MatrixArray array) {
            emit player1_->updateMatrix(std::move(array));
          });

  connect(player1Game_, &model::game::OngoingGame::scoreUpdate,
          [this](unsigned int score) { player1_->setScore(score); });

  connect(player2Game_, &model::game::OngoingGame::matrixUpdate,
          [this](MatrixArray array) {
            emit player2_->updateMatrix(std::move(array));
          });

  player1_->setHighScore(player1->highScore());
  player1Game_->start();
  player2Game_->start();

  setBackgroundBrush(QColor{0, 0, 0});

  player2_->setPos(player1_->x() + player1_->boundingRect().width(),
                   player1_->y());

  connect(socket, &Socket_Client::move,
          [this](model::tetrimino::Direction dir) { player2Game_->move(dir); });

  connect(socket, &Socket_Client::rotate,
          [this](bool clockwise) { player2Game_->rotate(clockwise); });

  connect(socket, &Socket_Client::hold,
          [this]() { player2Game_->holdFalling(); });
  connect(socket, &Socket_Client::lock, [this]() { player2Game_->lock(); });
  connect(socket, &Socket_Client::harddrop,
          [this]() { player2Game_->hardDrop(); });

  addItem(player1_);
  addItem(player2_);
}

MultiplayerScene::~MultiplayerScene() {
  if (player1_ != nullptr) {
    delete player1_;
    player1_ = nullptr;
  }

  if (player1Game_ != nullptr) {
    player1Game_->stop();
    delete player1Game_;
    player1Game_ = nullptr;
  }

  if (player2_ != nullptr) {
    delete player2_;
    player2_ = nullptr;
  }
}

void MultiplayerScene::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      player1Game_->move(model::tetrimino::LEFT);
      break;
    case Qt::Key_Right:
      player1Game_->move(model::tetrimino::RIGHT);
      break;
    case Qt::Key_Down:
      player1Game_->softDrop();
      break;
    case Qt::Key_Space:
      player1Game_->hardDrop();
      break;
    case Qt::Key_Up:
      player1Game_->rotate(true);
      break;
    case Qt::Key_Control:
      player1Game_->rotate(false);
      break;
    case Qt::Key_Shift:
      player1Game_->holdFalling();
      break;
  }
}

}  // namespace tetris::client::scene
