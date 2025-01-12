#pragma once

#include <string>
#include <cstdint>

/**
 * ���� ������ ����� Ÿ�̸��Դϴ�.
 * �� Ÿ�̸Ӵ� GLFW�� ������� �����Ǿ����ϴ�.
 */
class GameTimer
{
public:
	/**
	 * Ÿ�̸��� ������ �� ���� �Ҹ����Դϴ�.
	 * �̶�, �� Ÿ�̸Ӹ� ����ϱ� ���ؼ��� ���� ó���� Reset �޼��带 ȣ���ؾ� �մϴ�.
	 */
	GameTimer() = default;
	GameTimer(GameTimer&& instance) noexcept;
	GameTimer(const GameTimer& instance) noexcept;
	virtual ~GameTimer() = default;

	GameTimer& operator=(GameTimer&& instance) noexcept;
	GameTimer& operator=(const GameTimer& instance) noexcept;

	/** �ʴ��� ��Ÿ �ð� ���� ����ϴ�. */
	float GetDeltaSeconds() const;

	/** �ʱ�ȭ ������ �������� �ʴ��� ��ü �ð� ���� ����ϴ�. */
	float GetTotalSeconds() const;

	/** Ÿ�̸Ӹ� �ʱ�ȭ�մϴ�. */
	void Reset();

	/** Ÿ�̸Ӹ� �����մϴ�. */
	void Start();

	/** Ÿ�̸Ӹ� �����մϴ�. */
	void Stop();

	/** Ÿ�̸Ӹ� ������Ʈ�մϴ�. */
	void Tick();

private:
	/** Ÿ�̸��� ���� �����Դϴ�. */
	bool bIsStop_ = false;

	/** Ÿ�̸��� �ð� ��� �� ������ �Ǵ� �ð��Դϴ�. Reset�� ȣ���ϸ� �ʱ�ȭ�˴ϴ�. */
	float baseTime_ = 0LL;

	/** Ÿ�̸��� ���� �ð��Դϴ�. Stop�� ȣ���ϴ� ������ ���� �ʱ�ȭ�˴ϴ�. */
	float pausedTime_ = 0LL;

	/** Ÿ�̸��� ���� �ð��Դϴ�. Stop�� ȣ���ϴ� �������� ���� ���ŵ˴ϴ�. */
	float stopTime_ = 0LL;

	/** Tick�� ȣ���ϱ� ���� �ð� ���Դϴ�. */
	float prevTime_ = 0LL;

	/** Tick�� ȣ���� ������ �ð� ���Դϴ�. */
	float currTime_ = 0LL;
};