#include "CodeCountLine.h"
#include "ui_CodeCountLine.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QClipboard>
#include <QMimeData>
#include <QCryptographicHash>


#include "tools/time_string.h"

QSettings settings("CodeCountLine.ini", QSettings::IniFormat);

CodeCountLine::CodeCountLine(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::CodeCountLine)
{
	ui->setupUi(this);

    this->restoreGeometry(settings.value("geometry").toByteArray());
    ui->templateSearch->setText(settings.value("tamplate", "*.cpp;*.h;*.ui").toString());
    ui->path->setText(settings.value("path").toString());
    ui->exception->setText(settings.value("exception").toString());

    qApp->applicationFilePath() + "/win.txt";

    ui->copyBuffer->setEnabled(false);
    ui->fileCreate->setEnabled(false);

    ui->tableWidget->resizeColumnsToContents();

    QString help;


    help = "Начать подсчёт файлов и кода в них";
    ui->start->setStatusTip(help);
    ui->start->setToolTip(help);

    help = "Копировать таблицу в буфер обмена";
    ui->copyBuffer->setStatusTip(help);
    ui->copyBuffer->setToolTip(help);

    help = "Сохранить весь исходный код в одном файле";
    ui->fileCreate->setStatusTip(help);
    ui->fileCreate->setToolTip(help);

    help = "Настройки для создаваемого файла";
    ui->fileConfig->setStatusTip(help);
    ui->fileConfig->setToolTip(help);
    ui->fileConfig->hide();

    help = "Укажите путь к папке с кодом";
    ui->getPath->setStatusTip(help);
    ui->getPath->setToolTip(help);
}


CodeCountLine::~CodeCountLine()
{
	delete ui;
}


void CodeCountLine::closeEvent(QCloseEvent* ce)
{
    settings.setValue("geometry", this->saveGeometry());
    settings.setValue("path", ui->path->text());
    settings.setValue("template", ui->templateSearch->text());
    settings.setValue("exception", ui->exception->text());
    ce->accept();
}


//************************************************************************************************************************
///  Начать подсчёт
//************************************************************************************************************************

void CodeCountLine::start()
{
    QString path = ui->path->text();

    if(path == "")
	{
        QMessageBox::warning(this, "Не чего считать",
                             "Отсутствует папка для подсчёта количества строк кода :(\n"
                             "Не получится ничего посчитать.");
		return;
	}

    file_count = 0;
    string_count = 0;
    time_start = QTime::currentTime();
    ui->tableWidget->setRowCount(0);
    templ = ui->templateSearch->text().split(";");
    exception = ui->exception->text().split(";");

    schetPapok(path, "");
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->resizeColumnsToContents();

    ui->copyBuffer->setEnabled(true);
    ui->fileCreate->setEnabled(true);

    ui->resLine->setText(QString::number(string_count));
    ui->resFile->setText(QString::number(file_count));
    ui->resTime->setText(TimeString::convertMSecToString(abs(QTime::currentTime().msecsTo(time_start)), true));
}


//************************************************************************************************************************
///  Указать путь к папке с кодом
//************************************************************************************************************************

void CodeCountLine::getPath()
{
	QString str;
	str = QFileDialog::getExistingDirectory(this, "Выберете папку для посчёта в ней кода.", "Хмм");

    ui->path->setText(str);
}


//************************************************************************************************************************
///  О программе
//************************************************************************************************************************

void CodeCountLine::about()
{
    QMessageBox::about(this, "О программе подсчтёта кода",
                       "Версия " + QString(VERSION) +
                       "<P>Программа подсчёта кода создана: Щелыкалиным Максим"
					   "<P><A HREF=\"mailto:Schelikal@gmail.com?subject=Разработчику программы подсчёта кода"
									"\">Написать письмо разработчику программы</A></P>");
}


//************************************************************************************************************************
///  Рекурсивный метод подсчёта папок
//************************************************************************************************************************

void CodeCountLine::schetPapok(const QString &path, const QString &sub_path)
{
    QDir dir(path);
    QStringList lst;

	lst = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

	int col = lst.count();

	for(int i = 0; i < col; i++)
    {
        if(exception.contains(lst[i]) )
            continue;
        schetPapok(path + "/" + lst[i], sub_path + "/" + lst[i]);
    }

    lst.clear();
    lst = dir.entryList(templ, QDir::Files | QDir::NoDotAndDotDot);

	col = lst.count();
    file_count += col;

	for(int i = 0; i < col; i++)
    {
        schetFile(path + "/" + lst[i], sub_path + "/");
    }

    int row_count = ui->tableWidget->rowCount();
    if(row_count % 20 == 0)
    {
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->selectRow(row_count - 1);
        qApp->processEvents();
    }
}


//************************************************************************************************************************
///  Метод получения информации о файле
//************************************************************************************************************************

void CodeCountLine::schetFile(QString file_name, QString sub_path)
{
    QFile file(file_name);
    QFileInfo file_info(file_name);
    QByteArray* ba = new QByteArray();
    QByteArray ba_temp;
	int colStr = 0;

	if(!file.open(QIODevice::ReadOnly))
	{
        QMessageBox::critical(this, "Беда", "Не удалсь открыть файл:\n" + file_name
							  + "\nДля подстчёта количества строк кода");
		return;
	}

	while(!file.atEnd())
	{
        ba_temp = QString::fromUtf8(file.readLine()).split("//").first().toUtf8();

        if( ! ba_temp.simplified().isEmpty())
        {
            ba->append(ba_temp);
            colStr++;
        }
	}

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);

    sub_path = (sub_path == "/") ? "" : sub_path;
    QString
            sub_file_name = sub_path + file_info.fileName();

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem( sub_file_name ) );
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(file_info.size())));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(file_info.birthTime().toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString(QCryptographicHash::hash(*ba, QCryptographicHash::Md5).toHex())));


    files.insert(sub_file_name, ba);

    string_count += colStr;
}


//************************************************************************************************************************
///  Сохранить таблицу в буфер обмена
//************************************************************************************************************************

void CodeCountLine::on_copyBuffer_clicked()
{
    QString tableStr = "";
    int row = ui->tableWidget->rowCount();
    int column = ui->tableWidget->columnCount();

    tableStr = "<html><table cellspacing=-1 cellpadding=2 border=1 bordercolor=black>"
               "<tr>";

    for(int i = 0; i < column; ++i)
    {
        tableStr += "<th>" + ui->tableWidget->horizontalHeaderItem(i)->text() + "</th>";
    }

    tableStr += "</tr>";

    for(int i = 0; i < row; ++i)
    {
        tableStr += "<tr>";
        for(int j = 0; j < column; ++j)
            tableStr += "<td>" + ui->tableWidget->item(i, j)->text() + "</td>";
        tableStr += "</tr>";
    }

    tableStr += "</table></html>";

    QMimeData* mime = new QMimeData();

    mime->setHtml(tableStr);

    QApplication::clipboard()->setMimeData(mime);
}

