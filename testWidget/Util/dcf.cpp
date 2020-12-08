#include "dcf.h"
#include <QDebug>

DCF::DCF(QObject *parent) :
    QObject(parent)
{
}

QByteArray DCF::getSendCMD()
{
    QByteArray ba;
    qDebug() << tr("请在子类中重写该方法！DCF::getSendCMD()");
    return ba;
}

//void DCF::setDatas(QByteArray)
//{
//    qDebug() << tr("请在子类中重写该方法！DCF::setDatas(QByteArray)");
//}

QByteArray DCF::formatCMD(QByteArray ba)
{
    QByteArray format;
    quint8 checksum = 0;
    format.append(0xaa);
    for (int i=0; i<ba.size(); i++)
    {
        checksum += (quint8)ba.at(i);
        if ((quint8)ba.at(i) == 0xaa)
        {
            format.append(0xbb);
            format.append(0x0a);
        }
        else if ((quint8)ba.at(i) == 0xbb)
        {
            format.append(0xbb);
            format.append(0x0b);
        }
        else
        {
            format.append(ba.at(i));
        }
    }

    if (0xaa == checksum)
    {
        format.append(0xbb);
        format.append(0x0a);
    }
    else if (0xbb == checksum)
    {
        format.append(0xbb);
        format.append(0x0b);
    }
    else
    {
        format.append(checksum);
    }

    format.append(0xaa);

    return format;
}

/************
*
*返回值：0：反转义正确，1：发生转义问题，2：数据长度错误，3：校验和错误，4：通道数据长度校验错误（ACK_GET_SYS_INFO)
*************/
quint8 DCF::translateDatas(QByteArray source, QByteArray *dest) //source不包括起始码和结束码
{
    for (int i=0; i<source.size(); i++)
    {
        if (source.at(i) == (char)0xbb)
        {
            if (i+1 < source.size())
            {
                if (source.at(i+1) == (char)0x0a)
                {
                    dest->append(0xaa);
                }
                else if (source.at(i+1) == (char)0x0b)
                {
                    dest->append(0xbb);
                }
                else
                {
                    qDebug() << tr("接收到的数据格式不正确！转义问题！");
                    return 1;
                }

                i++;
            }
        }
        else
        {
            dest->append(source.at(i));
        }
    }

    //数据长度
    quint32 length = 0;
    length = 0x000000ff & dest->at(0);
    length = length << 8;
    length = length | (0x000000ff & dest->at(1));
    length = length << 8;
    length = length | (0x000000ff & dest->at(2));
    length = length << 8;
    length = length | (0x000000ff & dest->at(3));

    if (length != (quint32)(dest->length() - 1))
    {
        qDebug() << "length:" << length;
        qDebug() << "dest length:" << dest->length();
        return 2;
    }

//    if (dest->at(5) == (char)0x0a)    //该数据是ACK_GET_SYS_INFO，则需要校验通道数与通道数据,避免获取通道信息时下标越界
//    {
//        quint8 chanNum = dest->at(67); //通道数
//        if ((quint32)(chanNum * 90 + 77) != length)
//        {
//            qDebug() << tr("通道数据长度校验错误！") << "chanNum x 90 + 77:" << chanNum*90+77 << ",length:" << length;
//            return 4;
//        }
//    }

    //校验和
    quint8 checksum = 0;
    for (int i=0; i<dest->size()-1; i++)
    {
        checksum += dest->at(i);
    }

    if (checksum != (quint8)(dest->at(dest->size()-1)))
    {
        qDebug() << tr("校验和不正确：累加==%1，接收==%2").arg(checksum).arg((quint8)(dest->at(dest->size()-1)));
        return 3;
    }

    return 0;
}
