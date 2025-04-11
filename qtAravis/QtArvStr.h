// QtArvStr.h - String utilities ported from arvstr.c
#pragma once

#include <QString>
#include <QVector>
#include <QByteArray>

namespace QtArvStr {

	QString strip(QString str, const QString& illegalChars, QChar replacementChar);
	bool isUri(const QString& str);
	QString toUri(const QString& path);
	bool parseDouble(QString& str, double& outVal);
	int parseDoubleList(QString& str, int nValues, QVector<double>& outValues);
	QString hexDump(const QByteArray& data);

} // namespace QtArvStr
