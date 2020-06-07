#pragma once
#include "stdafx.h"


class HelloWorld : public Layer
{
private:

	cCandyManager * candy;

public:
    static Scene* createScene();

    virtual bool init();  

	bool onTouchBegan(Touch *touch, Event *unused_event); 
	void onTouchEnded(Touch *touch, Event *unused_event); 
	void onTouchMoved(Touch *touch, Event *unused_event); 

    CREATE_FUNC(HelloWorld);
};