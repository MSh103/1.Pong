#pragma once

#include <string>

#include "Paddle.h"
#include "Ball.h"

struct GameSpecification
{
	int ScreenWidth, ScreenHeight;
	std::string Title;
};

enum class GameState : int
{
	Title,
	SinglePlayer,
	MultiPlayer,
	Player1Win,
	Player2Win,
	Lose,
	Win,
	End
};

class Game
{
public:
	Game(const GameSpecification& spec);
	~Game();

	void Run();

private:
	void DrawTitleScreen();

private:
	GameSpecification m_Spec;

	Paddle m_LeftPaddle;
	Paddle m_RightPaddle;
	Ball m_Ball;

	Sound m_BeepSE;
	Sound m_HitSE;

	GameState m_State = GameState::Title;
};