#define _CRT_SECURE_NO_WARNINGS
#include "balance_binary_tree.h"

void L_rotate(BiTree** biTree)
{
    BiTree* R = (*biTree)->r_child;
    BiTree* RL;
	if (R->l_child != NULL && R->r_child == NULL)
	{
        RL = R->l_child;
        RL->bf = R->bf = EH;
        if ((*biTree)->l_child != NULL)
            (*biTree)->bf = LH;
        else
            (*biTree)->bf = EH;
		(*biTree)->r_child = NULL;
		RL->r_child = R;
		RL->l_child = (*biTree);
		R->l_child = NULL;
		(*biTree) = RL;
		return;
	}
    if (R->l_child != NULL)
    {
        (*biTree)->bf = EH;
        (*biTree)->r_child = R->l_child;
    }
    else
    {
        (*biTree)->bf = ((*biTree)->l_child == NULL) ? EH : LH;
        (*biTree)->r_child = NULL;
    }
    R->bf = EH;
	R->l_child = (*biTree);
	(*biTree) = R;
}

void R_rotate(BiTree** biTree)
{
    BiTree* L = (*biTree)->l_child;
    BiTree* LR;
	if (L->r_child != NULL && L->l_child == NULL)
    {
        LR = L->r_child;
        LR->bf = L->bf = EH;
        if ((*biTree)->r_child != NULL)
            (*biTree)->bf = RH;
        else
            (*biTree)->bf = EH;
		(*biTree)->l_child = NULL;
		LR->l_child = L;
		LR->r_child = (*biTree);
		L->r_child = NULL;
		(*biTree) = LR;
		return;
	}
    if (L->r_child != NULL)
    {
        (*biTree)->bf = EH;
        (*biTree)->l_child = L->r_child;
    }
	else
	{
		(*biTree)->bf = ((*biTree)->r_child == NULL) ? EH : RH;
		(*biTree)->l_child = NULL;
	}
    L->bf = EH;
	L->r_child = (*biTree);
	(*biTree) = L;
}

void left_adjust(BiTree** biTree)
{
    BiTree* L = (*biTree)->l_child;
	switch (L->bf)
	{
	case LH:
		R_rotate(biTree);
		break;
	case RH:
        L_rotate(&(*biTree)->l_child);
        R_rotate(biTree);
	default:
		break;
	}
	
}

void right_adjust(BiTree** biTree)
{
    BiTree* R = (*biTree)->r_child;
    switch (R->bf)
    {
    case RH:
        L_rotate(biTree);
        break;
    case LH:
        R_rotate(&(*biTree)->r_child);
        L_rotate(biTree);
    default:
        break;
    }
}

int insert_node(BiTree** biTree, int data, int* grow)
{
    if (*biTree == NULL)
    {
        *biTree = (BiTree*)malloc(sizeof(BiTree));
        (*biTree)->bf = EH;
        (*biTree)->data = data;
        (*biTree)->l_child = NULL;
        (*biTree)->r_child = NULL;
        (*grow) = 1;
        return TRUE;
    }
    if ((*biTree)->data == data)
    {
        return FALSE;
    }
    if (data < (*biTree)->data)
    {
        if (!insert_node(&(*biTree)->l_child, data, grow))
        {
            return FALSE;
        }
        else
        {
            if (*grow)
            {
                switch ((*biTree)->bf)
                {
                case LH:
                    left_adjust(biTree);
                    (*grow) = 0;
                    break;
                case EH:
                    (*biTree)->bf = LH;
                    (*grow) = 1;
                    break;
                case RH:
                    (*biTree)->bf = EH;
                    (*grow) = 0;
                    break;
                }
            }

        }
    }
    else
    {
        if (!insert_node(&(*biTree)->r_child, data, grow))
        {
            return FALSE;
        }
        else
        {
            if (*grow)
            {
                switch ((*biTree)->bf)
                {
                case LH:
                    (*biTree)->bf = EH;
                    (*grow) = 0;
                    break;
                case EH:
                    (*biTree)->bf = RH;
                    (*grow) = 1;
                    break;
                case RH:
                    right_adjust(biTree);
                    (*grow) = 0;
                    break;
                }
            }

        }
    }
}

void print(BiTree* b)
{
	if (b == NULL)
		return;
	print(b->l_child);
	printf("%d ", b->data);
	print(b->r_child);
}

static void FREE(BiTree* biTree)
{
    if (biTree == NULL)
        return;
    FREE(biTree->l_child);
    FREE(biTree->r_child);
    free(biTree);
}


int main(void)
{
    BiTree* biTree = NULL;
    int data;
    int grow = 1;
    while (1)
    {
        printf("请输入节点数字,按-1结束\n"); 
        scanf("%d", &data);
        if (data == -1)
        {
            break;
        }
        insert_node(&biTree, data, &grow);
    }
    print(biTree);
    FREE(biTree);
    return 0;
}