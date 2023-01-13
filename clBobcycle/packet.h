#define _CRT_SECURE_NO_WARNINGS
#pragma once
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

    Type type;
    std::unique_ptr<char[]> buffer;
    size_t size;
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