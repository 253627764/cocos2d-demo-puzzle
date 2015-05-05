#ifndef _DEMO_SUCCESSLAYER_H_
#define _DEMO_SUCCESSLAYER_H_

#include "cocos2d.h"

class SuccessLayer : public cocos2d::Layer
{
public:
	SuccessLayer();
	~SuccessLayer();
	virtual bool init();
	CREATE_FUNC(SuccessLayer);
	void muenExitCb(cocos2d::Ref * s);
	void muenNextCb(cocos2d::Ref * s);
	static cocos2d::Scene * createScene();
private:
};


#endif //_DEMO_SUCCESSLAYER_H_