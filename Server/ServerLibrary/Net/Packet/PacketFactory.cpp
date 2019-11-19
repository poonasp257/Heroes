#include "stdafx.h"

Packet* PacketFactory::CreatePacket(PacketType type) {
    switch(type) {
		case PacketType::AuthLoginRequest: return new AuthLoginRequestPacket();
		case PacketType::AuthLoginResponse: return new AuthLoginResponsePacket();
		case PacketType::AuthRegisterRequest: return new AuthRegisterRequestPacket();
		case PacketType::AuthRegisterResponse: return new AuthRegisterResponsePacket();
		case PacketType::ChanelStatusRequest: return new ChanelStatusRequestPacket();
		case PacketType::ChanelStatusResponse: return new ChanelStatusResponsePacket();
		case PacketType::ConnectChanelRequest: return new ConnectChanelRequestPacket();
		case PacketType::ConnectChanelResponse: return new ConnectChanelResponsePacket();
		case PacketType::DisconnectChanelRequest: return new DisconnectChanelRequestPacket();
		case PacketType::DisconnectChanelResponse: return new DisconnectChanelResponsePacket();
		case PacketType::AccountInfoRequest: return new AccountInfoRequestPacket();
		case PacketType::AccountInfoResponse: return new AccountInfoResponsePacket();
		case PacketType::CreateCharacterRequest: return new CreateCharacterRequestPacket();
		case PacketType::CreateCharacterResponse: return new CreateCharacterResponsePacket();
		case PacketType::CharacterMoveRequest: return new CharacterMoveRequestPacket();
		case PacketType::CharacterMoveResponse: return new CharacterMoveResponsePacket();
        // case PacketType::CharacterMoveRequest: return new CharacterMoveRequest;
        // case PacketType::CharacterMoveResponse: return new CharacterMoveResponse;
        // case PacketType::CharacterAttackRequest: return new CharacterAttackRequest;
        // case PacketType::CharacterAttackResponse: return new CharacterAttackResponse;
        // case PacketType::CharacterActionRequest: return new CharacterActionRequest;
        // case PacketType::CharacterActionResponse: return new CharacterActionResponse;
        // case PacketType::ApplyCharacterStatRequest: return new ApplyCharacterStatRequest;
        // case PacketType::ApplyCharacterStatResponse: return new ApplyCharacterStatResponse;
        // case PacketType::ResetCharacterStatRequest: return new ResetCharacterStatRequest;
        // case PacketType::ResetCharacterStatResponse: return new ResetCharacterStatResponse;
        // case PacketType::ApplyCharacterSkillRequest: return new ApplyCharacterSkillRequest;
        // case PacketType::ApplyCharacterSkillResponse: return new ApplyCharacterSkillResponse;
        // case PacketType::ResetCharacterSkillRequest: return new ResetCharacterSkillRequest;
        // case PacketType::ResetCharacterSkillResponse: return new ResetCharacterSkillResponse;
        // case PacketType::EquipItemRequest: return new EquipItemRequest;
        // case PacketType::EquipItemResponse: return new EquipItemResponse;
        // case PacketType::DeleteItemRequest: return new DeleteItemRequest;
        // case PacketType::DeleteItemResponse: return new DeleteItemResponse;
        // case PacketType::TradeItemRequest: return new TradeItemRequest;
        // case PacketType::TradeItemResponse: return new TradeItemResponse;
        // case PacketType::EchantItemRequest: return new EchantItemRequest;
        // case PacketType::EchantItemResponse: return new EchantItemResponse;
        // case PacketType::MonsterItemDropRequest: return new MonsterItemDropRequest;
        // case PacketType::MonsterItemDropResponse: return new MonsterItemDropResponse;
        // case PacketType::BuyItemAtMarketRequest: return new BuyItemAtMarketRequest;
        // case PacketType::BuyItemAtMarketResponse: return new BuyItemAtMarketResponse;
        // case PacketType::SellItemAtMarketRequest: return new SellItemAtMarketRequest;
        // case PacketType::SellItemAtMarketResponse: return new SellItemAtMarketResponse;
        // case PacketType::LogoutRequest: return new LogoutRequest;
        // case PacketType::LogoutResponse: return new LogoutResponse;
        case PacketType::ExitRequest: return new ExitRequestPacket;
        case PacketType::ExitResponse: return new ExitResponsePacket;
    }

    return nullptr;
}