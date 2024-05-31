#pragma once

#ifndef _BASE64_H_
#define _BASE64_H_

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
typedef unsigned char BYTE;

std::string base64_encode(BYTE const* buf, unsigned int bufLen);
std::vector<BYTE> base64_decode(std::string const&);
std::string convertAsciiToHangul(const std::string& asciiCodes);

#endif