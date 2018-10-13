#pragma once

int InStr(const char *str, const char *keyword, int start = 1);
int Len(const char *str);
int Len(const char str[]);
char* JointStr(const char *str1, const char *str2);
char* Mid(const char *str, int start, int length);
char* Left(const char *str, int length);
char* Right(const char *str, int length);
char* Replace(const char *str, const char *keyword, const char *replace);