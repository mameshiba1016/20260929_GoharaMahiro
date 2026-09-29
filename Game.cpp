#include "Game.h"
#include <iostream>
#include <limits>
#include "GameConfig.h"

Game::Game() : player_("Player"),cpu_("CPU"),gameOver_(false)
{
}

void Game::Run()
{
    deck_.Reset();

    player_.ClearHand();
    cpu_.ClearHand();

    gameOver_ = false;

    std::cout<< "       CARD GAME START        " << std::endl;

    DealInitialCards();

    ShowGameState();

    PlayerTurn();

    if (gameOver_)
    {
        return;
    }

    CpuTurn();

    if (gameOver_)
    {
        return;
    }

    ShowResult();
}

void Game::DealInitialCards()
{
    for (int cardCount = 0;cardCount < GameConfig::INITIAL_HAND_SIZE;++cardCount)
    {
        DrawCard(&player_);
        DrawCard(&cpu_);
    }
}

void Game::PlayerTurn()
{
    std::cout<< std::endl<< "========== Player Turn =========="<< std::endl;

    while (!gameOver_)
    {
        std::cout << std::endl;

        player_.ShowHand();

        if (player_.IsTwentyOne())
        {
            std::cout<< "Playerの合計が"<< GameConfig::TARGET_SCORE<< "です。"<< std::endl;

            std::cout<< "CPUのターンへ移ります。"<< std::endl;

            return;
        }

        if (player_.IsBust())
        {
            std::cout<< "Playerはバーストしました。"<< std::endl;

            std::cout<< "Playerの負けです。"<< std::endl;

            gameOver_ = true;

            return;
        }

        const PlayerAction action = InputPlayerAction();

        switch (action)
        {
        case PlayerAction::Draw:
        {
            std::cout<< "Playerがカードを引きます。"<< std::endl;

            DrawCard(&player_);

            const Card* drawnCard =player_.GetCard(player_.GetCardCount()- GameConfig::MIN_CARD_VALUE);

            if (drawnCard != nullptr)
            {
                std::cout<< "引いたカード："<< drawnCard->GetValue()<< std::endl;
            }

            std::cout<< "現在の合計："<< player_.GetScore()<< std::endl;

            if (player_.IsBust())
            {
                std::cout<< "Playerはバーストしました。"<< std::endl;

                std::cout<< "Playerの負けです。"<< std::endl;

                gameOver_ = true;

                return;
            }

            if (player_.IsTwentyOne())
            {
                std::cout<< "Playerの合計が"<< GameConfig::TARGET_SCORE<< "になりました。"<< std::endl;

                return;
            }

            break;
        }

        case PlayerAction::Stand:
        {
            std::cout<< "Playerはカードを引きません。"<< std::endl;

            return;
        }
        }
    }
}

void Game::CpuTurn()
{
    std::cout<< std::endl<< "========== CPU Turn =========="<< std::endl;

    while (!gameOver_)
    {
        std::cout << std::endl;

        cpu_.ShowHand();

        if (cpu_.IsTwentyOne())
        {
            std::cout<< "CPUの合計が"<< GameConfig::TARGET_SCORE<< "です。"<< std::endl;

            return;
        }

        if (cpu_.IsBust())
        {
            std::cout<< "CPUはバーストしました。"<< std::endl;

            std::cout<< "Playerの勝ちです。"<< std::endl;

            gameOver_ = true;

            return;
        }

        const bool shouldDraw =cpuAI_.ShouldDraw(&cpu_,&player_);

        if (!shouldDraw)
        {
            std::cout<< "CPUはカードを引きません。"<< std::endl;

            return;
        }

        std::cout<< "CPUはカードを引きます。"<< std::endl;

        DrawCard(&cpu_);

        const Card* drawnCard =cpu_.GetCard(cpu_.GetCardCount()- GameConfig::MIN_CARD_VALUE);

        if (drawnCard != nullptr)
        {
            std::cout<< "CPUが引いたカード："<< drawnCard->GetValue()<< std::endl;
        }

        std::cout<< "CPUの合計："<< cpu_.GetScore()<< std::endl;

        if (cpu_.IsBust())
        {
            std::cout<< "CPUはバーストしました。"<< std::endl;

            std::cout<< "Playerの勝ちです。"<< std::endl;

            gameOver_ = true;

            return;
        }

        if (cpu_.IsTwentyOne())
        {
            std::cout<< "CPUの合計が"<< GameConfig::TARGET_SCORE<< "になりました。"<< std::endl;

            return;
        }
    }
}

void Game::DrawCard(Player* target)
{
    if (target == nullptr)
    {
        return;
    }

    if (deck_.IsEmpty())
    {
        std::cout<< "デッキにカードがありません。"<< std::endl;

        return;
    }

    const Card card = deck_.DrawCard();

    target->AddCard(card);
}

void Game::ShowGameState() const
{
    std::cout<< std::endl<< "========== Initial Cards =========="<< std::endl;

    player_.ShowHand();

    std::cout << std::endl;

    cpu_.ShowHand();

    std::cout << std::endl;

    std::cout<< "残りカード："<< deck_.GetRemainingCardCount()<< "枚"<< std::endl;
}

void Game::ShowResult() const
{
    const int playerScore = player_.GetScore();
    const int cpuScore = cpu_.GetScore();

    std::cout<< std::endl<< "RESULT" << std::endl;

    player_.ShowHand();

    std::cout << std::endl;

    cpu_.ShowHand();

    std::cout << std::endl;

    if (playerScore > cpuScore)
    {
        std::cout<< "Playerの勝ちです！"<< std::endl;

        return;
    }

    if (playerScore < cpuScore)
    {
        std::cout<< "CPUの勝ちです！"<< std::endl;

        return;
    }

    std::cout<< "引き分けです！"<< std::endl;
}

PlayerAction Game::InputPlayerAction() const
{
    while (true)
    {
        std::cout<< std::endl<< "カードを引きますか？"<< std::endl;

        std::cout<< GameConfig::INPUT_DRAW<< "：Yes"<< std::endl;

        std::cout<< GameConfig::INPUT_STAND<< "：No"<< std::endl;

        std::cout << "> ";

        int input = GameConfig::INPUT_STAND;

        std::cin >> input;

        if (std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

            std::cout<< "正しい値を入力してください。"<< std::endl;

            continue;
        }

        if (input == GameConfig::INPUT_DRAW)
        {
            return PlayerAction::Draw;
        }

        if (input == GameConfig::INPUT_STAND)
        {
            return PlayerAction::Stand;
        }

        std::cout<< GameConfig::INPUT_DRAW<< " または "<< GameConfig::INPUT_STAND<< " を入力してください。"<< std::endl;
    }
}