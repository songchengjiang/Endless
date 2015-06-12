#include "HelloWorldScene.h"

USING_NS_CC;

static const float RANGE_RADIUS = 300.0f;
static const float CIRCLE_RADIUS = 140.0f;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    //// add a label shows "Hello World"
    //// create and initialize a label
    //
    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //
    //// position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(label, 1);

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(sprite, 0);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchBegining, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchMoving, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto layer = Layer::create();
	layer->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(layer);

	_renderTex = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
	_renderTex->clear(1.0f, 1.0f, 1.0f, 1.0f);
	layer->addChild(_renderTex, -1);

	_circle = Node::create();
	_mark = Node::create();
	layer->addChild(_circle);
	_circle->addChild(_mark);
	_circle->setPosition(Vec2(RANGE_RADIUS - CIRCLE_RADIUS, 0.0f));

	_drawNode = DrawNode::create();
	_drawNode->drawCircle(Vec2(_circle->getPositionX(), _circle->getPositionY()), CIRCLE_RADIUS, 0.0, 64, false, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	_drawNode->drawCircle(Vec2::ZERO, RANGE_RADIUS, 0.0f, 64, false, Color4F(0.0f, 0.0f, 0.0f, 1.0f));
	layer->addChild(_drawNode);

	scheduleUpdate();

	_theta = 0.0f;
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::drawLines()
{
	{
		float patternCircleR = 140.0f;
		float circleR = 300.0f;
		float markR = 100.0f;
		drawPattern(circleR, patternCircleR, markR, Color3B(152, 235, 207));
	}

	{
		float patternCircleR = 140.0f;
		float circleR = 300.0f;
		float markR = 80.0f;
		drawPattern(circleR, patternCircleR, markR, Color3B(102, 180, 203));
	}


	{
		float patternCircleR = 140.0f;
		float circleR = 300.0f;
		float markR = 60.0f;
		drawPattern(circleR, patternCircleR, markR, Color3B(232, 229, 210));
	}


	{
		float patternCircleR = 140.0f;
		float circleR = 300.0f;
		float markR = 40.0f;
		drawPattern(circleR, patternCircleR, markR, Color3B(207, 110, 93));
	}
}

void HelloWorld::drawPattern(float radius1, float radius2, float radius3, const cocos2d::Color3B &color)
{
	_renderTex->begin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Mat4 baseMat = Mat4::IDENTITY;
	Mat4 firstMat = Mat4::IDENTITY;
	Mat4 secondMat = Mat4::IDENTITY;

	baseMat.translate(Vec3(visibleSize.width / 2.0f, visibleSize.height / 2.0f, 0.0f));
	firstMat.translate(Vec3(radius1 - radius2, 0.0f, 0.0f));
	secondMat.translate(Vec3(radius3, 0.0f, 0.0f));

	firstMat.rotate(Vec3(0.0f, 0.0f, 1.0f), -_theta);
	float theta1 = (_theta * radius2) / radius1;
	baseMat.rotate(Vec3(0.0f, 0.0f, 1.0f), theta1);

	Mat4 mat = baseMat * firstMat * secondMat;
	auto sprite = Sprite::create("fire.png");
	sprite->setScale(0.2f);
	sprite->setColor(color);
	sprite->setOpacity(128);
	sprite->setPosition(mat.m[12], mat.m[13]);
	sprite->visit();
	_renderTex->end();
}

void HelloWorld::update(float delta)
{
	//if (_theta < 2 * M_PI * 50){
	//	//for (unsigned int i = 0; i < 10; ++i){
	//		drawLines();
	//		_theta += 0.01;
	//	//}
	//}
	//else{
	//	_renderTex->saveToFile("tex.png");
	//	unscheduleUpdate();
	//}
}

void HelloWorld::onTouchMoving(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event)
{
	if (0 < touchs.size()){
		auto location = touchs[0]->getLocation();
		auto preLocation = touchs[0]->getPreviousLocation();
		Vec2 dir = location - _center;
		Vec2 preDir = preLocation - _center;
		dir.normalize();
		preDir.normalize();

		float theta = acosf(dir.dot(preDir));
		theta = dir.y < preDir.y ? -theta : theta;
		_theta += theta;
		drawPattern(300.0f, 140.0f, _markRadius, Color3B(152, 235, 207));
	}
}

void HelloWorld::onTouchBegining(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event)
{
	if (0 < touchs.size()){
		auto location = touchs[0]->getLocation();
		Mat4 mat = _circle->getWorldToNodeTransform();
		Mat4 inv = (_baseMat * _firstMat).getInversed();
		Vec3 localPos;
		inv.transformPoint(Vec3(location.x, location.y, 0.0f), &localPos);
		_markRadius = localPos.length();
	}
}

void HelloWorld::onTouchEnding(const std::vector<cocos2d::Touch*> &touchs, cocos2d::Event *event)
{
}
