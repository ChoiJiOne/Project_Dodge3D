#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief ���������� ���� �� ���̰� ������ ������ �ε��� ���Դϴ�.
 */
class ShadowMap : public IResource
{
public:
	/**
	 * @brief �ε��� ���� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	ShadowMap() = default;


	/**
	 * @brief �ε��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~ShadowMap();


	/**
	 * @brief �ε��� ���� ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ShadowMap);


	/**
	 * @brief �ε��� ���� �����մϴ�.
	 * 
	 * @param shadowWidth �ε��� ���� ���� ũ���Դϴ�.
	 * @param shadowHeight �ε��� ���� ���� ũ���Դϴ�.
	 */
	void Initialize(uint32_t shadowWidth, uint32_t shadowHeight);


	/**
	 * @brief �ε��� �� ������ ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ε��� ���� ���� ���� �ʱ�ȭ�մϴ�.
	 */
	void Clear();


	/**
	 * @brief �ε��� ���� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief �ε��� ���� ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief �ε��� ���� �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t unit) const;


private:
	/**
	 * @brief �ε��� ���� ���ε� �Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsBind_ = false;


	/**
	 * @brief �ε��� ���� ������ ���� ID���Դϴ�.
	 */
	uint32_t shadowMapFBO_ = 0;


	/**
	 * @brief �ε��� ���� ���̰� ���� ID���Դϴ�.
	 */
	uint32_t shadowMapID_ = 0;
};