#pragma once

class Player;

class CpuAI
{
public:
    CpuAI();

    bool ShouldDraw(const Player* cpu,const Player* player) const;
};