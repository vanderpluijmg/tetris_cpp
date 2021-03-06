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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_LOCKEDDOWNSTATE_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_LOCKEDDOWNSTATE_HPP_

#include <model/tetrimino/tetrimino_logic.hpp>

#include "fallingstate.hpp"
#include "model/game/gamestate.hpp"
#include "model/game/ongoinggame.hpp"

namespace tetris::model::game::states {
/**
 * @brief This class represents the state when the tetrimino is locked down
 */
class LockedDownState : public GameState {
 public:
  /**
   * @brief Default constructor
   *
   * @param game The game that have this state
   */
  inline explicit LockedDownState(OngoingGame *game);

  /**
   * @inherit
   */
  void start() override;

  /**
   * @inherit
   */
  void stop() override;

  /**
   * @inherit
   */
  void move(tetrimino::Direction direction) override;

  /**
   * @inherit
   */
  void holdFalling() override;

  /**
   * @inherit
   */
  void softDrop() override;

  /**
   * @inherit
   */
  void hardDrop() override;

  /**
   * @inherit
   */
  void rotate(bool clockwise) override;

};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/
LockedDownState::LockedDownState(OngoingGame *game)
    : GameState{StateType::LOCKED_DOWN, game} {
  game->refreshLockingTimer();
}
}  // namespace tetris::model::game::states

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_LOCKEDDOWNSTATE_HPP_
