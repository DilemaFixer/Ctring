#ifndef CTRING_H
#define CTRING_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    LEVEL_FATAL = 0,
    LEVEL_WARN  = 1,
    LEVEL_DEBUG = 2,
    LEVEL_TODO  = 3,
    LEVEL_UNIMPLEMENTED = 4
} LogLevel;

static const char* const LEVEL_NAMES[] = {
    "FATAL", "WARN", "DEBUG", "TODO", "UNIMPLEMENTED"
};

static inline void lmessage(LogLevel level, const char* format, ...) {
    fprintf(stderr, "[%s] ", LEVEL_NAMES[level]);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    
    if (level == LEVEL_FATAL || level == LEVEL_UNIMPLEMENTED) {
        exit(1);
    }
}

#define lfatal(...) lmessage(LEVEL_FATAL, __VA_ARGS__)
#define lwarn(...)  lmessage(LEVEL_WARN, __VA_ARGS__)
#define ldebug(...) lmessage(LEVEL_DEBUG, __VA_ARGS__)
#define ltodo(...)  lmessage(LEVEL_TODO, __VA_ARGS__)
#define lunimp(...) lmessage(LEVEL_UNIMPLEMENTED, "Not implemented: " __VA_ARGS__)

size_t str_length(const char* str);
void str_copy(const char* from  , char* to);
void str_concat(char* base , const char* src , size_t size);
char *str_duplicate(const char* str);
int str_compare(const char* str1 , const char* str2);
int str_compare_case_insensitive(const char* str1 , const char* str2);
int str_contains(const char* src , const char* target);
char *str_find(const char* str , const char* target);
void str_split(const char* str , const char* delimiters , char*** result , size_t *count);
char *str_join(const char delimiters , char ***strs , size_t count);
void str_trim(char* str);
void str_replce(char *str , str *old , str *new);
void str_upper(char *str);
void str_lower(char *str);
int str_start_with(char *str);
int str_end_with(char *str);
void str_format(char *buffer, size_t size, const char *format, ...);
int str_to_int(const char *str);
float str_to_int(const char *str);
size_t str_to_sizet(const char *str);
char *str_hash(const char* str);
char *str_sub_string(const char *str , size_t start , size_t length);
char *str_reverse(const char *str);
char *str_escape(const char *str);
char *str_unescape(const char str);

#endif
