#pragma once

#include "stdafx.h"

class alphaGo : public Layer
{
private:

	bool isGameOver;

	cOmok* Omok;

public:
    static Scene* createScene();

    virtual bool init();  

    void menuCloseCallback(Ref* pSender);
    
	void Update(float dt);

	virtual bool onTouchBegan(Touch*touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch*touch, Event* unused_event);

    //!< ¾ÀÀ» µî·Ï ½ÃÅ´
	CREATE_FUNC(alphaGo);
};