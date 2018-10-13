#pragma once

int InStr(char *str, char *keyword, int start = 1);
int Len(char *str);
int Len(const char str[]);
char* JointStr(char *str1, char *str2);
char* Mid(char *str, int start, int length);
char* Left(char *str, int length);
char* Right(char *str, int length);
char* Replace(char *str, char *keyword, char *replace);