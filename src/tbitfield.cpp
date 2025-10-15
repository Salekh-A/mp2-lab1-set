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



TBitField::TBitField(int len)
{
    BitLen = len;
    MemLen = (len + 31) / 32;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.BitLen;
    pMem = new TELEM(MemLen);
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << n % 32;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    pMem[GetMemIndex(n)] |= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0) {
        return 0;
    }
    else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    int k = 0;
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < MemLen; i++) {
            if (pMem == bf.pMem) k++;
        }
    }
    if (k == BitLen) return 1;
    else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 1;
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < MemLen; i++) {
            if (pMem != bf.pMem) return 1;
            else return 0;
        }
    }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int MaxLen;
    if (BitLen >= bf.BitLen) MaxLen = BitLen;
    else MaxLen = bf.BitLen;

    TBitField res(MaxLen);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = pMem[i];
    }

    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] |= pMem[i];
    }
    
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int MaxLen;
    if (BitLen >= bf.BitLen) MaxLen = BitLen;
    else MaxLen = bf.BitLen;

    TBitField res(MaxLen);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = pMem[i];
    }

    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] &= pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = ~pMem[i];
    }
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; i++) {
        int bit;
        istr >> bit;
        if (bit == 1) bf.SetBit(i);
        else bf.ClrBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        int bit;
        ostr << bf.GetBit(i);
    }
    return ostr;
}
