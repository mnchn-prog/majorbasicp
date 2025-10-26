#pragma once
#include "Cell.h"
#include "GameState.h"
#include <chrono>

class Game
{
private:
	GameState* whiteState, * blackState;
	Player turn;
	Cell (&board)[Rank::Ranksize][File::Filesize];
	void RemovePiece(Piece* capturedPiece, Player color);

	//시간 관련
	GameMode mode;
	std::chrono::steady_clock::time_point lastMoveTime;
	int whiteTimeLeft;
	int blackTimeLeft;

public:
	Game(Cell (&board)[8][8], GameState* ws, GameState* bs, Player turn, GameMode gm = GameMode::classical) : board(board), whiteState(ws), blackState(bs), turn(turn), mode(gm) 
	{
		switch(mode)
		{
			case GameMode::classical: whiteTimeLeft = blackTimeLeft = 30*60; break;
        	case GameMode::rapid: whiteTimeLeft = blackTimeLeft = 10*60; break;
        	case GameMode::blitz: whiteTimeLeft = blackTimeLeft = 3*60; break;
		}
	}

	// 오류 문구
	int get_visual_width(const string& s);
	void ShowCommandStart();
	void ShowCommandEnd();
	void ShowCommand(vector<pair<string,string>> data);
	string unicodeForPiece(Player color, PieceType p) const;
    //void MovePiece(string startPos, string endPos); // 기획서랑 똑같게 하려면 고쳐야됨
	Piece* SelectStartPos(string startPos);
	bool SelectEndPos(Piece* currentPiece, string endPos, bool& isPosForm);
	void ShowBoard(bool whiteChecked, bool blackChecked, bool printCheck = false) const;
	bool RefreshBoard(bool& whiteChecked, bool& blackChecked);
	inline Player GetTrun() const {return turn;}

	void SetGameMode(GameMode gm) 
	{ 
		mode = gm; 
		switch(mode)
		{
			case GameMode::classical: whiteTimeLeft = blackTimeLeft = 30*60; break;
        	case GameMode::rapid: whiteTimeLeft = blackTimeLeft = 10*60; break;
        	case GameMode::blitz: whiteTimeLeft = blackTimeLeft = 3*60; break;
		}
	}

	void StartTimer() { lastMoveTime = std::chrono::steady_clock::now(); }
	void UpdateTime();
	string FormatTime(int sec) const;
	int GetWhiteTime() const {return whiteTimeLeft;}
	int GetBlackTime() const {return blackTimeLeft;}
	bool checkTimeZero()
	{
		if (GetWhiteTime() <= 0 || GetBlackTime() <= 0)
        {
            cout << (GetWhiteTime() <= 0 ? "White" : "Black") << " 시간 종료! 게임 종료." << endl;
            // 누구 승리인지?
			return true;
        }
		return false;
	}
};