#pragma once

#include <string>
using namespace std;

#define STRING_SIZE 255

int InStr(const char *str, const char *keyword, int start = 1);
int Len(const char *str);
char* JointStr(char buff[], const char *str1, const char *str2);
char* Mid(char buff[], const char *str, int start, int length);
char* Left(char buff[], const char *str, int length);
char* Right(char buff[], const char *str, int length);
char* Replace(char buff[], const char *str, const char *keyword, const char *replace);
int Value(const char *str);

int InStr( string str,  string keyword, int start = 1);
int Len( string str);
string JointStr(string str1,  string str2);
string Mid(string str, int start, int length);
string Left(string str, int length);
string Right(string str, int length);
string Replace(string str,  string keyword,  string replace);
int Value( string str);