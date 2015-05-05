#include "MainScene.h"
#include "MainLayer.h"

USING_NS_CC;

MainScene::MainScene()
{}
MainScene::~MainScene()
{}

bool MainScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::create());
		auto size = Director::getInstance()->getVisibleSize();
		auto layer = MainLayer::create();
		CC_BREAK_IF(!layer);
		layer->setAnchorPoint(Vec2::ZERO);
		layer->setPosition(Vec2::ZERO);
		this->addChild(layer);
		bRet = true;
	} while (0);
	return bRet;
}