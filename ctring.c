#include "ctring.h"
#include "stdlib.h"
#include "string.h"

int str_compare_case_insensitive(const char *str1, const char *str2) {
  if (str1 == NULL || str2 == NULL) {
    if (str1 == NULL && str2 == NULL)
      return 1;
    else
      return 0;
  }

  while (*str1 && *str2) {
    char c1 = *str1;
    char c2 = *str2;

    if (c1 >= 'A' && c1 <= 'Z')
      c1 += 32;
    if (c2 >= 'A' && c2 <= 'Z')
      c2 += 32;

    if (c1 != c2)
      return c1 - c2;

    str1++;
    str2++;
  }

  return *str1 - *str2;
}

int str_contains(const char *src, const char *target) {
  if (src == NULL || target == NULL)
    return 0;
  if (*target == '\0')
    return 1;

  while (*src) {
    const char *s = src;
    const char *t = target;

    while (*s && *t && *s == *t) {
      s++;
      t++;
    }

    if (*t == '\0')
      return 1;
    src++;
  }

  return 0;
}

char *str_find(const char *str, const char *target) {
  if (str == NULL || target == NULL)
    return NULL;
  if (*target == '\0')
    return (char *)str;

  while (*str) {
    const char *s = str;
    const char *t = target;

    while (*s && *t && *s == *t) {
      s++;
      t++;
    }

    if (*t == '\0')
      return (char *)str;
    str++;
  }

  return NULL;
}

void str_split(const char *str, const char *delimiters, char ***result,
               size_t *count) {
  if (str == NULL || delimiters == NULL || result == NULL || count == NULL) {
    *count = 0;
    *result = NULL;
    return;
  }

  size_t len = str_length(str);
  size_t max_tokens = len + 1;
  *result = (char **)malloc(sizeof(char *) * max_tokens);

  if (!*result) {
    lfatal("Memory allocation failed in str_split");
    return;
  }

  *count = 0;
  const char *start = str;
  const char *end = str;

  while (*end) {
    int is_delimiter = 0;
    const char *d = delimiters;

    while (*d) {
      if (*end == *d) {
        is_delimiter = 1;
        break;
      }
      d++;
    }

    if (is_delimiter || *(end + 1) == '\0') {
      size_t token_len = end - start;
      if (*(end + 1) == '\0' && !is_delimiter)
        token_len++;

      if (token_len > 0) {
        (*result)[*count] = (char *)malloc(sizeof(char) * (token_len + 1));
        if (!(*result)[*count]) {
          lfatal("Memory allocation failed for token in str_split");
          return;
        }

        for (size_t i = 0; i < token_len; i++) {
          (*result)[*count][i] = start[i];
        }
        (*result)[*count][token_len] = '\0';
        (*count)++;
      }

      start = end + 1;
    }

    end++;
  }
}

char *str_join(const char delimiter, char ***strs, size_t count) {
  if (strs == NULL || *strs == NULL || count == 0) {
    return string_empty();
  }

  size_t total_len = 0;
  for (size_t i = 0; i < count; i++) {
    if ((*strs)[i]) {
      total_len += str_length((*strs)[i]);
    }
  }

  total_len += count - 1;

  char *result = (char *)malloc(sizeof(char) * (total_len + 1));
  if (!result) {
    lfatal("Memory allocation failed in str_join");
    return NULL;
  }

  size_t pos = 0;
  for (size_t i = 0; i < count; i++) {
    if ((*strs)[i]) {
      size_t len = str_length((*strs)[i]);
      for (size_t j = 0; j < len; j++) {
        result[pos++] = (*strs)[i][j];
      }
    }

    if (i < count - 1) {
      result[pos++] = delimiter;
    }
  }

  result[pos] = '\0';
  return result;
}

void str_trim(char *str) {
  if (str == NULL)
    return;

  size_t len = str_length(str);
  if (len == 0)
    return;

  size_t start = 0;
  while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' ||
         str[start] == '\r') {
    start++;
    if (start == len) {
      str[0] = '\0';
      return;
    }
  }

  size_t end = len - 1;
  while (end > start && (str[end] == ' ' || str[end] == '\t' ||
                         str[end] == '\n' || str[end] == '\r')) {
    end--;
  }

  size_t new_len = end - start + 1;
  for (size_t i = 0; i < new_len; i++) {
    str[i] = str[start + i];
  }

  str[new_len] = '\0';
}

void str_replce(char *str, char **old, char *next) {
  if (str == NULL || old == NULL || *old == NULL || next == NULL)
    return;

  size_t str_len = str_length(str);
  size_t old_len = str_length(*old);
  size_t new_len = str_length(next);

  if (str_len == 0 || old_len == 0)
    return;

  char *temp = str_duplicate(str);
  size_t temp_idx = 0;
  size_t str_idx = 0;

  while (temp[temp_idx]) {
    if (strncmp(&temp[temp_idx], *old, old_len) == 0) {
      for (size_t i = 0; i < new_len; i++) {
        str[str_idx++] = next[i];
      }
      temp_idx += old_len;
    } else {
      str[str_idx++] = temp[temp_idx++];
    }
  }

  str[str_idx] = '\0';
  free(temp);
}

