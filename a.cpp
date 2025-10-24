#include <iostream>
#include <vector> // GameState 초기화를 위해 필요
#include <algorithm> // GameState 초기화를 위해 필요
#include <iterator> // GameState 초기화를 위해 필요

// ⚠️ Windows API와의 충돌 방지 매크로
#define NOMINMAX 
#define RPC_NO_WINDOWS_H 

// ⚠️ Windows 유니코드 출력을 위해 가장 먼저 인클루드 (표준 헤더보다 먼저)
#ifdef _WIN32
#include <windows.h>
#endif

// 모든 프로젝트 헤더 파일 인클루드
#include "Cell.h"
#include "Piece.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Game.h"

using namespace std;
//g++ -o chess_game a.cpp Game.cpp GameState.cpp Piece.cpp Knight.cpp Bishop.cpp Pawn.cpp Rook.cpp Queen.cpp King.cpp -finput-charset=UTF-8 -fexec-charset=UTF-8 -std=c++11
Cell board[Rank::Ranksize][File::Filesize];

GameMode ChoiceGameMode();
void InitializeConsole();
int main()
{
    // ⬇️ Windows 환경에서 콘솔 출력 인코딩을 UTF-8로 설정
//#ifdef _WIN32
//    SetConsoleOutputCP(CP_UTF8);
//#endif
    InitializeConsole();
    
	// 1. 기물 초기 배치 및 목록 생성
    vector<Piece*> whitePieces;
    vector<Piece*> blackPieces;

    // 킹, 퀸, 룩, 비숍, 나이트
    whitePieces.push_back(new Rook(static_cast<File>(0), static_cast<Rank>(0), PieceType::typeRook, Player::white));
    whitePieces.push_back(new Knight(static_cast<File>(1), static_cast<Rank>(0), PieceType::typeKnight, Player::white));
    whitePieces.push_back(new Bishop(static_cast<File>(2), static_cast<Rank>(0), PieceType::typeBishop, Player::white));
    whitePieces.push_back(new Queen(static_cast<File>(3), static_cast<Rank>(0), PieceType::typeQueen, Player::white));
    whitePieces.push_back(new King(static_cast<File>(4), static_cast<Rank>(0), PieceType::typeKing, Player::white));
    whitePieces.push_back(new Bishop(static_cast<File>(5), static_cast<Rank>(0), PieceType::typeBishop, Player::white));
    whitePieces.push_back(new Knight(static_cast<File>(6), static_cast<Rank>(0), PieceType::typeKnight, Player::white));
    whitePieces.push_back(new Rook(static_cast<File>(7), static_cast<Rank>(0), PieceType::typeRook, Player::white));
    
    // 폰 (1랭크)
    for(int i = 0; i < File::Filesize; ++i) {
        whitePieces.push_back(new Pawn(static_cast<File>(i), static_cast<Rank>(1), PieceType::typePawn, Player::white));
    }


    blackPieces.push_back(new Rook(static_cast<File>(0), static_cast<Rank>(7), PieceType::typeRook, Player::black));
    blackPieces.push_back(new Knight(static_cast<File>(1), static_cast<Rank>(7), PieceType::typeKnight, Player::black));
    blackPieces.push_back(new Bishop(static_cast<File>(2), static_cast<Rank>(7), PieceType::typeBishop, Player::black));
    blackPieces.push_back(new Queen(static_cast<File>(3), static_cast<Rank>(7), PieceType::typeQueen, Player::black));
    blackPieces.push_back(new King(static_cast<File>(4), static_cast<Rank>(7), PieceType::typeKing, Player::black));
    blackPieces.push_back(new Bishop(static_cast<File>(5), static_cast<Rank>(7), PieceType::typeBishop, Player::black));
    blackPieces.push_back(new Knight(static_cast<File>(6), static_cast<Rank>(7), PieceType::typeKnight, Player::black));
    blackPieces.push_back(new Rook(static_cast<File>(7), static_cast<Rank>(7), PieceType::typeRook, Player::black));
    
    // 폰 (6랭크)
    for(int i = 0; i < File::Filesize; ++i) {
        blackPieces.push_back(new Pawn(static_cast<File>(i), static_cast<Rank>(6), PieceType::typePawn, Player::black));
    }


    // 2. GameState 초기화 (vector<Piece*>를 인자로 받는 생성자 사용)
    GameState w(whitePieces, Player::white);
    GameState b(blackPieces, Player::black);

    // 3. 게임 시작
	Game game(board, &w, &b, Player::white);
    GameMode gameMode = GameMode::classical;

    std::cout << "=========================================\n";
    std::cout << "||                                     ||\n";
    std::cout << "||             CHESS GAME              ||\n";
    std::cout << "||                                     ||\n";
    std::cout << "||   1. 게임 시작                      ||\n";
    std::cout << "||   2. 게임 모드                      ||\n";
    std::cout << "||   3. 게임 규칙                      ||\n";
    std::cout << "||   4. 종료                           ||\n";
    std::cout << "||                                     ||\n";
    std::cout << "=========================================\n";
    std::cout << ">> 선택하세요: ";
    int num; cin >> num;
    switch(num)
    {
	    case 1:
            while (true)
	        {
		        system("cls");
		        game.RefreshBoard();
		        game.ShowBoard();
		        //system("pause");
		        string startPos, endPos;
		        cout << "움직일 기물 위치 입력: ";
		        cin >> startPos;
		        cout << "도착할 위치 입력: ";
		        cin >> endPos;
		        game.MovePiece(startPos, endPos);
	        }
            break;
        case 2:
            gameMode = ChoiceGameMode();
            break;
        case 3:
            game.ShowCommand();
            
    }
}

GameMode ChoiceGameMode()
{
    cout << "1. 클래시컬 2. 래피드 3. 블리츠 \n>>번호를 입력하세요: ";
    int n; cin >> n;
    switch(n)
    {
        case 1: return GameMode::classical;
        case 2: return GameMode::rapid;
        case 3: return GameMode::blitz;
    }
    cout;
}
void InitializeConsole() {
#if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
        case 4: return GameMode::bullet;
        return GameMode::classical;
    }
}

void StartGame(Game game)
{
    while (true)
	{
	system("cls");
	game.RefreshBoard();
	game.ShowBoard();
    system("pause");
	string startPos, endPos;
	cout << (game.GetTrun() == 0 ? "white" : "black") << " | 움직일 기물 위치 입력: ";
	cin >> startPos;
	cout << (game.GetTrun() == 0 ? "white" : "black") << " | 도착할 위치 입력: ";
	cin >> endPos;
	game.MovePiece(startPos, endPos);
	}
}
