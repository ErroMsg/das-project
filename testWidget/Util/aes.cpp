#include <QDebug>
#include <QFile>
#include <string.h>
#include "aes.h"
#include <math.h>
#include <QPointF>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

const unsigned char AES::Sbox[16*16]=
{// populate the Sbox matrix
 /* 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f */
 /*0*/  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
 /*1*/  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
 /*2*/  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
 /*3*/  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
 /*4*/  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
 /*5*/  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
 /*6*/  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
 /*7*/  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
 /*8*/  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
 /*9*/  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
 /*a*/  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
 /*b*/  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
 /*c*/  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
 /*d*/  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
 /*e*/  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
 /*f*/  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const unsigned char AES::iSbox[16*16]=
{
    // populate the iSbox matrix
    /* 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f */
    /*0*/  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    /*1*/  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    /*2*/  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    /*3*/  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    /*4*/  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    /*5*/  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    /*6*/  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    /*7*/  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    /*8*/  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    /*9*/  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    /*a*/  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    /*b*/  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    /*c*/  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    /*d*/  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    /*e*/  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    /*f*/  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

const unsigned char AES::Rcon[11*4]=
{
    0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00,
    0x1b, 0x00, 0x00, 0x00,
    0x36, 0x00, 0x00, 0x00
};

AES::AES()
{
}

AES::AES(int keySize, unsigned char *key)
{
    // expand the seed key into a key schedule and store in w
    RunKeyExpansion(keySize, key);
}

AES::~AES()
{

}

void AES::FileCipher(QFile *fin, QFile *fout)
{
    unsigned char input[16];
    unsigned char output [16];

    if(fin->open(QIODevice::ReadOnly) && fout->open(QIODevice::ReadWrite))
    {
        while(!fin->atEnd())
        {
            memset((void *)input,0,16);
            fin->read((char*)input,16);
            Cipher(input,output);
            fout->write((char*)output,16);
        }
    }

    fin->close();
    fout->close();
}

void AES::FileInvCipher(QFile *fin, QFile *fout)
{
    unsigned char input[16];
    unsigned char output [16];

    if(fin->open(QIODevice::ReadOnly) && fout->open(QIODevice::ReadWrite))
    {
        while(!fin->atEnd())
        {
            memset((void *)input,0,16);
            fin->read((char*)input,16);
            InvCipher(input,output);
            fout->write((char*)output,16);
        }
    }

    fin->close();
    fout->close();
}

void AES::Cipher(unsigned char* input, unsigned char* output)  // encipher 16-bit input
{
    // state = input
    memset(&State[0][0],0,16);
    int i;
    for (i = 0; i < (4 * Nb); i++)//
    {
        State[i % 4][ i / 4] = input[i];
    }

    AddRoundKey(0);

    for (int round = 1; round <= (Nr - 1); round++)  // main round loop
    {
        SubBytes();
        ShiftRows();
        MixColumns();
        AddRoundKey(round);
    }  // main round loop

    SubBytes();
    ShiftRows();
    AddRoundKey(Nr);

    // output = state
    for (i = 0; i < (4 * Nb); i++)
    {
        output[i] =  State[i % 4][ i / 4];
    }

}  // Cipher()

void AES::InvCipher(unsigned char * input, unsigned char * output)  // decipher 16-bit input
{
    // state = input
    int i;
    memset(&State[0][0],0,16);
    for (i = 0; i < (4 * Nb); i++)
    {
        State[i % 4][ i / 4] = input[i];
    }

    AddRoundKey(Nr);

    for (int round = Nr-1; round >= 1; round--)  // main round loop
    {
        InvShiftRows();
        InvSubBytes();
        AddRoundKey(round);
        InvMixColumns();
    }  // end main round loop for InvCipher

    InvShiftRows();
    InvSubBytes();
    AddRoundKey(0);

    // output = state
    for (i = 0; i < (4 * Nb); i++)
    {
        output[i] =  State[i % 4][ i / 4];
    }

}  // InvCipher()

void AES::Cipher(unsigned char *input, unsigned char *output, unsigned char *key, int keySize)
{
    // expand the seed key into a key schedule and store in w
    RunKeyExpansion(keySize, key);
    Cipher(input, output);
}

void AES::InvCipher(unsigned char *input, unsigned char *output, unsigned char *key, int keySize)
{
    // expand the seed key into a key schedule and store in w
    RunKeyExpansion(keySize, key);
    InvCipher(input, output);
}

void AES::RunKeyExpansion(int keySize, unsigned char* keyBytes)
{
    SetNbNkNr(keySize);//初始化
    memcpy(key, keyBytes, keySize);
    KeyExpansion();
}

void AES::SetNbNkNr(int keyS)
{
    Nb = 4;     // block size always = 4 words = 16 bytes = 128 bits for AES
    if (keyS == Bits128)
    {
        Nk = 4;   // key size = 4 words = 16 bytes = 128 bits
        Nr = 10;  // rounds for algorithm = 10
    }
    else if (keyS == Bits192)
    {
        Nk = 6;   // 6 words = 24 bytes = 192 bits
        Nr = 12;
    }
    else if (keyS == Bits256)
    {
        Nk = 8;   // 8 words = 32 bytes = 256 bits
        Nr = 14;
    }
}  // SetNbNkNr()

void AES::KeyExpansion()
{
    unsigned char result[4],result2[4];
    memset(w,0,16*15);//没有根据key的位数进行开辟空间，直接开辟了最大空间
    int row;
    for (row = 0; row < Nk; row++)//Nk=4,6,8得到初始密码
    {
        w[4*row+0] =  key[4*row];
        w[4*row+1] =  key[4*row+1];
        w[4*row+2] =  key[4*row+2];
        w[4*row+3] =  key[4*row+3];
    }

    unsigned char temp[4];

    for (row = Nk; row < Nb * (Nr+1); row++)//产生密匙顺序表
    {
        temp[0] =  w[4*(row-1)+0];
        temp[1] =  w[4*(row-1)+1];
        temp[2] =  w[4*(row-1)+2];
        temp[3] =  w[4*(row-1)+3];

        if (row % Nk == 0)
        {
            RotWord(temp,result);
            SubWord(result,result2);
            memcpy(temp,result2,4);//
            //RotWord 例程非常简单，它接受 4 字节的数组并将它们向左旋转位移 1 位。
            //因为轮回次序表 w[] 有四列，所以 RotWord 会将一行 w[] 向左旋转位移.
            //SubWord 例程使用置换表 Sbox，针对密钥次序表 w[] 的给定行执行逐字节置换。
            temp[0] = (byte)( (int)temp[0] ^ (int) Rcon[4*(row/Nk)+0] );
            temp[1] = (byte)( (int)temp[1] ^ (int) Rcon[4*(row/Nk)+1] );
            temp[2] = (byte)( (int)temp[2] ^ (int) Rcon[4*(row/Nk)+2] );
            temp[3] = (byte)( (int)temp[3] ^ (int) Rcon[4*(row/Nk)+3] );
        }
        else if ( Nk > 6 && (row % Nk == 4) )
        {
            SubWord(temp,result);
            memcpy(temp,result,4);
        }
        // w[row] = w[row-Nk] xor temp
        w[4*row+0] = (byte) ( (int) w[4*(row-Nk)+0] ^ (int)temp[0] );
        w[4*row+1] = (byte) ( (int) w[4*(row-Nk)+1] ^ (int)temp[1] );
        w[4*row+2] = (byte) ( (int) w[4*(row-Nk)+2] ^ (int)temp[2] );
        w[4*row+3] = (byte) ( (int) w[4*(row-Nk)+3] ^ (int)temp[3] );
    }  // for loop
}  // KeyExpansion()

void AES::SubWord(unsigned char * word,unsigned char* result)
{//不要这样返回！
    result[0] =  Sbox[ 16*(word[0] >> 4)+ (word[0] & 0x0f) ];
    result[1] =  Sbox[ 16*(word[1] >> 4)+ (word[1] & 0x0f) ];
    result[2] =  Sbox[ 16*(word[2] >> 4)+ (word[2] & 0x0f) ];
    result[3] =  Sbox[ 16*(word[3] >> 4)+ (word[3] & 0x0f) ];
}

void AES::RotWord(unsigned char * word,unsigned char *result)
{//不要这样返回
    result[0] = word[1];
    result[1] = word[2];
    result[2] = word[3];
    result[3] = word[0];
}

void AES::AddRoundKey(int round)
{
    int r,c;
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {//w:    4*x+y
            State[r][c]=(unsigned char)((int)State[r][c]^(int)w[4*((round*4)+c)+r]);
        }
    }
}  // AddRoundKey()

void AES::SubBytes()
{
    int r,c;
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            State[r][c] =  Sbox[ 16*(State[r][c] >> 4)+ ( State[r][c] & 0x0f) ];
        }
    }
}  // SubBytes

