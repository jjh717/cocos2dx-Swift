#include "OpenItemScene.h"
//#include "SimpleAudioEngine.h"
//#include "Effekseer/Effekseer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* OpenItem::createScene()
{
    return OpenItem::create();
}

bool OpenItem::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto rsize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    
    // for update
    this->scheduleUpdate();

    /**
        You create an instance of efk::EffectManager.
    */
//    manager = efk::EffectManager::create(rsize);

 
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("visibleSize %f %f" , visibleSize.width, visibleSize.height);
    CCLOG("origin %f %f" , origin.x, origin.y);
     
    
    
    for(int i = 0; i < 10; i++) {
        auto cardSprite = Sprite::create("Img/cardBack.png");

        cardSprite->setAnchorPoint(Vec2(0.5, 0.5));
        cardSprite->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
        cardSprite->setContentSize(Size(cardSize.width - 10, cardSize.height));
        cardSprite->setTag(i);
        this->addChild(cardSprite, 5);
        
        cardSprites.insert(cardSprites.end(), cardSprite);
    }



    shellLayer = Layer::create();
    shellLayer->setIgnoreAnchorPointForPosition(false);
    shellLayer->setAnchorPoint(Vec2(0.5, 0.5));
    shellLayer->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    shellLayer->setContentSize(Size(cardSize.width + 20, cardSize.height + 20));
    this->addChild( shellLayer, (int)cardSprites.size());

    shellTop = Sprite::create("Img/shellTop.png");
    shellTop->setPosition(Vec2(0, 0));
    shellTop->setAnchorPoint(Vec2(0, 0));
    shellTop->setContentSize(Size(shellLayer->getContentSize().width, shellLayer->getContentSize().height));
    shellLayer->addChild(shellTop);

    shellMiddle = Sprite::create("Img/shellMiddle.png");
    shellMiddle->setPosition(Vec2(shellLayer->getContentSize().width, 0));
    shellMiddle->setAnchorPoint(Vec2(1, 0));
    shellMiddle->setContentSize(Size(shellLayer->getContentSize().width, shellLayer->getContentSize().height));
    shellLayer->addChild(shellMiddle);

    auto shellBottom = Sprite::create("Img/shellBottom.png");
    shellBottom->setPosition(Vec2(0, 0));
    shellBottom->setAnchorPoint(Vec2(0, 0));
    shellBottom->setContentSize(Size(shellLayer->getContentSize().width, shellLayer->getContentSize().height));
    shellLayer->addChild(shellBottom);

    shellTouchEvent(shellLayer);
    
//    effectSwitch(0);
    
    return true;
}

void OpenItem::cuttingAnimaion() {
    if(!isAnimation) {
        gatherParticle = ParticleSystemQuad::create("Particle/gather.plist");
        gatherParticle->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
        gatherParticle->setScale(0.6);
        this->addChild( gatherParticle, 10);
        
        
        
        
        ScaleTo* end = ScaleTo::create(0.3, 0, 1);
        MoveBy* move = MoveBy::create(0.3, Vec2(-10, 0));
        DelayTime *pause = DelayTime::create(0.3);

        auto callback = CallFunc::create( CC_CALLBACK_0( OpenItem::shellMiddleRemove, this ) );
        Sequence* anim = Sequence::create(Spawn::createWithTwoActions(end, move), pause, callback, NULL);
        
        Speed *rep = Speed::create(anim, 2);
        shellMiddle->runAction(rep);
        
        
        
    }
    isAnimation = true;
}
 
void OpenItem::shellMiddleRemove()
{
    CCLOG("shellMiddleRemove");
    
    shellLayer->removeChild(shellTop);
    shellLayer->removeChild(shellMiddle);
 
    for(int i = 0; i < 10; i++) {
        MoveTo* move = MoveTo::create(1, Vec2(cardSprites[i]->getPosition().x, Director::getInstance()->getWinSize().height + cardSprites[i]->getContentSize().height));
//        MoveTo* move = MoveTo::create(0.5, Vec2(0, 100));
        DelayTime *pause = DelayTime::create(0.5*i);

        auto callback = CallFuncN::create(CC_CALLBACK_1(OpenItem::cardPopOutCallBack, this));
        Sequence* anim = Sequence::create(pause, move, callback, NULL);

        Speed *rep = Speed::create(anim, 5);
        cardSprites[i]->runAction(rep);
    }
    
}

void OpenItem::cardPopOutCallBack(Ref *sender)
{
    Sprite *sp = (Sprite *)sender;
    CCLOG("cardPopOutCallBack : %d", sp->getTag());
//    CCLOG("getPosition : %f", sp->getPosition().y);
//    this->removeChild(sp);
    
    if(sp->getTag() == cardSprites.size() - 1) {
        this->removeChild(shellLayer);
        this->removeChild(gatherParticle);
         
        this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&OpenItem::cardAppear), 1.0f);
    }
}
  
