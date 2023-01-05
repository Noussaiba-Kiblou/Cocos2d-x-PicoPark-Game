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

#include "NextGameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"


USING_NS_CC;
int DireX = 0;
int DireY = 0;
cocos2d::Sprite* mySrpite5;
Scene* NextGameScene::createScene()
{
         // 'scene' is an autorelease object
          auto scene = Scene::create();

        // 'layer' is an autorelease object
          auto layer = NextGameScene::create();

        // add layer as a child to scene
         scene->addChild(layer);

         // return the scene
            return scene;
}

    // on "init" you need to initialize your instance
    bool NextGameScene::init()
{
     //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
     
    auto backgroundSprite = Sprite::create("BGG.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    mySprite5 = Sprite::create("Piicii.png");
    mySprite5->setPosition(Point(100, 150));
    mySprite5->setScale(0.3);
    this->addChild(mySprite5, 1);

    mySprite6 = Sprite::create("A.png");
    mySprite6->setPosition(Point(150, 120));
    mySprite6->setScale(0.3);
    this->addChild(mySprite6, 1);

    mySprite7 = Sprite::create("B.png");
    mySprite7->setPosition(Point(250, 200));
    mySprite7->setScale(0.3);
    this->addChild(mySprite7, 1);

    mySprite8= Sprite::create("C.png");
    mySprite8->setPosition(Point(390, 120));
    mySprite8->setScale(0.3);
    this->addChild(mySprite8, 1);


    this->scheduleOnce(CC_SCHEDULE_SELECTOR(NextGameScene::GoToGameOverScene), DISPLAY_TIME_NEXT_GAME_SCENE);



    // keyboard
        auto eventListener = EventListenerKeyboard::create();
        eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {

        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            DireY += 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            DireX -= 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            DireY -= 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            DireX += 3.0f;
            break;
        }
    };

    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            DireY -= 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            DireX += 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            DireY += 3.0f;
            break;

        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            DireX -= 3.0f;
            break;
        }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    this->scheduleUpdate();



   

    return true;
}

    void NextGameScene::update(float dt) {

        float newPosX = mySprite5->getPositionX() + (DireX);
        float newPosY = mySprite5->getPositionY() + (DireY);

        mySprite5->setPosition(newPosX, newPosY);
    }
    void NextGameScene::GoToGameOverScene(float dt)
    {
        auto scene = GameOverScene::createScene();

        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
