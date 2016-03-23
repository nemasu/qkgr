#include "pkginfo.h"

#include <QProcess>
#include <QJsonArray>
#include <QVariant>
#include <QJsonObject>
#include <QFile>

PkgDetail
PkgInfo::GetPkgDetail( QString name ) {
	PkgDetail pkgDetail;

	QJsonDocument pkgJson = PkgInfo::ReadPkgJson( name );
	if( !pkgJson.isObject() ) {
		return pkgDetail;
	}

	QJsonObject pkg = pkgJson.object();
	pkgDetail.name = pkg.value("name").toString();
	pkgDetail.desc = pkg.value("desc").toString();

	QList<QVariant> depsVariant = pkg.value("deps").toArray().toVariantList();
	QList<QString> deps;
	foreach( QVariant variant, depsVariant ) {
		deps.push_back(variant.toString());
	}
	pkgDetail.deps = deps;

	pkgDetail.installed = pkg.value("installed").toString();
	pkgDetail.version = pkg.value("version").toString();

	return pkgDetail;
}

QList<QString>
PkgInfo::GetPkgList() {
	QList<QString> pkgList;

	QFile packagesFile("/var/noop/packages");
	if( !packagesFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
		return pkgList;
	}
	while (!packagesFile.atEnd()) {
        QString line = packagesFile.readLine();
		pkgList.push_back(line.left(line.indexOf(",")));
    }

	return pkgList;
}

QJsonDocument
PkgInfo::ReadPkgJson( QString name ) {
	QProcess pkgr;
	QString exec = "pkgr";
	QStringList params;
	params << "--jsonmeta" << name;
	pkgr.start(exec, params);
	pkgr.waitForFinished(); 
	QString output(pkgr.readAllStandardOutput());
	return QJsonDocument::fromJson(output.toUtf8());
}
