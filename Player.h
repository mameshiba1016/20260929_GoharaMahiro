#pragma once

#include <string>
#include <vector>
#include "Card.h"

class Player
{
private:
    std::string name_;
    std::vector<Card> hand_;

public:
    Player();
    explicit Player(const std::string& name);

    void AddCard(const Card& card);
    void ClearHand();

    int GetScore() const;
    int GetCardCount() const;

    const Card* GetCard(int index) const;

    const std::string& GetName() const;

    bool IsBust() const;
    bool IsTwentyOne() const;

    void ShowHand() const;
};