#ifndef TIMESTRING_H
#define TIMESTRING_H


#include <QTime>
#include <QString>
#include <QDebug>

class TimeString
{
public:
    TimeString();


    //!
    //! \brief convertMSecToString - Вывод интервала из микросекунд в формат часов, минут, секунд
    //! \param m_sec - количество микросекунд
    //! \param word - снабдить надпись словами или использовать двоеточия
    //! \return преобразованную строку
    //!
    static QString convertMSecToString(int m_sec, bool word = false);


    //!
    //! \brief getIntervalToTimeStart - Рассчёт и вовод интервала из микросекунд в формат часов, минут, секунд. Интервал задаётся от времени старта до текущего.
    //! \param time_start - начало интервала
    //! \param word - снабдить надпись словами или использовать двоеточия
    //! \return вычеслиенный интервал в виде строки
    //!

    static QString getIntervalToTimeStart(QTime time_start, bool word = false);

    //!
    //! \brief printIntervalToTimeStart - Печать в отладочную консоль интервала от времени начала и сообщения
    //! \param time_start - начало интервала
    //! \param text - текст выводимый после времени в отладочной консоли
    //! \param word - снабдить надпись словами или использовать двоеточия
    //!
    static void printIntervalToTimeStart(QTime time_start, const QString& text, bool word = false);
};

#endif // TIMESTRING_H
