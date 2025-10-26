#include "Game.h"
#include <algorithm>

using namespace std;

string Game::unicodeForPiece(Player color, PieceType p) const{

    if(color == Player::black)
    {
        switch(p){
            case PieceType::typeKing: return "♚"; case PieceType::typeQueen: return "♛"; case PieceType::typeRook: return "♜";
            case PieceType::typeBishop: return "♝"; case PieceType::typeKnight: return "♞"; case PieceType::typePawn: return "♟";
            default: return ".";
        }
    }
    else
    {
        switch(p){
            case PieceType::typeKing: return "♔"; case PieceType::typeQueen: return "♕"; case PieceType::typeRook: return "♖";
            case PieceType::typeBishop: return "♗"; case PieceType::typeKnight: return "♘"; case PieceType::typePawn: return "♙";
            default: return ".";
        }
    }
    // ⚠️ 함수가 string을 반환해야 하지만, switch문 외부에서 반환하지 않을 수 있어 return을 추가합니다.
    return ".";
}

Piece* Game::SelectStartPos(File startX, Rank startY) {

    // 입력 유효성 검사
    if (startX < 0 || startX >= File::Filesize || startY < 0 || startY >= Rank::Ranksize) {
        ShowCommand(); // 여기에 문자열 대신 표준 명령어 출력(완)
        return nullptr;
    }
    Piece* whitePiece = whiteState->getPieceInBoard(startX, startY);
    Piece* blackPiece = blackState->getPieceInBoard(startX, startY);

    // 자기 턴의 말인지 확인
    if (turn == Player::white && whitePiece != nullptr) return whitePiece;
    if (turn == Player::black && blackPiece != nullptr) return blackPiece;

    else 
    {
        cout << "해당 칸에  선택가능한 기물이 없습니다" << endl;
    }
    return nullptr;
}

