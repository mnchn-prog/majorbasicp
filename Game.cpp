#include "Game.h"

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
void Game::RemovePiece(Piece* capturedPiece, Player color)
{
    GameState* curState = color == Player::white ? whiteState : blackState;
    vector<Piece*>& p = curState->GetPieces();
    auto new_end = std::remove_if(p.begin(), p.end(), 
        [capturedPiece](Piece* currentPiece) {
            // 원시 포인터 주소가 일치하는지 확인합니다.
            return currentPiece == capturedPiece;
        });

    // 3. 기물이 실제로 삭제되는지 확인하고 메모리를 해제합니다.
    // 삭제된 요소가 있다면 (즉, new_end가 p.end()가 아니라면)
    if (new_end != p.end()) {
        // new_end부터 p.end() 직전까지의 모든 포인터가 삭제 대상입니다.
        for (auto it = new_end; it != p.end(); ++it) {
            delete *it; // 힙 메모리 해제
            *it = nullptr; // 안전을 위해 포인터는 nullptr로 설정 (선택 사항)
        }
        
        // 4. erase 호출: vector의 크기를 실제로 줄입니다.
        p.erase(new_end, p.end());
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
				board[i][j] = Cell(Player::white, whitePiece->GetType(), false, false, whitePiece);
			}
			else if (blackPiece != nullptr) 
			{
				board[i][j] = Cell(Player::black, blackPiece->GetType(), false, false, blackPiece);
			}
			else 
			{
				board[i][j] = Cell(Player::playerNone, PieceType::typeNone, false, false, nullptr);
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

