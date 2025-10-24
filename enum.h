#pragma once

enum PieceType
{
	typeNone,
	typePawn,
	typeKnight,
	typeBishop,
	typeRook,
	typeQueen,
	typeKing
};

enum File
{
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	Filesize
};

enum Rank
{
	one,
	two,
	thr,
	fou,
	fiv,
	six,
	sev,
	egi,
	Ranksize
};

enum Player
{
	white,
	black,
	playerNone
};

enum GameMode
{
	classical,
	rapid,
	blitz,
};

