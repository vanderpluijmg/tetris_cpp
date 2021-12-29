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
#include "catch2/catch.hpp"
#include "model/tetrimino/tetrimino.hpp"

using namespace tetris::model::tetrimino;

TEST_CASE("class Orientation") {
  SECTION("rotate start NORTH") {
    REQUIRE(rotate(NORTH, true) == EAST);
    REQUIRE(rotate(NORTH, false) == WEST);
  }
  SECTION("rotate start EAST") {
    REQUIRE(rotate(EAST, true) == SOUTH);
    REQUIRE(rotate(EAST, false) == NORTH);
  }
  SECTION("rotate start SOUTH") {
    REQUIRE(rotate(SOUTH, true) == WEST);
    REQUIRE(rotate(SOUTH, false) == EAST);
  }
  SECTION("rotate start WEST") {
    REQUIRE(rotate(WEST, true) == NORTH);
    REQUIRE(rotate(WEST, false) == SOUTH);
  }
}