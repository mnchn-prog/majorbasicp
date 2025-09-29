#include <iostream>
#include <vector>
#include <string>
// ⚠️ UNICODE 정의를 windows.h 포함 이전에 추가
#define UNICODE 
#define _UNICODE 
#include <windows.h> // 콘솔 색상 제어를 위해 필요
#include <io.h>      // _setmode를 위해 필요
#include <fcntl.h>   // _O_U16TEXT를 위해 필요

using namespace std;

// 유니코드 체스 기물 (와이드 문자열 사용)
const wstring W_KING   = L"\u265A";  // ♔ 
const wstring W_QUEEN  = L"\u265B";  // ♕
const wstring W_ROOK   = L"\u265C";  // ♖
const wstring W_BISHOP = L"\u265D"; // ♗
const wstring W_KNIGHT = L"\u265E"; // ♘
const wstring W_PAWN   = L"\u265F";  // ♙

const wstring B_KING   = L"\u2654";  // ♚
const wstring B_QUEEN  = L"\u2655";  // ♛
const wstring B_ROOK   = L"\u2656";  // ♜
const wstring B_BISHOP = L"\u2657"; // ♝
const wstring B_KNIGHT = L"\u2658"; // ♞
const wstring B_PAWN   = L"\u2659";  // ♟

// 기물 정보 (공백은 빈 칸)
const wstring INITIAL_BOARD[8][8] = {
    {B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK},
    {B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN},
    {L" ", L" ", L" ", L" ", L" ", L" ", L" ", L" "},
    {L" ", L" ", L" ", L" ", L" ", L" ", L" ", L" "},
    {L" ", L" ", L" ", L" ", L" ", L" ", L" ", L" "},
    {L" ", L" ", L" ", L" ", L" ", L" ", L" ", L" "},
    {W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN},
    {W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK}
};

// 콘솔 핸들러
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// 콘솔 색상 설정 함수
void setConsoleColor(int foreground, int background) {
    SetConsoleTextAttribute(hConsole, foreground | (background << 4));
}

// 체스판 그리기 함수
void drawBoard(const wstring board[8][8]) {
    // 콘솔의 유니코드(와이드 문자열) 출력을 위해 UTF-16으로 모드 설정
    // 이 설정은 SetConsoleOutputCP(65001)과 함께 사용해야 함
    _setmode(_fileno(stdout), _O_U16TEXT);

    // 기본 콘솔 속성 저장
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD saved_attributes = csbi.wAttributes;

    // --------------------
    // 1. 열 인덱스 출력 (a ~ h)
    // --------------------
    setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0); 
    wcout << L" \n   ";
    for (int col = 0; col < 8; ++col) {
        wcout << L"   " << (wchar_t)('a' + col) << L"  "; 
    }
    wcout << endl;

    // --------------------
    // 2. 보드 본체 출력
    // --------------------
    for (int row = 0; row < 8; ++row) {
        // A. 경계선 출력 (선택 사항이지만, 보드를 명확하게 구분해줍니다)
        setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
        wcout << L"  -----------------------------------------" << endl;

        // B. 각 행 출력 (높이를 위해 한 줄에 모든 요소를 출력)
        
        // 행 인덱스 출력
        setConsoleColor(FOREGROUND_INTENSITY, 0); 
        wcout << (8 - row) << L" |"; // 행 번호 | 기물 칸 시작

        for (int col = 0; col < 8; ++col) {
            
            // 1. 체크무늬 배경색 결정 (WINDOWS_H 색상 코드)
            bool isLightSquare = (row + col) % 2 == 0;
            
            int BG_COLOR;
            // 밝은 칸: 회색 (밝은 배경)
            if (isLightSquare) {
                // 밝은 회색 (BACKGROUND_INTENSITY만 켜면 됨)
                BG_COLOR = BACKGROUND_INTENSITY; 
            } 
            // 어두운 칸: 검은색 (어두운 배경)
            else {
                BG_COLOR = 0; 
            }

            // 2. 기물 색상 결정 (글자색)
            wstring piece = board[row][col];
            int FG_COLOR;
            
            if (piece != L" ") {
                // 백팀 기물 (파랑)
                if (piece[0] >= 0x265A && piece[0] <= 0x265F) { 
                    FG_COLOR = FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 파란색 기물
                }
                // 흑팀 기물 (빨강)
                else if (piece[0] >= 0x2654 && piece[0] <= 0x2659) { 
                    FG_COLOR = FOREGROUND_RED | FOREGROUND_INTENSITY; // 빨간색 기물
                }
                else {
                    FG_COLOR = FOREGROUND_INTENSITY; // 빈 칸은 기본색
                }
            } else {
                // 빈 칸의 글자색은 배경과 같거나, 잘 안보이는 색으로 설정
                FG_COLOR = BG_COLOR; 
            }

            // 3. 색상 설정 및 출력
            setConsoleColor(FG_COLOR, BG_COLOR);
            wcout << L"  " << piece << L"  "; // 5칸 너비 출력 (기물 1칸 + 공백 4칸)
        }

        // 행 끝 마무리 및 색상 복원
        setConsoleColor(saved_attributes & 0xF, 0); // 글자색은 유지, 배경색은 검정(0)으로
        wcout << L" | " << (8 - row);   // 오른쪽 경계와 행 번호
        wcout << endl;
    }
    
    // C. 마지막 경계선 및 색상 초기화
    setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
    wcout << L"  -----------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, saved_attributes); // 저장된 기본 속성으로 완전히 복원
}

int main() {
    // 1. 유니코드 출력 설정 (Windows 콘솔 환경에서 필수)
    SetConsoleOutputCP(65001); // 출력 코드 페이지를 UTF-8 (65001)로 설정
    
    // 2. 콘솔 제목 설정
    SetConsoleTitle(L"C++ CLI Chess Project");

    // 3. 보드 출력
    drawBoard(INITIAL_BOARD);

    wcout << L"\n프로젝트 기본 세팅 완료! 기물 이동을 구현해 보세요." << endl;
    wcout << L"---" << endl;
    wcout << L"참고: 흰색 기물(백)은 파란색, 검은색 기물(흑)은 빨간색으로 표시됩니다." << endl;

    // 프로그램이 바로 종료되지 않도록 대기
    cin.get(); 

    return 0;
}
