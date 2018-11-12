#include "StrLikeExcel.h"

int InStr(const char *str, const char *keyword, int start) {
	int i, j = 0;
	if((Len(str) < start) || Len(keyword) == 0) return 0;
	i = start - 1;
	while (*(str + i) != '\0') {
		if (*(str + i) == *(keyword + j)) {
			j++;
			if (*(keyword + j) == '\0') {
				return (i - j + 2);
			}
		}else{
			j = 0;
		}
		i++;
	}
	
	return 0;
}

int InStr(string str, string keyword, int start) {
	int i = str.find(keyword, start - 1);
	if (i == string::npos)
		return 0;
	else
		return i + 1;
}

int Len(const char *str) {
	int i = 0;

	if (*str == '\0')
		return 0;

	while (*(str + i) != '\0') i++;

	return i;
}

int Len(string str) {
	return str.length();
}

char* JointStr(char buff[], const char *str1, const char *str2) {
	int i = 0, j = 0;
	//char rt[STRING_SIZE];
	int len_str1 = Len(str1);
	int len_str2 = Len(str2);

	while (i < len_str1) {
		buff[i] = *(str1 + i);
		i++;
	}

	while (j < len_str2){
		buff[i] = *(str2 + j);
		i++;
		j++;
	}
	buff[i] = '\0';

	return buff;
}

string JointStr(string str1, string str2) {
	return str1 + str2;
}

char* Mid(char buff[], const char *str, int start, int length) {
	//char rt[STRING_SIZE];
	int i;
	for (i = 0; i < length; i++) {
		if (*(str + start - 1 + i) != '\0')
			buff[i] = *(str + start - 1 + i);
		else
			break;
	}
	buff[i] = '\0';

	return buff;
}

string Mid(string str, int start, unsigned int length) {
	if (length > str.length())
		length = str.length();
	return str.substr(start - 1, length);
}

char* Left(char buff[], const char *str, int length) {
	//char rt[STRING_SIZE];
	int i;
	if (length > Len(str))
		length = Len(str);
	for(i = 0; i < length; i++)
		buff[i] = *(str + i);
	buff[i] = '\0';
	return buff;
}

string Left(string str, unsigned int length) {
	if (length > str.length())
		return str;
	return str.substr(0, length);
}

char* Right(char buff[], const char *str, int length) {
	int len = Len(str);
	if (length > len)
		length = len;
	return Mid(buff, str, len - length + 1, len);
}

string Right(string str, unsigned int length) {
	if (length > str.length())
		return str;
	return str.substr(str.length() - length, length);
}

char* Replace(char buff[], const char *str, const char *keyword, const char *replace){
	int i,j = 1;
	//iはkeywordの位置、jはstr用の位置

	char rt[STRING_SIZE];
	char tmp[STRING_SIZE];
	char str2[STRING_SIZE];

	str2[0] = '\0';
	JointStr(str2, str2, str);

	if (InStr(str, keyword) == 0) {
		for (i = 0; i < Len(str) + 1; i++)
			buff[i] = *(str + i);
		return buff;
	}

	rt[0] = '\0';
	tmp[0] = '\0';
	buff[0] = '\0';

	//abcdecde,cd
	while ((i = InStr(str2, keyword, j)) != 0) {
		Mid(tmp, str2, j, i - 1 - j + 1);
		JointStr(rt, rt, tmp);
		JointStr(rt, rt, replace);
		//for (k = 0; k < Len(tmp) + 1; k++)
			//rt[k] = *(tmp + k);
		j = i + Len(keyword);
	}

	Mid(tmp, str2, j, Len(str));
	JointStr(rt, rt, tmp);

	rt[Len(rt)] = '\0';
	JointStr(buff, buff, rt);
	
	return buff;
}

string Replace(string str, string keyword, string replace) {
	int i, j = 1;
	//iはkeywordの位置、jはstr用の位置

	string rt;

	if (InStr(str, keyword) == 0) {
		return str;
	}

	//abcdecde,cd
	while ((i = InStr(str, keyword, j)) != 0) {
		rt += Mid(str, j, i - 1 - j + 1);
		rt += replace;
		j = i + keyword.length();
	}

	rt += Mid(str, j, str.length());

	return rt;
}

int Value(const char *str) {
	int i = 0;
	int tmp;
	int rt = 0;

	while (*(str + i) != '\0') {
		tmp = (int)(*(str + i) - '0');
		if (tmp >= 0 && tmp <= 9) {
			rt = rt * 10 + tmp;
		}
		i++;
	}

	return rt;
}

int Value(string str) {
	int i = 0;
	int tmp;
	int rt = 0;

	while (str[i] != '\0') {
		tmp = (int)(str[i] - '0');
		if (tmp >= 0 && tmp <= 9) {
			rt = rt * 10 + tmp;
		}
		i++;
	}

	return rt;
}