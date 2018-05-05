#define _CRT_SECURE_NO_WARNINGS
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
#include <easyx.h>
#include <string>
#include <numeric>
#include <fstream>
using namespace std;


#define WIDTH 950
#define HEIGHT 540

#define  UP    72
#define  DOWN  80
#define  LEFT  75
#define  RIGHT 77
#define  SPACE 32

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

//��ʾ��������ť
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

//ϵͳ��ʼ��
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
	outtextxy(GAME_WIDTH + 10, HEIGHT * 0.5 + 20, "Name: ");
	outtextxy(GAME_WIDTH + 60, HEIGHT * 0.5 + 20, user.name);
	outtextxy(GAME_WIDTH + 10, HEIGHT * 0.55 + 20, "Score: ");
}

//��ⰴ��
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

//�ж϶�Ӧ�����Ƿ��й�ͷ��true�����У�false������
boolean isBoneExists(int zone, map<int, boolean> statusMap)
{
	map<int, boolean>::iterator iter;
	boolean result = false;
	//����ÿ�������Ƿ��й�ͷ
	for (iter = statusMap.begin(); iter != statusMap.end(); iter++)
	{
		if (zone == iter->first)
		{
			if (iter->second)
			{
				result = true;
				break;
			}
			else
			{
				result = false;
				break;
			}
		}
	}

	return result;
}

//��ʾС����
void displayDog(Dog dog, IMAGE back,map<int,boolean> statusMap, int &delTag, IMAGE p1, IMAGE p2)
{
	BeginBatchDraw();//��ʼ������ͼ
	putimage(0, 0, &back);

	setbkmode(TRANSPARENT);

	//����1
	if (dog.x>=90 && dog.x<=130 && dog.y>=200 && dog.y<=250)
	{
		if (isBoneExists(1, statusMap))
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			delTag = 1;
		}
		else
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			putimage(dog.x, dog.y, &p2, SRCINVERT);
		}
	}
	//����2
	else if (dog.x >= 340 && dog.x <= 380 && dog.y >= 200 && dog.y <= 250)
	{
		if (isBoneExists(2, statusMap))
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			delTag = 2;
		}
		else
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			putimage(dog.x, dog.y, &p2, SRCINVERT);
		}
	}
	//����3
	else if (dog.x >= 580 && dog.x <= 620 && dog.y >= 200 && dog.y <= 250)
	{
		if (isBoneExists(3, statusMap))
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			delTag = 3;
		}
		else
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			putimage(dog.x, dog.y, &p2, SRCINVERT);
		}
	}
	//����4
	else if (dog.x>=90 && dog.x<=130 && dog.y>=330 && dog.y<=380)
	{
		if (isBoneExists(4, statusMap))
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			delTag = 4;
		}
		else
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			putimage(dog.x, dog.y, &p2, SRCINVERT);
		}
	}
	//����5
	else if (dog.x >= 340 && dog.x <= 380 && dog.y >= 330 && dog.y <= 380)
	{
		if (isBoneExists(5, statusMap))
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			delTag = 5;
		}
		else
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			putimage(dog.x, dog.y, &p2, SRCINVERT);
		}
	}
	//����6
	else if (dog.x >= 580 && dog.x <= 620 && dog.y >= 330 && dog.y <= 380)
	{
		if (isBoneExists(6, statusMap))
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			delTag = 6;
		}
		else
		{
			putimage(dog.x, dog.y, &p1, SRCAND);
			putimage(dog.x, dog.y, &p2, SRCINVERT);
		}
	}

	//�Ƕ�������
	else
	{
		putimage(dog.x, dog.y, &p1, SRCAND);
		putimage(dog.x, dog.y, &p2, SRCINVERT);
		delTag = 0;
	}

	EndBatchDraw();//����������ͼ�������ƺõ�ͼƬͳһ������Ļ�ϡ�	
}

//ˮƽ�����ƶ�С��
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

//��ֱ�����ƶ�С��
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

//����ͷ�ڵ�
Bone* create_head(int n1, int n2)
{
	Bone *head = (Bone *)malloc(sizeof(Bone));
	head->x = n1;
	head->y = n2;
	head->next = nullptr;
	return head;
}

//�����ڵ�
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

//ɾ���ڵ�
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

//�ͷ��ڴ�,��ֹ�ڴ�й¶
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

