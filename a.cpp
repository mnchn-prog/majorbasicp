#include <iostream>
#include <vector> // GameState 초기화를 위해 필요
#include <algorithm> // GameState 초기화를 위해 필요
#include <iterator> // GameState 초기화를 위해 필요
#include <utility>  // ShowRule pair()


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
void StartGame(Game game);
void ShowRule();

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
        case 3:
            ShowRule();
        case 4:
            return 0;
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

void StartGame(Game game)
{
    while (true)
	{
        system("pause");
	    system("cls");

        game.RefreshBoard();
        game.UpdateTime(); // 턴 시간 차감
	    game.ShowBoard();

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
            
            else if(startPos.length() != 2)
            {
                // 문법 오류 결과 표시
                game.UpdateTime();            
                bool isEnd = game.checkTimeZero();
                if(isEnd) return;
                continue;
            }

            File startX = static_cast<File>(startPos[0] - 'a');
            Rank startY = static_cast<Rank>(startPos[1] - '1');
            selectedPiece = game.SelectStartPos(startX, startY);

            if(selectedPiece == nullptr) // 입력이 잘못됐을 때 처리
            {
                game.UpdateTime();            
                bool isEnd = game.checkTimeZero();
                if(isEnd) return;
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

            File endX = static_cast<File>(endPos[0] - 'a');
            Rank endY = static_cast<Rank>(endPos[1] - '1');
            if(endPos.length() != 2)
            {
                // 문법 오류결과 표시
                break; // 좌표형식이 아닐 경우에 다시 주 프롬포트
            }
            bool isPosForm = false;
	        availableEndPos = game.SelectEndPos(selectedPiece, endX, endY, isPosForm);
            if(!isPosForm) break; // 좌표 형식 자체가 아니면 다시 주 프롬포트
	    }
    }
}
int get_visual_width(const string& s) {
    int width = 0;
    for (size_t i = 0; i < s.length(); ) {
        unsigned char c = s[i];
        if (c < 0x80) { // ASCII 문자 (1바이트)
            width += 1;
            i += 1;
        }
        else { // 멀티바이트 문자 (한글 등)
            width += 2;
            i += 3; // UTF-8 한글은 3바이트
        }
    }
    return width;
}
void ShowRule()
{
    cout << "[Welcome to Chess World]" << endl;
    cout << "체스를 모방한 2인용 게임으로 백과 흑이 차례를 번갈아가면서 진행한다. " << endl;
    cout << "각 차례에 체스판의 좌표를 입력하여 기물을 선택하고 이동할 수 있다. " << endl;
    cout << "기물마다 이동방법은 상이하며 규칙으로 정의된 움직임만을 허용한다. " << endl;
    cout << "상대방의 왕을 먼저 잡으면 승리하고 시간을 다 써버리면 패배한다. " << endl;
    cout << "또한 항복, 합의에 의한 무승부로 게임을 종료할 수 있다." << endl;
    std::vector<std::pair<std::string, std::string>> data = {
         {"폰", "기본 한칸 전진, 처음만 두칸 가능"},
         {"나이트", "L자 형태로 앞으로 2칸 옆으로 1칸"},
         {"비숍", "대각선 방향으로 원하는 만큼 이동 가능하다."},
         {"룩", "사방으로 원하는 만큼 이동할 수 있다."},
         {"퀸", "모든방향으로 원하는 만큼 이동할 수 있다"},
         {"킹", "모든방향으로 한 칸씩만 움직일 수 있다."}
    };

    std::string header1 = "기물";
    std::string header2 = "이동방법";

    // 너비 설정
    int col1_width = 15;
    int col2_width = 45;

    // --- 표 그리기 시작 ---

    // 1. 상단 테두리
    std::cout << "┌";
    for (int i = 0; i < col1_width; ++i) std::cout << "─";
    std::cout << "┬";
    for (int i = 0; i < col2_width; ++i) std::cout << "─";
    std::cout << "┐" << std::endl;

    // 2. 헤더 내용
    std::cout << "│ " << header1;
    for (int i = 0; i < col1_width - get_visual_width(header1) - 1; ++i) std::cout << " ";
    std::cout << "│ " << header2;
    for (int i = 0; i < col2_width - get_visual_width(header2) - 1; ++i) std::cout << " ";
    std::cout << "│" << std::endl;

    // 3. 헤더와 내용의 구분선
    std::cout << "├";
    for (int i = 0; i < col1_width; ++i) std::cout << "─";
    std::cout << "┼";
    for (int i = 0; i < col2_width; ++i) std::cout << "─";
    std::cout << "┤" << std::endl;

    // 4. 데이터 내용 (4줄)
    for (const auto& row : data) {
        std::cout << "│ " << row.first;
        for (int i = 0; i < col1_width - get_visual_width(row.first) - 1; ++i) std::cout << " ";
        std::cout << "│ " << row.second;
        for (int i = 0; i < col2_width - get_visual_width(row.second) - 1; ++i) std::cout << " ";
        std::cout << "│" << std::endl;
    }

    // 5. 하단 테두리
    std::cout << "└";
    for (int i = 0; i < col1_width; ++i) std::cout << "─";
    std::cout << "┴";
    for (int i = 0; i < col2_width; ++i) std::cout << "─";
    std::cout << "┘" << std::endl;

    _getch();
    return;
}