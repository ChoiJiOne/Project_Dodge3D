#pragma once

#include "Box3D.h"
#include "GameObject.h"


/**
 * @brief ���� �� ������Ʈ�Դϴ�.
 */
class WestWall : public GameObject
{
public:
	/**
	 * @brief ���� �� ������Ʈ�� �⺻ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	WestWall() = default;


	/**
	 * @brief ���� �� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 */
	virtual ~WestWall();


	/**
	 * @brief ���� �� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(WestWall);


	/**
	 * @brief ���� �� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ���� �� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief ���� �� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���� �� ������Ʈ�� ��� ������ ����ϴ�.
	 *
	 * @return ���� �� ������Ʈ�� ��� ������ ��ȯ�մϴ�.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return &boundingVolume_; }


private:
	/**
	 * @brief ���� �� ������Ʈ�� ��� �����Դϴ�.
	 */
	Box3D boundingVolume_;
};