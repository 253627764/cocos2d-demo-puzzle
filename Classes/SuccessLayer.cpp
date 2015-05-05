#include "SuccessLayer.h"
#include "MainScene.h"
#include "GameOverLayer.h"


USING_NS_CC;

SuccessLayer::SuccessLayer()
{}
SuccessLayer::~SuccessLayer()
{}

Scene * SuccessLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SuccessLayer::create();
	scene->addChild(layer);
	return scene;
}

bool SuccessLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::create());
		auto picIndex = UserDefault::getInstance()->getIntegerForKey("picIndex", 1);
		char s[10];
		sprintf(s, "bg%d.jpg", picIndex-1);
		auto bgSp = Sprite::create(s);
		auto size = Director::getInstance()->getVisibleSize();
		bgSp->setPosition(size / 2);
		addChild(bgSp);
		auto label = Label::create("Success !!!", "Arial", 16);
		CC_BREAK_IF(!label);
		label->setPosition(Vec2(size.width / 2, size.height / 2 + label->getContentSize().height / 2));
		addChild(label);

		auto nextItem = MenuItemImage::create(
			"next.png",
			"next.png",
			CC_CALLBACK_1(SuccessLayer::muenNextCb, this));

		nextItem->setPosition(Vec2(size.width / 2 ,
			size.height / 2 - nextItem->getContentSize().height / 2));

		auto nextMenu = Menu::create(nextItem, NULL);
		nextMenu->setPosition(Vec2::ZERO);
		this->addChild(nextMenu, 1);


		auto closeItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(SuccessLayer::muenExitCb, this));

		closeItem->setPosition(Vec2(size.width / 2,
			closeItem->getContentSize().height / 2));

		auto closeMenu = Menu::create(closeItem, NULL);
		closeMenu->setPosition(Vec2::ZERO);
		this->addChild(closeMenu, 1);

		bRet = true;


	} while (0);

	return bRet;
}

void SuccessLayer::muenExitCb(Ref * s)
{
	Director::getInstance()->end();
}

void SuccessLayer::muenNextCb(Ref * s)
{
	int picIndex = UserDefault::getInstance()->getIntegerForKey("picIndex");
	if (picIndex > 4){
		auto scene = GameOverLayer::createScene();
		Director::getInstance()->replaceScene(TransitionFadeUp::create(1.0f,scene));
	}
	else{
		auto scene = MainScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
	}
}