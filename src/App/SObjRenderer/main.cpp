#include "SObjRenderer.h"

#include <QtWidgets/QApplication>
#include <qfile.h>
#include <qtextstream.h>

#include <iostream>

using namespace std;

static const char USAGE[] =
R"(SObjRenderer

    Usage:
      SObjRenderer [--notrootpath] --sobj=<sobjPath> [--maxdepth=<maxDepth>] [--samplenum=<sampleNum>] [--notdenoise] [--outpath==<outPath>]

    Options:
      --notrootpath            path is not from root path
      --sobj <sobjPath>        sobj path.
      --maxdepth <maxDepth>    max depth [default: 20]
      --samplenum <sampleNum>  sample num [default: 16]
      --notdenoise             not denoise
      --outpath <outPath>      output file path
)";

void ShowArgRst(const map<string, docopt::value> & rst);

int main(int argc, char *argv[])
{
	vector<string> args{ argv + 1, argv + argc };
	auto result = docopt::docopt(USAGE, args);
	ShowArgRst(result);

	SObjRenderer::ArgMap argMap;
	for (auto arg : ENUM_ARG::_values())
		argMap[arg] = result[string("--") + arg._to_string()];

	QApplication a(argc, argv);

	// load style sheet
	QFile f(":qdarkstyle/Resources/style.qss");
	if (f.exists()){
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		qApp->setStyleSheet(ts.readAll());
	}
	else
		printf("Unable to set stylesheet, file not found\n");

	Qt::WindowFlags flags = 0;
	flags |= Qt::WindowMinimizeButtonHint;
	flags |= Qt::WindowCloseButtonHint;
	flags |= Qt::MSWindowsFixedSizeDialogHint;

	SObjRenderer w(argMap, Q_NULLPTR, flags);
	w.show();
	return a.exec();
}

void ShowArgRst(const map<string, docopt::value> & rst) {
	cout << "[ Arg Result ]" << endl << endl;
	cout << "{" << endl;
	bool first = true;
	for (auto const & arg : rst) {
		if (first)
			first = false;
		else
			cout << "," << endl;

		cout << '"' << arg.first << '"' << ": " << arg.second;
	}
	cout << endl << "}" << endl << endl;
}
