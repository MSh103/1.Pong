#include "Game.h"
#include "Paddle.h"
#include "Ball.h"

#include <raymath.h>
#include <algorithm>


Paddle::Paddle(const GameSpecification& gameSpec, const Position& position)
	: m_ScreenWidth(gameSpec.ScreenWidth), m_ScreenHeight(gameSpec.ScreenHeight), m_Position(position)
{
	m_PaddleVelocity = { 0.f, 0.f };
	m_PaddleDimensions = { 5.f, gameSpec.ScreenHeight / 6.f };

	if (position == Position::Left)
		m_PaddlePosition.x = m_PaddingX;
	else
		m_PaddlePosition.x = gameSpec.ScreenWidth - (m_PaddingX + m_PaddleDimensions.x);
	m_PaddlePosition.y = (gameSpec.ScreenHeight / 2.f) - (m_PaddleDimensions.y / 2.f);

	m_DefaultPaddlePosition = m_PaddlePosition;
	m_DefaultPaddleVelocity = m_PaddleVelocity;
}

void Paddle::Reset()
{
	m_PaddlePosition = m_DefaultPaddlePosition;
	m_PaddleVelocity = m_DefaultPaddleVelocity;
	Score = 0;
}

void Paddle::Update(Ball& ball)
{
	if (m_Position == Position::Left)
	{
		if (m_PaddlePosition.y > m_PaddingY && IsKeyDown(KEY_W))
			m_PaddleVelocity.y = -m_Speed;
		else if ((m_PaddlePosition.y + m_PaddleDimensions.y) < (m_ScreenHeight - m_PaddingY) && IsKeyDown(KEY_S))
			m_PaddleVelocity.y = m_Speed;
		else
			m_PaddleVelocity.y = 0;
	}
	else if(m_Position == Position::Right && ball.GetPosition().x >= m_ScreenWidth * 2.f/6.f)
	{
		float paddleCenter = m_PaddlePosition.y + m_PaddleDimensions.y * 0.5f;
		float ballY = ball.GetPosition().y + ball.GetRadius();
		float tolerance = m_PaddleDimensions.y * 0.1f;

		if (ballY <= paddleCenter - tolerance && m_PaddlePosition.y > m_PaddingY)
			m_PaddleVelocity.y = -m_Speed;
		else if (ballY >= paddleCenter + tolerance
			&& m_PaddlePosition.y < m_ScreenHeight - (m_PaddingY + m_PaddleDimensions.y))
			m_PaddleVelocity.y = m_Speed;
		else 
			m_PaddleVelocity.y = 0;
	}
	
	m_PaddlePosition = Vector2Add(m_PaddlePosition, m_PaddleVelocity);
	m_PaddlePosition.y = std::clamp(
		m_PaddlePosition.y,
		m_PaddingY,
		m_ScreenHeight - m_PaddingY - m_PaddleDimensions.y
	);
}

void Paddle::Draw()
{
	Rectangle rect = { m_PaddlePosition.x, m_PaddlePosition.y, m_PaddleDimensions.x, m_PaddleDimensions.y };
	DrawRectangleRounded(rect, 2, 4, WHITE);
}
