#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <random>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <map>
#include <Windows.h>
#include <mmsystem.h>
using namespace std;

#pragma comment(lib,"Winmm.lib")


#define WIDTH 950
#define HEIGHT 540

#define  UP    72
#define  DOWN  80
#define  LEFT  75
#define  RIGHT 77
#define  SPACE 20

#define GAME_WIDTH (WIDTH*85/100)

//�û���
class User
{
public:
	char name[20];
	int score;
};

//С������
class Dog
{
public:
	int x;
	int y;
};

//��ͷ��
class Bone
{
public:
	int x;
	int y;
	Bone *next;
};

//��ȡ�����������
class Util
{
public:
	int getRandomNumber(int start, int end)
	{
		default_random_engine engine(time(nullptr));
		uniform_int_distribution<unsigned> uniform(start, end);

		return uniform(engine);
	}
};

void displayButton()
{
	setfillcolor(RGB(255, 255, 100));

	setbkmode(TRANSPARENT);

	fillrectangle(GAME_WIDTH + 40, 20, GAME_WIDTH + 100, 50);
	outtextxy(GAME_WIDTH + 50, 30, "��/��");

	fillrectangle(GAME_WIDTH + 40, 70, GAME_WIDTH + 100, 100);
	outtextxy(GAME_WIDTH + 50, 80, "����");

	fillrectangle(GAME_WIDTH + 40, 120, GAME_WIDTH + 100, 150);
	outtextxy(GAME_WIDTH + 50, 130, "ɾ��");

	fillrectangle(GAME_WIDTH + 40, 170, GAME_WIDTH + 100, 200);
	outtextxy(GAME_WIDTH + 50, 180, "�˳�");

}

void init(User &user, Dog dog)
{
	initgraph(WIDTH, HEIGHT);  //�����С
	setbkcolor(WHITE);         //����ɫ
	cleardevice();             //����
	setcolor(BLACK);             //����ɫ
	setlinestyle(PS_SOLID, 2);
	rectangle(1, 1, WIDTH - 1, HEIGHT - 1);  //�������

	line(GAME_WIDTH + 1, 0, GAME_WIDTH + 1, HEIGHT);
	line(GAME_WIDTH, HEIGHT * 1 / 2, WIDTH, HEIGHT * 1 / 2);

	displayButton();
	InputBox(user.name, 20, "�������û�����");
	outtextxy(GAME_WIDTH + 10, HEIGHT * 1 / 2 + 20, "Name: ");
	outtextxy(GAME_WIDTH + 60, HEIGHT * 1 / 2 + 20, user.name);

}

int checkButton(int mouseX, int mouseY)
{
	if (mouseX >= GAME_WIDTH + 40 && mouseX <= GAME_WIDTH + 100 && mouseY >= 20 && mouseY <= 50)
	{
		return 1;
	}
	else if (mouseX >= GAME_WIDTH + 40 && mouseX <= GAME_WIDTH + 100 && mouseY >= 70 && mouseY <= 100)
	{
		return 2;
	}
	else if (mouseX >= GAME_WIDTH + 40 && mouseX <= GAME_WIDTH + 100 && mouseY >= 120 && mouseY <= 150)
	{
		return 3;
	}

	else if (mouseX >= GAME_WIDTH + 40 && mouseX <= GAME_WIDTH + 100 && mouseY >= 170 && mouseY <= 200)
	{
		return 4;
	}
	
	else
	{
		return -1;
	}
}

void displayDog(Dog dog, IMAGE back, IMAGE p1, IMAGE p2)
{
	BeginBatchDraw();//��ʼ������ͼ
	putimage(0, 0, &back);
	putimage(dog.x, dog.y, &p1, SRCAND);
	putimage(dog.x, dog.y, &p2, SRCINVERT);
	EndBatchDraw();//����������ͼ�������ƺõ�ͼƬͳһ������Ļ�ϡ�	
}

void moveDogx(Dog &dog, int k)
{
	if (dog.x >= 10 && dog.x <= 650)
	{
		dog.x += k * 3;
	}
	else if (dog.x < 10)
	{
		dog.x = 10;
	}
	else
	{
		dog.x = 650;
	}
}

void moveDogy(Dog &dog, int k)
{
	if (dog.y >= 0 && dog.y <= 400)
	{
		dog.y += k * 3;
	}
	else if (dog.y < 0)
	{
		dog.y = 0;
	}
	else
	{
		dog.y = 400;
	}
}

Bone* create_head(int n1, int n2)
{
	Bone *head = (Bone *)malloc(sizeof(Bone));
	head->x = n1;
	head->y = n2;
	head->next = nullptr;
	return head;
}

void create_node(Bone *head, int n1, int n2)
{
	Bone *p, *t;
	p = (Bone *)malloc(sizeof(Bone));
	p->x = n1;
	p->y = n2;
	p->next = nullptr;
	t = head;
	while (t->next != nullptr)
	{
		t = t->next;
	}
	t->next = p;
}

void del_node(Bone *head, int n1, int n2)
{
	Bone *p, *t;
	p = head;
	t = head;
	while (p->x != n1 || p->y != n2)
	{
		t = p;
		p = p->next;
		if (p == nullptr)
		{
			break;
		}
	}
	if (p != nullptr)
	{
		if (p != head)
		{
			t->next = p->next;
			free(p);
		}
	}
}

void free_Bone(Bone *head)
{
	Bone *p;
	while (head != nullptr)
	{
		p = head;
		head = head->next;
		free(p);
	}
}

