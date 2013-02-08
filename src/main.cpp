#include <iostream>
#include <string>
using namespace std;
#include <QtGui/QApplication>
#include <cstdio>
#include <QRect>

#include "ArgParser/arg_parser.h"
#include "Engine/Engine.h"
#include "Engine/Filters/Convolution.h"
#include "Engine/Filters/Sobel.h"
#include "Engine/Filters/GreyWorld.h"
#include "Engine/Filters/Hystogram.h"
#include "Engine/Filters/Interpolation.h"
#include "Engine/Filters/Manually.h"
#include "Engine/Filters/Supplementary.h"
#include "Engine/Filters/GaussianS.h"
#include "GUI/gui.h"


#include <cstdlib>
#include <ctime>

QVector<QVector<float> > matrixFromString(const std::string& str);

int main(int argc, char *argv[])
{
	srand ( time(NULL) );
	
        Engine engine;
	string sSourcePath, sResultPath, sErrors;

	const string helpstr = 	" qPaint [options] [in-file] [out-file]\n\nOptions is:\n"
				"\t-g --gaussian <px>		фильтр гаусса задается радиуссом матрицы px\n"
				"\t-m --median <px>		медианный фильтр задается радиуссом матрицы px\n"
				"\t-s --sobel			фильтр собеля\n"
				"\t-a --gray-world			фильтр \"Серый мир\"\n"
				"\t-c --autocontrast 		линейное растяжение\n"
				"\t-l --autolevels			поканальное растяжение\n"
				"\t-r --rotate <degrees>		поворачивает на degrees градусов\n"
				"\t-z --resize <scale>		увеличивает в scale раз\n"
				"\t-k --custom <kernel>		фильтр с указанной матрицей kernel в формате 'a11,a12,a13;a21...a33' (минимум 3х3)\n"
				"\t-b --glass			фильтр \"Стекло\"\n\n"
				"\t-A --area <rect>		область интереса rect в формате <X>x<Y>-<Width>x<Height>\n"
				"\t-G --GUI			использовать графический интерфейс (включен по умолчанию)\n"
				"\t-C --Console			не использовать графический интерфес. Необходимо указать in-file и out-file\n"
				"\t-h --help			показать это сообщние и выйти\n";
	
	bool gui = true;
	QRect area;
	
	const Arg_parser::Option Options[] =
	{
		{ 'A', "area", Arg_parser::yes },
		
		{ 'x', "grayscale",	Arg_parser::no  },
                { 'g', "gaussian",	Arg_parser::yes },
                { 'm', "median",	Arg_parser::yes },
                { 's', "sharpen",	Arg_parser::no  },
                { 'a', "grey-world",	Arg_parser::no  },
                { 'c', "autocontrast",	Arg_parser::no  },
                { 'l', "autolevels",	Arg_parser::no  },
                { 'r', "rotate",	Arg_parser::yes },
                { 'z', "resize",	Arg_parser::yes },
                { 'k', "custom",	Arg_parser::yes },
                { 'b', "glass",		Arg_parser::no  },
                
                { 'G', "GUI", Arg_parser::no },
		{ 'C', "Console", Arg_parser::no },
		{ 'h', "help", Arg_parser::no }
	};

	const Arg_parser ArgParser( argc, argv, Options );
	if( ArgParser.error().size())
	{
		cerr<<"Command line error: "<<ArgParser.error()<<endl;
		return -1;
	}

	bool failed = false;
	try {
		for (int k = 0; k < ArgParser.arguments(); ++k)	{
			int iCode = ArgParser.code(k);

			switch ( (char)iCode) {
			case 'G':
				break;
			case 'C':
				gui = false;
				break;

			case 'x':
				engine.filter (Grayscale(area));
				break;
			case 'g': {
					int size;
					if ( sscanf ( ArgParser.argument (k).c_str(), "%u", &size  ) != 1 || size == 0 ) {
						cerr<<"Wrong gaussian size.\n";
						failed = true;
					}
					size = size*2 - 1;
					engine.filter (Gaussian(area,((float)size)/6,size));
				}
				break;
			case 'm': {
					int size;
					if ( sscanf ( ArgParser.argument (k).c_str(), "%u", &size  ) != 1|| size == 0 ) {
						cerr<<"Wrong median size.\n";
						failed = true;
					}
					size = size*2 - 1;
					engine.filter (Median(area,size));
				}
				break;
			case 's':
				engine.filter (Sobel(area));
				break;
			case 'a':
				engine.filter (GreyWorld(area));
				break;
			case 'c':
				engine.filter (HystogramLinear(area));
				break;
			case 'l':
				engine.filter (HystogramPerChennel(area));
				break;
			case 'r':{
					int degrees;
					if ( sscanf ( ArgParser.argument (k).c_str(), "%u", &degrees  ) != 1 ) {
						cerr<<"Wrong degrees.\n";
						failed = true;
					}
					engine.filter (Rotation(area,degrees));
				}
				break;
			case 'z': {
					float times;
					if ( sscanf ( ArgParser.argument (k).c_str(), "%f", &times  ) != 1 ) {
						cerr<<"Wrong times.\n";
						failed = true;
					}
					engine.filter (Rotation(area,times));
				}
				break;
			case 'k': 
				engine.filter (Manually(area,matrixFromString(ArgParser.argument (k))));
				break;
			case 'b':
				engine.filter (Glass(area));
				break;


			case 'A': {
					int x,y,w,h;
					if ( sscanf ( ArgParser.argument (k).c_str(), "%dx%d-%dx%d", &x, &y, &w, &h  ) != 4 ) {
						cerr<<"Wrong format of area. Format is: <X>x<Y>-<Width>x<Height>.\n";
						failed = true;
					}
				}
				break;
				
			case 'h':
				cout<<helpstr;
				return 0;
				break;
			case 0:
				if (sSourcePath.empty())
					sSourcePath = ArgParser.argument(k);
				else if (sResultPath.empty())
					sResultPath = ArgParser.argument(k);
				else
				{
					cerr<<"invalid unnamed command-line argument"<<endl;
					return 1;
				}
				break;
			}
		}
	} catch ( const logic_error& err) {
		cerr<<err.what();
		return 1;
	}
	if ( failed ) {
		return 1;
	}

        if (!gui )
        {
            if (sSourcePath.empty())
                    sErrors += "\n* Source path was not specified.";
            if (sResultPath.empty())
                    sErrors += "\n* Result path was not specified.";
	}
	if ( ! sSourcePath.empty())
	    if (!engine.load(QString(sSourcePath.c_str())) )
		sErrors += "\n* Can't load source image";
	

	if (!sErrors.empty())
	{
		cerr<<"Some errors were found:";
		cerr<<sErrors<<endl;
		return -1;
	}

	int result = 0;
	if ( gui ) {
		engine.launch();
		QApplication a(argc, argv);
		GUI w (engine);
		w.show();
		result = a.exec();
	} else {
		engine.launch();
	}
	if (!sResultPath.empty()) {
		if (!engine.save(QString(sResultPath.c_str())))	{
			cerr<<"Can't save output file"<<endl;
			return 1;
		}
	}
	return result;
}

