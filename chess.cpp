#include<iostream>
#include <cmath>
#include <string>
using namespace std;
enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Tile
{
	
	Piece piece;
	Color color;
	int x, y;
public:
	void setSpace(Tile*);
	void setEmpty();
	void setPieceAndColor(Piece, Color);
	Piece getPiece();
	Color getColor();
	void setX(int ex) { x = ex; }
	void setY(int why) { y = why; }
	int getX() { return x; }
	int getY() { return y; }
	Tile();
};

class ChessBoard
{
	Tile tile[8][8];
	Color turn=WHITE;
	bool Move_King(Tile* thisKing, Tile* thatSpace);
	bool Move_Queen(Tile* thisQueen, Tile* thatSpace);
	bool Move_Bishop(Tile* thisBishop, Tile* thatSpace);
	bool Move_Knight(Tile* thisKnight, Tile* thatSpace);
	bool Move_Rook(Tile* thisRook, Tile* thatSpace);
	bool Move_Pawn(Tile* thisPawn, Tile* thatSpace);
	bool makeMove_(int x1, int y1, int x2, int y2);
	void printChessBoard();
public:
	Tile* getTile(int x, int y) {
		return &tile[x][y];
	}
	void setTile(Tile * s, int x, int y){
		tile[x][y]=*s;
	}
	bool doMove_();
	
	void setChessBoard();
	bool playGame();
};


Tile::Tile()
{
	piece = EMPTY;
	color = NONE;
}

void Tile::setSpace(Tile* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

void Tile::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

Piece Tile::getPiece()
{
	return piece;
}

Color Tile::getColor()
{
	return color;
}

void Tile::setPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;

}


void ChessBoard::printChessBoard() {
	using namespace std;
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = tile[i][j].getPiece();
			Color c = tile[i][j].getColor();

			switch (p)
			{
			case KING: (c == WHITE) ? cout << " K " : cout << " k ";
				break;
			case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q ";
				break;
			case BISHOP:(c == WHITE) ? cout << " B " : cout << " b ";
				break;
			case KNIGHT:(c == WHITE) ? cout << " H " : cout << " h ";
				break;
			case ROOK: (c == WHITE) ? cout << " R " : cout << " r ";
				break;
			case PAWN: (c == WHITE) ? cout << " P " : cout << " p ";
				break;
			case EMPTY: cout << " " << "\21" << " ";
				break;
			default: cout << "XXX";
				break;
			}

		}
		cout << endl;
	}

}

