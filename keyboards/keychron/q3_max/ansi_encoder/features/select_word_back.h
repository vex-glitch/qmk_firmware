// Copyright 2021-2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file select_word_back.h
 * @brief Select word/line macro for backward selection.
 *
 * Overview
 * --------
 *
 * Implements a button that selects the current word in reverse direction,
 * assuming conventional text editor hotkeys. Pressing it again extends the
 * selection to the previous word. The effect is similar to word selection in
 * reverse (e.g., for editing tools).
 *
 * Pressing the button with shift selects the current line in reverse, and
 * pressing the button again extends the selection to the previous line.
 *
 * For full documentation, see the original implementation for forward selection.
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Handler function for select word in reverse. */
bool process_select_word_back(uint16_t keycode, keyrecord_t* record,
                              uint16_t sel_keycode);

/**
 * @fn select_word_back_task(void)
 * Matrix task function for Select Word Back.
 *
 * If using `SELECT_WORD_TIMEOUT`, call this function from your
 * `housekeeping_task_user()` function in keymap.c. (If no timeout is set,
 * calling `select_word_back_task()` has no effect.)
 */
#if SELECT_WORD_TIMEOUT > 0
void select_word_back_task(void);
#else
static inline void select_word_back_task(void) {}
#endif  // SELECT_WORD_TIMEOUT > 0

#ifdef __cplusplus
}
#endif
