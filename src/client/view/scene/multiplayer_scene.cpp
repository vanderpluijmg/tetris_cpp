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

#include "client/view/scene/multiplayer_scene.hpp"

#include <QKeyEvent>
#include <utility>

namespace tetris::view::scene {

MultiplayerScene::MultiplayerScene(model::game::Player *player1,
                                   QObject *parent)
    : QGraphicsScene(0, 0, 850, 1590, parent),
      player1_{new component::Game{}},
      player1Game_{new model::game::OngoingGame(player1, 42)} {
  addItem(player1_);

  connect(
      this, &scene::MultiplayerScene::matrixChanged, this,
      [this](MatrixArray array) { player1_->updateMatrix(std::move(array)); });
}

MultiplayerScene::~MultiplayerScene() {
  if (player1_ != nullptr) {
    delete player1_;
    player1_ = nullptr;
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
  }
}

}  // namespace tetris::view::scene