/*
 * Gugo.h
 *
 *  Created on: 15/gen/2015
 *      Author: XPIN12
 */

#ifndef GUGO_H_
#define GUGO_H_

#include "cocos2d.h"
using namespace cocos2d;

class Gugo : public cocos2d::Sprite {
	Sprite *_pallina;
	bool _urtato = false;
    Size _visibleSize ;
    Vec2 _origin ;


public:
	Gugo();
    ~Gugo();

    CC_SYNTHESIZE(int, _punti, Punti);
    CC_SYNTHESIZE(bool, _colpito, Colpito);

    static Gugo* gugoSpriteWithFile(const std::string& filename);


    inline float radius() const { return getTexture()->getContentSize().width * 0.5f; }

    virtual bool initWithFile(const std::string& filename) override;

    void aggiungiPallina(const std::string& filename);
    void aggiungiPallina(Sprite * node);
    void faiCaderePallina(Node * node);
    void faiVolare();
    void setInvisible(Node * node);
    void muovi();
    void muoviSinistraDestraInAlto();
    void muoviLeAli();
    void muoviSopraSotto();

};


#endif /* GUGO_H_ */
