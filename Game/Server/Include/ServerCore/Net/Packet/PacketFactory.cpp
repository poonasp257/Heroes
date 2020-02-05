#include "stdafx.h"

Packet* PacketFactory::CreatePacket(PacketType type) {
    switch(type) {		
		case PacketType::NotifyTerminal: return new NotifyTerminalPacket();
		case PacketType::DBAccountInfoRequest: return new DBAccountInfoRequestPacket();
		case PacketType::DBAccountInfoResponse: return new DBAccountInfoResponsePacket();
		case PacketType::DBCreateCharacterRequest: return new DBCreateCharacterRequestPacket();
		case PacketType::DBCreateCharacterResponse: return new DBCreateCharacterResponsePacket();
		case PacketType::DBDeleteCharacterRequest: return new DBDeleteCharacterRequestPacket();
		case PacketType::DBDeleteCharacterResponse: return new DBDeleteCharacterResponsePacket();
		case PacketType::DBConnectChannelRequest: return new DBConnectChannelRequestPacket();
		case PacketType::DBConnectChannelResponse: return new DBConnectChannelResponsePacket();
        case PacketType::ExitRequest: return new ExitRequestPacket();
        case PacketType::ExitResponse: return new ExitResponsePacket();
		case PacketType::ChannelListRequest: return new ChannelListRequestPacket();
		case PacketType::ChannelListResponse: return new ChannelListResponsePacket();
		case PacketType::AccountInfoRequest: return new AccountInfoRequestPacket();
		case PacketType::AccountInfoResponse: return new AccountInfoResponsePacket();
		case PacketType::CreateCharacterRequest: return new CreateCharacterRequestPacket();
		case PacketType::CreateCharacterResponse: return new CreateCharacterResponsePacket();
		case PacketType::DeleteCharacterRequest: return new DeleteCharacterRequestPacket();
		case PacketType::DeleteCharacterResponse: return new DeleteCharacterResponsePacket();
		case PacketType::ConnectChannelRequest: return new ConnectChannelRequestPacket();
		case PacketType::ConnectChannelResponse: return new ConnectChannelResponsePacket();
		case PacketType::DisconnectChannelRequest: return new DisconnectChannelRequestPacket();
		case PacketType::DisconnectChannelResponse: return new DisconnectChannelResponsePacket();
		case PacketType::NotifyConnectPlayer: return new NotifyConnectPlayerPacket();
		case PacketType::NotifyDisconnectPlayer: return new NotifyDisconnectPlayerPacket();
		case PacketType::NotifyCharacterMovement: return new NotifyCharacterMovementPacket();
		case PacketType::NotifyCharacterAction: return new NotifyCharacterActionPacket();
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
    }

    return nullptr;
}