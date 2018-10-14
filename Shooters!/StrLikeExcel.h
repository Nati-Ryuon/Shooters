#pragma once

#define STRING_SIZE 255

int InStr(const char *str, const char *keyword, int start = 1);
int Len(const char *str);
char* JointStr(char buff[], const char *str1, const char *str2);
char* Mid(char buff[], const char *str, int start, int length);
char* Left(char buff[], const char *str, int length);
char* Right(char buff[], const char *str, int length);
char* Replace(char buff[], const char *str, const char *keyword, const char *replace);
int Value(const char *str);