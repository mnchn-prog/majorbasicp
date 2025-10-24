#include "Game.h"

string Game::unicodeForPiece(Player color, PieceType p) const{

    if(color == Player::black)
    {
        switch(p){
            case PieceType::typeKing: return "♚"; case PieceType::typeQueen: return "♛"; case PieceType::typeRook: return "♜";
            case PieceType::typeBishop: return "♝"; case PieceType::typeKnight: return "♞"; case PieceType::typePawn: return "♟";
            default: 
                return ".";
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
	
    // 기물 이동 시도
	if(currentPiece->MovePos(endX, endY, board))
    {
        turn = (turn == Player::white ? Player::black : Player::white);
    }
    else
    {
        // 다시 입력받기 근데 구조 바꿔야함. 기획서대로면 startPos 먼저 받고 검증, 문제 없으면 endPos 받기
    }
}

void Game::RefreshBoard()
{
	for (int i = 0; i < Rank::Ranksize; i++)
	{
		for (int j = 0; j < File::Filesize; j++)
		{
			Piece* whitePiece = whiteState->getPieceInBoard(static_cast<File>(j), static_cast<Rank>(i));
			Piece* blackPiece = blackState->getPieceInBoard(static_cast<File>(j), static_cast<Rank>(i));
			if (whitePiece != nullptr) 
			{
				board[i][j] = Cell(Player::white, whitePiece->GetType(), false, false);
			}
			else if (blackPiece != nullptr) 
			{
				board[i][j] = Cell(Player::black, blackPiece->GetType(), false, false);
			}
			else 
			{
				board[i][j] = Cell(Player::playerNone, PieceType::typeNone, false, false);
			}

            //공격 정보 초기화
            board[i][j].AttackedByBlack = board[i][j].AttckedByWhite = false;
		}
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
}

void Game::ShowBoard() const
{
    string space(11, ' ');
    char arrow = turn == Player::white ? '>' : '<';
    cout << "  Black" << space << arrow << space << "White  " << endl;
    cout << "  30:00" << space << " " << space << "30:00  " << endl;
    // 1. 상단 경계선 출력
    cout << "black | 03:00" << endl;
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
    cout << "white | 03:00" << endl;
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
void Game::ShowRule()
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
 //{"help", "도움말을 표시합니다."}
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
void Game::ShowCommand()
{
    std::vector<std::pair<std::string, std::string>> data = {
     {"[a-h][1-8]", "움직일 기물을 선택한다."},
     {"gg, GG", "상대에게 항복한다"},
     {"bb, BB", "무승부를 신청한다"},
     {"tt, TT", "남은 시간을 갱신한다．"},
     {"qq, QQ", "남은시간을 확인한다."},
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

