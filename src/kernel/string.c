#include <string.h>

static uint8_t temp_buffer[SIZE_MAX];

int8_t memcmp(const void* c1, const void* c2, size_t sz) {
  const uint8_t* a = c1;
  const uint8_t* b = c2;
  for (size_t i = 0; i < sz; i++) {
    if ((uint8_t)a[i] > (uint8_t)b[i])
      return 1;
    else if (a[i] < b[i])
      return -1;
  }
  return 0;
}

void* memset(void* dst, uint8_t val, size_t sz) {
  uint8_t* buf = dst;
  for (size_t i = 0; i < sz; i++) {
    buf[i] = val;
  }
  return (void*)buf;
}

void* memcpy(void* dst, const void* src, size_t sz) {
  const uint8_t* sbuf = src;
  uint8_t* dbuf       = dst;
  for (size_t i = 0; i < sz; i++) {
    dbuf[i] = sbuf[i];
  }
  return (void*)dbuf;
}

void* memmove(void* dst, const void* src, size_t sz) {
  size_t i;
  const uint8_t* sbuf = src;
  uint8_t* dbuf       = dst;
  memset((void*)&temp_buffer, 0x0, SIZE_MAX);

  for (i = 0; i < sz; i++) {
    temp_buffer[i] = sbuf[i];
  }
  for (i = 0; i < sz; i++) {
    dbuf[i] = temp_buffer[i];
  }

  memset((void*)&temp_buffer, 0x0, SIZE_MAX);
  return (void*)dbuf;
}

size_t strlen(const char* str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}
