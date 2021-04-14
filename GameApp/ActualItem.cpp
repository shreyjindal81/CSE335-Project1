#include "pch.h"
#include "ActualItem.h"

CActualItem::CActualItem(std::wstring file, double x, double y, std::wstring id)
{
	mId = id;
	mFile = file;
	mX = x;
	mY = y;
}