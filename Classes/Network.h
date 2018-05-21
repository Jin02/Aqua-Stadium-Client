//
//  Network.h
//  Sea
//
//  Created by 박 진 on 12. 10. 9..
//
//

#pragma once

#include <stdlib.h>
#include <memory.h>
#include <curl/curl.h>
#include <string>

#define NETWORK_RESPONSE_TIME 5

struct CURL_DATA {
    char    *pContent;
    int      size;
    
    CURL_DATA()
    {
        pContent    = (char*)malloc(1); //어짜피 realloc함 임시적
        size        = 0;
    }
    
    ~CURL_DATA()
    {
        free(pContent);
        pContent = NULL;
    }
};

class Network
{
private:
    CURL        *m_pCTX;
    
public:
    Network(bool isMsgBoxOn = false);
    ~Network();
    
private:
    static int _WriteCurlDataCallback(void *ptr, int size, int nmemb, void *pData);
    
public:
    CURLcode    connectHttp(const char *url, CURL_DATA *pData);
    
public:
    int             GetResponseCode();
    std::string     GetContentType();
    double          GetSize();
    double          GetSpeed();
};