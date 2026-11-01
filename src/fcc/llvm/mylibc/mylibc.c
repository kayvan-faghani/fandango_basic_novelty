// #include <stdio.h>
#include <stddef.h>
// #include <ctype.h>

// Currently unused.

int __my_memcmp(const void* ptr1, const void* ptr2, size_t num) {
    // Cast both pointers to unsigned char* (byte-wise comparison)
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;

    // Compare the memory byte by byte
    for (size_t i = 0; i < num; ++i) {
        if (p1[i] != p2[i]) {
            // Return the difference between the first differing bytes
            return p1[i] - p2[i];
        }
    }

    // If all bytes are equal, return 0
    return 0;
}

int __my_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int __my_strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
    }
    return 0;
}

char* __my_strchr(const char *str, int ch) {
    // Loop through each character in the string
    while (*str != '\0') {
        if (*str == (char)ch) { // If the character matches
            return (char *)str; // Return the current position
        }
        str++;
    }
    // Check if the character to search is the null terminator
    if (ch == '\0') {
        return (char *)str;
    }
    return NULL; // Character not found
}

void* __my_memchr(const void *ptr, int value, size_t num) {
    const unsigned char *byte_ptr = (const unsigned char *)ptr;

    for (size_t i = 0; i < num; i++) {
        if (byte_ptr[i] == (unsigned char)value) { // If the byte matches
            return (void *)&byte_ptr[i]; // Return the address of the match
        }
    }
    return NULL; // Byte not found
}

// int __my_strcasecmp(const char *str1, const char *str2) {
//     while (*str1 && *str2) {
//         char c1 = tolower((unsigned char)*str1); // Convert both characters to lowercase
//         char c2 = tolower((unsigned char)*str2);
//         if (c1 != c2) { // If characters don't match
//             return c1 - c2; // Return the difference
//         }
//         str1++;
//         str2++;
//     }
//     // If one string is shorter, return the difference at the null terminator
//     return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
// }

// int __my_strncasecmp(const char *str1, const char *str2, size_t n) {
//     while (n > 0 && *str1 && *str2) {
//         char c1 = tolower((unsigned char)*str1); // Convert both characters to lowercase
//         char c2 = tolower((unsigned char)*str2);
//         if (c1 != c2) { // If characters don't match
//             return c1 - c2; // Return the difference
//         }
//         str1++;
//         str2++;
//         n--; // Decrement the comparison count
//     }
//     // If we've compared n characters or reached the end of one string, return the difference
//     return n == 0 ? 0 : tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
// }