void displayBone(Bone *head, IMAGE b1, IMAGE b2, IMAGE b3, int k) {
	Bone *p;
	p = head;
	BeginBatchDraw();//��ʼ������ͼ
	while (p != nullptr)
	{

		if (p->x == 110 || p->x == 360)
		{

			putimage(p->x, p->y, &b1, SRCAND);

			putimage(p->x, p->y, &b2, SRCINVERT);
		}
		else
		{

			putimage(p->x, p->y, &b1, SRCAND);

			putimage(p->x, p->y, &b2, SRCINVERT);
		}


		p = p->next;
	}
	FlushBatchDraw();
	EndBatchDraw();//����������ͼ�������ƺõ�ͼƬͳһ������Ļ�ϡ�
}

void add_bone(Bone *head, int tag, int &count, map<int,boolean> &statusMap)
{
	switch (tag)
	{
		case 2:
		{
			create_node(head, 360, 230);
			count = tag;
			statusMap[tag] = true;
		}break;

		case 3:
		{
			create_node(head, 600, 230);
			count = tag;
			statusMap[tag] = true;
		}break;

		case 4:
		{
			create_node(head, 110, 360);
			count = tag;
			statusMap[tag] = true;
		}break;

		case 5:
		{
			create_node(head, 360, 360);
			count = tag;
			statusMap[tag] = true;
		}break;

		case 6:
		{
			create_node(head, 600, 360);
			count = tag;
			statusMap[tag] = true;
		}break;
	}
}

void deleteBone(Bone *head, int &count, map<int, boolean> &statusMap)
{
	switch (count)
	{
		case 1:
		{
			MessageBox(nullptr, "����ɾ����һ����ͷ", "����", MB_OK + 48);
		}break;

		case 2:
		{
			del_node(head, 360, 230); count--;
			statusMap[count] = false;
		}break;

		case 3:
		{
			del_node(head, 600, 230); count--;
			statusMap[count] = false;
		}break;

		case 4:
		{
			del_node(head, 110, 360); count--;
			statusMap[count] = false;
		}break;

		case 5:
		{
			del_node(head, 360, 360); count--;
			statusMap[count] = false;
		}break;

		case 6:
		{
			del_node(head, 600, 360); count--;
			statusMap[count] = false;
		}break;

		default:
			break;
	}
}

void gameOver()
{
	exit(0);
}

int main()
{
	int mouseX;	        //���λ������X
	int mouseY;
	MOUSEMSG mmsg;	    //�����Ϣ����
	int flag = -1, step = 1, count = 1;
	char c = 0, d = 0;
	int tag=1;
	User user;
	Bone *head;
	Bone *head2;
	Dog dog = {10,400};
	init(user, dog);
	IMAGE back, p1, p2, b1, b2, b3;
	map<int, boolean> statusMap;
	head = create_head(110, 230);

	loadimage(&back,"image\\background.jpg");
	loadimage(&p1,"image\\dog02.jpg");
	loadimage(&p2,"image\\dog01.jpg");
	loadimage(&b1,"image\\bone02.jpg");
	loadimage(&b2,"image\\bone01.jpg");
	loadimage(&b3,"image\\bone03.jpg");
	displayDog(dog, back, p1, p2);

	Util util;

	// ������
	mciSendString("open Innocence.mp3 play Innocence.mp3 repeat", NULL, 0, NULL);

	mciSendString("play mymusic", NULL, 0, NULL);

	while(1)
	{
		if(MouseHit())
		{	
			mmsg = GetMouseMsg();
			switch(mmsg.uMsg)
			{
				case WM_LBUTTONDOWN:
					mouseX = mmsg.x; 
				    mouseY = mmsg.y;    //ȡ�����x,yֵ
					
				//����ڰ�ť��
				if(mouseX > GAME_WIDTH && mouseX<=WIDTH && mouseY>0&& mouseY<=HEIGHT)
				{
					flag = checkButton(mouseX,mouseY);
				}	
			}              
		}
		if(_kbhit())
		{
			if (_getch() == 0xE0)
			{
				c = _getch();
			}
			else
			{
				c = _getch();
			}

			if(c==RIGHT) 
			{
				moveDogx(dog,1);
				displayDog(dog, back, p1, p2);
			}
			if(c==LEFT) 
			{
				moveDogx(dog,-1);
				displayDog(dog, back, p1, p2);
			}
			if(c==UP)
			{
				moveDogy(dog,-1);
				displayDog(dog, back, p1, p2);
			}
			if(c==DOWN)
			{
				moveDogy(dog,1);
				displayDog(dog, back, p1, p2);
			}
			if(c==SPACE)
			{
			}
			c = 0;
		}
			
		if(flag==1)
		{
			step++;
			if(step % 2 == 0)
			{
			displayBone(head, b1, b2, b3, count);
			flag = -1;
			}
			else
			{
			displayDog(dog, back, p1, p2);
			flag = -1;
			}
		}
		else if(flag==2)
		{
			tag = util.getRandomNumber(2, 6);

			//������tag���ڣ�˵���ö����Ѿ��й�ͷ,��֮û�й�ͷ
			if (statusMap.count(tag)==0 || statusMap[tag]==false)
			{
				add_bone(head, tag, count, statusMap);
				flag = -1;
			}
			else if(statusMap.count(tag)==1)
			{
				MessageBox(nullptr, "��Ǹ���ö����Ѿ��й�ͷ", "��ʾ", MB_OK+64);
				flag = -1;
			}
		}
		else if(flag==3)
		{
			deleteBone(head, count, statusMap);
			flag = -1;
		}
		else if(flag==4)
		{
			gameOver();
		}
	}
	_getch();
	return 0;
}




