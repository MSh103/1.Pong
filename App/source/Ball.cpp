#include "Ball.h"

#include "Game.h"
#include "Paddle.h"

#include <cmath>
#include <time.h>
#include <numbers>

#include <raymath.h>

Ball::Ball(const GameSpecification& spec)
	: m_ScreenWidth(spec.ScreenWidth), m_ScreenHeight(spec.ScreenHeight)
{
	SetRandomSeed((unsigned int)time(NULL));

	float side = GetRandomValue(0, 100);
	float dir = GetRandomValue(0, 30);
	dir = dir * std::numbers::pi / 180;
	float x, y;

	if (side <= 50)
	{
		x = cos(dir) * m_Radius;
		y = sin(dir) * m_Radius;
	}
	else 
	{
		x = -cos(dir) * m_Radius;
		y = -sin(dir) * m_Radius;
	}

	m_BallVelocity = { x,y };
	m_BallPosition = { spec.ScreenWidth / 2.f, spec.ScreenHeight / 2.f };

	m_DefaultBallPosition = m_BallPosition;
}

void Ball::Reset()
{
	m_BallPosition = m_DefaultBallPosition;
	
	float side = GetRandomValue(0, 100);
	float dir = GetRandomValue(0, 30);
	dir = dir * std::numbers::pi/180;
	float x, y;

	if (side <= 50)
	{
		x = cos(dir) * m_Radius;
		y = sin(dir) * m_Radius;
	}
	else
	{
		x = -cos(dir) * m_Radius;
		y = -sin(dir) * m_Radius;
	}

	m_BallVelocity = { x,y };
}

void Ball::Update(Paddle& leftPaddle, Paddle& rightPaddle, GameState& state, Sound beep, Sound hit)
{
	if (m_BallPosition.y <= 0 + m_Radius || m_BallPosition.y >= (m_ScreenHeight - m_Radius))
	{
		m_BallVelocity.y = -m_BallVelocity.y;
		PlaySound(hit);
	}

	if (state == GameState::SinglePlayer)
	{
		if (m_BallPosition.x <= 0 + m_Radius)
			state = GameState::Lose;
		else if (m_BallPosition.x >= (m_ScreenWidth - m_Radius))
			state = GameState::Win;
	}
	else if (state == GameState::MultiPlayer)
	{
		if (m_BallPosition.x <= 0 + m_Radius)
			state = GameState::Player2Win;
		else if (m_BallPosition.x >= (m_ScreenWidth - m_Radius))
			state = GameState::Player1Win;
	}

	constexpr float paddleInfluence = 0.4f;
	constexpr float paddleDeflection = 0.001f;

	if (CheckCollisionCircleRec({ GetFuturePosition().x, m_BallPosition.y }, m_Radius, leftPaddle.GetRectangle()))
	{
		m_BallVelocity.x = std::min(std::abs(m_BallVelocity.x) + paddleDeflection, m_MaxBallSpeed);
		m_BallVelocity.y += leftPaddle.GetVelocity().y * paddleInfluence;

		leftPaddle.Score++;
		PlaySound(beep);
		PlaySound(hit);
	}
	if (CheckCollisionCircleRec({ m_BallPosition.x, GetFuturePosition().y }, m_Radius, leftPaddle.GetRectangle()))
	{
		m_BallVelocity.y += leftPaddle.GetVelocity().y + paddleInfluence;
		
		leftPaddle.Score++;
		PlaySound(beep);
		PlaySound(hit);
	}


	if (CheckCollisionCircleRec({ GetFuturePosition().x, m_BallPosition.y }, m_Radius, rightPaddle.GetRectangle()))
	{
		m_BallVelocity.x = -(std::min(std::abs(m_BallVelocity.x) + paddleDeflection, m_MaxBallSpeed));
		m_BallVelocity.y += rightPaddle.GetVelocity().y * paddleInfluence;
		
		rightPaddle.Score++;
		PlaySound(beep);
		PlaySound(hit);
	}
	if (CheckCollisionCircleRec({ m_BallPosition.x, GetFuturePosition().y }, m_Radius, rightPaddle.GetRectangle()))
	{
		m_BallVelocity.y = -m_BallVelocity.y;
		
		rightPaddle.Score++;
		PlaySound(beep);
		PlaySound(hit);
	}


	m_BallPosition = Vector2Add(m_BallPosition, m_BallVelocity);
}

void Ball::Draw()
{
	DrawCircleV(m_BallPosition, m_Radius, WHITE);
}
