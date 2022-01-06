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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_GAMEWINDOW_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_GAMEWINDOW_HPP_

#include <QGraphicsView>

#include "client/view/scene/game_scene.hpp"
namespace tetris::view::window {
/**
 * @brief This class Represents a GameWindow
 */
class GameWindow : public QGraphicsView {
  Q_OBJECT
 protected:
  /**
   * @brief Scene of a game
   */
  scene::GameScene *gameScene_;

 public:
  /**
   * @brief Default constructor of a GameWindow
   *
   * @param parent Parent QWidget (for memory)
   */
  explicit GameWindow(QWidget *parent = nullptr);

 signals:
  void matrixChanged(MatrixArray matrix);

  //  inline scene::Functions getFunction() { return gameScene_->getFunction();
  //  }
};
}  // namespace tetris::view::window

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_GAMEWINDOW_HPP_