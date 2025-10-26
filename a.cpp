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
void StartGame(Game& game);

int main()
{
    // ⬇️ Windows 환경에서 콘솔 출력 인코딩을 UTF-8로 설정
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    
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

    cout << "1. 게임 시작 2. 게임 모드 3. 게임 설명 4. 프로그램 종료 \n번호를 입력하세요(1~4): ";
    int num; cin >> num;
    GameMode gameMode = GameMode::classical;
	Game game(board, &w, &b, Player::white, gameMode);
    switch(num)
    {
	    case 1:
            StartGame(game);
            break;
        case 2:
            gameMode = ChoiceGameMode();
            game.SetGameMode(gameMode);
            break;
    }
}

GameMode ChoiceGameMode()
{
    cout << "1. 클래식(30분) 2. 래피드(10분) 3. 블리츠(3분) \n번호를 입력하세요: ";
    int n; cin >> n;
    switch(n)
    {
        case 1: return GameMode::classical;
        case 2: return GameMode::rapid;
        case 3: return GameMode::blitz;
        return GameMode::classical;
    }
}


void StartGame(Game& game)
{
    bool drawOffered = false;
    Player drawOfferBy = Player::playerNone;

    while (true)
	{
        system("pause");
	    system("cls");
        bool whiteChecked = false, blackChecked = false;
        game.RefreshBoard(whiteChecked, blackChecked);
	    game.ShowBoard(whiteChecked, blackChecked);

	    string startPos, endPos;
        Piece* selectedPiece = nullptr;
        while(selectedPiece == nullptr)
        {   
	        cout << (game.GetTrun() == 0 ? "white" : "black") << " | 움직일 기물 위치 입력: ";
	        cin >> startPos;
            
            // ⬇️ tt 또는 TT 입력 시 현재 시간 출력
            if (startPos == "tt" || startPos == "TT")
            {
                cout << "⏱ White 남은 시간: " << game.FormatTime(game.GetWhiteTime()) << endl;
                cout << "⏱ Black 남은 시간: " << game.FormatTime(game.GetBlackTime()) << endl;
                system("pause");
                continue;
            }
           // ⬇️ GG 또는 gg 입력 시 항복 처리
            if (startPos == "gg" || startPos == "GG")
            {
                cout << "🏳️ " << (game.GetTrun() == 0 ? "White" : "Black") << " 항복!" << endl;
                cout << "메인메뉴로 돌아가려면 Enter키를 누르세요..." << endl;
                system("pause");
                return;
            }
            // ⬇️ BB 또는 bb 입력 시 무승부 처리
            if (startPos == "bb" || startPos == "BB")
            {
                Player currentPlayer = game.GetTrun() == 0 ? Player::white : Player::black;

                if (!drawOffered)
                {
                    drawOffered = true;
                    drawOfferBy = currentPlayer;
                    cout << "🤝 무승부를 제안했습니다. 상대방이 수락하면 BB 또는 bb 입력하세요.\n";
                    system("pause");
                    continue;
                }
                else if (drawOfferBy != currentPlayer)
                {
                    cout << "🤝 무승부가 성립되었습니다!\n";
                    cout << "메인메뉴로 돌아가려면 Enter키를 누르세요..." << endl;
                    system("pause");
                    return;
                }
                else
                {
                    cout << "⚠️ 이미 무승부를 제안했습니다.\n";
                    system("pause");
                    continue;
                }
            }

            selectedPiece = game.SelectStartPos(startPos);

            if(selectedPiece == nullptr) // 입력이 잘못됐을 때 처리
            {
                if(game.checkTimeZero()) return;
                system("pause");
                system("cls");
                game.UpdateTime();
                game.ShowBoard(whiteChecked, blackChecked);
            }            
        }

        bool availableEndPos = false;
        while(availableEndPos == false)
        {
	        cout << (game.GetTrun() == 0 ? "white" : "black") << " | 도착할 위치 입력: ";
	        cin >> endPos;
            if(endPos == "qq" || endPos == "QQ") // 되돌리기일 경우 다시 주 프롬포트
            {
                break;
            }

            bool isPosForm = false;
            game.UpdateTime();
	        availableEndPos = game.SelectEndPos(selectedPiece, endPos, isPosForm);
            if(!isPosForm) 
            {
                game.UpdateTime();
                if(game.checkTimeZero()) return;
                break; // 좌표 형식 자체가 아니면 다시 주 프롬포트
            }
	    }
        if(game.checkTimeZero()) return;
    }
}