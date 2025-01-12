#pragma once

#include <string>
#include <cstdint>

/**
 * 게임 내에서 사용할 타이머입니다.
 * 이 타이머는 GLFW를 기반으로 구현되었습니다.
 */
class GameTimer
{
public:
	/**
	 * 타이머의 생성자 및 가상 소멸자입니다.
	 * 이때, 이 타이머를 사용하기 위해서는 가장 처음에 Reset 메서드를 호출해야 합니다.
	 */
	GameTimer() = default;
	GameTimer(GameTimer&& instance) noexcept;
	GameTimer(const GameTimer& instance) noexcept;
	virtual ~GameTimer() = default;

	GameTimer& operator=(GameTimer&& instance) noexcept;
	GameTimer& operator=(const GameTimer& instance) noexcept;

	/** 초단위 델타 시간 값을 얻습니다. */
	float GetDeltaSeconds() const;

	/** 초기화 시점을 기준으로 초단위 전체 시간 값을 얻습니다. */
	float GetTotalSeconds() const;

	/** 타이머를 초기화합니다. */
	void Reset();

	/** 타이머를 시작합니다. */
	void Start();

	/** 타이머를 중지합니다. */
	void Stop();

	/** 타이머를 업데이트합니다. */
	void Tick();

private:
	/** 타이머의 중지 여부입니다. */
	bool bIsStop_ = false;

	/** 타이머의 시간 계산 시 기준이 되는 시간입니다. Reset을 호출하면 초기화됩니다. */
	float baseTime_ = 0LL;

	/** 타이머의 중지 시간입니다. Stop을 호출하는 시점에 값이 초기화됩니다. */
	float pausedTime_ = 0LL;

	/** 타이머의 중지 시간입니다. Stop을 호출하는 시점부터 값이 갱신됩니다. */
	float stopTime_ = 0LL;

	/** Tick을 호출하기 전의 시간 값입니다. */
	float prevTime_ = 0LL;

	/** Tick을 호출한 직후의 시간 값입니다. */
	float currTime_ = 0LL;
};