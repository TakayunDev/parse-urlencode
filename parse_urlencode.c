#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char
get_2bytes(const char *str) {
  char buf[3] = {0};

  buf[0] = str[0];
  buf[1] = str[1];

  return (char)strtol(buf, NULL, 16);
}

void
parse_urlencode(char *out, const char *encoded)
{
  size_t i, cur = 0;

  for (i = 0; encoded[i] != '\0'; i++) {
    // replace '+' to ' '
    if (encoded[i] == '+') {
      out[cur++] = ' ';
      continue;
    }

    // parse parcent encoding
    if (encoded[i] == '%') {
      i++; // skip '%'
      out[cur++] = get_2bytes(encoded+i);
      i++; // skip 2bytes
      continue;
    }

    out[cur++] = encoded[i];

  }
  out[cur] = '\0';

}

int main(void) {
  char *url = "Hello+%2A+Mirai+Akari%21";
  char *decoded = calloc(sizeof(char), strlen(url)+1);

  parse_urlencode(decoded, url);

  printf("url    : %s\n", url);
  printf("decoded: %s\n", decoded);

  return 0;
}
