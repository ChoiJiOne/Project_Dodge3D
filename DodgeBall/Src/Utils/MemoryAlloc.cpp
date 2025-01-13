#include <mimalloc.h>
#include <mimalloc-new-delete.h>

#include "Utils/MemoryAlloc.h"

void* MemoryAlloc(size_t size, void* user)
{
	(void)(user); /** ������� �ʽ��ϴ�. */
	return mi_malloc(size);
}

void* MemoryRealloc(void* block, size_t size, void* user)
{
	(void)(user); /** ������� �ʽ��ϴ�. */
	return mi_realloc(block, size);
}

void MemoryFree(void* block, void* user)
{
	(void)(user); /** ������� �ʽ��ϴ�. */
	mi_free(block);
}