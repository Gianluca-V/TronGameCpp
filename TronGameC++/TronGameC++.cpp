#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime> 
using namespace std;

bool GameOver;
const int WIDTH = 85;
const int HEIGHT = 20;
int PlayerX, PlayerY;
int Player2X, Player2Y;
int TailX[10000], TailY[10000];
int Tail2X[10000], Tail2Y[10000];
int NTails;
int NTails2;
enum EDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
EDirection Dir;
EDirection Dir2;
bool PlayerWin;
bool BothWin;


void Setup()
{
	PlayerWin = false;
	BothWin = false;
	GameOver = false;
	Dir = STOP;
	Dir2 = STOP;

	PlayerX = 60;
	PlayerY = HEIGHT-2;

	Player2X = 30;
	Player2Y = 2;

	NTails = 0;
	NTails2 = 0;
	system("color 9");
}

void Draw()
{

	system("cls");                  //reset screen

	for (int i = 0; i < WIDTH + 2; i++)                 //print the top border
	{
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < HEIGHT; i++)                //print the left and right borders
	{
		for (int j = 0; j <= WIDTH; j++)
		{
			if (j == 0 || j == WIDTH)
			{
				cout << "#";
			}
			if (j == PlayerX && i == PlayerY)
			{
				cout << "O";
			}
			else if (j == Player2X && i == Player2Y)
			{
				cout << "0";
			}
			else
			{
				bool printed = false;
				for (int t = 1; t < NTails; t++)
				{
					if (j == TailX[t] && i == TailY[t])
					{
						cout << "o";
						printed = true;
					}
				}
				for (int t = 1; t < NTails2; t++)
				{
					if (j == Tail2X[t] && i == Tail2Y[t])
					{
						cout << "*";
						printed = true;
					}
				}
				if (!printed)
				{
					cout << " ";
				}

			}

		}
		cout << endl;
	}

	for (int i = 0; i < WIDTH + 2; i++)                 //print the botom border
	{
		cout << "#";
	}

	cout << endl;

}

void Input()
{
	//get the player input and change direction
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			Dir = UP;
			break;

		case 'a':
			Dir = LEFT;
			break;

		case 's':
			Dir = DOWN;
			break;

		case 'd':
			Dir = RIGHT;
			break;

		case 'i':
			Dir2 = UP;
			break;

		case 'j':
			Dir2 = LEFT;
			break;

		case 'k':
			Dir2 = DOWN;
			break;

		case 'l':
			Dir2 = RIGHT;
			break;

		default:
			break;
		}
	}



}
void Logic()
{
	// update the players coords
	int PlayerPreX = PlayerX;		
	int PlayerPreY = PlayerY;

	int Player2PreX = Player2X;
	int Player2PreY = Player2Y;	

	//change players coords
	switch (Dir)
	{
	case LEFT:
		PlayerX--;
		NTails++;
		break;
	case RIGHT:
		PlayerX++;
		NTails++;
		break;
	case UP:
		PlayerY--;
		NTails++;
		break;
	case DOWN:
		PlayerY++;
		NTails++;
		break;

	default:
		break;
	}


	switch (Dir2)
	{
	case LEFT:
		Player2X--;
		NTails2++;
		break;
	case RIGHT:
		Player2X++;
		NTails2++;
		break;
	case UP:
		Player2Y--;
		NTails2++;
		break;
	case DOWN:
		Player2Y++;
		NTails2++;
		break;

	default:
		break;
	}

	TailX[NTails] = PlayerPreX;
	TailY[NTails] = PlayerPreY;

	Tail2X[NTails2] = Player2PreX;
	Tail2Y[NTails2] = Player2PreY;

	//constrols gameover logic
	if (!GameOver)									
	{
		for (int i = 0, t = 0; i < NTails; i++)					//if player 1 collides with own tail
		{
			if (PlayerX == TailX[i] && PlayerY == TailY[i])
			{
				GameOver = true;
			}
		}
	}

	if (!GameOver)
	{
		for (int i = 0, t = 0; i < NTails2; i++)				//if player 1 collides with player 2 tail
		{
			if (PlayerX == Tail2X[i] && PlayerY == Tail2Y[i])
			{
				GameOver = true;
			}
		}
	}

	if (!GameOver)
	{
		for (int i = 0, t = 0; i < NTails2; i++)			//if player 2 collides with own tail
		{
			if (Player2X == Tail2X[i] && Player2Y == Tail2Y[i])
			{
				GameOver = true;
				PlayerWin = true;
			}
		}
	}

	if (!GameOver)
	{
		for (int i = 0, t = 0; i < NTails; i++)				//if player 2 collides with player 1 tail		
		{
			if (Player2X == TailX[i] && Player2Y == TailY[i])
			{
				GameOver = true;
				PlayerWin = true;
			}
		}
	}


	if (PlayerX == Player2X && Player2Y == PlayerY)		//if both collides with each other
	{
		GameOver = true;
		BothWin = true;
	}

	//portal-like walls
	if (PlayerX < 0)						
	{
		PlayerX = WIDTH-2;
	}
	if (PlayerX > WIDTH-2)
	{
		PlayerX = 0;
	}

	if (Player2X < 0)
	{
		Player2X = WIDTH-2;
	}
	if (Player2X > WIDTH-2)
	{
		Player2X = 0;
	}

	if (PlayerY < 0)
	{
		PlayerY = HEIGHT-1;
	}
	if (PlayerY > HEIGHT-1)
	{
		PlayerY = 0;
	}

	if (Player2Y < 0)
	{
		Player2Y = HEIGHT-1;
	}
	if (Player2Y > HEIGHT-1)
	{
		Player2Y = 0;
	}




}

void Play() {
	cout << "JUGADOR 1 (WASD) = O" << endl;
	cout << "JUGADOR 2 (IJKL) = 0" << endl;

	Sleep(500);

	for (int i = 5; i > 0; i--)
	{
		cout << i << endl;
		Sleep(1000);
	}

	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(16.6);		//change this number to change fps
	}

	system("color 4");
	system("cls");
	Draw();
	Sleep(2000);
	system("color 2");
	system("cls");

	if (PlayerWin)
	{
		cout << "PLAYER 1 WINS";
	}
	else if (BothWin)
	{
		cout << "BOTH DIED, IT'S A DRAW";
	}
	else
	{
		cout << "PLAYER 2 WINS";
	}

	cout <<endl<<endl<< "Play again? Y/N    ";
	string answer;
	cin >> answer;
	system("color 9");
	system("cls");
	if (answer == "Y" || answer == "y") Play();
}

void main()
{
	Play();
	

}



