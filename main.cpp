#include "CodeCountLine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    CodeCountLine w;
	w.show();

	return a.exec();
}
