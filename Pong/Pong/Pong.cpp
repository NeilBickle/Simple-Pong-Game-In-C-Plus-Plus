

#include <iostream>
#include <time.h>
#include <conio.h>
#include <cstdlib>
using namespace std;
enum eDirection { STOP = 0, LEFT = 1, RIGHT = 4, UPLEFT = 2, DOWNLEFT = 3, UPRIGHT = 5, DOWNRIGHT = 6 };
class aBall {
private:
	int a, b;
	int OGA, OGB;
	eDirection directionofball;
public:
	aBall(int ThePosofA, int ThePosofB) 
	{
		OGA = ThePosofA;
		OGB = ThePosofB;
		a = ThePosofA;
		b = ThePosofB;
		directionofball = STOP;
	}
	void ResetTheGame() {
		a = OGA;
		b = OGB;
		directionofball = STOP;
	}
	void changetheDirection(eDirection t) {
		directionofball = t;
	}
	void TheRandomDirection() {
		directionofball = (eDirection)((rand() % 6) + 1);
	}
	inline int geta() { return a;  }
	inline int getb() { return b;  }
	inline eDirection getTheDir() { return directionofball;  }
	void Movement() {
		switch (directionofball)
		{
		case STOP:
			break;
		case LEFT:
			a--;
			break;
		case RIGHT:
			a++;
			break;
		case UPLEFT:
			a--; b--;
			break;
		case DOWNLEFT:
			a--; b++;
			break;
		case UPRIGHT:
			a++; b--;
			break;
		case DOWNRIGHT:
			a++; b++;
			break;
		default:
			break;
		}
	}
	friend ostream & operator<<(ostream & o, aBall g) {
		o << "Ball [" << g.a << "," << g.b << "][" << g.directionofball << "]";
		return o;
	}
};
class aInput {
private:
	int a, b;
	int PastA, PastB;
public:
	aInput(){
		a = b = 0;
	}
	aInput(int locationA, int locationB) : aInput() 
	{
		PastA = locationA;
		PastB = locationB;
		a = locationA;
		b = locationB;
	}
	inline void ResetTheGame() { a = PastA; b = PastB; }
	inline int GetA() { return a; }
	inline int GetB() { return b; }
	inline void UpMovement() { b--; }
	inline void DownMovement() { b++; }
	friend ostream& operator<<(ostream& o, aInput j) {
		o << "Input [" << j.a << "," << j.b << "]";
		return o;
	}
};
class aGameExec {
private:
	int WidthOfLevel, HeightOfLevel;
	int P1Score, P2Score;
	char P1UP, P1DOWN, P2UP, P2DOWN;
	bool Leave;
	aBall* Ball;
	aInput* p1;
	aInput* p2;
public:
	aGameExec(int Width, int Height) {
		srand(time(NULL));
		Leave = false;
		P1UP = 'w'; P2UP = 'o';
		P2DOWN = 'l'; P1DOWN = 's';
		P1Score = P2Score = 0;
		WidthOfLevel = Width;
		HeightOfLevel = Height;
		Ball = new aBall(Width / 2, Height / 2);
		p1 = new aInput(1, Height / 2 - 3);
		p2 = new aInput(Width - 2, Height / 2 - 3);
	}
	~aGameExec()
	{
		delete Ball, p1, p2;
	}
	void Scored(aInput* p)
	{
		if (p == p1)
			P1Score++;
		else if (p == p2)
			P2Score++;

		Ball->ResetTheGame();
		p1->ResetTheGame();
		p2->ResetTheGame();
	}
	void Graphics()
	{
		system("cls");
		for (int c = 0; c < WidthOfLevel + 2; c++)
			cout << "\xB2";
		cout << endl;

		for (int c = 0; c < HeightOfLevel; c++)
		{
			for (int h = 0; h < WidthOfLevel; h++)
			{
				int TheBallA = Ball->geta();
				int TheBallB = Ball->getb();
				int TheP1A = p1->GetA();
				int TheP2A = p2->GetA();
				int TheP1B = p1->GetB();
				int TheP2B = p2->GetB();

				if (h == 0)
					cout << "\xB2";

				if (TheBallA == h && TheBallB == c)
					cout << "O";
				else if (TheP1A == h && TheP1B == c)
					cout << "\xB2";
				else if (TheP2A == h && TheP2B == c)
					cout << "\xB2";

				else if (TheP1A == h && TheP1B + 1 == c)
					cout << "\xB2";
				else if (TheP1A == h && TheP1B + 2 == c)
					cout << "\xB2";
				else if (TheP1A == h && TheP1B + 3 == c)
					cout << "\xB2";

				else if (TheP2A == h && TheP2B + 1 == c)
					cout << "\xB2";
				else if (TheP2A == h && TheP2B + 2 == c)
					cout << "\xB2";
				else if (TheP2A == h && TheP2B + 3 == c)
					cout << "\xB2";
				else
					cout << " ";

				if (h == WidthOfLevel - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int c = 0; c < WidthOfLevel + 2; c++)
			cout << "\xB2";
		cout << endl;

		cout << "Player 1 Score: " << P1Score << endl;
		cout <<	"Player 2 Score: " << P2Score << endl;
	}
	void Inputer() {
		Ball->Movement();

		int TheBallA = Ball->geta();
		int TheBallB = Ball->getb();
		int TheP1A = p1->GetA();
		int TheP2A = p2->GetA();
		int TheP1B = p1->GetB();
		int TheP2B = p2->GetB();

		if (_kbhit()) {
			char AtTheMomment = _getch();
			if (AtTheMomment == P1UP)
				if (TheP1B > 0)
					p1->UpMovement();
			if (AtTheMomment == P2UP)
				if (TheP2B > 0)
					p2->UpMovement();
			if (AtTheMomment == P1DOWN)
				if (TheP1B + 4 < HeightOfLevel)
					p1->DownMovement();
			if (AtTheMomment == P2DOWN)
				if (TheP2B + 4 < HeightOfLevel)
					p2->DownMovement();

			if (Ball->getTheDir() == STOP)
				Ball->TheRandomDirection();

			if (AtTheMomment == 'x')
				Leave = true;

		}
	}
	void GameLogic() {

		int TheBallA = Ball->geta();
		int TheBallB = Ball->getb();
		int TheP1A = p1->GetA();
		int TheP2A = p2->GetA();
		int TheP1B = p1->GetB();
		int TheP2B = p2->GetB();

		for (int u = 0; u < 4; u++)
			if (TheBallA == TheP1A + 1)
				if (TheBallB == TheP1B + u)
					Ball->changetheDirection((eDirection)((rand() % 3) + 4));

		for (int u = 0; u < 4; u++)
			if (TheBallA == TheP2A - 1)
				if (TheBallB == TheP2B + u)
					Ball->changetheDirection((eDirection)((rand() % 3) + 1));


		if (TheBallB == HeightOfLevel - 1)
			Ball->changetheDirection(Ball->getTheDir() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		if (TheBallB == 0)
			Ball->changetheDirection(Ball->getTheDir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		if (TheBallA == WidthOfLevel - 1)
			Scored(p1);

		if (TheBallA == 0)
			Scored(p2);

		if (P1Score == 5)
		{
		cout << "Player 1 Wins!" << endl;
			Leave = true;
		}			
		else if (P2Score == 5) 
		{
		cout << "Player 2 Wins!" << endl;
		Leave = true;
		}
			
		
			
	}
	void Running() {
		while (!Leave) {
			Graphics();
			Inputer();
			GameLogic();
		}
	}
};
int main()
{
	aGameExec b(60, 40);
	b.Running();
	return 0;
}

