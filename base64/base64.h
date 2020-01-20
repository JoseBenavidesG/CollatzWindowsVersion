//
// Created by joseb on 18-01-2020.
//

#ifndef WSDL_JBG_BASE64_H
#define WSDL_JBG_BASE64_H
//
//  base64 encoding and decoding with C++.
//  Version: 1.01.00
//


#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);


#endif //WSDL_JBG_BASE64_H