//��ʾ���й�ͷ
void displayAllBones(Bone *head, map<int,boolean> statusMap, IMAGE b1, IMAGE b2, IMAGE b3)
{
	Bone *p;
	p = head;
	BeginBatchDraw();//��ʼ������ͼ
	

	for (int i = 0; i < statusMap.size(); i++)
	{
		if (statusMap[i])
		{
			switch (i)
			{
			case 1:
			{
				putimage(110, 230, &b1, SRCAND);

				putimage(110, 230, &b2, SRCINVERT);
			}break;

			case 2:
			{
				putimage(360, 230, &b1, SRCAND);

				putimage(360, 230, &b2, SRCINVERT);
			}break;

			case 3:
			{
				putimage(600, 230, &b1, SRCAND);

				putimage(600, 230, &b2, SRCINVERT);
			}break;

			case 4:
			{
				putimage(110, 360, &b1, SRCAND);

				putimage(110, 360, &b2, SRCINVERT);
			}break;

			case 5:
			{
				putimage(360, 360, &b1, SRCAND);

				putimage(360, 360, &b2, SRCINVERT);
			}break;

			case 6:
			{
				putimage(600, 360, &b1, SRCAND);

				putimage(600, 360, &b2, SRCINVERT);
			}break;

			default:break;
			}
		}
	}

	FlushBatchDraw();
	EndBatchDraw();
}

//��ʾָ���Ĺ�ͷ
void displayBone(IMAGE b1, IMAGE b2, IMAGE b3,int count) 
{
	BeginBatchDraw();//��ʼ������ͼ
	switch (count)
	{
	case 1:
	{
		putimage(110, 230, &b1, SRCAND);

		putimage(110, 230, &b2, SRCINVERT);
	}break;

	case 2:
	{
		putimage(360, 230, &b1, SRCAND);

		putimage(360, 230, &b2, SRCINVERT);
	}break;

	case 3:
	{
		putimage(600, 230, &b1, SRCAND);

		putimage(600, 230, &b2, SRCINVERT);
	}break;

	case 4:
	{
		putimage(110, 360, &b1, SRCAND);

		putimage(110, 360, &b2, SRCINVERT);
	}break;

	case 5:
	{
		putimage(360, 360, &b1, SRCAND);

		putimage(360, 360, &b2, SRCINVERT);
	}break;

	case 6:
	{
		putimage(600, 360, &b1, SRCAND);

		putimage(600, 360, &b2, SRCINVERT);
	}break;

	default:break;
	}
	FlushBatchDraw();
	EndBatchDraw();//����������ͼ�������ƺõ�ͼƬͳһ������Ļ�ϡ�
}

