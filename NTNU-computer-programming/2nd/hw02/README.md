> **Student ID: 41047035S**  
> **Student Name: 林昕鋭**  
> **Teacher Name: 紀博文**  
> **Finish Date: 2022/03/08**

## To build your code, please run:
```
make
```

## hw0201
### Another Character Encoding  
> After reading string from user's input,convert to each character. Then,convert character to interger. Use Ternary Operator to reverse interger. Finally, convert to character and print it.  

> If you want to execute it, typing the command below:
```
./hw0101
```

## hw0102
### Replacement
> Record length of orginal string,keyword,replace. Loop for each character in orginal string and loop for keyword to find position. Position is to be located in orginal string to replace new keyword.

> If you want to execute it, typing the command below:
```
./hw0102
```

## hw0103
### My String Library v1
> All functions are in "mystring.h". There are some function prototype:
```
long int mystrtol(const char *nptr, char **endptr, int base);
```
> Please reference linux manual.  
> If you want to execute it, you will need to add new file named "hw0103.c" by yourself

## hw0104
### My String Library v2
> All functions are in "mystring.h". There are some function prototype:
```
char *mystrchr(const char *s, int c); 
char *mystrrchr(const char *s, int c);
size_t mystrspn(const char *s, const char *accept); 
size_t mystrcspn(const char *s, const char *reject);
char *mystrpbrk(const char *s, const char *accept);
char *mystrstr(const char *haystack, const char *needle); 
char *mystrtok(char *str, const char *delim);
```
> Please reference linux manual.  
> If you want to execute it, you will need to add new file named "hw0104.c" by yourself

## hw0105
### Split
> All functions are in "mystring.h". There are some function prototype:
```
int mystrsplit(char ***pppList, int *pCounter, const char *pStr, const char * pSeparator);
```
> Please reference "Python3 Split" official document.  
> If you want to execute it, you will need to add new file named "hw0105.c" by yourself