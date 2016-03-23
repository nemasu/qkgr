#include <QtTest/QtTest>
#include "../pkginfo.h"


class TestPkgInfo : public QObject {
	Q_OBJECT
	private slots:
		void testReadPkgJson();
};

void TestPkgInfo::testReadPkgJson() {
	PkgDetail pkg = PkgInfo::GetPkgDetail("sed");
	QVERIFY(pkg.name == "sed");
	QVERIFY(pkg.installed == "true");
}

QTEST_MAIN(TestPkgInfo)
#include "testpkginfo.moc"
