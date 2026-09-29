#pragma once

#include "CpuAI.h"
#include "Deck.h"
#include "Player.h"
#include "PlayerAction.h"

class Game
{
private:
    Deck deck_;

    Player player_;
    Player cpu_;

    CpuAI cpuAI_;

    bool gameOver_;

private:
    void DealInitialCards();

    void PlayerTurn();
    void CpuTurn();

    void DrawCard(Player* target);

    void ShowGameState() const;
    void ShowResult() const;

    PlayerAction InputPlayerAction() const;

public:
    Game();

    void Run();
};