#pragma once
#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define LH 1
#define EH 0
#define RH -1

/*
    Æ½ºâ¶ş²æÊ÷(²åÈë)
*/

typedef struct bi_tree BiTree;

struct bi_tree
{
    int data;
    int bf;
    BiTree* l_child;
    BiTree* r_child;
};