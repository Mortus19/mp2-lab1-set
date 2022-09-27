// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

/*
int  BitLen; // длина битового поля - макс. к-во битов
TELEM* pMem; // память для представления битового поля
int  MemLen; // к-во эл-тов Мем для представления бит.поля
*/
TBitField::TBitField(int len)
{
    if (len < 0) {
        throw "Len must be not negative";
    }
    
    BitLen = len;
    MemLen = (len + (sizeof(TELEM)*8) - 1) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }


}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{

    if (pMem!=nullptr) {
        delete pMem;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n + ((sizeof(TELEM) * 8)) - 1) / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (1 << n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8)) * (sizeof(TELEM) * 8);
    pMem[index] |= GetMemMask(number_bit);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8)) * (sizeof(TELEM) * 8);
    pMem[index] &= ~(GetMemMask(number_bit));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8)) * (sizeof(TELEM) * 8);
    return pMem[index] & GetMemMask(number_bit);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return FAKE_BITFIELD;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
