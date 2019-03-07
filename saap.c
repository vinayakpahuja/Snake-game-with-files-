 #include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#define r 20
#define c 80
int fx,fy,px,py;
struct node
{
	int x;
	int y;
	char data;
	struct	node *next;
	char food;
};
struct node *head=NULL;
void gotoxy(int x,int y)
{
	COORD f;
	f.X=x;
	f.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),f);
}

struct node* create(int arr[20][80],char n,int m,int p)
{
struct 	node *t;
	t=(struct node *)malloc(sizeof(struct node));
	t->data=n;
	t->x=m;
	t->y=p;
	t->next=NULL;
	arr[t->x][t->y]=t->data;
	return t;
}
void insert(int arr[20][80],char n,int m,int p)
	{

		struct node *temp,*t=head;
		temp=create(arr,n,m,p);
		if(head==NULL)
		{
			
			head=temp;
	
		}
		else
		{
		while(t->next!=NULL)
		{
			t=t->next;
		}
		t->next=temp;
		temp->next=NULL;
	}	
	}
void draw_board(int arr[20][80])
{
	int i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
		
			if(i==0 || j==0 ||i==r-1||j==c-1)
			{
				printf("X");
		
			}
		else printf(" ");
		}
		printf("\n");
	}
}

	void shift(int arr[20][80],int pp,int qq)
	{
		struct node *t=head,*temp;
	temp=create(arr,t->data,pp,qq);
		temp->next=t;
		head=temp;

		temp=temp->next;
		struct node *p;
	
		while(temp->next!=NULL)
		{
			temp->data=temp->next->data;
		
			arr[temp->x][temp->y]=temp->data;
			p=temp;
			temp=temp->next;
		}
		p->next=NULL;
		arr[temp->x][temp->y]=' ';
		temp=NULL;
	}
	void boundary_check()
	{
		struct node *t=head,*temp;
		if(t->x<1)
		{
			t->x=18-t->x;
		}
		else if(t->x>18)
		{
			t->x=1;
		}
		else if(t->y<1)
		{
			t->y=c-2-t->y;
		}
		else if(t->y>78)
		{
			t->y=1;
		}
		
		
		
		
	}
	void food_create(int arr[20][80],int *p,int *q)
	{
		int fx1=*p;
		int fy1=*q;
		struct node *t=head;
		while(t->next!=NULL)
		{
			if(t->x==fx1 || t->y==fy1)
			{
				fx1=rand()%19+1;
				fy1=rand()%79+1;
				t=head;
			}
			t=t->next;
		}
			create(arr,'f',fx1,fy1);
		
		p=fx1;
		q=fy1;
	}
		void poison_create(int arr[20][80],int *p,int *q)
	{
		int px1=*p;
		int py1=*q;
		struct node *t=head;
		while(t->next!=NULL)
		{
			if(t->x==px1 || t->y==py1)
			{
				px1=rand()%19+1;
				py1=rand()%79+1;
				t=head;
			}
			t=t->next;
		}
		create(arr,'p',px1,py1);
		
		p=px1;
		q=py1;
	}
	void food_eat(int arr[20][80],int fx,int fy,int *flag)
	{
		struct node *t=head,*temp;
		*flag=0;
		if(t->x==fx && t->y==fy)
		{
		temp=create(arr,'h',fx,fy);
		temp->next=t;
		head=temp;
		temp->next->data='*';
		*flag=1;
		}
		
	}
	void poison_eat(int arr[20][80],int px,int py,int *flag)
	{
		struct node *t=head,*temp;
		*flag=0;
		if(t->x==px && t->y==py)
		{
			if(t->next->next==NULL)
			{
				exit(0);
			}
		while(t->next->next!=NULL)
		{
			temp=t;
			t=t->next;
			
		}
		t->next->x=t->x;
		t->next->y=t->y;
		temp->next=t->next;
		*flag=1;
		}
		
	}
	void display(int arr[20][80])
	{
		struct node *t=head;
	int i,j;
		
			for(i=1;i<r-1;i++)
			{
				for(j=1;j<c-1;j++)
				{
					arr[i][j]=' ';
				}
			}
			
		
	while(t!=NULL)
	{
		arr[t->x][t->y]=t->data;
		t=t->next;
	}
	arr[px][py]='p';
	arr[fx][fy]='f';
		for(i=1;i<r-1;i++)
		{
			gotoxy(1,5+i);			
			for(j=1;j<c-1;j++)
			{
				printf("%c",arr[i][j]);
			}
		}
		Sleep(0);
	}
int snake_check()
{
	struct node *t=head;
	int p,q,v=0;
	p=t->x;
	q=t->y;
	t=t->next;
	while(t!=NULL)
	{
		if(t->x==p && t->y==q)
		{
			v=1;
			break;
		}
		
	t=t->next;	
	}
return v;	
}


