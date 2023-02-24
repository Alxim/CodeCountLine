#include "CodeCountLine.h"
#include "ui_CodeCountLine.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QClipboard>


//  Создание файла для регистрации РИД

void CodeCountLine::on_fileCreate_clicked()
{
    QStringList keys = files.keys();
    QString str, path;

    path = settings.value("file_result", "result.txt").toString();
    path = QFileDialog::getSaveFileName(this, "Выберите место сохранения",
                                        path);

    if(path.isEmpty())
        return;

    settings.setValue("file_result", path);

    QFile file(path);

    if( ! file.open(QFile::WriteOnly) )
    {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось открыть файл:\n"
                              + file.fileName());
        return;
    }

    int col = keys.size();
    for(int i = 0; i < col; i++)
    {
        str = "\n\n" + keys[i] + "\n";
        file.write(str.toUtf8());
        file.write(*files.value(keys[i]));

        ui->statusBar->setStatusTip( QString::number( col / (i+1) ) + " %" );
        qApp->processEvents();
    }

    file.close();
    QApplication::clipboard()->setText(str);

    QMessageBox::information(this, "Ура!", "Всё получилось! ");
}


//  Настройки файла

void CodeCountLine::on_fileConfig_clicked()
{

}
