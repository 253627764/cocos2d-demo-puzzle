#ifndef _DEMO_GAMEOVERLAYER_H_
#define  _DEMO_GAMEOVERLAYER_H_

#include "cocos2d.h"

class GameOverLayer:public cocos2d::Layer			
{
public:
	GameOverLayer();
	~GameOverLayer();
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
	static cocos2d::Scene * createScene();
private:

};

#endif  _DEMO_GAMEOVERLAYER_H_