#pragma once

#include <raylib.h>

enum class GameState : int;
struct GameSpecification;
class Paddle;

class Ball
{
public:
	Ball(const GameSpecification& spec);
	~Ball() = default;

	const Vector2& GetFuturePosition() { return { m_BallPosition.x + m_BallVelocity.x, m_BallPosition.y + m_BallVelocity.y }; }
	const Vector2& GetPosition() { return m_BallPosition; }
	const float& GetRadius() { return m_Radius; }

	void Reset();

	void Update(Paddle& leftPaddle, Paddle& rightPaddle, GameState& state);
	void Draw();

private:
	const float m_Radius = 5.f;
	Vector2 m_BallVelocity;
	Vector2 m_BallPosition;
	Vector2 m_DefaultBallPosition;

	static constexpr float m_MaxBallSpeed = 24.0f;

	float m_ScreenWidth, m_ScreenHeight;
};