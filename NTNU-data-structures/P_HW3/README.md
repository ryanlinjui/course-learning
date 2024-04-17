> **Student ID: 41047035S**  
> **Student Name: 林昕鋭**  
> **Teacher Name: 柯佳伶**  
> **Finish Date: 2022/11/10**

# Math expression tools

To build it, please run:
```
make
```

To run the program after building:
```
./main
```

## How to use it?
1. Input infix expression data.
2. The infix data must be consist of 0~20 chars for each input data. Press enter key after finish input. Each of char must follow the rule below:
    - "0" to "9"
    - "(" or ")"
    - "+", "-", "*", "/"
    - The space char is not permit.

3. Show all of the result:
    - postfix expression
    - prefix expression
    - level order expression
    - operation result

4. Repeat above the rule, until input "q" char to exit.

## Procedure info
> All of the functions define in expression.h file

```c
// Expression tree data structure
typedef struct _sExpTree ExpTree;
struct _sExpTree
{
    char item;
    ExpTree *left;
    ExpTree *right;
};

// Convert infix string to postfix string 
char* get_postfix(char *infix);

// Return expression opration result
int32_t cal_postfix(char *postfix);

// Return the postfix tree after initial it
ExpTree* init_postfix_tree(char* postfix);

// Print the preorder result of string
void preorder(ExpTree *t);

// Print the postorder result of string
void postorder(ExpTree *t);

// Print the level result of string
void levelorder(ExpTree *t);
```