QVector<QVector<float> > matrixFromString(const std::string& in_str) {

	const char* str = in_str.c_str();
	const char* strPtr = str;

	int width = -1;

	enum {
		begin,
		number,
		comma,
		dotcomma
	} state = begin;

	QVector<QVector<float> > matrix;
	
	for ( int column = 0;*strPtr != '\0'; str=strPtr ) {
		while ( isspace(*str) ) {
			++str;
		}
		float f = strtod ( str, const_cast<char**>(&strPtr) );
		if ( strPtr > str ) {
			if ( state == begin ) {
				matrix.append ( QVector<float>() );
				matrix[column++].append (f);
				state = number;
			} else
			if ( state == comma || state == dotcomma ) {
				if ( width < 0 ) {
					matrix.append ( QVector<float>() );
				} else
				if ( column >= width ) {
					throw logic_error ("Wrong row width.\n");
				}
				matrix[column++].append (f);
				state = number;
			} else
			if ( state == number ) {
				throw logic_error ("Need punctuation.\n");
			}
			continue;
		}
		if (*str == ',') {
			if ( state == number ) {
				state = comma;
			} else {
				throw logic_error ("Unexpected comma.\n");
			}
			++strPtr;
			continue;
		}
		if (*str == ';') {
			if ( state == number ) {
				if ( width < 0 ) {
					width = column;
				} else if ( column < width ) {
					throw logic_error ("Wrong row width.\n");
				}
				column = 0;
				state = dotcomma;
			} else {
				throw logic_error ("Unexpected dotcomma.\n");
			}
			++strPtr;
			continue;
		}
		throw logic_error ("Unexpected symbol.\n");
	}
	return matrix;

}
