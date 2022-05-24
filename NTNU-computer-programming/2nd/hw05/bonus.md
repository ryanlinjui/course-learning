> **Student ID: 41047035S**  
> **Student Name: 林昕鋭**  
> **Teacher Name: 紀博文**  
> **Finish Date: 2022/05/24**

## bonus
### Question:

Alice writes the following code.

```c
//Code 1 : Error (Segmentation Fault (Core Dump))
#include <stdio.h>

void init( int n ) 
{
    char str[10000000];
    for( int i = 0 ; i < n ; i++ ) 
    {
        str[i] = i; 
    }
    return; 
}

int main() 
{
    init( 10 );
    return 0; 
}

```

```c
// Code 2 : Work
#include <stdio.h>

void init( int n ) 
{
    static char str[10000000]; // <---------
    for( int i = 0 ; i < n ; i++ ) 
    {
        str[i] = i; 
    }
    return; 
}

int main() 
{
    init( 10 );
    return 0; 
}
```

```c
// Code 3 : Work
#include <stdio.h>

char str[10000000]; // <---------
void init( int n ) {
    for( int i = 0 ; i < n ; i++ )
    {
        str[i] = i;
    }
    return; 
}
int main()
{
    init( 10 );
    return 0; 
}
```

Would you please explain what happens to Alice?

### Answer:  
Code 1 is Stack in memory allocation, that's local variable.  
Code 2 is Data segment in memory allocation, that's static variable.  
Code 3 is Data segment in memory allocation, that's global variable.  

The reason that Code 1 happen segmentation fault is because that compiler will set memory limit of stack. Default usually is N KB or 10N KB. When memory is allocated too large that variable needed. It will cause stack overflow. So that segmentation fault.