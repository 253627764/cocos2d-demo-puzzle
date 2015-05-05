#include "GameOverLayer.h"

USING_NS_CC;

GameOverLayer::GameOverLayer()
{}
GameOverLayer::~GameOverLayer()
{}
Scene * GameOverLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverLayer::create();
	scene->addChild(layer);
	return scene;
}
bool GameOverLayer::init()
{
	bool bRet = true;
	do
	{
		CC_BREAK_IF(!Layer::create());
		auto size = Director::getInstance()->getVisibleSize();
		auto bgSp = Sprite::create("bg.png");
		bgSp->setPosition(size /2);
		addChild(bgSp);
		auto label = Label::create("game over", "Arial", 20);
		label->setPosition(size / 2);
		addChild(label);

		bRet = true;
	} while (0);
	return bRet;
}