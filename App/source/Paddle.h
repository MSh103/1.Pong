#pragma once

#include <raylib.h>


struct GameSpecification;
class Ball;
enum class GameState : int;

class Paddle
{
public:
	enum class Position
	{
		Left, Right
	};

	Paddle(const GameSpecification& gameSpec, const Position& position);
	~Paddle() = default;

	const Rectangle& GetRectangle() { return { m_PaddlePosition.x, m_PaddlePosition.y, m_PaddleDimensions.x, m_PaddleDimensions.y }; }
	Vector2& GetVelocity() { return m_PaddleVelocity; }
	
	void Reset();

	void Update(Ball& ball, GameState& state);
	void Draw();

private:
	void UpdateAi(Ball& ball);
	void UpdateLocal();


public:
	int Score = 0;

private:
	Vector2 m_PaddleVelocity;
	Vector2 m_PaddleDimensions;
	Vector2 m_PaddlePosition;
	
	Vector2 m_DefaultPaddleVelocity;
	Vector2 m_DefaultPaddlePosition;

	const float m_PaddingY = 15;
	const float m_PaddingX = 10;

	const float m_Speed = 6.f;

	float m_ScreenWidth;
	float m_ScreenHeight;
	Position m_Position;
};