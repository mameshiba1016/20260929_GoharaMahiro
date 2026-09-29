#include "Player.h"
#include <iostream>
#include "GameConfig.h"

Player::Player() : name_("Player")
{
}

Player::Player(const std::string& name) : name_(name)
{
}

void Player::AddCard(const Card& card)
{
    hand_.push_back(card);
}

void Player::ClearHand()
{
    hand_.clear();
}

int Player::GetScore() const
{
    int totalScore = 0;

    for (const Card& card : hand_)
    {
        totalScore += card.GetValue();
    }

    return totalScore;
}

int Player::GetCardCount() const
{
    return static_cast<int>(hand_.size());
}

const Card* Player::GetCard(int index) const
{
    if (index < 0)
    {
        return nullptr;
    }

    if (index >= GetCardCount())
    {
        return nullptr;
    }

    return &hand_[index];
}

const std::string& Player::GetName() const
{
    return name_;
}

bool Player::IsBust() const
{
    return GetScore() >= GameConfig::BUST_SCORE;
}

bool Player::IsTwentyOne() const
{
    return GetScore() == GameConfig::TARGET_SCORE;
}

void Player::ShowHand() const
{
    std::cout << name_ << "：";

    for (int index = 0; index < GetCardCount(); ++index)
    {
        const Card* card = GetCard(index);

        if (card == nullptr)
        {
            continue;
        }

        std::cout << card->GetValue();

        if (index < GetCardCount() - 1)
        {
            std::cout << "、";
        }
    }

    std::cout << std::endl;

    std::cout<< "合計："<< GetScore()<< std::endl;
}