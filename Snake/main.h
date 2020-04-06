#include <iostream>
#include <conio.h>

using namespace std;

namespace Snake
{	
	class Engine
	{
	public:
		
		std::string GetOS(){

			#ifdef _WIN32
			return "windows";
			#elif __unix || __unix__
			return "unix";
			#endif
		
		}
		
		const int MapWidth = 40;
		const int MapHeight = 20;
		
		int x,y, fruitPosX, fruitPosY, score;
		int tailX[100], tailY[100];
		int tailLength = 0;
		
		enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
		eDirection dir;
		
		bool gameOver;
		bool debug;
		
		void Setup()
		{
			gameOver = false;
			dir = STOP;
			x = MapWidth/2;
			y = MapHeight/2;
			
			fruitPosX = rand() % MapWidth;
			fruitPosY = rand() % MapHeight;
			score = 0;
			
			debug = true;
		}
		
		void Draw()
		{	
			if(GetOS() == "unix")
			{
				system("clear"); //clears screen each frame
			}
			else if(GetOS() == "windows")
			{
				system("clr");
			}
			//draws map
			for(int i = 0; i<MapWidth; i++) //draws top
				{
					printf("#");
				}
			cout<<endl;
			
			for(int i = 0; i<MapHeight; i++) //draws walls, blankspaces and gameObjects
				{
					for(int j = 0; j<MapWidth; j++)
					{
						if(j == 0) //Walls
						{
							printf("#");
						}
						if(i == y && j == x) //Player Head
						{
							printf("O");
						}
						else if(i == fruitPosY && j == fruitPosX) //Fruit
						{
							printf("F");
						}
						else
						{	
							bool printed = false;
							for(int k = 0; k < tailLength; k++)
							{	
								
								if(tailX[k] == j && tailY[k] == i)
								{
									printf("o");
									printed = true;
								}
								
							}
							if(!printed) //blankspaces
							{
								printf(" ");
							}
						}
						
						if(j == MapWidth - 1) //Walls
						{
							printf("#");
						}
					}
					cout<<endl;
				}
				
			for(int i = 0; i<MapWidth; i++) //draws bottom
				{
					printf("#");
				}
			cout<<endl;
			cout<<"Score: "<<score<<endl;
			if(debug)
			{
				cout<<"--debug--"<<endl;
				cout<<"TailLength: "<<tailLength<<endl;
				cout<<"xPos: "<<x<<endl;
				cout<<"yPos: "<<y<<endl;
			}
			
			
			
		}
		
		void Input()
		{
			if(_kbhit())
			{
				switch(_getche()) //setting direction
				{
					case 'a':
						dir = LEFT;
						break;
					case 'd':
						dir = RIGHT;
						break;
					case 'w':
						dir = UP;
						break;
					case 's':
						dir = DOWN;
						break;
						//Exits game
					case 'x':
						death();
						break;
				}
			}
		}
		
		void Logic()
		{	
			int prevX = tailX[0];
			int prevY = tailY[0];
			int prev2X, prev2Y;
			tailX[0] = x;
			tailY[0] = y;
			
			for(int i = 1; i < tailLength; i++)
			{
				prev2X = tailX[i];
				prev2Y = tailY[i];
				tailX[i] = prevX;
				tailY[i] = prevY;
				prevX = prev2X;
				prevY = prev2Y;
			}
			
			switch(dir) //Movement
			{
				case LEFT:
					x -= 1;
					break;
				case RIGHT:
					x += 1;
					break;
				case UP:
					usleep(5000);
					y -= 1;
					break;
				case DOWN:
					usleep(5000);
					y += 1;
					break;
				default:
					break;
			}
			
			if(x > MapWidth || x < 0|| y > MapHeight || y < 0)
			{
				death();
			}
			for(int i = 0; i<tailLength; i++)
			{
				if(tailX[i] == x && tailY[i] == y)
				{
					death();
				}
			}
			
			if(x == fruitPosX && y == fruitPosY)
			{	
				tailLength++;
				score += 10;
				fruitPosX = rand() % MapWidth;
				fruitPosY = rand() % MapHeight;
			}
		}
		
		void death()
		{
			gameOver = true;
		}
		
	};
}