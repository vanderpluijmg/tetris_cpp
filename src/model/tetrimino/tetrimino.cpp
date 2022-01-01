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

#include "model/tetrimino/tetrimino.hpp"

#include <stdexcept>
#include <vector>

namespace tetris::model::tetrimino {

void Tetrimino::move(Direction direction) {
  tetris::utils::Coordinate newCoordinate = coordinate_.value() + direction;
  coordinate_.emplace(newCoordinate);
}

void Tetrimino::move(Direction direction,
                     std::vector<std::vector<bool>> matrixMask) {
  tetris::utils::Coordinate newCoordinate = coordinate_.value() + direction;

  for (size_t line = 0; line < minos_.size(); ++line) {
    for (size_t col = 0; col < minos_[line].size(); ++col) {
      if (minos_[line][col].has_value()) {
        auto x = newCoordinate.x() + col;
        auto y = newCoordinate.y() + line;

        if (y >= 0 && y > matrixMask.size() && x >= 0 &&
            x < matrixMask[y].size()) {
          throw std::logic_error("This move places the Tetrimino out of bound");
        } else if (!matrixMask[y][x]) {
          throw std::logic_error(
              "This move is impossible because there is a Mino in the way");
        }
      }
    }
  }

  coordinate_.emplace(newCoordinate);
}
void Tetrimino::rotate(bool clockwise,
                       std::vector<std::vector<bool>> matrixMask) {
  Orientation tempOrientation = tetrimino::rotate(orientation_, clockwise);
  auto tempMinos = rotateCheck(clockwise);
  for (int i = 0; i < tempMinos.size(); i++) {
    for (int j = 0; j < tempMinos.at(i).size(); j++) {
      if ((!matrixMask[i][j]) && (tempMinos[i][j] != std::nullopt))
        throw std::logic_error("Rotation not possible");
    }
  }
  minos_ = tempMinos;
  orientation_ = tempOrientation;
}
}  // namespace tetris::model::tetrimino
