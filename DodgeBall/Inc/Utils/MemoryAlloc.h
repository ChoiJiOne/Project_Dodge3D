#pragma once

/**
 * mimalloc ���̺귯�� ����� Ŀ���� �޸� �Ҵ��� ���� �Լ����Դϴ�.
 * �̶�, user �����ʹ� ������� �ʽ��ϴ�.
 */
void* MemoryAlloc(size_t size, void* user);
void* MemoryRealloc(void* block, size_t size, void* user);
void  MemoryFree(void* block, void* user);