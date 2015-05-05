#include <algorithm>
#include "MainLayer.h"
#include "SuccessLayer.h"


using std::random_shuffle;
USING_NS_CC;
MainLayer::MainLayer()
{
	// 屏幕可视化长宽
	winWith = Director::getInstance()->getWinSize().width;
	winHeight = Director::getInstance()->getWinSize().height;

}
MainLayer::~MainLayer()
{}

bool MainLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::create());
		this->initPic();

		auto lisener = EventListenerTouchOneByOne::create();
		lisener->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchBegan, this);
		lisener->onTouchMoved = CC_CALLBACK_2(MainLayer::onTouchMoved, this);
		lisener->onTouchEnded = CC_CALLBACK_2(MainLayer::onTouchEnded, this);
		//lisener->onTouchCancelled = CC_CALLBACK_2(MainLayer::onTouchCancelled, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(lisener, this);

		bRet = true;
	} while (0);
	return bRet;
}

bool MainLayer::onTouchBegan(Touch * t, Event * e)
{
	auto location = this->convertToNodeSpace(t->getLocation());
	for (unsigned int i = 0; i < listSp.size(); i++)
	{
		auto sp = listSp.at(i);
		if (sp->getBoundingBox().containsPoint(location))
		{
			selectIndex = i; // 记录点击位置图
			beganLocatin = sp->getPosition();
			sp->setZOrder(10);
			break;
		}
	}
	return true;
}

void MainLayer::onTouchMoved(Touch * t, Event * e)
{
	auto contentSize = listSp.at(selectIndex)->getContentSize();
	auto loc = t->getLocation();
	//边界判断
	if (loc.x - contentSize.width / 2 < 0){
		loc.x = 0;
	}
	if (loc.x + contentSize.width > winWith){
		loc.x = winWith - contentSize.width;
	}
	if (loc.y - contentSize.height < 0){
		loc.y = contentSize.height;
	}
	if (loc.y + contentSize.height > winHeight){
		loc.y = winHeight;
	}
	listSp.at(selectIndex)->setPosition(loc);
}

void MainLayer::onTouchEnded(Touch * t, Event * e)
{
	bool hasR = false; // 判断是否需要交换
	auto location = this->convertToNodeSpace(t->getLocation());
	for (unsigned int i = 0; i < listSp.size(); i++)
	{
		auto sp = listSp.at(i);
		if (sp->getBoundingBox().containsPoint(location))
		{
			if (i == selectIndex){
				continue;
			}
			hasR = true;
			auto tempVec2 = sp->getPosition();
			sp->setPosition(beganLocatin);
			listSp.at(selectIndex)->setPosition(tempVec2);
			sp->setZOrder(0);
			listSp.at(selectIndex)->setZOrder(0);
			listSp.swap(i, selectIndex);
			break;
		}
	}
	int success = 0;
	// 判断拼图位置正确数
	for (unsigned int i = 0; i < listSp.size(); i++)
	{
		if (listSp.at(i)->getTag() == i){// 当前位置正确，变亮
			listSp.at(i)->setColor(Color3B(255, 255, 255));
			success++;
		}
		else{
			listSp.at(i)->setColor(Color3B(122, 122, 122));
		}
	}

	// 拼图完成
	if (success == listSp.size()){
		auto scene = SuccessLayer::createScene();
		Director::getInstance()->replaceScene(TransitionJumpZoom::create(1.0f, scene));
	}
	// 没有移动位置
	if (!hasR){
		listSp.at(selectIndex)->setPosition(beganLocatin);
	}
}

void MainLayer::initPic()
{
	auto picIndex = UserDefault::getInstance()->getIntegerForKey("picIndex", 1);

	char s[10];
	sprintf(s, "bg%d.jpg", picIndex);
	auto texture = TextureCache::getInstance()->addImage(s);
	auto lw = winWith / 3;
	auto lh = winHeight / 3;
	listSp.reserve(9);
	int tag = 0;
	std::vector<Vec2> loc;
	loc.reserve(9);
	// 初始化9格图片
	for (int w = 0; w < 3; w++){
		for (int h = 0; h < 3; h++)
		{
			auto sp0 = Sprite::createWithTexture(texture, Rect((0 + w)*lw, (0 + h)*lh, lw, lh));
			sp0->setColor(Color3B(122, 122, 122));
			sp0->setAnchorPoint(Vec2(0, 1));
			auto s = Vec2(w*lw, (3 - h)* lh);
			loc.push_back(s);
			sp0->setTag(tag);
			listSp.pushBack(sp0);
			++tag;
		}
	}
	// 随机种子，若不加，每次random结果一样
	srand(static_cast<unsigned int>(time(0)));
	random_shuffle(listSp.begin(), listSp.end());
	int y = 0;
	for (int i = 0; i < 9; i++)
	{
		auto s = loc.at(i);
		listSp.at(i)->setPosition(s);
		this->addChild(listSp.at(i));

	}
	// 设置下一副图索引
	UserDefault::getInstance()->setIntegerForKey("picIndex", ++picIndex);
}

void MainLayer::graySprite(Sprite * sprite)
{
	if (sprite)
	{
		GLProgram * p = new GLProgram();
		p->initWithFilenames("gray.vsh", "gray.fsh");
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		p->link();
		p->updateUniforms();
		sprite->setShaderProgram(p);
	}
}