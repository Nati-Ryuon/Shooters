#include "StrLikeExcel.h"
//#include <string>

//using namespace std;

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

int Len(const char *str) {
	int i = 0;

	if (*str == '\0')
		return 0;

	while (*(str + i) != '\0') i++;

	return i;
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

char* Right(char buff[], const char *str, int length) {
	int len = Len(str);
	if (length > len)
		length = len;
	return Mid(buff, str, len - length + 1, len);
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