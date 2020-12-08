#ifndef AES_H
#define AES_H
#include <QPointF>
typedef unsigned char byte;

enum KeySize // key size, in bits, for construtor
{
    Bits128 = 16,
    Bits192 = 24,
    Bits256 = 32
};

class QFile;

class AES
{
public:
    AES();
    AES(int keySize, unsigned char* key);
    ~AES();

private:
    static const unsigned char Sbox[16*16];
    static const unsigned char iSbox[16*16];
    static const unsigned char Rcon[11*4];

    int Nb;         // block size in 32-bit words.  Always 4 for AES.  (128 bits).
    int Nk;         // key size in 32-bit words.  4, 6, 8.  (128, 192, 256 bits).
    int Nr;         // number of rounds. 10, 12, 14.

    unsigned char key[32];     // the seed key. size will be 4 * keySize from ctor.
    unsigned char w[16*15];      // key schedule array. (Nb*(Nr+1))*4
    unsigned char State[4][4];  // State matrix

private:
    void RunKeyExpansion(int keySize, unsigned char* keyBytes);
    void SetNbNkNr(int keyS);
    void KeyExpansion();
    void AddRoundKey(int round);
    void SubWord(unsigned char * word,unsigned char* result);
    void RotWord(unsigned char * word,unsigned char* result);
    void SubBytes();
    void InvSubBytes();
    void ShiftRows();
    void InvShiftRows();
    void MixColumns();
    void InvMixColumns();
    unsigned char gfmultby01(unsigned char b);
    unsigned char gfmultby02(unsigned char b);
    unsigned char gfmultby03(unsigned char b);
    unsigned char gfmultby09(unsigned char b);
    unsigned char gfmultby0b(unsigned char b);
    unsigned char gfmultby0d(unsigned char b);
    unsigned char gfmultby0e(unsigned char b);

public:
    void FileCipher(QFile *fin, QFile *fout);
    void FileInvCipher(QFile *fin, QFile *fout);

    void Cipher(unsigned char* input, unsigned char* output);
    void InvCipher(unsigned char * input, unsigned char * output);

    void Cipher(unsigned char* input, unsigned char* output,
                unsigned char *key, int keySize = Bits128);  // encipher 16-bit input
    void InvCipher(unsigned char * input, unsigned char * output,
                   unsigned char *key, int keySize = Bits128);  // decipher 16-bit input

    static double ComputeAzimuth(double lon1, double lat1, double lon2, double lat2);  //距离两个经纬度间的方位角
    static QPointF ConvertDistanceToLogLat(double lon, double lat, double dist, double brng);  //计算到某个经纬度，指定方向角下指定距离的点
    static double GetDistance(const double& lat1, const double& lng1, const double& lat2, const double& lng2);  //计算两个经纬度间的距离

    //根据整体海缆位置计算坐标
    static bool getPosLonLat(QString dbconnName,double cablePos,QString segcode,int phasecode,QPointF &resultPt);

    //获取线路起点段名称
    static QString getStartReferenceName(QString connectionName,QString lincode,int phase);

    //光纤外报警 故障，获取起始的变电站
    static QString getStartStationName(QString connectionName,QString linecode);

    static bool isPluginLoadLoaded(QString connectionName,QString pluginName);
};

#endif // AES_H
