#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<bits/stdc++.h>
#include<string.h>
using namespace std;
int firstmovep1=0;
int firstmovep2=0;

int abs(int x)
{
	if(x < 0)
	{
		return -1*x;
	}
	return x;
}

int clearScreen()
{
	cout<<string(100,'\n');
}



class ChessPiece{
	private:
	public:
	string type;
	int player;
	int x,y; // range from 0 to 7
	bool isNull;
	ChessPiece(string type,int x, int y,int player)
	{
		this->type = type;
		this->x = x;
		this->y = y;
		this->player = player;
		this->isNull = false;
	}
	ChessPiece()
	{
		this->isNull = true;
	}
};

class Move
{
	public:
	int startX,startY,endX,endY;
	Move(int sx,int sy,int ex,int ey)
	{
		this->startX = sx;
		this->startY = sy;
		this->endX = ex;
		this->endY = ey;
	}
};

class ChessBoard
{
	private:
	int currentPlayer;
	vector<ChessPiece> pieces;
	ChessPiece* getPieceAtLocation(int x, int y)
	{
		for(int i=0;i<this->pieces.size();i++)
		{
			ChessPiece *piece = &(this->pieces.at(i));
			if(piece->x == x && piece->y == y)
			{
				return piece;
			}
		}
		return new ChessPiece(); //this constructor denotes a "null" chess piece.
	}
	string validateMove(Move m)
	{
		ChessPiece piece = *getPieceAtLocation(m.startX,m.startY);
		ChessPiece victimPiece = *getPieceAtLocation(m.endX,m.endY);

		int x = piece.x;
		int y = piece.y;

		if(m.endX == x && m.endY == y){
			return "The chosen Chess Piece must actually move!";
		}
		if(piece.isNull){
			return "The chosen Chess Piece does not exist!";
		}
		if(victimPiece.player == piece.player && !victimPiece.isNull){
			return "You cannot move into your own pieces!";
		}


		if(piece.type == "K")
		{
			if(abs(x-m.endX) <= 1 && abs(y-m.endY) <= 1)
			{
				return "";
			}
			return "Kings can only move unit away!";
		}
		else if(piece.type == "Q")
		{
			int blockingPieceX = x;
			int blockingPieceY = y;
			if(abs(x-m.endX) == abs(y-m.endY)) // Diagonal
			{
				if(m.endX > x)
				{
					if(m.endY > y) // Right and Up
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY++;
						}
						return "";
					}
					else // Right and Down
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY--;
						}
						return "";
					}
				}
				else
				{
					if(m.endY > y) // Left and Up
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY++;
						}
						return "";
					}
					else // Left and Down
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY--;
						}
						return "";
					}
				}
			}
			else if(y-m.endY == 0) // Horizontal
			{
				if(m.endX > x) // Right
				{
					int blockingPieceX = x+1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX++;
					}
					return "";
				}
				else // Left
				{
					int blockingPieceX = x-1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX--;
					}
					return "";
				}
			}
			else if(x-m.endX == 0) // Vertical
			{
				if(m.endY > y) // Up
				{
					int blockingPieceX = x;
					int blockingPieceY = y+1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY++;
					}
					return "";
				}
				else // Down
				{
					int blockingPieceX = x;
					int blockingPieceY = y-1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY--;
					}
					return "";
				}
			}
			return "A queen cannot move in that way!";
		}
		else if(piece.type == "B")
		{
			if(abs(x-m.endX) == abs(y-m.endY)) // Diagonal
			{
				if(m.endX > x)
				{
					if(m.endY > y) // Right and Up
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY++;
						}
						return "";
					}
					else // Right and Down
					{
						int blockingPieceX = x+1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX++;
							blockingPieceY--;
						}
						return "";
					}
				}
				else
				{
					if(m.endY > y) // Left and Up
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y+1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY++;
						}
						return "";
					}
					else // Left and Down
					{
						int blockingPieceX = x-1;
						int blockingPieceY = y-1;
						while(blockingPieceX != m.endX || blockingPieceY != m.endY)
						{
							if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
							{
								return "There is a piece in the way!";
							}
							blockingPieceX--;
							blockingPieceY--;
						}
						return "";
					}
				}
			}
			return "A bishop cannot move in that way!";
		}
		else if(piece.type == "N")
		{
			if((abs(x-m.endX) == 2 && abs(y-m.endY) == 1) || (abs(x-m.endX) == 1 && abs(y-m.endY) == 2))
			{
				return "";
			}
			return "A knight cannot move in that way!";
		}
		else if(piece.type == "R")
		{
			if(y-m.endY == 0) // Horizontal
			{
				if(m.endX > x) // Right
				{
					int blockingPieceX = x+1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX++;
					}
					return "";
				}
				else // Left
				{
					int blockingPieceX = x-1;
					int blockingPieceY = y;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceX--;
					}
					return "";
				}
			}
			else if(x-m.endX == 0) // Vertical
			{
				if(m.endY > y) // Up
				{
					int blockingPieceX = x;
					int blockingPieceY = y+1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY++;
					}
					return "";
				}
				else // Down
				{
					int blockingPieceX = x;
					int blockingPieceY = y-1;
					while(blockingPieceX != m.endX || blockingPieceY != m.endY)
					{
						if(!getPieceAtLocation(blockingPieceX,blockingPieceY)->isNull)
						{
							return "There is a piece in the way!";
						}
						blockingPieceY--;
					}
					return "";
				}
			}
			return "A rook can only move vertically or horizontally!";
		}
		else if(piece.type == "P" || piece.type == "P" )
		{
			if(piece.player == 1)
			{
				if(y == 1 && (x-m.endX == 0 && m.endY-y == 2)) //row 2 going 2 spaces forward
				{
					if(victimPiece.isNull && getPieceAtLocation(x,y+1)->isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally and cannot jump over other pieces!";
					}
				}
				else if(x-m.endX == 0 && m.endY-y == 1) //move 1 forward
				{
					if(victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally!";
					}
				}
				else if(abs(x-m.endX) == 1 && m.endY-y == 1) //attack
				{
					if(!victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only move diagonally when attacking!";
					}
				}
				return "Pawns cannot move in that way...ever";
			}
			else if(piece.player == 2)
			{
				if(y == 6 && (x-m.endX == 0 && y-m.endY == 2)) //row 2 going 2 spaces forward
				{
					if(victimPiece.isNull && getPieceAtLocation(x,y-1)->isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally and cannot jump over other pieces!";
					}
				}
				else if(x-m.endX == 0 && y-m.endY == 1) //move 1 forward
				{
					if(victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only attack diagonally!";
					}
				}
				else if(abs(x-m.endX) == 1 && y-m.endY == 1) //attack
				{
					if(!victimPiece.isNull)
					{
						return "";
					}
					else
					{
						return "A pawn can only move diagonally when attacking!";
					}
				}
				return "Pawns cannot move in that way...ever";
			}
		}
		else
		{
			return "That type of piece doesn't exist?!";
		}
	}
		string SuggestMove(Move m)
	{
		ChessPiece piece = *getPieceAtLocation(m.startX,m.startY);
        int x = piece.x;
        int y = piece.y;
		if(piece.isNull){
			return "The chosen Chess Piece does not exist!";
		}

        if(piece.type == "K")
		{
			return "Kings can only move a unit away!";
		}
		else if(piece.type == "Q")
		{
		    return "A queen can move in vertical,horizontal and diagonal manner";
		}

		else if(piece.type == "B")
		{

			return "A bishop can only move diagonally!";
		}
		else if(piece.type == "N")
		{
			return "A knight can only move in a L path!";
		}
		else if(piece.type == "R")
		{

			return "A rook can only move vertically or horizontally!";
		}
		else if(piece.type == "P")
		{char xcoordinate;
		xcoordinate = x+'a';
			if(piece.player == 1)
			{
			    if(firstmovep1==0)
                {
                    firstmovep1++;
                    cout<<xcoordinate<<","<<(y+2)<<endl;

                }

			    cout<<xcoordinate<<","<<(y+1)<<endl;
			    return "A Pawn can only move vertically one step at a time";
			}
			else if(piece.player == 2)
			{
			    if(firstmovep2==0)
                {
                    firstmovep1++;
                    cout<<xcoordinate<<","<<(y-2);

                }

			    cout<<xcoordinate<<","<<(y-1)<<endl;

				return "A Pawn can only move vertically one step at a time";
			}
		}

	}
	public:
	void printBoard()
	{
		for(int y=7;y>=0;y--)
		{
			cout<<endl<<"   ---------------------------------------------------------------------------------"<<endl;
			cout<<setw(2)<<y<<" |";
			for(int x=0;x<=7;x++)
			{
				ChessPiece *piece = getPieceAtLocation(x,y);
				if(!piece->isNull)
				{
					string pieceString = piece->type;
					pieceString.append("_");
					pieceString.append(((piece->player == 1) ? "W" : "B"));
					cout<<setw(9)<<pieceString;
				}
				else
				{
					cout<<setw(9)<<"";
				}
				cout<<"|";
			}
		}
		cout<<endl<<"   ---------------------------------------------------------------------------------"<<endl;
		char j;
		for(int i=0,j='a';i<=7,j<='h';i++,j++)
		{
			cout<<setw(5)<<"";
			cout<<setw(5)<<char(j);
		}
		cout<<endl;
	}

	Move getMove()
	{
		int startX,startY,endX,endY;
		char startXchar,endXchar;
		Move m = Move(0,0,0,0);
        Move n = Move(0,0,0,0);
		string choice;
		string message = "";
		string suggest;
		do{
			clearScreen();
			do{

           cout<<"------------------------"<<endl;
			cout<<"1.continue 2.print 3.exit"<<endl;
			cin>>choice;
			if (choice.compare("exit") == 0 || choice.compare("3") == 0 )
            {
                exit(0);
            }
            else if(choice.compare("print") == 0 || choice.compare("2") == 0 )
                printBoard();

            else
                cout<<"invalid input"<<endl;

            cout<<"------------------------"<<endl;
            }while(choice != "continue" && choice != "1");

            clearScreen();
            printBoard();
			cout<<message<<endl;
			string prompt = (currentPlayer == 1) ? "(White) Player One's Turn!" : "(Black) Player Two's Turn!";
			cout<<prompt<<endl;

			cout<<"------------------------"<<endl;
			cout<<"Enter the Location of the piece you want to move: "<<endl;
			cin>>startXchar;
			startX=int(startXchar-'a');
			cin>>startY;
			cout<<"You have selected :";

			cout<<getPieceAtLocation(startX,startY)->type<<endl;
			cout<<"Possible moves:";
			n = Move(startX,startY,0,0);
            suggest = SuggestMove(n);
            cout<< suggest<<endl;
			cout<<"enter the new position: "<<endl;
			cin>>endXchar;
			endX=int(endXchar-'a');
			cin>>endY;
			m = Move(startX,startY,endX,endY);
			message = validateMove(m);

			/*  check that a player does not move into check */
			ChessBoard hypotheticalBoard = ChessBoard(currentPlayer,this->pieces);
			hypotheticalBoard.makeMove(m);
			hypotheticalBoard.check();
			if(hypotheticalBoard.check() == currentPlayer)
			{
				message = "When in check, any move you make must take you out of check!";
			}

			// Check that each player only moves his own pieces.
			if(getPieceAtLocation(startX,startY)->player != currentPlayer)
			{
				message = "You cannot move your opponent's pieces!";
			}
		}while(message != "");
		return m;
	}
	bool makeMove(Move m)
	{
		ChessPiece *piece = getPieceAtLocation(m.startX,m.startY);
		for(int i=0;i<pieces.size();i++)
		{
			if(pieces.at(i).x == m.endX && pieces.at(i).y == m.endY)
			{
				pieces.at(i).isNull = true;
			}
		}
		piece->x = m.endX;
		piece->y = m.endY;

		this->currentPlayer = (currentPlayer == 1) ? 2 : 1;
	}
	bool stalemate() // returns true if there is a stalemate.
	{
		if(check() == 0)
		{
			for(int i=0;i<pieces.size();i++)
			{
				ChessPiece testPiece = pieces.at(i);
				if(testPiece.player == currentPlayer)
				{
					for(int x = 0;x<=7;x++)
					{
						for(int y = 0;y<=7;y++)
						{
							Move testMove = Move(testPiece.x,testPiece.y,x,y);
							if(validateMove(testMove) == "")
							{
								cout<<"Stalemate: false"<<endl;
								return false;
							}
						}
					}
				}
			}
			cout<<"Stalemate: TRUE!!!"<<endl;
			return true;
		}
	}
	int checkmate() // returns the number of the defeated player (1 or 2) or zero if the game is still going.
	{
		if(check() != 0)
		{
			for(int i=0;i<pieces.size();i++)
			{
				ChessPiece testPiece = pieces.at(i);
				if(testPiece.player == check())
				{
					for(int x = 0;x<=7;x++)
					{
						for(int y = 0;y<=7;y++)
						{
							Move testMove = Move(testPiece.x,testPiece.y,x,y);
							if(validateMove(testMove) == "")
							{
								/*  check that a player does not move into check */
								ChessBoard hypotheticalBoard = ChessBoard(currentPlayer,this->pieces);
								hypotheticalBoard.makeMove(testMove);
								hypotheticalBoard.check();
								if(hypotheticalBoard.check() == 0)
								{
									return 0;
								}
							}
						}
					}
				}
			}
			return check();
		}
		else
		{
			return 0;
		}
	}
	int check() // returns the number of the player that is in check (1 or 2) or zero if nobody is in check
	{
		ChessPiece whiteKing;
		ChessPiece blackKing;
		for(int i=0;i<pieces.size();i++)
		{
			ChessPiece currentPiece = pieces.at(i);
			if(currentPiece.type == "K" && currentPiece.player == 1)
			{
				whiteKing = currentPiece;
			}
			else if(currentPiece.type == "K" && currentPiece.player == 2)
			{
				blackKing = currentPiece;
			}
		}
		for(int i=0;i<pieces.size();i++)
		{
			ChessPiece currentPiece = pieces.at(i);
			Move attackBlackKing = Move(currentPiece.x,currentPiece.y,blackKing.x,blackKing.y);
			Move attackWhiteKing = Move(currentPiece.x,currentPiece.y,whiteKing.x,whiteKing.y);
			if(currentPiece.player == 1 && validateMove(attackBlackKing) == "")
			{
				return 2;
			}
			else if(currentPiece.player == 2 && validateMove(attackWhiteKing) == "")
			{
				return 1;
			}
		}
		return 0;
	}
	ChessBoard()
	{
		this->currentPlayer = 1;
		this->pieces = vector<ChessPiece>();
		for(int x=0;x<=7;x++)
		{
			this->pieces.push_back(ChessPiece("P",x,1,1));
			this->pieces.push_back(ChessPiece("P",x,6,2));
		}

		// Player 1 Pieces
		this->pieces.push_back(ChessPiece("K",4,0,1));
		this->pieces.push_back(ChessPiece("Q",3,0,1));
		this->pieces.push_back(ChessPiece("B",2,0,1));
		this->pieces.push_back(ChessPiece("B",5,0,1));
		this->pieces.push_back(ChessPiece("N",1,0,1));
		this->pieces.push_back(ChessPiece("N",6,0,1));
		this->pieces.push_back(ChessPiece("R",0,0,1));
		this->pieces.push_back(ChessPiece("R",7,0,1));

		// Player 2 Pieces
		this->pieces.push_back(ChessPiece("K",4,7,2));
		this->pieces.push_back(ChessPiece("Q",3,7,2));
		this->pieces.push_back(ChessPiece("B",2,7,2));
		this->pieces.push_back(ChessPiece("B",5,7,2));
		this->pieces.push_back(ChessPiece("N",1,7,2));
		this->pieces.push_back(ChessPiece("N",6,7,2));
		this->pieces.push_back(ChessPiece("R",0,7,2));
		this->pieces.push_back(ChessPiece("R",7,7,2));
	}
	ChessBoard(int currentPlayer, vector<ChessPiece> otherPieces)
	{
		this->currentPlayer = currentPlayer;
		this->pieces = vector<ChessPiece>(otherPieces);
	}
};


int main()
{
	ChessBoard cb = ChessBoard();
	bool continuePlaying = true;
	int checkmateStatus = 0;
	bool stalemateStatus = false;
	while(continuePlaying)
	{
		Move m = cb.getMove();
		cb.makeMove(m);
		checkmateStatus = cb.checkmate();
		stalemateStatus = cb.stalemate();
		if(checkmateStatus != 0 || stalemateStatus == true)
		{
			continuePlaying = false;
		}
	}
	if(checkmateStatus != 0)
	{
		cout<<"Checkmate!"<<endl;
		if(checkmateStatus == 1)
		{
			cout<<"Black (player 2) Wins!"<<endl;
		}
		else
		{
			cout<<"White (player 1) Wins!"<<endl;
		}
	}
	else if(stalemateStatus == true)
	{
		cout<<"Stalemate!"<<endl;
	}
	else{
		cout<<"game unexpectedly ended"<<endl;
	}
	return 0;
}