void OpenItem::shellTouchEvent(Layer *src)
{
    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        auto target = event->getCurrentTarget();
        Vec2 pos = touch->getLocation();
        
        CCLOG("target %f %f" , target->getPosition().x, target->getPosition().y);
        CCLOG("pos %f %f" , pos.x, pos.y);
        
        Rect boundary = target->getBoundingBox();
        if (boundary.containsPoint(pos)) {
            cuttingAnimaion();
            return true;
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, src);
}

void OpenItem::spriteTouchEvent(Sprite *src)
{
    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        auto target = event->getCurrentTarget();
        Vec2 pos = touch->getLocation();
        
        CCLOG("target %f %f" , target->getPosition().x, target->getPosition().y);
        CCLOG("pos %f %f" , pos.x, pos.y);
        
        Rect boundary = target->getBoundingBox();
        if (boundary.containsPoint(pos)) {
            flipAction((Sprite *)target);
            return true;
        }
        return false;
    };
     
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, src);
}

void OpenItem::flipAction2(Ref *sender)
{
    Sprite *sp = (Sprite *)sender;
    CCLOG("flipAction2 : %d", sp->getTag());

    std::string string = StringUtils::format("Img/card%d.png",(int)sp->getTag());
    Size size = sp->getContentSize();
    sp->setTexture(string);
    sp->setContentSize(size);
    
    auto rotate = RotateBy::create(0.5, Vec3(0, 90, 0));
    Sequence* anim = Sequence::create(rotate, NULL);
    sp->runAction(anim);
    
    ParticleSystemQuad *cardEffect = ParticleSystemQuad::create("Particle/light.plist");
    cardEffect->setPosition(sp->getPosition());
    cardEffect->setScale(0.4);
    this->addChild( cardEffect, 0);
}

void OpenItem::flipAction(Sprite *back) {
    auto rotate = RotateBy::create(0.5, Vec3(0, 90, 0));
    auto callback = CallFuncN::create(CC_CALLBACK_1(OpenItem::flipAction2, this));
    Sequence* anim = Sequence::create(rotate, callback, NULL);
    back->runAction(anim);
}
 
float sizeRatio(float srcWidth, float srcHeight, float dstWidth)
{
    return srcHeight * dstWidth / srcWidth;
}

