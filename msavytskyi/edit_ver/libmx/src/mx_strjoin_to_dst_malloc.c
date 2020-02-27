#include "libmx.h"

char *mx_strjoin_to_dst_malloc(char *s1, const char *s2) {
	if(s1 == NULL && s2 == NULL)
		return NULL;
	else if(s2 == NULL)
		return mx_strdup(s1);
	else if(s1 == NULL)
		return mx_strdup(s2);
	char *str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
	char *res = str;
	str = mx_strcpy(str, s1);
	while(*str)
		str++;
	mx_strcpy(str, s2);
	free(s1);
	s1 = res;
	return res;
}

// int main() {
// 	char *str = mx_strnew(5);
// 	for(int i = 0; i < 5; i++)
// 		str[i] = 'h';
// 	char *src = " World";
// 	//printf("%s\n", mx_strjoin("NULL ", "     \nNULL"));
// 	str = mx_strjoin_to_dst_malloc(str, "he");
// 	printf("%s\n", str);
// 	system("leaks -q a.out");
// }
