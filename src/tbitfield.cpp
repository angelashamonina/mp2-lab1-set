// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) 
	{ 
		throw "incorrect len"; 
	}
	BitLen = len;
	MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < (MemLen); i++)
	{
		pMem[i] = bf.pMem[i];
	}

}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen - 1)) 
	{ 
		throw "incorrect index";
	}
	else { 
		return (n / (8 * sizeof(TELEM))); 
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > BitLen - 1) || (n < 0)) 
	{ 
		throw "Negative n-bit"; 
	}
	else {
		return  (1 << (n % (8 * sizeof(TELEM))));
	}
}
// доступ к битам битового поля
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > BitLen - 1) || (n < 0)) 
	{ 
		throw "Negative n-bit"; 
	}
	else { 
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > BitLen - 1) || (n < 0)) 
	{ 
		throw "Negative n-bit"; 
	}
	else {
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > BitLen - 1) || (n < 0)) 
	{
		throw "Negative n-bit"; 
	}
	if (pMem[GetMemIndex(n)] & GetMemMask(n)) 
	{
		return 1; 
	}
	else {
		return 0; 
	}
}
// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}

	else {
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i]) {

				return 0;
			}
		return 1;
			
	}

}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if ((*this) == bf)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = BitLen;
	if (BitLen < bf.BitLen)
	{
		len = bf.BitLen;
	}

	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}
	return tmp;

}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int len = BitLen;
	if (BitLen < bf.BitLen)
	{
		len = bf.BitLen;
	}
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}
	for (int i = bf.BitLen; i < BitLen; i++)
	{
		tmp.ClrBit(i);
	}
	return tmp;
	
}

TBitField TBitField::operator~(void) // отрицание
{

	TBitField tmp = (*this);
	for (int i = 0; i < BitLen; i++) {

		if (tmp.GetBit(i))
		{
			tmp.ClrBit(i);
		}

		else
		{
			tmp.SetBit(i);
		}

	}

	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char tmp;

	for (int i = 0; i < bf.GetLength(); i++)
	{
		istr >> tmp;

		if (tmp == '1')
		{
			bf.SetBit(i);
		}
		if (tmp == '0')
		{
			bf.ClrBit(i);
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
	{
		ostr << bf.GetBit(i);
	}
	ostr << "\n";
	return ostr;
}
str;
}
