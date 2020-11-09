
#include <stdio.h>

struct nodetype{
	char board [3][3]; // characters allowed are 'X','O',' ' where last one represents empty
	int turn;
	struct nodetype *son;
	struct nodetype *next;
}; typedef struct nodetype *NODEPTR, NODE;

NODEPTR getnode()
{
	NODEPTR new_node = (NODEPTR)malloc(sizeof(NODE));
	return new_node;
}

NODEPTR buildtree(char board[3][3],int depth)
{
	NODEPTR parent_tree;
	int i,j;
	parent_tree = getnode();
    //Attaching the present board to the parent_tree of the tree
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			parent_tree->board[i][j]=board[i][j];
		}
	}

    parent_tree->turn=1;
	parent_tree->son=NULL;
	parent_tree->next=NULL;
	//Calling the main tree building function
	expand(parent_tree,0,depth);
	return parent_tree;
}

void bestmove(char board[3][3],int lookahead,char player)
{
	NODEPTR root, best;
	int i,j;
    //Constructing the tree to the specified depth
	root = buildtree(board,lookahead);
    //Choosing the best branch from the given tree
    int value;
	bestbranch(root,player,&best, &value);

    //Printing the board after the best move is done
	for (i=0;i<3;++i)
	{
	    printf("\n");
		for (j=0;j<3;++j)
		{
			printf("%c | ", best->board[i][j]);
		}
	}
	printf("\n best next state is printed \n");
}

NODEPTR generate(char board[3][3])
{
	// finding the player by no of x's and o's
	int i,j,k,l;
	int c1 = 0;
	int c2 = 0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(board[i][j] == 'X')
				c1++;
			else if(board[i][j] == '0')
				c2++;
			else
				continue;
		}
	}

	//deciding whose chance it is
	char present;
	if(c1 >= c2)
		present = '0';
	else
		present = 'X    ';

	NODEPTR head = NULL;
	NODEPTR list_last = head;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if((board[i][j] == 'X') || (board[i][j] == '0'))
            {
                continue;
            }
			else
			{
				//create new boards (after next move)
				NODEPTR new_node = (NODEPTR)malloc(sizeof(NODE));
				for(k=0;k<3;k++)
				{
					for(l=0;l<3;l++)
					{
						new_node->board[k][l] = board[k][l];
					}
				}
				new_node->board[i][j] = present;

				//adding the newly created structure into the list
				if(head == NULL)
				{
					head = new_node;
					list_last = head;
				}
				else
				{
					list_last->next = new_node;
					list_last = new_node;
				}
			}
		}
	}

	list_last->next = NULL;
	return head;
}

void expand(NODEPTR p,int plevel,int depth)
{
    NODEPTR q;
    if(plevel<depth)
    {
        //generating the next levels possibilities
        q = generate(p->board);

        p->son = q;
        while(q!=NULL)
        {
            q->turn = (-1)*(p->turn);
            q->son=NULL;
            expand(q,plevel+1,depth);
            q=q->next;
        }
    }
}