void AES::InvSubBytes()
{
    int r,c;
    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            State[r][c] =  iSbox[ 16*( State[r][c] >> 4)+( State[r][c] & 0x0f) ];
        }
    }
}  // InvSubBytes

void AES::ShiftRows()
{
    unsigned char temp[4*4];
    int r,c;
    for (r = 0; r < 4; r++)  // copy State into temp[]
    {
        for (c = 0; c < 4; c++)
        {
            temp[4*r+c] =  State[r][c];
        }
    }
    //??
    for (r = 1; r < 4; r++)  // shift temp into State
    {
        for (c = 0; c < 4; c++)
        {
            State[r][c] = temp[ 4*r+ (c + r) % Nb ];
        }
    }
}  // ShiftRows()

void AES::InvShiftRows()
{
    unsigned char temp[4*4];
    int r,c;
    for (r = 0; r < 4; r++)  // copy State into temp[]
    {
        for (c = 0; c < 4; c++)
        {
            temp[4*r+c] =  State[r][c];
        }
    }
    for (r = 1; r < 4; r++)  // shift temp into State
    {
        for (c = 0; c < 4; c++)
        {
            State[r][ (c + r) % Nb ] = temp[4*r+c];
        }
    }
}  // InvShiftRows()

void AES::MixColumns()
{
    unsigned char temp[4*4];
    int r,c;
    for (r = 0; r < 4; r++)  // copy State into temp[]
    {
        for (c = 0; c < 4; c++)
        {
            temp[4*r+c] =  State[r][c];
        }
    }

    for (c = 0; c < 4; c++)
    {
        State[0][c] = (unsigned char) ( (int)gfmultby02(temp[0+c]) ^ (int)gfmultby03(temp[4*1+c]) ^
                                        (int)gfmultby01(temp[4*2+c]) ^ (int)gfmultby01(temp[4*3+c]) );
        State[1][c] = (unsigned char) ( (int)gfmultby01(temp[0+c]) ^ (int)gfmultby02(temp[4*1+c]) ^
                                        (int)gfmultby03(temp[4*2+c]) ^ (int)gfmultby01(temp[4*3+c]) );
        State[2][c] = (unsigned char) ( (int)gfmultby01(temp[0+c]) ^ (int)gfmultby01(temp[4*1+c]) ^
                                        (int)gfmultby02(temp[4*2+c]) ^ (int)gfmultby03(temp[4*3+c]) );
        State[3][c] = (unsigned char) ( (int)gfmultby03(temp[0+c]) ^ (int)gfmultby01(temp[4*1+c]) ^
                                        (int)gfmultby01(temp[4*2+c]) ^ (int)gfmultby02(temp[4*3+c]) );
    }
}  // MixColumns

