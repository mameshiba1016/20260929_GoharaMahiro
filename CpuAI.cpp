#include "CpuAI.h"
#include "GameConfig.h"
#include "Player.h"

CpuAI::CpuAI()
{
}

bool CpuAI::ShouldDraw(const Player* cpu,const Player* player) const
{
    if (cpu == nullptr || player == nullptr)
    {
        return false;
    }

    const int cpuScore = cpu->GetScore();
    const int playerScore = player->GetScore();
    // 21ˆÈã‚Ìê‡‚Íˆø‚©‚È‚¢
    if (cpuScore >= GameConfig::TARGET_SCORE)
    {
        return false;
    }
    // 15ˆÈ‰º‚Ìê‡‚Í•K‚¸ˆø‚­
    if (cpuScore <= GameConfig::CPU_FORCE_DRAW_MAX_SCORE)
    {
        return true;
    }
    // 16ˆÈã‚Ìê‡A
    // Player‚æ‚è“_”‚ª’á‚¯‚ê‚Îˆø‚­
    return cpuScore < playerScore;
}