int evaluate(char brd[3][3],char player){
    int i, j;
    char b[3][3];
    for (i=0;i<3;++i)
    {
        for (j=0;j<3;++j)
            {
                b[i][j]=brd[i][j];
            }
    }
    //char player;
    int row;
    int column;
    char opponent = (player == 'X') ? '0' : 'X', piece;
    char space = ' ';
    int count=0;
    //int row,column;
	//cheking no:of rows open fopr player
    for (row = 0; row<3; row++)
    {
        if (((b[row][0]==player)||(b[row][0]==space)) &&
            ((b[row][1]==player)||(b[row][1]==space)) && ((b[row][2]==player)||(b[row][2]==space)))
        count = count+1;
    }

    // Checking no:of columns open for player
    for (column = 0; column<3; column++)
    {
        if (((b[0][column]==player)||(b[0][column]==space)) &&
            ((b[1][column]==player)||(b[1][column]==space)) && ((b[2][column]==player)||(b[2][column]==space)))
       count = count+1;
    }

    // Checking no:of diagonals open for player
    if (((b[0][0]==player)||(b[0][0]==space)) &&
            ((b[1][1]==player)||(b[1][1]==space)) && ((b[2][2]==player)||(b[2][2]==space)))
       count = count+1;

    if (((b[0][2]==player)||(b[0][2]==space)) &&
            ((b[1][1]==player)||(b[1][1]==space)) && ((b[2][0]==player)||(b[2][0]==space)))
       count = count+1;

 int count1=0;
 //cheking no:of rows open for opp
        for (row = 0; row<3; row++)
    {
        if (((b[row][0]==opponent)||(b[row][0]==space)) &&
            ((b[row][1]==opponent)||(b[row][1]==space)) && ((b[row][2]==opponent)||(b[row][2]==space)))
        count1 = count1+1;
    }

    // Checking no:of columns open for player
    for (column = 0; column<3; column++)
    {
        if (((b[0][column]==opponent)||(b[0][column]==space)) &&
            ((b[1][column]==opponent)||(b[1][column]==space)) && ((b[2][column]==opponent)||(b[2][column]==space)))
       count1 = count1+1;
    }

    // Checking no:of diagonals open for player
    if (((b[0][0]==opponent)||(b[0][0]==space)) &&
        ((b[1][1]==opponent)||(b[1][1]==space)) && ((b[2][2]==opponent)||(b[2][2]==space)))
       count1 = count1+1;

    if (((b[0][2]==opponent)||(b[0][2]==space)) &&
        ((b[1][1]==opponent)||(b[1][1]==space)) && ((b[2][0]==opponent)||(b[2][0]==space)))
       count1 = count+1;
       int eval;
       eval=count-count1;
    // Else if none of them have won then return 0
     //printf("eval is %d",eval);
     return(eval);
}

void bestbranch(NODEPTR pnd,char player,NODEPTR* pbest, int* pvalue)
{
NODEPTR p,*pbest2;
int val;
if (pnd->son==NULL)
{
	*pvalue=evaluate(pnd->board,player);
	*pbest=pnd;
}
else {
	p=pnd->son;
	bestbranch(p,player,pbest,pvalue);
	*pbest=p;
	if(pnd->turn==-1)
	*pvalue=-*pvalue;
	p=p->next;
	while (p!=NULL){
		bestbranch(p,player,&pbest2,&val);
		if(pnd->turn==-1)
		val=-val;
		if (val>*pvalue){
			*pvalue=val;
			*pbest=p;
		}
		p=p->next;
	}
	if(pnd->turn==-1)
	*pvalue=-*pvalue;
}
}

int main(void) {

    int lookahead = 3; //lookahead to be considered

    printf("\n Written code takes a current board state as input and returns best possible move as output \n");
    char board [3][3];
    int i,j;
    printf("Enter board values(X/0/<space>) row wise \n");
    for (i=0;i<3;++i)
    {printf("\n");
        for (j=0;j<3;++j)
        {
            scanf("%c",&board[i][j]);
            printf("%c |",board[i][j]);
        }
    }
printf("\n input board is printed \n");
    //finding the nest player
    int x_no=0;
    int o_no=0;
    for (i=0;i<3;++i)
    {
        for (j=0;j<3;++j)
        {
            if (board[i][j]=='X')
                x_no++;
            else if (board[i][j]=='0')
                o_no++;
        }
    }
printf("%d %d",x_no,o_no);
    char player;
    if(abs(x_no-o_no)>1)
    {
        printf("\n incorrect input .. ending \n");
        return(1);
    }
    else
    {
        printf("\n valid input entered \n");
    if (x_no >= o_no)
        player ='0';
    else
        player ='X';
    }
    //calling the main function
    bestmove(board,lookahead,player);
    return 0;
}



