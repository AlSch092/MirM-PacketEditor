#pragma once
#include "PacketBuilder.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <string>

namespace PacketHelper
{
	int rand_lim(int limit);

	std::string randomStr(size_t size);
	std::wstring randomWStr(size_t size);

	std::string string_to_hex(const std::string& input);
	std::string hex_to_string(const std::string& input);

	uint16_t changeEndianness16(UINT16 val);
	int32_t changeEndianness32(int32_t val);

	LPBYTE ToPacketFormat(const CHAR* input);
	std::string ToString(LPBYTE packetStr, int byteLength);

	int GetPacketLength(const CHAR* input);

	BOOL LogSendPacketToQueue(LPBYTE data, UINT length);
	BOOL LogRecvPacketToQueue(LPBYTE data, UINT length);
};