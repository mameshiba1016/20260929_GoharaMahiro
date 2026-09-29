#include "Deck.h"
#include <algorithm>
#include <stdexcept>
#include "GameConfig.h"

Deck::Deck() : randomEngine_(std::random_device{}())
{
    Reset();
}

void Deck::Reset()
{
    cards_.clear();

    for (int value = GameConfig::MIN_CARD_VALUE;value <= GameConfig::MAX_CARD_VALUE;++value)
    {
        for (int count = 0;count < GameConfig::COPIES_PER_CARD;++count)
        {
            cards_.emplace_back(value);
        }
    }

    Shuffle();
}

void Deck::Shuffle()
{
    std::shuffle(cards_.begin(),cards_.end(),randomEngine_);
}

Card Deck::DrawCard()
{
    if (IsEmpty())
    {
        throw std::runtime_error("デッキにカードがありません。");
    }

    const Card card = cards_.back();

    cards_.pop_back();

    return card;
}

int Deck::GetRemainingCardCount() const
{
    return static_cast<int>(cards_.size());
}

bool Deck::IsEmpty() const
{
    return cards_.empty();
}