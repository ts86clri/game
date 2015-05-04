#include "HelloWorldScene.h"

USING_NS_CC;

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
    
	//画面取得
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//画像表示
	Sprite* sprite = Sprite::create("hosi.png");
	//位置指定
	sprite->setPosition(Vec2(300, 200));
	sprite->setTag(1);

	//イベント
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(sprite);

	// callbackの定義
	CallFunc* callback = CallFunc::create([](){
		printf("callback");
	});

	// callbackの実行
	callback->execute(); // callback

    return true;
}

//タップしたところに移動
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* envent)
{
	auto location = touch->getLocation();
	auto sprite = this->getChildByTag(1);

	sprite->setPosition(location);

	return true;

}

//タップし続けている間その場所に移動
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto location = touch->getLocation();
	auto sprite = this->getChildByTag(1);

	sprite->setPosition(location);

}

//タップはなした時に画像を中央に移動して消す
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	//目的地へのアクション
	auto visibleSize = Director::getInstance()->getVisibleOrigin();
	auto point = Point(Vec2(300, 200));
	auto move = MoveTo::create(2.0f, point);

	//画像の取得
	auto sprite = this->getChildByTag(1);

	//callbackでの消去処理
	auto removeSprite = CallFunc::create([this, sprite]()
	{	
		this->removeChild(sprite);
	});
	//順次実行 move ➡ removeSprite
	auto sequence = Sequence::create(move, removeSprite, NULL);
	sprite->runAction(sequence);

}