void AES::InvMixColumns()
{
    unsigned char temp[4*4];
    int r,c;
    for (r = 0; r < 4; r++)  // copy State into temp[]
    {
        for (c = 0; c < 4; c++)
        {
            temp[4*r+c] =  State[r][c];
        }
    }

    for (c = 0; c < 4; c++)
    {
        State[0][c] = (unsigned char) ( (int)gfmultby0e(temp[c]) ^ (int)gfmultby0b(temp[4+c]) ^
                                        (int)gfmultby0d(temp[4*2+c]) ^ (int)gfmultby09(temp[4*3+c]) );
        State[1][c] = (unsigned char) ( (int)gfmultby09(temp[c]) ^ (int)gfmultby0e(temp[4+c]) ^
                                        (int)gfmultby0b(temp[4*2+c]) ^ (int)gfmultby0d(temp[4*3+c]) );
        State[2][c] = (unsigned char) ( (int)gfmultby0d(temp[c]) ^ (int)gfmultby09(temp[4+c]) ^
                                        (int)gfmultby0e(temp[4*2+c]) ^ (int)gfmultby0b(temp[4*3+c]) );
        State[3][c] = (unsigned char) ( (int)gfmultby0b(temp[c]) ^ (int)gfmultby0d(temp[4+c]) ^
                                        (int)gfmultby09(temp[4*2+c]) ^ (int)gfmultby0e(temp[4*3+c]) );
    }
}  // InvMixColumns

unsigned char AES::gfmultby01(unsigned char b)
{
    return b;
}

unsigned char AES::gfmultby02(unsigned char b)
{
    if (b < 0x80)
        return (unsigned char)(int)(b <<1);
    else
        return (unsigned char)( (int)(b << 1) ^ (int)(0x1b) );
}

unsigned char AES::gfmultby03(unsigned char b)
{
    return (unsigned char) ( (int)gfmultby02(b) ^ (int)b );
}

unsigned char AES::gfmultby09(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
                            (int)b );
}

