#ifndef DCF_H
#define DCF_H

#include <QObject>

/*************************
 *说明：格式化DTS通信数据的工具类，包括转义及反转义、生成发送命令、
 *     解析数据等。所有DTS命令封装类均继承自该类。
 *作者：jt
 *时间：2012-8-1
 *************************/
class DCF : public QObject      //DCF--DataCommunicationFormatter
{
    Q_OBJECT
public:
    explicit DCF(QObject *parent = 0);

    quint32 getDataLen() const {    return m_dataLen;   }
    void setDataLen(quint32 len) {  m_dataLen = len;    }
    quint8 getDevCode() const { return m_devCode;   }
    void setDevCode(quint8 code) {  m_devCode = code;   }
    quint8 getCmdType() const { return m_cmdType;   }
    void setCmdType(quint8 type) {  m_cmdType = type;   }

    virtual QByteArray getSendCMD();              //获取命令的虚函数，由子类重写
//    virtual void setDatas(QByteArray datas);
    QByteArray formatCMD(QByteArray);
    static quint8 translateDatas(QByteArray source, QByteArray *dest);

signals:

public slots:



protected:
    quint32 m_dataLen;      //数据长度
    quint8 m_devCode;       //设备编号
    quint8 m_cmdType;       //命令类型
};

#endif // DCF_H
