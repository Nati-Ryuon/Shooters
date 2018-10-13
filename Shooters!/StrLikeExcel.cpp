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
				return (i + 1);
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
	while (*(str + i) != '\0') i++;
	return i;
}

char* JointStr(const char *str1, const char *str2) {
	int i = 0, j = 0;
	char rt[255];
	int len_str1 = Len(str1);
	int len_str2 = Len(str2);

	while (i < len_str1) {
		rt[i] = *(str1 + i);
		i++;
	}

	while (j < len_str2){
		rt[i] = *(str2 + j);
		i++;
		j++;
	}
	rt[i] = '\0';

	return rt;
}

char* Mid(const char *str, int start, int length) {
	char rt[255];
	int i;
	for (i = 0; i < length; i++) {
		if (*(str + start - 1 + i) != '\0')
			rt[i] = *(str + start - 1 + i);
		else
			break;
	}
	rt[i] = '\0';

	return rt;
}

char* Left(const char *str, int length) {
	char rt[255];
	int i;
	if (length > Len(str))
		length = Len(str);
	for(i = 0; i < length; i++)
		rt[i] = *(str + i);
	rt[i] = '\0';
	return rt;
}

char* Right(const char *str, int length) {
	int len = Len(str);
	if (length > len)
		length = len;
	return Mid(str, len - length + 1, len);
}

char* Replace(const char *str, const char *keyword, const char *replace){
	int i,j = 1,k;
	//iはkeywordの位置、jはstr用の位置、kはrtの位置

	char rt[255];
	char *tmp;

	if (InStr(str, keyword) == 0) {
		for (i = 0; i < Len(str) + 1; i++)
			rt[i] = *(str + i);
		return rt;
	}

	while ((i = InStr(str, keyword, j)) != 0) {
		tmp = JointStr(rt, Mid(str, j, i - 1));
		for (k = 0; k < Len(tmp) + 1; k++)
			rt[i] = *(tmp + k);
		tmp = JointStr(rt, replace);
		for (k = 0; k < Len(tmp) + 1; k++)
			rt[i] = *(tmp + k);
		j = i + Len(replace);
	}

	rt[Len(rt)] = '\0';
	return rt;
}