void OpenItem::cardAppear(float dt)
{
    //80, 110
    int leftMargin = 30;
    int cardBetweenMargin = 10;
    int topMargin = 10;
    float cardWidth = (Director::getInstance()->getVisibleSize().width - leftMargin - (cardBetweenMargin * 4)) / 3;
    float cardHeight = sizeRatio(cardSize.width, cardSize.height, cardWidth);
    Size cardSizeInResult = Size(cardWidth, cardHeight);
    cardSprites[0]->setContentSize(cardSizeInResult);
    
    // + cardSprites[0]->getContentSize().height
    std::vector<cocos2d::Vec2> cardPos;
    Vec2 cardPos1 = Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 + topMargin / 2 + cardHeight / 2);
    cardPos.insert(cardPos.end(), cardPos1);
    
    Vec2 cardPos2 = Vec2(cardPos1.x - cardBetweenMargin - cardWidth, cardPos1.y);
    cardPos.insert(cardPos.end(), cardPos2);
    
    Vec2 cardPos3 = Vec2(cardPos1.x + cardBetweenMargin + cardWidth, cardPos1.y);
    cardPos.insert(cardPos.end(), cardPos3);
    
    
    
    Vec2 cardPos4 = Vec2(cardPos1.x, Director::getInstance()->getWinSize().height / 2 - topMargin / 2 - cardHeight / 2);
    cardPos.insert(cardPos.end(), cardPos4);
    
    Vec2 cardPos5 = Vec2(cardPos2.x, cardPos4.y);
    cardPos.insert(cardPos.end(), cardPos5);
    
    Vec2 cardPos6 = Vec2(cardPos3.x, cardPos4.y);
    cardPos.insert(cardPos.end(), cardPos6);
    
    
    
    
    Vec2 cardPos7 = Vec2(cardPos1.x - cardWidth / 2 - cardBetweenMargin / 2, cardPos1.y + topMargin + cardHeight);
    cardPos.insert(cardPos.end(), cardPos7);
    
    Vec2 cardPos8 = Vec2(cardPos1.x + cardWidth / 2 + cardBetweenMargin / 2, cardPos7.y);
    cardPos.insert(cardPos.end(), cardPos8);
    
    
    
    Vec2 cardPos9 = Vec2(cardPos7.x, cardPos4.y - topMargin - cardHeight);
    cardPos.insert(cardPos.end(), cardPos9);

    Vec2 cardPos10 = Vec2(cardPos8.x, cardPos9.y);
    cardPos.insert(cardPos.end(), cardPos10);
    


    for(int i = 0; i < 10; i++) {
        cardSprites[i]->setContentSize(cardSizeInResult);
        
        spriteTouchEvent(cardSprites[i]);
        
        MoveTo* move = MoveTo::create(0.5, cardPos[i]);
        DelayTime *pause = DelayTime::create(0.2*i);

        //    auto callback = CallFuncN::create(CC_CALLBACK_1(OpenItem::cardPopOutCallBack, this));
        Sequence* anim = Sequence::create(pause, move, NULL);

        Speed *rep = Speed::create(anim, 5);
        cardSprites[i]->runAction(rep);
    }
    
    
    auto okBtn = ui::Button::create("Img/buttons_background.png");
    okBtn->setTitleText("확인");
    okBtn->setTitleColor(Color3B(0, 0, 0));
    okBtn->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 50));
    okBtn->setContentSize(Size(120, 30));
    okBtn->addClickEventListener([&](Ref* pSender) {
        CCLOG("확인");
        
    });
    this->addChild(okBtn);
    
}
//
//void OpenItem::effectSwitch(int effectIndex) {
//    if(particleEmitter != NULL) {
//        particleEmitter->setIsLooping(false);
//        particleEmitter->removeFromParent();
//    }
//    switch (effectIndex) {
//        case 0: {
//            auto effect = efk::Effect::create("Particle/background.efk");
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//                particleEmitter->setIsLooping(true);
//                particleEmitter->setAnchorPoint(Vec2(0, 0));
//                particleEmitter->setPosition(Vec2(shellLayer->getPosition().x , shellLayer->getPosition().y));
//                particleEmitter->setScale(30);
//                particleEmitter->setSpeed(1);
//                particleEmitter->setRotation3D(cocos2d::Vec3(0, 0, 0));
////                particleEmitter->setPosition3D(Vec3(shellLayer->getPosition().x , shellLayer->getPosition().y, 120));
////                particleEmitter->setRotation3D(cocos2d::Vec3(0, 0, 0));
//                this->addChild(particleEmitter, 0);
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//        case 1: {
//            auto effect = efk::Effect::create("magicCold.efk");
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//                particleEmitter->setIsLooping(true);
//                particleEmitter->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 , Director::getInstance()->getWinSize().height / 2));
//                particleEmitter->setScale(8);
//                this->addChild(particleEmitter, 0);
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//        case 2: {
//            auto effect = efk::Effect::create("SquareWave.efk");
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//
//                particleEmitter->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 , Director::getInstance()->getWinSize().height / 2));
//                particleEmitter->setScale(8);
//                this->addChild(particleEmitter, 0);
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//        case 3: {
//            auto effect = efk::Effect::create("particle.efk");
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//
//                //particleEmitter->setRotation3D(cocos2d::Vec3(0, 90, 0));
//
//                particleEmitter->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 , Director::getInstance()->getWinSize().height / 2));
//                particleEmitter->setScale(8);
//                particleEmitter->setIsLooping(true);
//                this->addChild(particleEmitter, 0);
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//        case 4: {
//            auto effect = efk::Effect::create("dust.efk");
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//
//                particleEmitter->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 , Director::getInstance()->getWinSize().height / 2));
//                particleEmitter->setScale(8);
//                this->addChild(particleEmitter, 0);
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//        case 5: {
//            auto effect = efk::Effect::create("fire.efk");
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//
//                particleEmitter->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 , Director::getInstance()->getWinSize().height / 4));
//                particleEmitter->setScale(6);
//                this->addChild(particleEmitter, 0);
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//
//        case 6: {
//            auto effect = efk::Effect::create("Homing_Laser01.efk");
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//
//                particleEmitter->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 , Director::getInstance()->getWinSize().height / 2));
//                particleEmitter->setScale(4);
//                this->addChild(particleEmitter, 0);
//
//                /**
//                    Some parameters are required to set after addChild
//                */
//                particleEmitter->setTargetPosition(cocos2d::Vec3(320, 480, 0));
//
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//        case 7: {
//            auto effect = efk::Effect::create("Laser01.efk", 13.0f);
//            if (effect != nullptr)
//            {
//                particleEmitter = efk::EffectEmitter::create(manager);
//                particleEmitter->setEffect(effect);
//                particleEmitter->setPlayOnEnter(true);
//
//                particleEmitter->setRotation3D(cocos2d::Vec3(0, 90, 0));
//                particleEmitter->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 , Director::getInstance()->getWinSize().height / 2));
//
//                this->addChild(particleEmitter, 0);
//
//                // No need (because it uses autorelease after 1.41)
//                //effect->release();
//            }
//            break;
//        }
//        default:
//            break;
//    }
//}

void OpenItem::update(float delta)
{
    /**
        You update the manager every frame.
    */
//    manager->update();

    count++;
}

OpenItem::~OpenItem()
{
    /**
        You will destroy the manager on exit.
    */
//    manager->release();
}

void OpenItem::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
{
    /**
        You inherit visit and add a process to actually draw the effect.
    */
//    manager->begin(renderer, _globalZOrder);
    cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
//    manager->end(renderer, _globalZOrder);
}

