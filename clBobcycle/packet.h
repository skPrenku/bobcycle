#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#include <WinSock2.h>
#include <iostream>



struct Packet {
    enum class Type : std::int16_t {
		txt_data, 
		clip_data, 
		hw_data, 
		snd_data, 
		img_data, 
		vid_data, 
		ft_data 
	};

	Type type = {};
    std::unique_ptr<char[]> buffer;
    size_t size = {};
};

inline Packet makePacket(const std::string& text , Packet::Type textType) {
	Packet packet{ textType, std::make_unique<char[]>(text.size()), text.size() };
	memcpy(packet.buffer.get(), text.data(), text.size());
	return packet;
}

inline Packet makePacketFromSound(const char* data, size_t size) {
	Packet packet{ Packet::Type::snd_data, std::make_unique<char[]>(size), size };
	memcpy(packet.buffer.get(), data, size);
	return packet;
}

inline Packet makePacketFromImage(const char* data, size_t size) {
	Packet packet{ Packet::Type::img_data, std::make_unique<char[]>(size), size };
	memcpy(packet.buffer.get(), data, size);
	return packet;
}

inline void sendPacket(SOCKET s, const Packet& packet) {
	std::uint16_t type = static_cast<std::uint16_t>(htons((short)packet.type));
	std::uint32_t size = static_cast<std::uint32_t>(htonl(packet.size));
	send(s, (char*)&type, sizeof(type), 0);
	send(s, (char*)&size, sizeof(size), 0);
	send(s, packet.buffer.get(), packet.size, 0);
}

inline Packet recvPacket(SOCKET s) {
	Packet packet;

	std::uint16_t type;
	recv(s, (char*) &type, sizeof(type), 0);
	packet.type = static_cast<Packet::Type>(ntohs(type));

	std::uint32_t size;
	recv(s, (char*)&size, sizeof(size), 0);
	packet.size = static_cast<std::uint32_t>(ntohl(size));

	auto buffer = std::make_unique<char[]>(packet.size);
	recv(s, packet.buffer.get(), packet.size, 0);
	std::swap(buffer, packet.buffer);

	return packet;
}