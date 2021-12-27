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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_TETRIMINO_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_TETRIMINO_HPP_

#include <array>
#include <optional>

#include "direction.hpp"
#include "mino.hpp"
#include "orientation.hpp"
#include "utils/coordinate.hpp"

using OptionalMino = std::optional<tetris::model::tetrimino::Mino>;

namespace tetris::model::tetrimino {
/**
 * @brief Class that represent a Tetrimino in general
 */
class Tetrimino {
 private:
  /**
   * @brief The actual Orientation of the Tetrimino
   */
  Orientation orientation_;

  /**
   * @brief The top-left Coordinate of the Tetrimino
   */
  utils::Coordinate coordinate_;

  /**
   * @brief The abstract representation of the Tetrimino in an 2D array of minos
   */
  std::array<std::array<OptionalMino, 4>, 4> minos_;

 public:
  /**
   * @brief Default constructor of a Tetrimino
   */
  inline Tetrimino();

  /**
   * @brief Getter of the Mino 2D array representation of the Tetrimino
   * @return 2D array of Mino's
   */
  [[nodiscard]] inline std::array<std::array<OptionalMino, 4>, 4> minos() const;

  /**
   * @brief Move a Tetrimino in a given direction
   * @param direction The direction of the move
   * TODO : Surrounding AREA
   */
  void move(Direction direction);

  /**
   * @brief Rotate a Tetrimino (if possible)
   * @param clockwise true if clockwise, false if anticlockwise
   * TODO : Surrounding AREA
   */
  virtual void rotate(bool clockwise) = 0;

  /**
   * @brief Gets the coordinates of the tetrimino.
   * @return Coordinates parameter of the tetrimino.
   */
  [[nodiscard]] utils::Coordinate getCoordinates() const;

  /**
   * Gets the X coordinate of the tetrimino.
   * @return X coordinate value.
   */
  [[nodiscard]] long X() const;
  /**
   * @brief Gets the Y coordinate of the tetrimino.
   * @return Y coordinate value.
   */
  [[nodiscard]] long Y() const;
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/

Tetrimino::Tetrimino() : orientation_{NORTH}, coordinate_{} {}

std::array<std::array<OptionalMino, 4>, 4> Tetrimino::minos() const {
  return minos_;
}
long Tetrimino::X() const { return coordinate_.x(); }

utils::Coordinate Tetrimino::getCoordinates() const { return coordinate_; }

long Tetrimino::Y() const { return coordinate_.y(); }
// namespace tetris::model::tetrimino

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_TETRIMINO_HPP_
}