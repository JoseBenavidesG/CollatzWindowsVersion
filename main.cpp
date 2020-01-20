#include <iostream>
#include <cstdlib>
#include "webserver.h"
#include "socket/src/Socket.h"
#include <cctype>

std::string s;
bool isOk(std::string x) {

    while(s.size() > 1 && x[0] == ' ')
        x.erase(x.begin());

    int ini = x[0] == '-';

    for(int i=ini;i<x.size();i++)
        if('0' <= x[i] && x[i] <= '9')
            continue;
        else
            return false;

    return true;

}

int toNumber(std::string x) {

    while(s.size() > 1 && x[0] == ' ')
        x.erase(x.begin());

    int ini = x[0] == '-', res = 0;

    for(int i=ini;i<x.size();i++) {
        res *= 10;
        res += x[i] - '0';
    }

    return ini?-res:res;

}


void Request_Handler(webserver::http_request* r) {
    Socket s = *(r->s_);
    int num=0;
    std::string  naturalNumber;
    std::string title;
    std::string body;
    std::string bgcolor="#ffffff";

    std::string strTmp= (isOk(r->path_.substr(1,-1))) ?r->path_.substr(1,-1):"\0";


    if (
         ( r->path_ == ("/" + strTmp)) &&
         ( strTmp.length() > 0 && std::stoi(strTmp) > 0)
        ) {
        std::string json;
        bool firtsElement=true;
        int nCollatz =  std::stoi(strTmp);
        bool notInfinite = true;
        do  {
            if (!firtsElement) json += ", ";
            if (nCollatz % 2 == 0) {
                nCollatz /= 2;
            } else {
                nCollatz = 3 * nCollatz + 1;
            }
            if (firtsElement) {
                json = "[";
                firtsElement = false;
            }
            json += std::to_string(nCollatz);
            if (nCollatz == 1) notInfinite=false;
        }while(notInfinite);
        json += "]";

        std::cout << json << std::endl;

        r->status_ = "200 Ok";
        body = json;
    }else{
        r->status_ = " 404 Not Found";
        title      = " URL Incorrecta";
        body       = " <h1>URL Incorrecta!!!</h1>";
        body       = " solo numeros naturales (1,2,3,4....)";
        body      += " use el sgte formato de URL : localhost:8080/23";
        std::cout << title << std::endl;
        std::cout << body << std::endl;
    }


    r->answer_  = "<html><head><title>";
    r->answer_ += title;
    r->answer_ += "</title></head><body bgcolor='" + bgcolor + "'>";
    r->answer_ += body;
    r->answer_ += "</body></html>";
}

int main() {
    webserver(8080, Request_Handler);
}