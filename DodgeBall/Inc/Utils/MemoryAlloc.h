#pragma once

/**
 * mimalloc 라이브러리 기반의 커스텀 메모리 할당을 위한 함수들입니다.
 * 이때, user 포인터는 사용하지 않습니다.
 */
void* MemoryAlloc(size_t size, void* user);
void* MemoryRealloc(void* block, size_t size, void* user);
void  MemoryFree(void* block, void* user);