// --------------------------------------
// ② 도착 위치 입력 및 이동 처리
// --------------------------------------
bool Game::SelectEndPos(Piece* currentPiece, File endX, Rank endY, bool& isPosForm) {
    // 입력 유효성 검사

    if (endX < 0 || endX >= File::Filesize || endY < 0 || endY >= Rank::Ranksize) {
        ShowCommand(); // 여기에 문자열 대신 표준 명령어 출력(완)
        return false;
    }

    Piece* capturedPiece = nullptr;

    // 이동 시도
    if (currentPiece->MovePos(endX, endY, board, capturedPiece)) 
    {
        // 말이 잡혔다면 제거
        if (capturedPiece != nullptr) 
        {
            RemovePiece(capturedPiece, turn == Player::white ? Player::black : Player::white);
        }

        // 턴 전환
        turn = (turn == Player::white ? Player::black : Player::white);
        cout << "기물이 이동되었습니다." << endl;
        // 체크입니다 5초간 출력, 킹이 잡혔다면 게임결과 출력
        return true;
    } 
    
    else 
    {
        cout << "잘못된 	행마입니다." << endl;
        isPosForm = true;
        return false;
    }
}
/*
void Game::MovePiece(string startPos, string endPos)
{
	GameState* curState = turn == Player::white ? whiteState : blackState;
	
    // 턴 전환 로직은 말을 움직일 수 있는지 확인 후, MovePos가 성공했을 때만 실행되어야 하므로 아래에서 수정하겠습니다.
	// turn = (turn == Player::white ? Player::black : Player::white);

	//좌표 유효성 검사
	if (startPos[0] < 'a' || startPos[0] > 'h' || startPos[1] < '1' || startPos[1] > '8')
	{
		cout << "유효하지 않은 출발지점 입력값입니다" << endl;
		return;
	}
	File startX = static_cast<File>(startPos[0] - 'a');
	Rank startY = static_cast<Rank>(startPos[1] - '1');
    
    // 턴 소유권 검사를 위해 양쪽 GameState에서 기물을 찾습니다.
    Piece* whitePiece = whiteState->getPieceInBoard(startX, startY);
    Piece* blackPiece = blackState->getPieceInBoard(startX, startY);
    Piece* currentPiece = nullptr;

    if (whitePiece != nullptr && turn == Player::white) {
        currentPiece = whitePiece;
    } else if (blackPiece != nullptr && turn == Player::black) {
        currentPiece = blackPiece;
    }
    
    if (currentPiece == nullptr)
	{
        // 턴은 맞는데 말이 없는 경우
        if ((whitePiece != nullptr || blackPiece != nullptr) && 
            (whitePiece != nullptr ? turn != Player::white : turn != Player::black)) {
            cout << (turn == Player::white ? "흑색 말" : "흰색 말") << "은 움직일 수 없습니다." << endl;
        } else {
            cout << "입력한 좌표에 기물이 없습니다." << endl;
        }
		system("pause");
        return;
	}


	// 문제 없으면 
	if (endPos[0] < 'a' || endPos[0] > 'h' || endPos[1] < '1' || endPos[1] > '8')
	{
		cout << "유효하지 않은 도착지점 입력값입니다" << endl;
		system("pause");

		return;
	}

	File endX = static_cast<File>(endPos[0] - 'a');
	Rank endY = static_cast<Rank>(endPos[1] - '1');
	// 기물 잡기
    Piece* capturedPiece = nullptr;
    // 기물 이동 시도
	if(currentPiece->MovePos(endX, endY, board, capturedPiece))
    {
        turn = (turn == Player::white ? Player::black : Player::white);
        if(capturedPiece != nullptr)
        {
            RemovePiece(capturedPiece, turn); // white면 black이 잡히니까 턴 넘긴다음에 하면 똑같음
        }
    }
    else
    {
        // 다시 입력받기 근데 구조 바꿔야함. 기획서대로면 startPos 먼저 받고 검증, 문제 없으면 endPos 받기
    }
}
*/
void Game::RemovePiece(Piece* capturedPiece, Player color)
{
    GameState* curState = color == Player::white ? whiteState : blackState;
    vector<Piece*>& p = curState->GetPieces(); 

    // 1. std::remove_if로 잡힌 기물 포인터의 위치를 끝으로 이동시킴
    auto new_end = std::remove_if(p.begin(), p.end(), 
        [capturedPiece](Piece* currentPiece) {
            return currentPiece == capturedPiece;
        });

    // 2. vector의 크기를 실제로 줄임 (delete는 하지 않음!)
    if (new_end != p.end()) {
        p.erase(new_end, p.end());
    }

    delete capturedPiece; 
}

void Game::RefreshBoard()
{
    Position wKingPos, bKingPos;
    wKingPos.x = bKingPos.x = File::Filesize;
	wKingPos.y = bKingPos.y = Rank::Ranksize;
    for (int i = 0; i < Rank::Ranksize; i++)
	{
		for (int j = 0; j < File::Filesize; j++)
		{
			Piece* whitePiece = whiteState->getPieceInBoard(static_cast<File>(j), static_cast<Rank>(i));
			Piece* blackPiece = blackState->getPieceInBoard(static_cast<File>(j), static_cast<Rank>(i));
			if (whitePiece != nullptr) 
			{
				board[i][j] = Cell(Player::white, whitePiece->GetType(), false, false, whitePiece);
                if(whitePiece->GetType() == PieceType::typeKing)
                {
                    wKingPos = whitePiece->GetPos();
                }
            }
			else if (blackPiece != nullptr) 
			{
				board[i][j] = Cell(Player::black, blackPiece->GetType(), false, false, blackPiece);
                if(blackPiece->GetType() == PieceType::typeKing)
                {
                    bKingPos = blackPiece->GetPos();
                }
            }
			else 
			{
				board[i][j] = Cell(Player::playerNone, PieceType::typeNone, false, false, nullptr);
			}
		}
	}
	if(wKingPos.x == 8 && wKingPos.y == 8)
    {
        //게임 결과 출력 (흑 승)
    }
    else if(bKingPos.x == 8 && bKingPos.y == 8)
    {
        //게임 결과 출력 (백 승)
    }

    vector<Piece*> whitePieces = whiteState->GetPieces();
    vector<Piece*> blackPieces = blackState->GetPieces();

    for(Piece* p : whitePieces)
    {
        for(auto pos : p->CheckAttackCell(board))
        {
            board[pos.second][pos.first].AttckedByWhite = true;
        }
    }

    for(Piece* p : blackPieces)
    {
        for(auto pos : p->CheckAttackCell(board))
        {
            board[pos.second][pos.first].AttackedByBlack = true;
        }
    }
    if(board[wKingPos.x][wKingPos.y].AttackedByBlack)
    {
        cout << "체크입니다" << endl; // 5초간..? 스레드 슬립?
    }
    if(board[bKingPos.x][bKingPos.y].AttckedByWhite)
    {
        cout << "체크입니다" << endl; // 5초간?
    }
}

