#ifndef __PKGR_H__
#define __PKGR_H__

#include <vector>
#include <string>

using std::vector;
using std::string;

class pkgr {
	public:
		pkgr();
		~pkgr();
		static int InstallPkgs(vector<string> pkgs);
		static int InstallPkg(string pkg);
};

#endif
