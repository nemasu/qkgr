#include "pkgr.h"
#include <iostream>
#include <cstdio>
#include <cstdint>
#include <cerrno>
#include <cstring>
#include <unistd.h>

using std::cerr;
using std::endl;

pkgr::pkgr() {

}

pkgr::~pkgr() {

}

int
pkgr::InstallPkgs( vector<string> pkgs ) {

	string args = "/usr/sbin/pkgr -i";
	for( string pkg : pkgs ) {
		args = args + " " + pkg;
	}
	const char *r = "w";
	FILE *fd = popen(args.c_str(), r);
	if( !fd ) {
		cerr << "popen(" << args << ") failed: " << strerror(errno) << endl;
		return -1;
	}

	return fclose(fd);
}

int
pkgr::InstallPkg( string pkg ) {
	vector<string> pkgs;
	pkgs.push_back(pkg);
	return InstallPkgs(pkgs);
}
