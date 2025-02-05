#include "Packet.hpp"
#include "network/exceptions/NetworkExceptions.hpp"
#include "network/packets/ErrorPacket.hpp"
#include "network/packets/GameOverPacket.hpp"
#include "network/packets/GameStartPacket.hpp"
#include <cstring>

namespace Network {

std::unique_ptr<Packet> Packet::deserialize(const std::vector<uint8_t> &data) {
  PacketType type;
  if (data.size() < sizeof(PacketType)) {
    throw IncompletePacketException("Packet size is too small");
  }

  std::memcpy(&type, data.data(), sizeof(PacketType));

  switch (type) {
  case PacketType::ERROR: return ErrorPacket::deserialize(data);
  case PacketType::NONE: throw InvalidPacketFormatException("NONE is not a valid packet"); break;
  case PacketType::GAME_START: return GameStartPacket::deserialize(data); break;
  case PacketType::GAME_OVER: return GameOverPacket::deserialize(data); break;
  default:
    throw UnsupportedPacketVersionException("Packet version " + std::to_string(static_cast<uint>(type)) +
                                            "could not be deserialized");
    break;
  }
}

std::ostream &operator<<(std::ostream &os, Packet::PacketType type) {
  switch (type) {
  case Packet::PacketType::ERROR: os << "ERROR"; break;
  case Packet::PacketType::NONE: os << "NONE"; break;
  case Packet::PacketType::GAME_START: os << "GAME_START"; break;
  case Packet::PacketType::GAME_OVER: os << "GAME_OVER"; break;
  }
  return os;
}
} // namespace Network
