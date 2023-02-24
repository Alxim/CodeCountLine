#include "time_string.h"

TimeString::TimeString()
{

}


//*************************************************************************************************************************************************
///  Вывод интервала из микросекунд в формат часов, минут, секунд
//*************************************************************************************************************************************************

QString TimeString::convertMSecToString(int m_sec, bool word)
{
    if(word)
    {
        QString result;
        int temp = m_sec/1000/60/60%60;

        if(temp != 0)
            result += QString::number(temp)  + " часов "
                    + QString::number(m_sec/1000/60%60)  + " минут "
                    + QString::number(m_sec/1000%60) + " секунд "
                    + QString::number(m_sec%1000) + " микросекунд ";
        else {
            temp = m_sec/1000/60%60;
            if(temp != 0)
                result += QString::number(m_sec/1000/60%60)  + " минут "
                        + QString::number(m_sec/1000%60) + " секунд "
                        + QString::number(m_sec%1000) + " микросекунд ";
            else {
                temp = m_sec/1000%60;
                if(temp != 0)
                    result += QString::number(m_sec/1000%60) + " секунд "
                            + QString::number(m_sec%1000) + " микросекунд ";
                else
                    result += QString::number(m_sec%1000) + " микросекунд ";
            }
        }

        return result;
    }

    return QString::number(m_sec/1000/60/60%60).rightJustified(2, '0') + ":"
            + QString::number(m_sec/1000/60%60).rightJustified(2, '0') + ":"
            + QString::number(m_sec/1000%60).rightJustified(2, '0') + "."
            + QString::number(m_sec%1000).rightJustified(3, '0');
}


//*************************************************************************************************************************************************
///  Рассчёт и вовод интервала из микросекунд в формат часов, минут, секунд
//*************************************************************************************************************************************************

QString TimeString::getIntervalToTimeStart(QTime time_start, bool word)
{
    int m_sec = time_start.msecsTo(QTime::currentTime());
    return convertMSecToString(m_sec, word);
}


//*************************************************************************************************************************************************
///  Печать в консоль интервала от времени начала и сообщения
//*************************************************************************************************************************************************

void TimeString::printIntervalToTimeStart(QTime time_start, const QString& text, bool word)
{
    int m_sec = time_start.msecsTo(QTime::currentTime());
    qDebug() << convertMSecToString(m_sec, word) << " " << text;
}
