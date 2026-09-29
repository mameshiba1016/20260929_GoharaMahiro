#pragma once

class Card
{
private:
    int value_;

public:
    Card();
    explicit Card(int value);

    int GetValue() const;
};