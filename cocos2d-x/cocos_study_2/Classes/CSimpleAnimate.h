#ifndef __SIMPLEANIMATE_H__
#define __SIMPLEANIMATE_H__

#include "cocos2d.h"

USING_NS_CC;

class CSimpleAnimate {

private:
	CSimpleAnimate();
public:

	static Action * CreateAction(const char *tFrameNamePattern,int tStart,int tEnd);

	static void addPlist(const std::string &tFileName);
	static void removePlist(const std::string &tFileName);

};

#endif // !__SIMPLEANIMATE_H__