void str_upper(char *str) {
  if (str == NULL)
    return;

  while (*str) {
    if (*str >= 'a' && *str <= 'z') {
      *str = *str - 32;
    }
    str++;
  }
}

void str_lower(char *str) {
  if (str == NULL)
    return;

  while (*str) {
    if (*str >= 'A' && *str <= 'Z') {
      *str = *str + 32;
    }
    str++;
  }
}

int str_start_with(char *str, char *prefix) {
  if (str == NULL || prefix == NULL)
    return 0;

  while (*prefix) {
    if (*prefix != *str)
      return 0;
    prefix++;
    str++;
  }

  return 1;
}

void str_format(char *buffer, size_t size, const char *format, ...) {
  if (buffer == NULL || format == NULL)
    return;

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, size, format, args);
  va_end(args);
}

int str_to_int(const char *str) {
  if (str == NULL)
    return 0;

  int result = 0;
  int sign = 1;

  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }

  return result * sign;
}

float str_to_float(const char *str) {
  if (str == NULL)
    return 0.0f;

  float result = 0.0f;
  float fraction = 0.0f;
  float div = 1.0f;
  int sign = 1;
  int in_fraction = 0;

  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  while (*str) {
    if (*str == '.') {
      in_fraction = 1;
      str++;
      continue;
    }

    if (*str >= '0' && *str <= '9') {
      if (in_fraction) {
        div /= 10.0f;
        fraction += (*str - '0') * div;
      } else {
        result = result * 10.0f + (*str - '0');
      }
    }

    str++;
  }

  return (result + fraction) * sign;
}

size_t str_to_sizet(const char *str) {
  if (str == NULL)
    return 0;

  size_t result = 0;

  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }

  return result;
}

char *str_hash(const char *str) {
  if (str == NULL)
    return NULL;

  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  char *hash_str = (char *)malloc(sizeof(char) * 17);
  if (!hash_str) {
    lfatal("Memory allocation failed in str_hash");
    return NULL;
  }

  snprintf(hash_str, 17, "%016lx", hash);
  return hash_str;
}

char *str_sub_string(const char *str, size_t start, size_t length) {
  if (str == NULL)
    return NULL;

  size_t str_len = str_length(str);

  if (start >= str_len)
    return string_empty();

  if (start + length > str_len) {
    length = str_len - start;
  }

  char *result = (char *)malloc(sizeof(char) * (length + 1));
  if (!result) {
    lfatal("Memory allocation failed in str_sub_string");
    return NULL;
  }

  for (size_t i = 0; i < length; i++) {
    result[i] = str[start + i];
  }

  result[length] = '\0';
  return result;
}

char *str_reverse(const char *str) {
  if (str == NULL)
    return NULL;

  size_t len = str_length(str);
  char *result = (char *)malloc(sizeof(char) * (len + 1));

  if (!result) {
    lfatal("Memory allocation failed in str_reverse");
    return NULL;
  }

  for (size_t i = 0; i < len; i++) {
    result[i] = str[len - i - 1];
  }

  result[len] = '\0';
  return result;
}

char *str_escape(const char *str) {
  if (str == NULL)
    return NULL;

  size_t len = str_length(str);
  size_t escaped_len = len;

  for (size_t i = 0; i < len; i++) {
    if (str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == '\\' ||
        str[i] == '\"') {
      escaped_len++;
    }
  }

  char *result = (char *)malloc(sizeof(char) * (escaped_len + 1));
  if (!result) {
    lfatal("Memory allocation failed in str_escape");
    return NULL;
  }

  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    switch (str[i]) {
    case '\n':
      result[j++] = '\\';
      result[j++] = 'n';
      break;
    case '\r':
      result[j++] = '\\';
      result[j++] = 'r';
      break;
    case '\t':
      result[j++] = '\\';
      result[j++] = 't';
      break;
    case '\\':
      result[j++] = '\\';
      result[j++] = '\\';
      break;
    case '\"':
      result[j++] = '\\';
      result[j++] = '\"';
      break;
    default:
      result[j++] = str[i];
      break;
    }
  }

  result[j] = '\0';
  return result;
}

char *str_unescape(const char *str) {
  if (str == NULL)
    return NULL;

  size_t len = str_length(str);
  char *result = (char *)malloc(sizeof(char) * (len + 1));

  if (!result) {
    lfatal("Memory allocation failed in str_unescape");
    return NULL;
  }

  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    if (str[i] == '\\' && i + 1 < len) {
      switch (str[i + 1]) {
      case 'n':
        result[j++] = '\n';
        i++;
        break;
      case 'r':
        result[j++] = '\r';
        i++;
        break;
      case 't':
        result[j++] = '\t';
        i++;
        break;
      case '\\':
        result[j++] = '\\';
        i++;
        break;
      case '\"':
        result[j++] = '\"';
        i++;
        break;
      default:
        result[j++] = str[i];
        break;
      }
    } else {
      result[j++] = str[i];
    }
  }

  result[j] = '\0';
  return result;
}
