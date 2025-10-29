#include "ImageLabel.h"

ImageLabel::ImageLabel(QWidget* parent)
	: QLabel(parent)
{
}

void ImageLabel::setImage(QImage image)
{
	image_ = image;
	updateImage();
}


void ImageLabel::resizeEvent(QResizeEvent* event)
{
	updateImage();
	QLabel::resizeEvent(event);
}


void ImageLabel::updateImage()
{
	double aspect_ratio = static_cast<double>(image_.width()) / image_.height();

	if (aspect_ratio * height() <= width())
	{
		setPixmap(QPixmap::fromImage(image_).scaledToHeight(height(), Qt::SmoothTransformation));
	}
	else
	{
		setPixmap(QPixmap::fromImage(image_).scaledToWidth(width(), Qt::SmoothTransformation));
	}
}