int main()
{
int arr[20][80],i,j,flag,pflag;
int count=0;
char p[100]={'h','*','*','*','t'};   //snake structure
for( i=0;i<r;i++)
{
	for( j=0;j<c;j++)
	{
		arr[i][j]=' ';
		
	}
}
int choice;
draw_board(arr);
gotoxy(25,5);
printf("WELCOME TO SNAKE GAME");
gotoxy(27,7);
printf("1.New game\n");
gotoxy(27,9);
printf("2.Load Game\n");
gotoxy(27,13);
scanf("%d",&choice);
system("cls");
switch(choice)
{

case 1:
	{
	
for(i=3;i<8;i++)
{

	insert(arr,p[i-3],5,i);     //snake insertion using linked lst
}
	fx=(rand()%19)+1;
	 fy=(rand()%79)+1;         //rand function is used to generate random food value
	px=(rand()%19)+1;
		 py=(rand()%79)+1;
break;
	}
	case 2:
		{
			int x,y;
			char z;
			FILE *fp;                                                  //load last time using file handling
			fp=fopen("snakefile.txt","r");
			if(fp==NULL)
			{
				printf("file don't exit");
			}
			fscanf(fp,"%d %d",&x,&y);
			fx=x;
			fy=y;
			fscanf(fp,"%d %d",&x,&y);
			px=x;
			py=y;
			while(fscanf(fp,"%d %d %c",&x,&y,&z)!=EOF)
			{
				insert(arr,z,x,y);
			}
			fclose(fp);
			break;
		}
	}
			food_create(arr,&fx,&fy);
			poison_create(arr,&px,&py);      //poison is used to decrement size of snake 
	printf("enter w to top\n");
	printf("enter s to bottom\n");
	printf("enter a to left\n");
		printf("enter d to right\n");
		printf("ENter p to quit\n");
		draw_board(arr);                        //to display border
		display(arr);
	char ch;
	char key;
	while(ch!='p')
	{
		if(kbhit())                               //used for continuous flow of snake
		{
		ch=getch();
		}
	
	switch(ch)
	{
	
	case 'w':
	{
		struct node *t=head;
		if(key=='s')                                 //key is used to store previous motion of snake;
		{
			ch='s';
			break;
		}
		shift(arr,(t->x)-1,t->y);
		if(snake_check()==1)
		{
		
			exit(0);
		}
	//	system("cls");
	food_eat(arr,fx,fy,&flag);
	
	if(flag==1)
	{
		flag=0;
		fx=(rand()%19)+1;
		fy=(rand()%79)+1;
		food_create(arr,&fx,&fy);
	}
	poison_eat(arr,px,py,&pflag);
		if(pflag==1)
	{
		pflag=0;
		px=(rand()%19)+1;
		py=(rand()%79)+1;
		poison_create(arr,&px,&py);
	}
		boundary_check();
	//1	draw_board(arr);
	display(arr);
	//		printf("ENter choice\n");
//	scanf("\n%c",&ch);
	key=ch;
		break;
	}
	case 's':
		{
			struct node *t=head;
			if(key=='w')
			{
				ch='w';
				break;
			}
			shift(arr,(t->x)+1,t->y);
			if(snake_check()==1 && ch!='w')
		{
			
			exit(0);
		}
	//	system("cls");
			food_eat(arr,fx,fy,&flag);
				if(flag==1)
	{
		flag=0;
		fx=(rand()%19)+1;
		fy=(rand()%79)+1;
		food_create(arr,&fx,&fy);
	}
		poison_eat(arr,px,py,&pflag);
		if(pflag==1)
	{
		pflag=0;
		px=(rand()%19)+1;
		py=(rand()%79)+1;
		poison_create(arr,&px,&py);
	}
			boundary_check(arr);
		//draw_board(arr);
	display(arr);
//			printf("ENter choice\n");
//	scanf("\n%c",&ch);
	key=ch;
		break;
		}
	case 'a':
			{
			struct node *t=head;
			if(key=='d')
		{
			ch='d';
			break;
		}
			shift(arr,(t->x),(t->y)-1);
			if(snake_check()==1)
		{
			
			exit(0);
		}
			//	system("cls");
				food_eat(arr,fx,fy,&flag);
					if(flag==1)
	{
		flag=0;
		fx=(rand()%19)+1;
		fy=(rand()%79)+1;
		food_create(arr,&fx,&fy);
	}
		poison_eat(arr,px,py,&pflag);
		if(pflag==1)
	{
		pflag=0;
		px=(rand()%19)+1;
		py=(rand()%79)+1;
		poison_create(arr,&px,&py);
	}
				boundary_check(arr);
		//draw_board(arr);
	display(arr);
//			printf("ENter choice\n");
//	scanf("\n%c",&ch);
		key=ch;
		break;	
			}
	case 'd':
		{
			struct node *t=head;
			if(key=='a')
		{
			ch='a';
			break;
		}
			shift(arr,(t->x),(t->y)+1);
			if(snake_check()==1)
		{
			
			exit(0);
		}
			//	system("cls");
				food_eat(arr,fx,fy,&flag);
					if(flag==1)
	{
		flag=0;
		fx=(rand()%19)+1;
		fy=(rand()%79)+1;
		food_create(arr,&fx,&fy);
	}
		poison_eat(arr,px,py,&pflag);
		if(pflag==1)
	{
		
		pflag=0;
		px=(rand()%19)+1;
		py=(rand()%79)+1;
		poison_create(arr,&px,&py);
	}
				boundary_check(arr);
		//draw_board(arr);
	display(arr);
//			printf("ENter choice\n");
//	scanf("\n%c",&ch);
	key=ch;
		break;
		}
		default:
		{
			if(ch!='p')
			ch=key;
			break;
		}

	
}
}
struct node *t=head;
			FILE *fp;                //used to store current game before quiting the game;
			fp=fopen("snakefile.txt","w");
			fprintf(fp,"%d %d\n",fx,fy);
			fprintf(fp,"%d %d\n",px,py);          
		
			while(t!=NULL)
			{
			fprintf(fp,"%d %d %c\n",t->x,t->y,t->data);
			t=t->next;
			}
		fclose(fp);


}
