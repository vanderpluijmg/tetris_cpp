// MIT License
//
// Copyright (c) 2021 Andrew SASSOYE, Constantin GUNDUZ, Gregory VAN DER PLUIJM,
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

#include "model/game/state/notstartedstate.hpp"

#include <stdexcept>

#include "model/game/state/exceptions/notstartedexception.hpp"
#include "model/game/state/fallingstate.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::game::states {

#define gameNotStarted(arg)                                       \
  throw exceptions::notStartedException(arg, __FILE__, __LINE__); \
  ;

void NotStartedState::start() {
  game_->falling(tetrimino::createTetrimino(game_->pickMino()));
  game_->next(game_->pickMino());
  game_->state(std::make_unique<FallingState>(game_));
}

void NotStartedState::stop() {
  gameNotStarted("You cannot stop an un started game");
}

void NotStartedState::move(tetrimino::Direction direction) {
  gameNotStarted("You cannot move in an un started game");
}

void NotStartedState::holdFalling() {
  gameNotStarted("You cannot hold in an un started game");
}

void NotStartedState::softDrop() {
  gameNotStarted("You cannot drop an un started game");
}

void NotStartedState::hardDrop() {
  gameNotStarted("You cannot drop an un started game");
}

void NotStartedState::rotate(bool clockwise) {
  gameNotStarted("You cannot rotate an un started game");
}

void NotStartedState::lock() {
  gameNotStarted("You cannot lock an un started game");
}

}  // namespace tetris::model::game::states