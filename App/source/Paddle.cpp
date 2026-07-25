#include "Game.h"
#include "Paddle.h"

#include <raymath.h>


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

void Paddle::Update()
{
	if (m_Position != Position::Left)
		return;

	if (m_PaddlePosition.y > m_PaddingY && IsKeyDown(KEY_W))
		m_PaddleVelocity.y = -m_Speed;
	else if ((m_PaddlePosition.y + m_PaddleDimensions.y) < (m_ScreenHeight - m_PaddingY) && IsKeyDown(KEY_S))
		m_PaddleVelocity.y = m_Speed;
	else
		m_PaddleVelocity.y = 0;

	m_PaddlePosition = Vector2Add(m_PaddlePosition, m_PaddleVelocity);
}

void Paddle::Draw()
{
	Rectangle rect = { m_PaddlePosition.x, m_PaddlePosition.y, m_PaddleDimensions.x, m_PaddleDimensions.y };
	DrawRectangleRounded(rect, 2, 4, WHITE);
}
