#ifndef __OPENITEM_SCENE_H__
#define __OPENITEM_SCENE_H__

#include "cocos2d.h"

//#if COCOS2D_VERSION >= 0x00040000
//#include "EffekseerForCocos2d-x.h"
//#else
//#include "Effekseer/Effekseer.h"
//#endif

using namespace std;
class OpenItem : public cocos2d::Scene
{
private:
    /**
        You add efk :: EffectManager * to the layer member variable. This class manages effects.
    */
//    efk::EffectManager*        manager = nullptr;
//    efk::EffectEmitter *particleEmitter = NULL;
    int count = 0;
    int effectIndex = 0;
    bool isAnimation = false;
    
    std::vector<cocos2d::Sprite*> cardSprites;
    
    cocos2d::Layer *shellLayer = NULL;
    cocos2d::Sprite *shellTop = NULL;
    cocos2d::Sprite *shellMiddle = NULL;
    cocos2d::Size cardSize = cocos2d::Size(80, 110);
      
    cocos2d::ParticleSystemQuad *gatherParticle = NULL;
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    virtual void update(float delta) override;
    
    void effectSwitch(int effectIndex);
    void cuttingAnimaion();
    
    void shellMiddleRemove();
    void cardPopOutCallBack(Ref *sender);
    void cardAppear(float dt);
    
    void flipAction(cocos2d::Sprite *back);
    void flipAction2(Ref *sender);
    
    void shellTouchEvent(cocos2d::Layer *src);
    void spriteTouchEvent(cocos2d::Sprite *src);
    
    virtual ~OpenItem();
    
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;
    CREATE_FUNC(OpenItem);
};
#endif  
