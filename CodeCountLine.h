#ifndef COLICHSTROKKODA_H
#define COLICHSTROKKODA_H

#include <QMainWindow>
#include <QTime>
#include <QByteArray>
#include <QSettings>

extern QSettings settings;

namespace Ui {
class CodeCountLine;
}

class CodeCountLine : public QMainWindow
{
	Q_OBJECT

public:
    explicit CodeCountLine(QWidget *parent = nullptr);
    ~CodeCountLine();

protected:
    void closeEvent(QCloseEvent* ce);

private slots:

    //!
    //! \brief start - запуск подсчёта и заполнения данных в таблицу
    //!
    void start();


    //!
    //! \brief getPath - Установка пути к папке с кодом
    //!
    void getPath();


    //!
    //! \brief about - о программме
    //!
    void about();


    //!
    //! \brief on_copyBuffer_clicked - копировать html-таблицу с результатами в буфер обмена
    //!
    void on_copyBuffer_clicked();


    //!
    //! \brief on_FileCreate_clicked создаёт файл с кодом
    //!
    void on_fileCreate_clicked();


    //!
    //! \brief on_FileConfig_clicked задаёт конфигурацию создаваемого файла
    //!
    void on_fileConfig_clicked();

private:
    Ui::CodeCountLine *ui;

    //!
    //! \brief string_count - общее количество строк кода во всех файлах
    //!
    double string_count;


    //!
    //! \brief file_count - количество посчитанных файлов
    //!
    int file_count;

    //!
    //! \brief time_start - время начала подсчёта файлов
    //!
    QTime time_start;

    //!
    //! \brief files - содержимое посчитанных файлов, в котором могут быть удалены пустые строки. Используется для формирования общего файла с кодом.
    //!
    QHash <QString, QByteArray*> files;



    //!
    //! \brief templ - перечень шаблонов файлов для сканирования
    //!
    QStringList templ;


    //!
    //! \brief exception - перечень шаблонов для игнорирования файлов
    //!
    QStringList exception;


    //!
    //! \brief schetPapok - рекурсивная функция подсчёта папок
    //! \param path - абсолютный путь для подсчёта папок
    //! \param sub_path - относительный путь тукцщей папки. Вычисялется от корневой папки с кодом
    //!
    void schetPapok(const QString& path, const QString& sub_path);

    //!
    //! \brief schetFile - Метод получения информации о файле
    //! \param file_name - абсолютное имя файла
    //! \param sub_path - относительный путь к файлу. Вычисляется от папки начала подсчёта
    //!
    void schetFile(QString file_name, QString sub_path);

};

#endif // COLICHSTROKKODA_H
