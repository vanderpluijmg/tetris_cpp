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
#include "model/tetrimino/type/stetrimino.hpp"

#include "catch2/catch.hpp"

using namespace tetris::model::tetrimino;

TEST_CASE("class STetrimino") {
  using line = std::array<OptionalMino, 4>;

  std::array<line, 4> northShape = {
      line{std::nullopt, S_MINO, S_MINO, std::nullopt},
      line{S_MINO, S_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}};

  std::array<line, 4> eastShape = {
      line{std::nullopt, S_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, S_MINO, S_MINO, std::nullopt},
      line{std::nullopt, std::nullopt, S_MINO, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}};

  std::array<line, 4> southShape = {
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt},
      line{std::nullopt, S_MINO, S_MINO, std::nullopt},
      line{S_MINO, S_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}};

  std::array<line, 4> westShape = {
      line{S_MINO, std::nullopt, std::nullopt, std::nullopt},
      line{S_MINO, S_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, S_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}};

  SECTION("Constructor") {
    auto tetrimino = STetrimino();
    REQUIRE(tetrimino.X() == 3);
    REQUIRE(tetrimino.Y() == 0);

    for (size_t line = 0; line < tetrimino.minos().size(); ++line) {
      for (size_t column = 0;
           column < tetrimino.minos().at(tetrimino.orientation())[line].size();
           ++column) {
        REQUIRE(tetrimino.minos().at(tetrimino.orientation())[line][column] ==
                northShape[line][column]);
      }
    }
  }
  SECTION("rotate") {
    SECTION("check eastShape") {
      auto tetrimino = STetrimino();
      tetrimino.rotate(true);

      for (size_t line = 0; line < tetrimino.minos().size(); ++line) {
        for (size_t column = 0;
             column <
             tetrimino.minos().at(tetrimino.orientation())[line].size();
             ++column) {
          REQUIRE(tetrimino.minos().at(tetrimino.orientation())[line][column] ==
                  eastShape[line][column]);
        }
      }
    }
    SECTION("check southShape") {
      auto tetrimino = STetrimino();
      tetrimino.rotate(true);
      tetrimino.rotate(true);

      for (size_t line = 0; line < tetrimino.minos().size(); ++line) {
        for (size_t column = 0;
             column <
             tetrimino.minos().at(tetrimino.orientation())[line].size();
             ++column) {
          REQUIRE(tetrimino.minos().at(tetrimino.orientation())[line][column] ==
                  southShape[line][column]);
        }
      }
    }
    SECTION("check westShape") {
      auto tetrimino = STetrimino();
      tetrimino.rotate(false);
      for (size_t line = 0; line < tetrimino.minos().size(); ++line) {
        for (size_t column = 0;
             column <
             tetrimino.minos().at(tetrimino.orientation())[line].size();
             ++column) {
          REQUIRE(tetrimino.minos().at(tetrimino.orientation())[line][column] ==
                  westShape[line][column]);
        }
      }
    }
  }
  SECTION("move") {
    SECTION("Left") {
      auto tetrimino = STetrimino();
      tetrimino.move(LEFT);
      REQUIRE(tetrimino.X() == 2);
      REQUIRE(tetrimino.Y() == 0);
    }
    SECTION("Right") {
      auto tetrimino = STetrimino();
      tetrimino.move(RIGHT);
      REQUIRE(tetrimino.X() == 4);
      REQUIRE(tetrimino.Y() == 0);
    }
    SECTION("Down") {
      auto tetrimino = STetrimino();
      tetrimino.move(DOWN);
      REQUIRE(tetrimino.X() == 3);
      REQUIRE(tetrimino.Y() == 1);
    }
  }
}