#pragma once 
#include "lib/cstd.h"

#define Welcome_MSG \
"Welcome to PM2 modifier\n" \
"Please input your filename\n"

#define TOPIC_MSG \
"Select a topic:\n" \
"(1) Attribute\n" \
"(2) Reputation\n" \
"(3) Ability\n" \
"(4) Performance\n" \
"(5) Date\n" \
"(6) Figure\n" \
"(0) Save and Exit program\n"

#define ATTRIBUTE_MSG \
"Select a arrribute you want to modify:\n" \
"(1) stamina\n" \
"(2) strnth\n" \
"(3) intell\n" \
"(4) elegance\n" \
"(5) glamour\n" \
"(6) morality\n" \
"(7) faith\n" \
"(8) karma\n" \
"(9) senstv\n" \
"(10) stress\n" \
"(0) Previous\n"

#define ABILITY_MSG \
"Select a ablity you want to modify:\n" \
"(1) fgt_skl\n" \
"(2) attack\n" \
"(3) defense\n" \
"(4) mag_skl\n" \
"(5) mag_atk\n" \
"(6) mag_def\n" \
"(0) Previous\n"

#define REPUTATION_MSG \
"Select a reputation you want to modify:\n" \
"(1) fgt_rep\n" \
"(2) mag_rep\n" \
"(3) scl_rep\n" \
"(4) hkp_rep\n" \
"(0) Previous\n"

#define PERFORMANCE_MSG \
"Select a performance you want to modify:\n" \
"(1) fgt_skl\n" \
"(2) attack\n" \
"(3) defense\n" \
"(4) mag_skl\n" \
"(5) mag_atk\n" \
"(6) mag_def\n" \
"(0) Previous\n"

#define DATE_MSG \
"Select a date you want to modify:\n" \
"(1) month\n" \
"(2) week\n" \
"(3) day\n"

#define FIGURE_MSG \
"Select a figure you want to modify:\n" \
"(1) height\n" \
"(2) weight\n" \
"(3) chest\n" \
"(4) waist\n" \
"(5) buttock\n"

struct 
{
    uint16_t stamina;
    uint16_t strnth;
    uint16_t intell;
    uint16_t elegance;
    uint16_t glamour;
    uint16_t morality;
    uint16_t faith;
    uint16_t karma;
    uint16_t senstv;
    uint16_t stress;
}Attribute; //size: 20 Bytes

struct
{
    uint16_t fgt_rep;
    uint16_t mag_rep;
    uint16_t scl_rep;
    uint16_t hkp_rep;
}Reputation; //size: 8 Bytes

struct
{
    uint16_t fgt_skl;
    uint16_t attack;
    uint16_t defense;
    uint16_t mag_skl;
    uint16_t mag_atk;
    uint16_t mag_def; 
}Ability; //size: 12 Bytes

struct
{
    uint16_t decorum;
    uint16_t art_skl;
    uint16_t speech;
    uint16_t cooking;
    uint16_t cln_ldr;
    uint16_t personal;
}Performance; //size: 12 Bytes

struct
{
    uint16_t month;
    uint16_t week;
    uint16_t day;
}Date; //size: 6 Bytes

struct
{
    uint16_t height;
    uint16_t weight;
    uint16_t chest;
    uint16_t waist;
    uint16_t buttock;
}Figure; //size: 10 Bytes

#define ATTRIBUTE_OFFSET 62
#define REPUTATION_OFFSET 84
#define ABILITY_OFFSET 92
#define PERFORMANCE_OFFSET 104
#define DATE_OFFSET 52
#define FIGURE_OFFSET 210

char *file=NULL;
int32_t fd=0;
uint64_t file_size = 0;

