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
    MemLen = (len + (sizeof(TELEM) * 8) - 1) / (sizeof(TELEM) * 8);
    if (len == 0) {
        pMem = nullptr;
        
    }
    else {
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = 0;
        }
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
    if (n < 0)
        throw "NOT GET INDEX";
    return (n + ((sizeof(TELEM) * 8)) - 1) / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0)
        throw "NOT GET MASK";
    return (1 << n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if(n < 0)
        throw "NOT SET BIT";
    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8)) * (sizeof(TELEM) * 8);
    pMem[index] |= GetMemMask(number_bit);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0)
        throw "NOT CLEAR BIT";
    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8)) * (sizeof(TELEM) * 8);
    pMem[index] &= ~(GetMemMask(number_bit));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0)
        throw "NOT GET BIT";
    int index = GetMemIndex(n);
    int number_bit = n - (n / (sizeof(TELEM) * 8)) * (sizeof(TELEM) * 8);
    return pMem[index] & GetMemMask(number_bit);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

    if (pMem != nullptr) {
        delete[]pMem;
    }
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (*this == bf)
        return 0;
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int size = max(BitLen, bf.BitLen);
    TBitField tmp(size);
    int blocks = max(MemLen, bf.MemLen);
    for (int i = 0; i < blocks; i++) {
        tmp.pMem[i] = 0;
        if (i < MemLen)
            tmp.pMem[i] |= pMem[i];
        if (i < bf.MemLen)
            tmp.pMem[i] |= bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int size = max(BitLen, bf.BitLen);
    TBitField tmp(size);
    int blocks = max(MemLen, bf.MemLen);
    for (int i = 0; i < blocks; i++) {
        if (i < MemLen && i<bf.MemLen)
            tmp.pMem[i] = pMem[i]&bf.pMem[i];
        else
            tmp.pMem[i]=0;
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (int i = 0; i < MemLen-1;i++) {
        tmp.pMem[i] = ~pMem[i];
    }
    int last_number_bit = BitLen - (MemLen - 1) * (sizeof(TELEM) * 8);
    tmp.pMem[MemLen - 1] = ~pMem[MemLen - 1];
    if (last_number_bit < sizeof(TELEM) * 8) {
        int mask = 1 << (last_number_bit + 1) - 1;
        tmp.pMem[MemLen - 1] &= mask;
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{

    
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i + 1)<<' ';
    }

    return ostr;
}
