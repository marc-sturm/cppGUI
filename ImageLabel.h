#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include "cppGUI_global.h"
#include <QLabel>

///Label managing the QImage it is displaying and
/// Updating the image on resizeEvents according to the aspect ratio of the image.
class CPPGUISHARED_EXPORT ImageLabel
		: public QLabel
{
	Q_OBJECT

public:
	ImageLabel(QWidget* parent = 0);

	void setImage(QImage image);

	void resizeEvent(QResizeEvent* event);

public slots:
	void updateImage();


private:
	QImage image_;

};

#endif // IMAGELABEL_H
