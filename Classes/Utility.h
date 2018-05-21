//
//  Utility.h
//  Sea
//
//  Created by 박 진 on 12. 10. 10..
//
//

#pragma once

#include <queue>
#include "cocos2d.h"

#define PTM_RATIO   32
#define PI          3.141592653589793238462643383279f

#define HIWORD(l)   ((short) (((long) ((l) >> 16)) & 0x0000FFFF))
#define LOWORD(l)   ((short) ((l) & 0x0000FFFF))

#define GETWORD_X(w) LOWORD(w)
#define GETWORD_Y(w) HIWORD(w)

#define MAKEWORD(x,y) ((long)((LOWORD(x) & 0x0000FFFF)|((((long)LOWORD(y)) << 16) & 0xFFFF0000)))

#define DEGREE_TO_RADIAN(d) d * PI / 180.f
#define RADIAN_TO_DEGREE(r) r * 180.f/PI

typedef unsigned char COLORVALUE;

struct COLOR_ARGB
{
    int a;
    int r;
    int g;
    int b;
    
    COLOR_ARGB() : a(255), r(255), g(255), b(255)
    {}
    COLOR_ARGB(COLORVALUE a, COLORVALUE r, COLORVALUE g, COLORVALUE b)
    {
        this->a = a;
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

template<typename TYPE>
struct POINT
{
    TYPE x, y;
    
    POINT(TYPE _x = 0, TYPE _y = 0)
    {
        x = _x;
        y = _y;
    }
};

template<typename TYPE>
struct SIZE
{
    TYPE width, height;
    
    SIZE(TYPE _w = 0, TYPE _h = 0)
    {
        width   = _w;
        height  = _h;
    }
};

template <typename TYPE>
inline bool intersectBoxWithBox(POINT<TYPE> pos1, SIZE<TYPE> size1,
                                POINT<TYPE> pos2, SIZE<TYPE> size2)
{
    //CA Edit
    //>, < to >=, <=
    
    if( pos2.x >= pos1.x + size1.width )
        return false;
    if( pos2.x + size2.width <= pos1.x )
        return false;
    if( pos2.y >= pos1.y + size1.height )
        return false;
    if( pos2.y + size2.height <= pos1.y )
        return false;
    
    return true;
}

template <typename TYPE>
inline bool intersectBoxWithPoint(POINT<TYPE> boxPos, SIZE<TYPE> boxSize, POINT<TYPE> pos)
{
    if( (boxPos.x <= pos.x && pos.x < boxPos.x + boxSize.width) &&
       (boxPos.y <= pos.y && pos.y < boxPos.y + boxSize.height) )
        return true;
    
    return false;
}

template <typename T>
static void stdQueueAllClear(std::queue<T> &stdQueue)
{
    while (stdQueue.empty()==false)
        stdQueue.pop();
}

static void TextFieldKeyBoardOn(cocos2d::CCNode *pNode, cocos2d::CCSet *pTouches, cocos2d::CCTextFieldTTF **ppTextFields, int num = 1)
{
    if(pNode->isVisible() == false)
        return;
    
    cocos2d::CCPoint point;
    cocos2d::CCTouch * pTouch = static_cast<cocos2d::CCTouch *>(*(pTouches->begin()));
    
    point = pTouch->getLocationInView();
    point = cocos2d::CCDirector::sharedDirector()->convertToGL(point);
    point.x -= pNode->getPositionX();
    point.y -= pNode->getPositionY();
    
    //뭐 여기서 남은 작업해주면되
    POINT<int> boxPos;
    SIZE<int>  boxSize;
    POINT<int> touchPoint = POINT<int>(point.x, point.y);
    
    for (int i=0; i<num; ++i) {
        boxPos.x = ppTextFields[i]->getPositionX();
        boxPos.y = ppTextFields[i]->getPositionY();
        boxSize.width = ppTextFields[i]->getContentSize().width;
        boxSize.height = ppTextFields[i]->getContentSize().height;
        
        if(intersectBoxWithPoint(boxPos, boxSize, touchPoint))
        {
            ppTextFields[i]->attachWithIME();
            break;
        }
        
        printf("%f %f \n", ppTextFields[i]->getAnchorPoint().x, ppTextFields[i]->getAnchorPoint().y);
    }
    
    printf("x %f, y %f \n", point.x, point.y);
}

static bool isExistFile(const char* path)
{
    bool has = false;
    
    FILE *p = fopen(path, "rb");
    has = p;
    fclose(p);
    
    return has;
}

static float calcDegreeBetweenTwoPoint(POINT<float> p1, POINT<float> p2)
{
    float x, y;
    
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    
    float  radian = atan2(x, y);
    float   degree = 180.f * radian / PI;
    
    return degree;
}

static POINT<float> rotatePoint(POINT<float> &point, float degree)
{
    POINT<float> p;
    float radian = DEGREE_TO_RADIAN(degree);
    
    p.x = point.x + (cos(radian) - sin(radian));
    p.y = point.y + (cos(radian) + sin(radian));
    
    return p;
}

static float calcDistance(float x1, float x2, float y1, float y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

#ifndef SAFE_DELETE//(P)
#define SAFE_DELETE(P) if(P){delete P; P = NULL;}
#endif