void set_modifier(char *filename)
{
    fd = open( filename, O_RDWR );
    CHECK_VALID(fd!=-1,"Open file error!!");
    
    file = NULL;

    // get fd size start
    struct stat statbuf; 
    if( fstat( fd, &statbuf ) < 0 )
    {
        close( fd );
        puts("fd error!!");
        exit(0);
    } 
    file_size =  statbuf.st_size; 
    // get fd size end

    file = mmap( 0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    
    memcpy(&Attribute,file+ATTRIBUTE_OFFSET,sizeof(Attribute));
    memcpy(&Reputation,file+REPUTATION_OFFSET,sizeof(Reputation));
    memcpy(&Ability,file+ABILITY_OFFSET,sizeof(Ability));
    memcpy(&Performance,file+PERFORMANCE_OFFSET,sizeof(Performance));
    memcpy(&Date,file+DATE_OFFSET,sizeof(Date));
    memcpy(&Figure,file+FIGURE_OFFSET,sizeof(Figure));
}

void save_modifier()
{
    memcpy(file+ATTRIBUTE_OFFSET,&Attribute,sizeof(Attribute));
    memcpy(file+REPUTATION_OFFSET,&Reputation,sizeof(Reputation));
    memcpy(file+ABILITY_OFFSET,&Ability,sizeof(Ability));
    memcpy(file+PERFORMANCE_OFFSET,&Performance,sizeof(Performance));
    memcpy(file+DATE_OFFSET,&Date,sizeof(Date));
    memcpy(file+FIGURE_OFFSET,&Figure,sizeof(Figure));
    munmap(file,file_size);
    close(fd);
}

void topic_menu(int32_t choice, uint8_t *func_num)
{
    system("clear");
    puts(TOPIC_MSG);
    CHECK_VALID(scanf("%d", &choice)==1 && choice>=0 && choice<=6,"Value must be one and in range 0 to 6!!");
    if(choice==0)
    {
        save_modifier();
        puts("File is modified, Saved");
        exit(0);
    }
    
    *func_num = (uint8_t)choice;
}

void attribute_menu(int32_t choice, uint8_t *func_num)
{
    system("clear");
    puts(ATTRIBUTE_MSG);
    CHECK_VALID(scanf("%d", &choice)==1 && choice>=0 && choice<=10,"Value must be one and in range 0 to 10!!");
    if(choice==0)
    {
        *func_num = 0;
    }
    else
    {
        uint16_t num=0;
        printf("Input chage value: ");
        scanf("%hu",&num);
        *((uint16_t*)&(Attribute)+((uint16_t)choice-1)) = num;
        *func_num = 1;
    }
}

void reputation_menu(int32_t choice, uint8_t *func_num)
{
    system("clear");
    puts(REPUTATION_MSG);
    CHECK_VALID(scanf("%d", &choice)==1 && choice>=0 && choice<=4,"Value must be one and in range 0 to 4!!");
    if(choice==0)
    {
        *func_num = 0;
    }
    else
    {
        uint16_t num=0;
        printf("Input chage value: ");
        scanf("%hu",&num);
        *((uint16_t*)&(Reputation)+((uint16_t)choice-1)) = num;
        *func_num = 2;
    }
}

void ablity_menu(int32_t choice, uint8_t *func_num)
{
    system("clear");
    puts(ABILITY_MSG);
    CHECK_VALID(scanf("%d", &choice)==1 && choice>=0 && choice<=6,"Value must be one and in range 0 to 6!!");
    if(choice==0)
    {
        *func_num = 0;
    }
    else
    {
        uint16_t num=0;
        printf("Input chage value: ");
        scanf("%hu",&num);
        *((uint16_t*)&(Ability)+((uint16_t)choice-1)) = num;
        *func_num = 3;
    }
}

void performance_menu(int32_t choice, uint8_t *func_num)
{
    system("clear");
    puts(PERFORMANCE_MSG);
    CHECK_VALID(scanf("%d", &choice)==1 && choice>=0 && choice<=6,"Value must be one and in range 0 to 6!!");
    if(choice==0)
    {
        *func_num = 0;
    }
    else
    {
        uint16_t num=0;
        printf("Input chage value: ");
        scanf("%hu",&num);
        *((uint16_t*)&(Performance)+((uint16_t)choice-1)) = num;
        *func_num = 4;
    }
}

void date_menu(int32_t choice, uint8_t *func_num)
{
    system("clear");
    puts(DATE_MSG);
    CHECK_VALID(scanf("%d", &choice)==1 && choice>=0 && choice<=3,"Value must be one and in range 0 to 3!!");
    if(choice==0)
    {
        *func_num = 0;
    }
    else
    {
        uint16_t num=0;
        printf("Input chage value: ");
        scanf("%hu",&num);
        *((uint16_t*)&(Date)+((uint16_t)choice-1)) = num;
        *func_num = 5;
    }
}

void figure_menu(int32_t choice, uint8_t *func_num)
{
    system("clear");
    puts(FIGURE_MSG);
    CHECK_VALID(scanf("%d", &choice)==1 && choice>=0 && choice<=5,"Value must be one and in range 0 to 5!!");
    if(choice==0)
    {
        *func_num = 0;
    }
    else
    {
        uint16_t num=0;
        printf("Input chage value: ");
        scanf("%hu",&num);
        *((uint16_t*)&(Figure)+((uint16_t)choice-1)) = num;
        *func_num = 6;
    }
}

void (*func_arr[7])(int32_t,uint8_t*) = {topic_menu,attribute_menu,reputation_menu,ablity_menu,performance_menu,date_menu,figure_menu};