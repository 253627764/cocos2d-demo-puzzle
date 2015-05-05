#ifndef _DEMO_MAINSCENE_H_
#define _DEMO_MAINSCENE_H_

#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
	MainScene();
	~MainScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
private:

};


#endif //_DEMO_MAINSCENE_H_