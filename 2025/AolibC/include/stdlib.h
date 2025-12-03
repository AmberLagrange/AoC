#ifndef STDLIB_H
#define STDLIB_H

int atoi(const char *str);
long atol(const char *str);
long long atoll(const char *str);

__attribute__((noreturn)) void exit(int status);

#endif // STDLIB_H

