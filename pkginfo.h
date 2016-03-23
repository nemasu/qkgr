#ifndef __PKGINFO_H__
#define __PKGINFO_H__

#include <QObject>
#include <QString>
#include <QList>
#include <QJsonDocument>

struct PkgDetail {
	QString name;
	QString desc;
	QString version;
	QList<QString> deps;
	QString installed;
};

class PkgInfo : public QObject {
	Q_OBJECT

	public:
		virtual ~PkgInfo(){}

	public slots:
		static PkgDetail GetPkgDetail(QString name);
		static QList<QString> GetPkgList();

	private slots:
		static QJsonDocument ReadPkgJson(QString name);
};

#endif
