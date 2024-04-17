> **Student ID: 41047035S**  
> **Student Name: 林昕鋭**  
> **Teacher Name: 柯佳伶**  
> **Finish Date: 2022/12/25**

# Program Homework 4

To build it, please run:
```
make
```

To run the program after building:
```
./main
```

## Procedure info
```c
// adjency list data structure
typedef struct _sList List;
struct _sList
{
    int32_t num;
    List *link;
};
int32_t visited[MAX_N];

// dfs algorithm to find connected component
void dfs(int32_t v,List **chain);

// connect each node to chain list
List** connect(List **chain,int32_t n1,int32_t n2);
```

