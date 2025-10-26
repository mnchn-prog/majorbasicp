#include <iostream>
#include <vector>    // GameState 초기화를 위해 필요
#include <algorithm> // GameState 초기화를 위해 필요
#include <iterator>  // GameState 초기화를 위해 필요

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
// g++ -o ChessGame a.cpp Game.cpp GameState.cpp Piece.cpp Knight.cpp Bishop.cpp Pawn.cpp Rook.cpp Queen.cpp King.cpp -finput-charset=UTF-8 -fexec-charset=UTF-8 -std=c++11
Cell board[Rank::Ranksize][File::Filesize];

GameMode ChoiceGameMode();
void StartGame(Game &game);
void ShowRule();
int get_visual_width(const string &s);
std::string trim(const std::string& s);

int main()
{
    // ⬇️ Windows 환경에서 콘솔 출력 인코딩을 UTF-8로 설정
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // 3. 게임 시작
    GameMode gameMode = GameMode::classical;
    while (true)
    {
        // 1. 기물 초기 배치 및 목록 생성
        vector<Piece *> whitePieces;
        vector<Piece *> blackPieces;

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
        for (int i = 0; i < File::Filesize; ++i)
        {
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
        for (int i = 0; i < File::Filesize; ++i)
        {
            blackPieces.push_back(new Pawn(static_cast<File>(i), static_cast<Rank>(6), PieceType::typePawn, Player::black));
        }

        // 2. GameState 초기화 (vector<Piece*>를 인자로 받는 생성자 사용)
        GameState w(whitePieces, Player::white);
        GameState b(blackPieces, Player::black);

        string num;
        int inum;

        
        while (true)
        {

            cout << "=========================================\n";
            cout << "||                                     ||\n";
            cout << "||             CHESS GAME              ||\n";
            cout << "||                                     ||\n";
            cout << "||   1. 게임 시작                      ||\n";
            cout << "||   2. 게임 모드                      ||\n";
            cout << "||   3. 게임 규칙                      ||\n";
            cout << "||   4. 종료                           ||\n";
            cout << "||                                     ||\n";
            cout << "=========================================\n";
            cout << ">> 선택하세요: ";
            getline(cin, num);
            try
            {
                inum = stoi(num);
            }
            catch (const exception &e)
            {
                cout << "오류: 불가능한 입력입니다. 1부터 4까지의 숫자 중 하나를 입력하세요.\n";
                system("pause");
                system("cls");
                continue;
            }
            if (1 > inum || inum > 4)
            {
                cout << "오류: 불가능한 입력입니다. 1부터 4까지의 숫자 중 하나를 입력하세요.\n";
                system("pause");
                system("cls");
            }
            else
                break;
        }

        switch (inum)
        {
        case 1:
            {
                Game game(board, &w, &b, Player::white, gameMode);
                StartGame(game);
                break;
            }
        case 2:
            { 
                gameMode = ChoiceGameMode();
                system("pause");
                system("cls");
                break;
            }
        case 3:
            {
                system("cls");
                ShowRule();
                system("pause");
                system("cls");
                break;
            }
        case 4:
            return 0;
        }
    }
}

GameMode ChoiceGameMode()
{
    while (true)
    {
        cout << "1. 클래시컬 2. 래피드 3. 블리츠 \n>> 번호를 입력하세요: ";
        string num;
        int inum;

        getline(cin, num);
        try
        {
            inum = stoi(num);
        }
        catch (const exception &e)
        {
            cout << "오류: 불가능한 입력입니다. 1부터 3까지의 숫자 중 하나를 입력하세요.\n";
            system("pause");
            system("cls");
            continue;
        }
        if (1 > inum || inum > 3)
        {
            cout << "오류: 불가능한 입력입니다. 1부터 3까지의 숫자 중 하나를 입력하세요.\n";
            system("pause");
            system("cls");
        }
        else
        {
            switch (inum)
            {
            case 1:
                cout << "클래시컬 모드로 설정되었습니다." << endl;
                return GameMode::classical;
            case 2:
                cout << "래피드 모드로 설정되었습니다." << endl;
                return GameMode::rapid;
            case 3:
                cout << "블리츠 모드로 설정되었습니다." << endl;
                return GameMode::blitz;
            }
        }
    }
}

void StartGame(Game &game)
{
    Player drawOfferBy = Player::playerNone;
    bool printCheck = true, printMove = false;
    game.StartTimer();
    while (true)
    {
        bool drawOffered = false;
        system("cls");
        bool whiteChecked = false, blackChecked = false;
        if (game.RefreshBoard(whiteChecked, blackChecked))
        {
            cout << 
            system("pause");
            return;
        }

        string startPos, endPos;
        Piece *selectedPiece = nullptr;
        while (selectedPiece == nullptr)
        {
            system("cls");
            game.ShowBoard(whiteChecked, blackChecked, printMove, printCheck);
            if(whiteChecked || blackChecked || printMove)
            {
                system("cls");
                game.ShowBoard(whiteChecked, blackChecked);
            }
            cout << "움직일 기물 위치 입력: ";

            getline(cin, startPos);
            startPos = trim(startPos);

            // ⬇️ tt 또는 TT 입력 시 현재 시간 출력
            if (startPos == "tt" || startPos == "TT")
            {
                system("pause");
                game.UpdateTime();
                system("cls");
                game.ShowBoard(whiteChecked, blackChecked);
                system("pause");
                printCheck = false;
                printMove = false;
                continue;
            }

            // ⬇️ GG 또는 gg 입력 시 항복 처리
            if (startPos == "gg" || startPos == "GG")
            {
                cout << "정말로 항복하시겠습니까? (항복하려면 \"gg\" 또는 \"GG\"를 입력하세요.): ";
                string answer;
                /*cin.clear(); // 스트림 상태 플래그 초기화
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                */
               getline(cin, answer);
                if (answer == "gg" || answer == "GG")
                {
                    cout << (game.GetTrun() == Player::white ? "white" : "black") << "님이 항복했습니다." << endl;
                    system("pause");
                    system("cls");
                    return;
                }
                else
                {
                    printCheck = false;
                    printMove = false;
                    continue;
                }
            }

            // ⬇️ BB 또는 bb 입력 시 무승부 처리
            if (startPos == "bb" || startPos == "BB")
            {
                system("cls");

                game.ShowBoard(whiteChecked, blackChecked, false, false, true);
                Player currentPlayer = game.GetTrun() == 0 ? Player::white : Player::black;

                if (!drawOffered)
                {
                    drawOffered = true;
                    drawOfferBy = currentPlayer;
                    cout << "무승부를 제안했습니다. 수락하려면 BB 또는 bb 입력하세요.\n";

                    string answer;
                    /*
                    cin.clear(); // 스트림 상태 플래그 초기화
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    */
                    getline(cin, answer);
                    if (answer == "bb" || answer == "BB")
                    {
                        cout << "무승부가 합의되었습니다, 게임 종료" << endl;
                        system("pause");
                        system("cls");
                        return;
                    }

                    else
                    {
                        printCheck = false;
                        printMove = false;
                        continue;
                    }
                }

                else
                {
                    cout << "이미 이번 턴에 무승부가 신청되었습니다.\n";
                }
            }

            selectedPiece = game.SelectStartPos(startPos);

            if (selectedPiece == nullptr) // 입력이 잘못됐을 때 처리
            {
                if (game.checkTimeZero())
                    return;
                system("pause");
                system("cls");
                game.UpdateTime();
                printCheck = false;
                printMove = false;
            }
        }

        bool availableEndPos = false;
        while (availableEndPos == false)
        {
            cout << "도착할 위치 입력: ";
            getline(cin, endPos);
            endPos = trim(endPos);
            if (endPos == "qq" || endPos == "QQ") // 되돌리기일 경우 다시 주 프롬포트
            {
                printCheck = false;
                printMove = false;
                break;
            }

            bool isPosForm = false;
            game.UpdateTime();
            availableEndPos = game.SelectEndPos(selectedPiece, endPos, isPosForm);
            if (!isPosForm)
            {
                game.UpdateTime();
                if (game.checkTimeZero())
                    return;
                printCheck = false;
                printMove = false;
                break; // 좌표 형식 자체가 아니면 다시 주 프롬포트
            }
            else
            {
                printCheck = true;
                printMove = true;
            }
        }
        system("pause");
    }
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
        {"킹", "모든방향으로 한 칸씩만 움직일 수 있다."}};

    std::string header1 = "기물";
    std::string header2 = "이동방법";

    // 너비 설정
    int col1_width = 15;
    int col2_width = 45;

    // --- 표 그리기 시작 ---

    // 1. 상단 테두리
    std::cout << "┌";
    for (int i = 0; i < col1_width; ++i)
        std::cout << "─";
    std::cout << "┬";
    for (int i = 0; i < col2_width; ++i)
        std::cout << "─";
    std::cout << "┐" << std::endl;

    // 2. 헤더 내용
    std::cout << "│ " << header1;
    for (int i = 0; i < col1_width - get_visual_width(header1) - 1; ++i)
        std::cout << " ";
    std::cout << "│ " << header2;
    for (int i = 0; i < col2_width - get_visual_width(header2) - 1; ++i)
        std::cout << " ";
    std::cout << "│" << std::endl;

    // 3. 헤더와 내용의 구분선
    std::cout << "├";
    for (int i = 0; i < col1_width; ++i)
        std::cout << "─";
    std::cout << "┼";
    for (int i = 0; i < col2_width; ++i)
        std::cout << "─";
    std::cout << "┤" << std::endl;

    // 4. 데이터 내용 (4줄)
    for (const auto &row : data)
    {
        std::cout << "│ " << row.first;
        for (int i = 0; i < col1_width - get_visual_width(row.first) - 1; ++i)
            std::cout << " ";
        std::cout << "│ " << row.second;
        for (int i = 0; i < col2_width - get_visual_width(row.second) - 1; ++i)
            std::cout << " ";
        std::cout << "│" << std::endl;
    }

    // 5. 하단 테두리
    std::cout << "└";
    for (int i = 0; i < col1_width; ++i)
        std::cout << "─";
    std::cout << "┴";
    for (int i = 0; i < col2_width; ++i)
        std::cout << "─";
    std::cout << "┘" << std::endl;
    return;
}

int get_visual_width(const string &s)
{
    int width = 0;
    for (size_t i = 0; i < s.length();)
    {
        unsigned char c = s[i];
        if (c < 0x80)
        { // ASCII 문자 (1바이트)
            width += 1;
            i += 1;
        }
        else
        { // 멀티바이트 문자 (한글 등)
            width += 2;
            i += 3; // UTF-8 한글은 3바이트
        }
    }
    return width;
}

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    if (start == std::string::npos) return ""; // 모두 공백이면 빈 문자열 반환
    return s.substr(start, end - start + 1);
}