void Game::ShowBoard() const
{
    // 1. 상단 경계선 출력
    cout << "black | " << FormatTime(blackTimeLeft) << endl;
    cout << "   ";
    for (int j = 0; j < File::Filesize; j++)
    {
        cout << "____";
    }
    cout << "_" << endl;
    
    for (int i = Rank::Ranksize - 1; i >= 0; i--)
    {
        // 2. 랭크 번호 (행 번호) 출력
        cout << " " << i + 1 << " "; 
        
        // 3. 기물과 세로 경계선 출력
        for (int j = 0; j < File::Filesize; j++)
        {
            cout << "|"; // 칸의 왼쪽 경계
            if (board[i][j].currentPiece == PieceType::typeNone) {
                cout << "   "; // 빈 칸은 공백 두 칸
            } else {
                // 기물 출력
                cout << " " << unicodeForPiece(board[i][j].pieceColor, board[i][j].currentPiece) << " "; 
            }
        }
        cout << "|"; // 맨 오른쪽 경계
        cout << endl;

        // 4. 칸 아래쪽 경계선 출력
        cout << "   ";
        for (int j = 0; j < File::Filesize; j++)
        {
            cout << "|___"; // 칸의 아래쪽 경계
        }
        cout << "|" << endl;
    }
    
    // 5. 파일 문자 (열 번호) 출력
    cout << "    ";
    for (int i = 0; i < File::Filesize; i++)
    {
        cout << " " << static_cast<char>(i + 'a') << "  "; // 파일 문자 사이 간격 조정
    }
    cout << endl;
    cout << "white | " << FormatTime(whiteTimeLeft) << endl;
}

void Game::SetGameMode(GameMode gm) {
    mode = gm;
    switch (mode)
    {
    case GameMode::classical: whiteTimeLeft = blackTimeLeft = 30 * 60; break;
    case GameMode::rapid: whiteTimeLeft = blackTimeLeft = 10 * 60; break;
    case GameMode::blitz: whiteTimeLeft = blackTimeLeft = 3 * 60; break;
    }
}
void Game::UpdateTime()
{
   auto now = std::chrono::steady_clock::now();
   int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastMoveTime).count();
   if(turn == Player::black) whiteTimeLeft -= elapsed;
   else blackTimeLeft -= elapsed;
   lastMoveTime = now;
}

string Game::FormatTime(int sec) const
{
   int m = sec / 60;
   int s = sec % 60;
   char buf[6];
   sprintf(buf, "%02d:%02d", m, s);
   return string(buf);
}

int Game::get_visual_width(const string& s) {
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

void Game::ShowCommand()
{
    std::vector<std::pair<std::string, std::string>> data = {
     {"[a-h][1-8]", "움직일 기물을 선택한다."},
     {"gg, GG", "상대에게 항복한다"},
     {"bb, BB", "무승부를 신청한다"},
     {"tt, TT", "남은 시간을 갱신한다．"},
     {"qq, QQ", "좌표를 다시 선택한다."},
    };

    std::string header1 = "명령어";
    std::string header2 = "해석";

    // 너비 설정
    int col1_width = 15;
    int col2_width = 25;

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