bool ChessBoard::doMove_() {
	using namespace std;
	string Move_;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
		(turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
		cout << "Type in your Move_ as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> Move_;
		x1 = Move_[0] - 48;
		y1 = Move_[1] - 48;
		x2 = Move_[2] - 48;
		y2 = Move_[3] - 48;
		if (getTile(x1, y1)->getColor() == turn)
		{


			if (makeMove_(x1, y1, x2, y2) == false)
			{
				cout << "Invalid Move_, try again." << endl;
			}
			else
				stop = true;
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	if (getTile(x2, y2)->getPiece() == KING)
		if (getTile(x1, y1)->getColor() == WHITE)
		{
			cout << "WHITE WINS" << endl;
			return false;
		}
		else

		{
			cout << "BLACK WINS" << endl;
			return false;
		}


	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;

	return true;

}

void ChessBoard::setChessBoard()
{
	tile[0][0].setPieceAndColor(ROOK, WHITE);
	tile[1][0].setPieceAndColor(KNIGHT, WHITE);
	tile[2][0].setPieceAndColor(BISHOP, WHITE);
	tile[3][0].setPieceAndColor(QUEEN, WHITE);
	tile[4][0].setPieceAndColor(KING, WHITE);
	tile[5][0].setPieceAndColor(BISHOP, WHITE);
	tile[6][0].setPieceAndColor(KNIGHT, WHITE);
	tile[7][0].setPieceAndColor(ROOK, WHITE);

	tile[0][7].setPieceAndColor(ROOK, BLACK);
	tile[1][7].setPieceAndColor(KNIGHT, BLACK);
	tile[2][7].setPieceAndColor(BISHOP, BLACK);
	tile[3][7].setPieceAndColor(QUEEN, BLACK);
	tile[4][7].setPieceAndColor(KING, BLACK);
	tile[5][7].setPieceAndColor(BISHOP, BLACK);
	tile[6][7].setPieceAndColor(KNIGHT, BLACK);
	tile[7][7].setPieceAndColor(ROOK, BLACK);

	for (int i = 0; i < 8; i++)
	{
		tile[i][1].setPieceAndColor(PAWN, WHITE);
		tile[i][6].setPieceAndColor(PAWN, BLACK);

	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			tile[j][i].setPieceAndColor(EMPTY, NONE);

	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			tile[i][j].setX(i);
			tile[i][j].setY(j);
		}

}

bool ChessBoard::playGame()
{
	system("cls");
	printChessBoard();
	return doMove_();

}

bool ChessBoard::Move_King(Tile* thisKing, Tile* thatSpace) {
	//off ChessBoard inputs should be handled elsewhere (before this)
	//Tiles with same color should be handled elsewhere (before this)
	if (abs(thatSpace->getX() - thisKing->getX()) == 1)
		if (abs(thatSpace->getY() - thisKing->getY()) == 1)
		{
			thatSpace->setSpace(thisKing);
			thisKing->setEmpty();
			return true;
		}
		else return false;
	else return false;
}
bool ChessBoard::Move_Queen(Tile* thisQueen, Tile* thatSpace) { //there might be problems with numbers of brackets
													   //off ChessBoard inputs should be handled elsewhere (before this)
													   //Tiles with same color should be handled elsewhere (before this)

	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	std::cout << "this";
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (tile[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (tile[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						std::cout << "It got here somehow";
						if (tile[queenX + xIncrement*i][queenY + yIncrement*i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
		//if()
	}



	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool ChessBoard::Move_Bishop(Tile* thisBishop, Tile* thatSpace) { //there might be problems with number of brackets
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Tile *s;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			std::cout << "It got here somehow";
			if (tile[bishopX + xIncrement*i][bishopY + yIncrement*i].getColor() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}
bool ChessBoard::Move_Knight(Tile* thisKnight, Tile* thatSpace)
{
	//off ChessBoard inputs should be handled elsewhere (before this)
	//Tiles with same color should be handled elsewhere (before this)
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		thatSpace->setSpace(thisKnight);
		thisKnight->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool ChessBoard::Move_Rook(Tile* thisRook, Tile* thatSpace)
{
	//off ChessBoard inputs should be handled elsewhere (before this)
	//Tiles with same color should be handled elsewhere (before this)
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{

		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

				if (tile[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (tile[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setEmpty();
		return true;
	}
	else
	{//Return some erorr or something. Probably return false;
		std::cout << "That is an invalid Move_ for rook";
		return false;
	}
}

bool ChessBoard::Move_Pawn(Tile* thisPawn, Tile* thatSpace) {
	//off ChessBoard inputs should be handled elsewhere (before this)
	//Tiles with same color should be handled elsewhere (before this)
	using namespace std;
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();


	if (thisPawn->getColor() == WHITE)
	{

		if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);
			thisPawn->setEmpty();
			return true;
		}
		else
			if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY  && thatSpace->getColor() == BLACK)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				return false;
	}
	else
		if (thisPawn->getColor() == BLACK)
		{
			if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY  && thatSpace->getColor() == WHITE)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					return true;
				}
				else
					return false;
		}
		else
			return false;
}
bool ChessBoard::makeMove_(int x1, int y1, int x2, int y2) {
	//Checking for turns will be done previous to this
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		std::cout << "One of your inputs was our of bounds" << std::endl;
		return false;
	}
	Tile* src = getTile(x1, y1);
	Tile* dest = getTile(x2, y2);

	if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
	{
		std::cout << "Invalid Move_: cannot land on your own piece" << std::endl;
		return false;
	}

	switch (src->getPiece())
	{
	case KING: return Move_King(src, dest);
		break;
	case QUEEN: return Move_Queen(src, dest);
		break;
	case BISHOP: return Move_Bishop(src, dest);
		break;
	case KNIGHT: return Move_Knight(src, dest);
		break;
	case ROOK: return Move_Rook(src, dest);
		break;
	case PAWN: return Move_Pawn(src, dest);
		break;
	case EMPTY: std::cout << "You do not have a piece there" << std::endl;  return false;
		break;
	default: std::cerr << "Something went wrong in the switch statement in makeMove_()" << std::endl;
		break;
	}
	return false;
}
int main()
{
	ChessBoard b;
	string s;
	bool newgame = true;
	cout << "   _____ _    _ ______  _____ _____ \n  / ____| |  | |  ____|/ ____/ ____| \n | |    | |__| | |__  | (___| (___  \n | |    |  __  |  __|  \\___  \\___ \\ \n | |____| |  | | |____ ____) |___) | \n  \\_____|_|  |_|______|_____/_____/ \n" << endl;

	cout << "Enter any key to continue" << endl;
	cin >> s;

	while(newgame){
		b.setChessBoard();
		while (b.playGame());
		cout << "Do you want to play again? (y for yes, anything else for no) ";
		cin >> s;
		if (s != "y")
			newgame = false;
	}


	return 0;
}