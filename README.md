# Ctring

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Language](https://img.shields.io/badge/language-C-orange)

A lightweight C string manipulation library providing essential string operations with error handling.

## 📥 Installation

### For Windows and Unix-based systems (Linux, macOS)

```bash
curl -o ctring.h https://raw.githubusercontent.com/DilemaFixer/Сtring/main/ctring.h
curl -o ctring.c https://raw.githubusercontent.com/DilemaFixer/Сtring/main/ctring.c
```

## 🛠️ API and Usage Examples

### 🔤 Basic String Operations

Core functions for string manipulation and information retrieval.

```c
// Create an empty string
char* string_empty();

// Get string length
size_t str_length(const char* str);

// Copy a string into a new buffer
void str_copy(const char* from, char** to);

// Concatenate strings with buffer size limit
char* str_concat(char* dest, const char* src, size_t size);

// Create a duplicate of a string
char* str_duplicate(const char* str);
```

Usage example:
```c
#include "ctring.h"

void string_basics() {
    char* empty = string_empty();
    
    char* original = "Hello, world!";
    size_t len = str_length(original);
    
    char* copy = NULL;
    str_copy(original, &copy);
    
    char buffer[100] = "Hello, ";
    str_concat(buffer, "world!", sizeof(buffer));
    
    char* duplicate = str_duplicate(original);
    
    // Don't forget to free allocated memory
    free(empty);
    free(copy);
    free(duplicate);
}
```

### 🔍 String Comparison and Search

Functions for comparing strings and finding patterns.

```c
// Compare two strings
int str_compare(const char* str1, const char* str2);

// Compare two strings, ignoring case
int str_compare_case_insensitive(const char* str1, const char* str2);

// Check if a string contains a substring
int str_contains(const char* src, const char* target);

// Find a substring within a string
char* str_find(const char* str, const char* target);

// Check if a string starts with a given prefix
int str_start_with(char* str, char* prefix);

// Check if a string ends with a given suffix
int str_end_with(char* str, char* suffix);
```

Usage example:
```c
#include "ctring.h"

void string_comparison() {
    const char* str1 = "Hello, World!";
    const char* str2 = "hello, world!";
    
    if (str_compare(str1, str2) == 0) {
        // Strings are equal
    }
    
    if (str_compare_case_insensitive(str1, str2) == 0) {
        // Strings are equal ignoring case
    }
    
    if (str_contains(str1, "World")) {
        // str1 contains "World"
    }
    
    char* found = str_find(str1, "World");
    if (found) {
        // found points to where "World" begins in str1
    }
    
    if (str_start_with(str1, "Hello")) {
        // str1 starts with "Hello"
    }
}
```

### 🔄 String Modification

Functions for modifying and transforming strings.

```c
// Split a string into parts using delimiters
void str_split(const char* str, const char* delimiters, char*** result, size_t* count);

// Join multiple strings with a delimiter
char* str_join(const char delimiter, char*** strs, size_t count);

// Remove whitespace from the beginning and end of a string
void str_trim(char* str);

// Replace occurrences of one substring with another
void str_replce(char* str, char** old, char* next);

// Convert string to uppercase
void str_upper(char* str);

// Convert string to lowercase
void str_lower(char* str);

// Format a string (similar to sprintf)
void str_format(char* buffer, size_t size, const char* format, ...);
```

Usage example:
```c
#include "ctring.h"

void string_modifications() {
    char text[100] = "  Hello, World!  ";
    str_trim(text);  // Now: "Hello, World!"
    
    char** parts = NULL;
    size_t count = 0;
    str_split("apple,banana,cherry", ",", &parts, &count);
    
    char* old_str = "World";
    str_replce(text, &old_str, "C Programming");
    
    str_upper(text);  // Convert to uppercase
    
    char buffer[100];
    str_format(buffer, sizeof(buffer), "Count: %d", 42);
    
    // Free split results
    for (size_t i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}
```

### 🔄 String Conversion

Functions for converting between strings and other data types.

```c
// Convert string to integer
int str_to_int(const char* str);

// Convert string to float
float str_to_float(const char* str);

// Convert string to size_t
size_t str_to_sizet(const char* str);
```

Usage example:
```c
#include "ctring.h"

void string_conversions() {
    const char* num_str = "123";
    int num = str_to_int(num_str);
    
    const char* float_str = "3.14159";
    float pi = str_to_float(float_str);
    
    const char* size_str = "1000";
    size_t size = str_to_sizet(size_str);
}
```

### 🧩 Advanced String Operations

More specialized string manipulation functions.

```c
// Generate a hash of a string
char* str_hash(const char* str);

// Extract a substring
char* str_sub_string(const char* str, size_t start, size_t length);

// Reverse a string
char* str_reverse(const char* str);

// Add escape characters to a string
char* str_escape(const char* str);

// Remove escape characters from a string
char* str_unescape(const char* str);
```

Usage example:
```c
#include "ctring.h"

void advanced_operations() {
    const char* text = "Hello, C Programming!";
    
    char* hash = str_hash(text);
    
    char* substring = str_sub_string(text, 7, 12); // "C Programming"
    
    char* reversed = str_reverse(text);
    
    char* escaped = str_escape("Line1\nLine2\tTabbed");
    
    char* unescaped = str_unescape("Line1\\nLine2\\tTabbed");
    
    // Free allocated memory
    free(hash);
    free(substring);
    free(reversed);
    free(escaped);
    free(unescaped);
}
```
