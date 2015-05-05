#ifndef _DEMO_MAINLAYER_H_
#define _DEMO_MAINLAYER_H_

#include "cocos2d.h"

class MainLayer : public cocos2d::Layer
{
public:
	MainLayer();
	~MainLayer();
	virtual bool init();
	CREATE_FUNC(MainLayer);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	//virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
private:
	cocos2d::Vector<cocos2d::Sprite * > listSp;
	CC_SYNTHESIZE(float, winWith, WinWith);
	CC_SYNTHESIZE(float, winHeight, WinHeight);
	void initPic();
	int state[3][3];
	void graySprite(cocos2d::Sprite * sprite);
	int selectIndex;
	cocos2d::Vec2 beganLocatin;
	cocos2d::Sprite * coverSp;
};


#endif //_DEMO_MAINLAYER_H_