#include "Game.h"

#include <raylib.h>

#include <print>

static void DrawCenteredText(std::string msg, int screenWidth, int y, int fontSize, Color color)
{
	int textSize = MeasureText(msg.c_str(), fontSize);
	int centerX = (screenWidth / 2) - (textSize / 2);

	DrawText(msg.c_str(), centerX, y, fontSize, color);
}

Game::Game(const GameSpecification& spec)
	:m_Spec(spec), m_LeftPaddle(spec, Paddle::Position::Left), m_RightPaddle(spec, Paddle::Position::Right), m_Ball(spec)
{
	InitWindow(spec.ScreenWidth, spec.ScreenHeight, spec.Title.c_str());
	SetTargetFPS(60);
}

Game::~Game()
{
	CloseWindow();
}

void Game::Run()
{
	while (!WindowShouldClose() && m_State != GameState::End)
	{
		/// //////////////UPDATE//////////////
		if (m_State == GameState::SinglePlayer || m_State == GameState::MultiPlayer)
		{
			m_LeftPaddle.Update(m_Ball, m_State);
			m_RightPaddle.Update(m_Ball, m_State);

			m_Ball.Update(m_LeftPaddle, m_RightPaddle, m_State);
		}
		if (m_State == GameState::Title)
		{
			if (IsKeyDown(KEY_ONE))
				m_State = GameState::SinglePlayer;
			if (IsKeyDown(KEY_TWO))
				m_State = GameState::MultiPlayer;
		}
		if (m_State == GameState::Win || m_State == GameState::Lose ||
			m_State == GameState::Player1Win || m_State == GameState::Player2Win)
		{
			if (IsKeyDown(KEY_SPACE))
			{
				m_State = GameState::Title;
				m_LeftPaddle.Reset();
				m_RightPaddle.Reset();
				m_Ball.Reset();
			}
			if (IsKeyDown(KEY_ENTER))
				m_State = GameState::End;
		}

		/// /////////////RENDER///////////////
		BeginDrawing();
		ClearBackground(BLACK);
		if (m_State != GameState::Title)
		{
			DrawText(std::format("{}", m_LeftPaddle.Score ).c_str(), m_Spec.ScreenWidth/ 2 - (17 + 10), 15, 32, WHITE);
			DrawText(std::format("{}", m_RightPaddle.Score).c_str(), m_Spec.ScreenWidth/ 2 + 10, 15, 32, WHITE);

			DrawLine(m_Spec.ScreenWidth / 2, 0, m_Spec.ScreenWidth / 2, m_Spec.ScreenHeight, WHITE);

			m_Ball.Draw();

			m_LeftPaddle.Draw();
			m_RightPaddle.Draw();
		}
		if (m_State == GameState::Title)
		{
			DrawTitleScreen();
		}
		if (m_State == GameState::Win)
		{
			DrawCenteredText("You Won!", m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3, 60, RED);
			DrawCenteredText(std::format("Score: {}", m_LeftPaddle.Score), m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3 + 100, 24, GREEN);
			DrawCenteredText("Press Space To Play Again...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 - 50, 32, SKYBLUE);
			DrawCenteredText("Press Enter To Exit...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 + 50, 32, SKYBLUE);
		}
		if (m_State == GameState::Lose)
		{
			DrawCenteredText("You Lost!", m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3, 60, RED);
			DrawCenteredText(std::format("Score: {}", m_RightPaddle.Score), m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3 + 100, 24, GREEN);
			DrawCenteredText("Press Space To Play Again...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 - 50, 32, SKYBLUE);
			DrawCenteredText("Press Enter To Exit...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 + 50, 32, SKYBLUE);
		}
		else if (m_State == GameState::Player1Win)
		{
			DrawCenteredText("Player 1 Won!", m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3, 60, RED);
			DrawCenteredText(std::format("Player 1 Score: {}", m_LeftPaddle.Score), m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3 + 70, 24, GREEN);
			DrawCenteredText(std::format("Player 2 Score: {}", m_RightPaddle.Score), m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3 + 100, 24, GREEN);
			DrawCenteredText("Press Space To Play Again...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 - 50, 32, SKYBLUE);
			DrawCenteredText("Press Enter To Exit...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 + 50, 32, SKYBLUE);
		}
		else if (m_State == GameState::Player2Win)
		{
			DrawCenteredText("Player 2 Won!", m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3, 60, RED);
			DrawCenteredText(std::format("Player 1 Score: {}", m_LeftPaddle.Score), m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3 + 70, 24, GREEN);
			DrawCenteredText(std::format("Player 2 Score: {}", m_RightPaddle.Score), m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3 + 100, 24, GREEN);
			DrawCenteredText("Press Space To Play Again...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 - 50, 32, SKYBLUE);
			DrawCenteredText("Press Enter To Exit...", m_Spec.ScreenWidth, m_Spec.ScreenHeight * 2 / 3 + 50, 32, SKYBLUE);
		}

		EndDrawing();
	}
}

void Game::DrawTitleScreen()
{
	DrawCenteredText("Pong", m_Spec.ScreenWidth, m_Spec.ScreenHeight / 3, 60, VIOLET);
	DrawCenteredText("Press 1 for SinglePlayer...", m_Spec.ScreenWidth, (m_Spec.ScreenHeight * 2 / 3) - 50, 32, PURPLE);
	DrawCenteredText("Press 2 for MultiPlayer...", m_Spec.ScreenWidth, (m_Spec.ScreenHeight * 2 / 3) + 50, 32, PURPLE);
}