//��ӹ�ͷ
void add_bone(Bone *head, int tag, int &count, map<int,boolean> &statusMap)
{
	switch (tag)
	{
		case 1:
		{
			count = tag;
			statusMap[tag] = true;
		}break;

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

//ɾ�������ӵĹ�ͷ
void deleteBone(Bone *head, int count, map<int, boolean> &statusMap)
{
	switch (count)
	{
		case 1:
		{
			//MessageBox(nullptr, "����ɾ����һ����ͷ", "����", MB_OK + 48);
			statusMap[count] = false;
		}break;

		case 2:
		{
			del_node(head, 360, 230);
			statusMap[count] = false;
		}break;

		case 3:
		{
			del_node(head, 600, 230);
			statusMap[count] = false;
		}break;

		case 4:
		{
			del_node(head, 110, 360);
			statusMap[count] = false;
		}break;

		case 5:
		{
			del_node(head, 360, 360);
			statusMap[count] = false;
		}break;

		case 6:
		{
			del_node(head, 600, 360);
			statusMap[count] = false;
		}break;

		default:
			break;
	}
}

//���ҵ���ͷ��������ɾ��
void deleteBoneByDog(Bone *head, int delTag, map<int, boolean> &statusMap)
{
	switch (delTag)
	{
	case 1:
	{
		//MessageBox(nullptr, "����ɾ����һ����ͷ", "����", MB_OK + 48);
		statusMap[delTag] = false;
	}break;

	case 2:
	{
		del_node(head, 360, 230);
		statusMap[delTag] = false;
	}break;

	case 3:
	{
		del_node(head, 600, 230);
		statusMap[delTag] = false;
	}break;

	case 4:
	{
		del_node(head, 110, 360);
		statusMap[delTag] = false;
	}break;

	case 5:
	{
		del_node(head, 360, 360);
		statusMap[delTag] = false;
	}break;

	case 6:
	{
		del_node(head, 600, 360);
		statusMap[delTag] = false;
	}break;

	default:
		break;
	}
}

//���÷���Ϣ���û���������info.ini�ļ���
void saveToFile(TCHAR *name,TCHAR *totalScore)
{
	ofstream outFile("info.ini", ios::out);

	//�����ʧ��,outfile����ֵ
	if (!outFile)                        
	{
		cout << "open error!" << endl;
		exit(1);
	}

	//������ļ�"info.ini"�������
	outFile << "Name: "<<name<<endl<<"Total score: "<<totalScore<<endl;
	        
	outFile.close();
}

//������Ϸ
void gameOver(User user,TCHAR *totalScore)
{
	saveToFile(user.name, totalScore);
	exit(0);
}

int main()
{
	int mouseX;	        //���λ������X
	int mouseY;
	MOUSEMSG mmsg;	    //�����Ϣ����
	int flag = -1, step = 1, count = 1;
	char c = 0;
	int tag=1;
	int delTag = 0;
	double location = 0.05;
	User user;
	user.score = 0;
	Bone *head;
	Dog dog = {10,400};
	init(user, dog);
	IMAGE back, p1, p2, b1, b2, b3;
	map<int, boolean> statusMap;
	statusMap[1] = true;
	TCHAR scoreNum[10];
	head = create_head(110, 230);

	loadimage(&back,"image\\background.jpg");
	loadimage(&p1,"image\\dog02.jpg");
	loadimage(&p2,"image\\dog01.jpg");
	loadimage(&b1,"image\\bone02.jpg");
	loadimage(&b2,"image\\bone01.jpg");
	loadimage(&b3,"image\\bone03.jpg");
	displayDog(dog, back, statusMap, delTag, p1, p2);

	Util util;


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
				displayDog(dog, back, statusMap, delTag, p1, p2);
			}
			if(c==LEFT) 
			{
				moveDogx(dog,-1);
				displayDog(dog, back, statusMap, delTag, p1, p2);
			}
			if(c==UP)
			{
				moveDogy(dog,-1);
				displayDog(dog, back, statusMap, delTag, p1, p2);
			}
			if(c==DOWN)
			{
				moveDogy(dog,1);
				displayDog(dog, back, statusMap, delTag, p1, p2);
			}
			if(c==SPACE)
			{
				if (delTag != 0)
				{
					if (statusMap[delTag])
					{
						displayBone(b1, b2, b3, delTag);
						deleteBoneByDog(head, delTag, statusMap);

						_itoa(++user.score, scoreNum, 10);

						if (user.score == 1)
						{
							outtextxy(GAME_WIDTH + 60, HEIGHT * 0.55 + 20, scoreNum);
						}
						else
						{
							location += 0.05;
							outtextxy(GAME_WIDTH + 60, HEIGHT * (0.55 + location) + 20, scoreNum);
						}
					}
					else
					{
						MessageBox(nullptr, "�ö����޹�ͷ�����ظ�����!", "����", MB_OK + 48);
					}
				}	
			}
			c = 0;
		}
			
		if(flag==1)
		{
			step++;
			if(step % 2 == 0)
			{
				displayAllBones(head, statusMap, b1, b2, b3);
				flag = -1;
			}
			else
			{
				displayDog(dog, back, statusMap, delTag, p1, p2);
				flag = -1;
			}
		}
		else if(flag==2)
		{
			tag = util.getRandomNumber(1, 6);

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
			map<int, boolean>::iterator iter;
			for (iter = statusMap.begin(); iter != statusMap.end(); iter++)
			{
				int key = iter->first;
				boolean val = iter->second;

				if (key == count)
				{
					//�����ͷ�Ѿ���ɾ��
					if (!val)
					{
						MessageBox(nullptr, "�ù�ͷ��ɾ�������ظ�����!", "����", MB_OK + 48);
						break;
					}
					else
					{
						deleteBone(head, count, statusMap);
						break;
					}
				}
			}
			
			flag = -1;
		}
		else if(flag==4)
		{
			gameOver(user,scoreNum);
		}
	}
	_getch();
	return 0;
}




