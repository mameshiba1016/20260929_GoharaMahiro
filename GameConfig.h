#pragma once

namespace GameConfig
{
    // Card
    constexpr int MIN_CARD_VALUE = 1;
    constexpr int MAX_CARD_VALUE = 11;
    constexpr int COPIES_PER_CARD = 4;
    // Hand
    constexpr int INITIAL_HAND_SIZE = 2;
    // Score
    constexpr int TARGET_SCORE = 21;
    constexpr int BUST_SCORE = TARGET_SCORE + 1;
    // CPU AI
    constexpr int CPU_FORCE_DRAW_MAX_SCORE = 15;
    // Input
    constexpr int INPUT_DRAW = 0;
    constexpr int INPUT_STAND = 1;
}