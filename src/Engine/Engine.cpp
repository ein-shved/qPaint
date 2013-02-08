#include "Engine.h"
#include <iostream>
#include <QFileInfo>
using namespace std;

bool Engine::load(const QString &in_sPath)
{
	QImage img;
	if ( img.load(in_sPath) ) {
		QFileInfo fi(in_sPath);
		_path = fi.absoluteFilePath();
		_image = QImage (img.width(),img.height(), QImage::Format_RGB32);
		for (int y = 0; y < img.height(); ++y){
			for (int x = 0; x < img.width(); ++x){
				_image.setPixel (x,y,img.pixel(x,y));
			}
		}
		return true;
	}
	return false;
}

bool Engine::save(const QString &in_sPath)
{
	QFileInfo fi(in_sPath);
	_path = fi.absoluteFilePath();
	return _image.save(_path);
}

void Engine::launch ()
{
        while ( !_filters.isEmpty()) {
                Filter *pFilter = _filters.dequeue();
		_image = pFilter->launch(_image);
		delete pFilter;
	}
}

void Engine::launch ( const Filter &filter)
{
	launch();
	_image = filter.launch(_image);
}
void Engine::operator () ()
{
	launch();
}