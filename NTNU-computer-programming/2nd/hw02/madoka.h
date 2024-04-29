#pragma once

typedef struct
{
    int hp;
    int (*is_dead)(void *this);
} Entity;

typedef struct
{
    Entity base;
    char *name;
    char *wish;
    int kimoji;
    int (*is_dead)(void *this);
    int (*is_despair) (void *this);
    void (*do_wish) (void *this);
    void (*despair) (void *this);
} Shoujo;

typedef void (*Skill) (void *this, void *target);

typedef struct _mhsj Mahoushoujo;
struct _mhsj
{
    Shoujo base;
    int atk;
    int (*is_dead)(void *this);
    void (*do_wish) (void *this);
    void (*attack) (Mahoushoujo *this, Entity *enemy);
    Skill skill;
};


typedef struct _mj Majo;
struct _mj
{
    Shoujo base;
    int atk;
    int (*is_dead)(void *this);
    void (*attack) (Majo *this, Entity *enemy);
    void (*kekkai) (Majo *this, Shoujo *sj);
};

Entity *Entity_ctor(Entity *this);
void Entity_dtor(Entity *this);
int Entity_is_dead(void *this);

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish);
void Shoujo_dtor(Shoujo *this);
int Shoujo_is_despair(void *this);
void Shoujo_do_wish(void *this);
void Shoujo_despair(void *this);

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill);
void Mahoushoujo_dtor(Mahoushoujo *this);
void Mahoushoujo_do_wish(void *this);
void Mahoushoujo_attack(Mahoushoujo *this, void *enemy);
void Mahoushoujo_despair(void *this);

Majo *Majo_ctor(Majo *this, const char *name, const char *wish);
void Majo_dtor(Majo *this);
void Majo_attack(Majo *this, void *enemy);
void Majo_kekkai(Majo *this, Shoujo *sj);
void Majo_despair(void *this);

Majo *mhsj_to_mj(Mahoushoujo *mhsj);

void Madoka_skill(void *this, void *target);
void Homura_skill(void *this, void *target);
void Sayaka_skill(void *this, void *target);
void Kyoko_skill(void *this, void *target);

#include <stdlib.h>
#include <stddef.h>


