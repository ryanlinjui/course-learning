#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

uint8_t match(char* pStr,char* pPattern)
{
    char *c_p=NULL,*m_p=NULL;
    while((*pStr)&&(*pPattern!='*')) 
    {
        if((*pPattern!=*pStr)&&(*pPattern!='?')) 
        {
            return 0;
        }
        pPattern++;
        pStr++;
    }
    while(*pStr) 
    {
        if(*pPattern=='*') 
        {
            pPattern++;
            if(!(*pPattern))
            {
                return 1;
            }
            m_p = pPattern;
            c_p = pStr+1;
        } 
        else if((*pPattern==*pStr)||(*pPattern=='?')) 
        {
            pPattern++;
            pStr++;
        } 
        else 
        {
            pPattern = m_p;
            pStr = c_p++;
        }
    }
    while(*pPattern=='*') 
    {
        pPattern++;
    }
    return !(*pPattern);
}
    
int mymatch(char ***pppList, const char *pStr, const char *pPattern)
{
    char *pStr_cp = malloc(strlen(pStr));
    char *pPattern_cp = malloc(strlen(pPattern));
    strncpy(pStr_cp,pStr,strlen(pStr));
    strncpy(pPattern_cp,pPattern,strlen(pPattern));
    if((pppList == NULL)||(pStr == NULL)||(pPattern == NULL))
    {
        return -1;
    }
    int sum = 0;                     
    if(*pppList == NULL) 
    { 
        *pppList = (char**)malloc(1000);
    }
    char *token = strtok(pStr_cp, " ");
    for(int i=0;token!=NULL;i++,token=strtok(NULL," "))
    {
        (*pppList)[i] = (char*)malloc(strlen(token));
        if(match(token,pPattern_cp))
        {
            sum++;
            strncpy((*pppList)[i],token,strlen(token));
        } 
    }
    free(pStr_cp);
    free(pPattern_cp);
    return sum;
}