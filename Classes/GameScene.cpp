/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "NextGameScene.h"
#include "Definitions.h"

USING_NS_CC;

int DirX = 0;
int DirY = 0;
cocos2d::Sprite* mySrpite1;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;


}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
   // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::GoToNextGameScene), DISPLAY_TIME_GAME_SCENE);


    mySprite1 = Sprite::create("PICI.png");
    mySprite1->setPosition(Point(120, 120));
    mySprite1->setScale(0.3);
    auto spriteBody = PhysicsBody::createBox(mySprite1->getContentSize(), PhysicsMaterial(0, 1, 0));
    mySprite1->setPhysicsBody(spriteBody);
    this->addChild(mySprite1, 1);

    mySprite2 = Sprite::create("PLAN.png");
    mySprite2->setPosition(Point(0, 0));
    this->addChild(mySprite2, 1);

    mySprite3 = Sprite::create("LEVEL1.png");
    mySprite3->setPosition(Point(75, 300));
    this->addChild(mySprite3, 1);

    auto backgroundSprite = Sprite::create("bgd.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    mySprite4 = Sprite::create("PIPE.png");
    mySprite4->setPosition(Point(250, 260));
    this->addChild(mySprite4);
    auto rotateAction = RotateBy::create(9, 360);
    auto action = RepeatForever::create(rotateAction);
    mySprite4->runAction(action);


    // keyboard  
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {

        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            DirX -= 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            DirX += 3.0f;
            break;
        }
    };

    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {

        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            DirX += 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            DirX -= 3.0f;
            break;
        }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    this->scheduleUpdate();


    return true;
}

void GameScene::update(float dt) {

    float newPosX = mySprite1->getPositionX() + (DirX);
    float newPosY = mySprite1->getPositionY() + (DirY);

    mySprite1->setPosition(newPosX, newPosY);

}

void GameScene::GoToNextGameScene(float dt)
{
    auto scene = NextGameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
    