unsigned char AES::gfmultby0b(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
                            (int)gfmultby02(b) ^
                            (int)b );
}

unsigned char AES::gfmultby0d(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
                            (int)gfmultby02(gfmultby02(b)) ^
                            (int)(b) );
}

unsigned char AES::gfmultby0e(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
                            (int)gfmultby02(gfmultby02(b)) ^
                            (int)gfmultby02(b) );
}

double Earth_Long_Radius = 6378137.0;   //地球长半径
double Earth_Short_Radius = 6356752.3142;  //地球短半径
double Earth_Oblate = 1 / 298.2572236;
#define SPI 3.14159265359
//报警位置计算
double rad(double d)
{
    return d * SPI / 180.0;  //转化为弧度
}

double deg(double d)
{
    return d * 180 / SPI;  //转化为角度
}

double AES::ComputeAzimuth(double lon1, double lat1, double lon2, double lat2)
{
    double result = 0.0;

    int ilat1 = (int) (0.50 + lat1 * 360000.0);
    int ilat2 = (int) (0.50 + lat2 * 360000.0);
    int ilon1 = (int) (0.50 + lon1 * 360000.0);
    int ilon2 = (int) (0.50 + lon2 * 360000.0);

    lat1 = rad(lat1);
    lon1 = rad(lon1);
    lat2 = rad(lat2);
    lon2 = rad(lon2);

    if ((ilat1 == ilat2) && (ilon1 == ilon2)) {
        return result;
    } else if (ilon1 == ilon2) {
        if (ilat1 > ilat2)
            result = 180.0;
    } else {
        double c = acos(sin(lat2) * sin(lat1) + cos(lat2) * cos(lat1) * cos((lon2 - lon1)));
        double A = asin(cos(lat2) * sin((lon2 - lon1)) / sin(c));
        result = deg(A);
        if ((ilat2 > ilat1) && (ilon2 > ilon1)) {
        } else if ((ilat2 < ilat1) && (ilon2 < ilon1)) {
            result = 180.0 - result;
        } else if ((ilat2 < ilat1) && (ilon2 > ilon1)) {
            result = 180.0 - result;
        } else if ((ilat2 > ilat1) && (ilon2 < ilon1)) {
            result += 360.0;
        }
    }

    return result;
}

QPointF AES::ConvertDistanceToLogLat(double lon, double lat, double dist, double brng)
{
    double alpha1 = rad(brng);
    double sinAlpha1 = sin(alpha1);
    double cosAlpha1 = cos(alpha1);

    double tanU1 = (1 - Earth_Oblate) * tan(rad(lat));
    double cosU1 = 1 / sqrt((1 + tanU1 * tanU1));
    double sinU1 = tanU1 * cosU1;
    double sigma1 = atan2(tanU1, cosAlpha1);
    double sinAlpha = cosU1 * sinAlpha1;
    double cosSqAlpha = 1 - sinAlpha * sinAlpha;
    double uSq = cosSqAlpha * (Earth_Long_Radius * Earth_Long_Radius - Earth_Short_Radius * Earth_Short_Radius) / (Earth_Short_Radius * Earth_Short_Radius);
    double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
    double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));

    double cos2SigmaM=0;
    double sinSigma=0;
    double cosSigma=0;
    double sigma = dist / (Earth_Short_Radius * A), sigmaP = 2 * SPI;
    while (fabs(sigma - sigmaP) > 1e-12)
    {
        cos2SigmaM = cos(2 * sigma1 + sigma);
        sinSigma = sin(sigma);
        cosSigma = cos(sigma);
        double deltaSigma = B * sinSigma * (cos2SigmaM + B / 4 * (cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)
                - B / 6 * cos2SigmaM * (-3 + 4 * sinSigma * sinSigma) * (-3 + 4 * cos2SigmaM * cos2SigmaM)));
        sigmaP = sigma;
        sigma = dist / (Earth_Short_Radius * A) + deltaSigma;
    }

    double tmp = sinU1 * sinSigma - cosU1 * cosSigma * cosAlpha1;
    double lat2 = atan2(sinU1 * cosSigma + cosU1 * sinSigma * cosAlpha1,
            (1 - Earth_Oblate) * sqrt(sinAlpha * sinAlpha + tmp * tmp));
    double lambda = atan2(sinSigma * sinAlpha1, cosU1 * cosSigma - sinU1 * sinSigma * cosAlpha1);
    double C = Earth_Oblate / 16 * cosSqAlpha * (4 + Earth_Oblate * (4 - 3 * cosSqAlpha));
    double L = lambda - (1 - C) * Earth_Oblate * sinAlpha
            * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)));

    return QPointF(lon+deg(L), deg(lat2));
}

