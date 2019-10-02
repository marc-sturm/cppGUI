#ifndef QRCODE_H
#define QRCODE_H

#include "cppGUI_global.h"
#include <QImage>

///QR code factory class
class CPPGUISHARED_EXPORT QrCodeFactory
{
public:
	///Returns the QR code image
	static QImage generate(const QByteArray& text, int size, QColor fg = Qt::black, QColor bg = Qt::white);
	///Returns the QR code as base64-encoded text, e.g. for embedding in HTML/XML.
	static QByteArray generateText(const QByteArray& text, int size, QColor fg = Qt::black, QColor bg = Qt::white);


protected:
	QrCode() = delete;
};

#endif // QRCODEGENERATOR_H
