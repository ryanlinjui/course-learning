#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_N 35
#define FILENAME "test.txt"

typedef struct _sList List;
struct _sList
{
    int32_t num;
    List *link;
};
int32_t visited[MAX_N];
int32_t ring_temp[MAX_N];
int32_t top=0;

void dfs(int32_t v,List **chain)
{
    visited[v]=1;
    ring_temp[top++]=v;
    for (List *w=chain[v]->link;w!=NULL;w=w->link)
    {
        if(!visited[w->num-1])
        {
            dfs(w->num-1,chain);
        }
        else
        {
            visited[w->num-1]++;
        }
    }
}

List** connect(List **chain,int32_t n1,int32_t n2)
{
    List *temp = chain[n1-1];

    while (temp->link!=NULL)
    {
        temp = temp->link;
    }
    temp->link = calloc(1,sizeof(List));
    temp->link->num = n2;
    temp->link->link = NULL; 

    // temp = chain[n2-1];
    // while (temp->link!=NULL)
    // {
    //     temp = temp->link;
    // }
    // temp->link = calloc(1,sizeof(List));
    // temp->link->num = n1; 
    // temp->link->link = NULL; 
    return chain;
}

int main()
{
    FILE *fd = fopen(FILENAME,"r");

    int32_t loop=0;
    fscanf(fd,"%d",&loop);
    int32_t connected_component=0;
    int32_t n=0,m=0;
    int32_t ring_num=0;
    int32_t is_chain=0;
    char *case2 = calloc(MAX_N,sizeof(char));

    List **chain = NULL;

    while (loop--)
    {
        top=0;
        connected_component=0;
        ring_num=0;
        is_chain=1;
        fscanf(fd,"%d %d",&n,&m);
        chain = calloc(n,sizeof(List*));
        for(int i=0;i<n;i++)
        {
            visited[i] = 0;
            chain[i]=calloc(1,sizeof(List));
            chain[i]->link = NULL;
        }
        for(int i=0;i<m;i++)
        {
            int32_t n1=0,n2=0;
            fscanf(fd,"%d %d",&n1,&n2);
            chain = connect(chain,n1,n2);
        }

        fgets(case2,MAX_N,fd);
        fgets(case2,MAX_N,fd);

        for(int i=0;i<n;i++)
        {
            if(!visited[i])
            {
                dfs(i,chain);
                connected_component++;
                int32_t count = 0;
                for(int j = 0; j < top; j++)
                {
                    count+=visited[ring_temp[j]];
                }
                if(count%top==1) // is ring
                {
                    ring_num++;
                    char *p = strtok(case2, " ");
                    while (p != NULL)
                    {
                        int32_t exit_loop=0;
                        for(int j=0;j<top;j++)
                        {
                            if(ring_temp[j]==atoi(p)-1)
                            {
                                exit_loop=1;
                                break;   
                            }
                            if(j==top-1) is_chain=0;
                        }
                        if(exit_loop) break;
                        p = strtok(NULL, " ");
                    }
                }
                top=0;
            }
        }
        printf("%d\n",connected_component);
        if(is_chain)
        {
            puts("Yes");
        }
        else
        {
            puts("No");
        }
        if(ring_num==connected_component)
        {
            printf("%d\n",connected_component);
        }
        else
        {
            printf("%d\n",connected_component-1);
        }
        free(chain);
    }
    fclose(fd);
    return 0;
}