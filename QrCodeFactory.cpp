#include "QrCodeFactory.h"
#include "QrCodeGenerator/QrCode.h"
#include <QPainter>
#include <QBuffer>

QImage QrCodeFactory::generate(const QByteArray& text, int size, QColor fg, QColor bg)
{
	//generate image and painter
	QImage image(size, size, QImage::Format_ARGB32);
	image.fill(bg);

	QPainter painter(&image);
	painter.setPen(Qt::NoPen);
	painter.setBrush(fg);

	//generate barcode
	qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(text.constData(), qrcodegen::QrCode::Ecc::LOW);
	const int s = qr.getSize();
	const double rectangle_size = size / (s+2);
	for(int y=0; y<s; y++)
	{
		for(int x=0; x<s; x++)
		{
			if(qr.getModule(x, y)) //1 is returned for black
			{
				painter.drawRect(QRectF((x+1)*rectangle_size, (y+1)*rectangle_size, rectangle_size, rectangle_size));
			}
		}
	}

	return image;
}

QByteArray QrCodeFactory::generateText(const QByteArray& text, int size, QColor fg, QColor bg)
{
	QImage image = generate(text, size, fg, bg);

	//save image
	QByteArray output;
	QBuffer buffer(&output);
	buffer.open(QIODevice::WriteOnly);
	image.save(&buffer, "PNG");

	return output.toBase64();
}