double AES::GetDistance(const double& lat1, const double& lng1, const double& lat2, const double& lng2)
{
   double radLat1 = rad(lat1);
   double radLat2 = rad(lat2);
   double a = radLat1 - radLat2;
   double b = rad(lng1) - rad(lng2);

   double s = 2 * asin(sqrt(pow(sin(a/2),2) +
    cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));
   s = s * Earth_Long_Radius;
   s = round(s * 10000) / 10000;
   return s;
}

bool AES::getPosLonLat(QString dbconnName, double cablePos, QString segcode, int phasecode, QPointF &resultPt)
{
    QSqlDatabase db = QSqlDatabase::database(dbconnName);
    if (db.isOpenError())
    {
        return false;
    }

    QString sql = QString("SELECT I.seg_code,I.phase_code,I.start_points,I.end_points,T.start_location,"
                     "T.end_location FROM cable_segment_point_info AS I LEFT JOIN cable_segment_detail_info "
                     "AS T ON I.seg_code = T.seg_code AND I.phase_code = T.phase_code "
                     "WHERE I.seg_code = '%1' AND I.phase_code = %2").arg(segcode).arg(phasecode);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        return false;
    }

    double lat1,lon1;
    double lat2,lon2;

    int segstart,segend;
    bool bfind = false;
    while (query.next())
    {

        QString startPt = query.value(2).toString();
        QString endpt = query.value(3).toString();
        segstart = query.value(4).toInt();
        segend = query.value(5).toInt();

        QStringList strlist;

        strlist = startPt.split(",");
        if(strlist.size() == 2)
        {
            lat1 = QString(strlist.at(0)).toDouble();
            lon1 = QString(strlist.at(1)).toDouble();
        }

        strlist = endpt.split(",");
        if(strlist.size() == 2)
        {
            lat2 = QString(strlist.at(0)).toDouble();
            lon2 = QString(strlist.at(1)).toDouble();
        }

        bfind = true;
    }

    if(cablePos < segstart || cablePos > segend)
        return false;

    double ath = ComputeAzimuth(lon1,lat1,lon2,lat2);
    double evt_dist = cablePos - segstart;
    int seg_length = segend - segstart;
    double absolute_dist = AES::GetDistance(lat1, lon1, lat2, lon2);  //段起始经纬度的距离
    double relative_dist = evt_dist / seg_length * absolute_dist;

    resultPt = ConvertDistanceToLogLat(lon1,lat1,relative_dist,ath);

    return bfind;
}

QString AES::getStartReferenceName(QString connectionName, QString lincode, int phase)
{
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (db.isOpenError())
    {
      return false;
    }

    QSqlQuery query(db);
    //获取事件发生时间
    QString sql = QString("select phase_name from cable_segment_point_info where seg_code "
                     "like '%1%' and phase_code = %2 order by seg_code").arg(lincode).arg(phase);

    if (!query.exec(sql))
    {
      return false;
    }

    QString result;

    while (query.next())
    {
        QString str = query.value(0).toString();
        QStringList ls = str.split("_");
        if(ls.size() == 2){
            result = ls.at(0);

            break;
        }
    }

    //select phase_name from cable_segment_point_info where seg_code like '1001%' and phase_code = 3 order by id
    return result;
}

QString AES::getStartStationName(QString connectionName, QString linecode)
{
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (db.isOpenError())
    {
      return "";
    }

    QSqlQuery query(db);

    //获取事件发生时间
    QString sql = QString("select I.station_name from cable_line_info as T left join "
                     "station_info as I on T.start_station = I.station_code where cable_code = '%1'").arg(linecode);


    if (!query.exec(sql))
    {
      return "";
    }

    QString result;

    while (query.next())
    {
        result = query.value(0).toString();
        break;
    }

    //select phase_name from cable_segment_point_info where seg_code like '1001%' and phase_code = 3 order by id
    return result;
}

bool AES::isPluginLoadLoaded(QString connectionName, QString pluginName)
{
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (db.isOpenError())
    {
      return false;
    }

    QSqlQuery query(db);

    //获取事件发生时间
    QString sql = QString("SELECT system_plugins_info.is_load FROM system_plugins_info WHERE plugin_filename = '%1'").arg(pluginName);


    if (!query.exec(sql))
    {
      return false;
    }

    QString result;

    while (query.next())
    {
        int value = query.value(0).toInt();
        return (value==0?false:true);
    }

    return false;
}

