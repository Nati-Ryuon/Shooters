#include "StrLikeExcel.h"

int InStr(char *str, char *keyword, int start) {
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

int Len(char *str) {
	int i = 0;
	while (*(str + i) != '\0') i++;
	return i;
}

int Len(const char str[]) {
	int i = 0;
	while (str[i] != '\0') i++;
	return i;
}

char* JointStr(char *str1, char *str2) {
	int i = 0;
	int len_str1 = Len(str1);
	int len_str2 = Len(str2);

	while (i < len_str2){
		*(str1 + len_str1 + i) = *(str2 + i);
		i++;
	}
	*(str1 + i) = '\0';

	return str1;
}

char* Mid(char *str, int start, int length) {
	char *rt;
	int i;
	for (i = 0; i < length; i++) {
		if (*(str + start - 1 + i) != '\0')
			*(rt + i) = *(str + start - 1 + i);
		else
			break;
	}
	*(rt + i) = '\0';

	return rt;
}

char* Left(char *str, int length) {
	*(str + length) = '\0';
	return str;
}

char* Right(char *str, int length) {
	int len = Len(str);
	return Mid(str, len - length + 1, len);
}

char* Replace(char *str, char *keyword, char *replace){
	int i,j = 1,k = 0;
	//iはkeywordの位置、jはstr用の位置、kはrtの位置

	char *rt;
	*rt = '\0';

	if (InStr(str, keyword) == 0)
		return str;

	while ((i = InStr(str, keyword, j)) != 0) {
		JointStr(rt, Mid(str, j, i - 1));
		JointStr(rt, replace);
		j = i + Len(replace);
	}

	*(rt + Len(rt)) = '\0';
	return rt;
}