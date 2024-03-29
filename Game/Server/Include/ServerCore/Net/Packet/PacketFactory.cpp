#include "stdafx.h"

std::unique_ptr<Packet> PacketFactory::CreatePacket(PacketType type) {
    switch(type) {		
        case PacketType::NotifyTerminal: return std::make_unique<NotifyTerminalPacket>();
		case PacketType::DBSearchAccountRequest: return std::make_unique<DBSearchAccountRequestPacket>();
		case PacketType::DBSearchAccountResponse: return std::make_unique<DBSearchAccountResponsePacket>();
        case PacketType::DBCreateAccountRequest: return std::make_unique<DBCreateAccountRequestPacket>();
        case PacketType::DBCreateAccountResponse: return std::make_unique<DBCreateAccountResponsePacket>();
        case PacketType::DBGetCharacterListRequest: return std::make_unique<DBGetCharacterListRequestPacket>();
        case PacketType::DBGetCharacterListResponse: return std::make_unique<DBGetCharacterListResponsePacket>();
        case PacketType::DBChangeCharacterOrderRequest: return std::make_unique<DBChangeCharacterOrderRequestPacket>();
        case PacketType::DBChangeCharacterOrderResponse: return std::make_unique<DBChangeCharacterOrderResponsePacket>();
		case PacketType::DBCreateCharacterRequest: return std::make_unique<DBCreateCharacterRequestPacket>();
		case PacketType::DBCreateCharacterResponse: return std::make_unique<DBCreateCharacterResponsePacket>();
		case PacketType::DBDeleteCharacterRequest: return std::make_unique<DBDeleteCharacterRequestPacket>();
		case PacketType::DBDeleteCharacterResponse: return std::make_unique<DBDeleteCharacterResponsePacket>();
        case PacketType::DBUpdateCharacterStatusRequest: return std::make_unique<DBUpdateCharacterStatusRequestPacket>();

        case PacketType::NotifyConnectPlayer: return std::make_unique<NotifyConnectPlayerPacket>();
        case PacketType::NotifyDisconnectPlayer: return std::make_unique<NotifyDisconnectPlayerPacket>();
        case PacketType::NotifyChat: return std::make_unique<NotifyChatPacket>();
        case PacketType::NotifyPlayerMovement: return std::make_unique<NotifyPlayerMovementPacket>();
        case PacketType::NotifyPlayerAction: return std::make_unique<NotifyPlayerActionPacket>();
        case PacketType::NotifyTakeDamagePlayer: return std::make_unique<NotifyTakeDamagePlayerPacket>();
        case PacketType::NotifyPlayerRevive: return std::make_unique<NotifyPlayerRevivePacket>();
        case PacketType::NotifyPlayerDead: return std::make_unique<NotifyPlayerDeadPacket>();
        case PacketType::NotifyLevelUpPlayer: return std::make_unique<NotifyLevelUpPlayerPacket>();
        case PacketType::NotifyMonsterMovement: return std::make_unique<NotifyMonsterMovementPacket>();
        case PacketType::NotifyMonsterAction: return std::make_unique<NotifyMonsterActionPacket>();
        case PacketType::NotifyTakeDamageMonster: return std::make_unique<NotifyTakeDamageMonsterPacket>();
        case PacketType::NotifyRespawnMonster: return std::make_unique<NotifyRespawnMonsterPacket>();
        case PacketType::NotifyLoseAggressionMonster: return std::make_unique<NotifyLoseAggressionMonsterPacket>();

        case PacketType::ExitRequest: return std::make_unique<ExitRequestPacket>();
        case PacketType::ExitResponse: return std::make_unique<ExitResponsePacket>();
		case PacketType::GetChannelListRequest: return std::make_unique<GetChannelListRequestPacket>();
		case PacketType::GetChannelListResponse: return std::make_unique<GetChannelListResponsePacket>();
		case PacketType::SearchAccountRequest: return std::make_unique<SearchAccountRequestPacket>();
		case PacketType::SearchAccountResponse: return std::make_unique<SearchAccountResponsePacket>();
        case PacketType::CreateAccountRequest: return std::make_unique<CreateAccountRequestPacket>();
        case PacketType::CreateAccountResponse: return std::make_unique<CreateAccountResponsePacket>();
        case PacketType::GetCharacterListRequest: return std::make_unique<GetCharacterListRequestPacket>();
        case PacketType::GetCharacterListResponse: return std::make_unique<GetCharacterListResponsePacket>();
        case PacketType::ChangeCharacterOrderRequest: return std::make_unique<ChangeCharacterOrderRequestPacket>();
        case PacketType::ChangeCharacterOrderResponse: return std::make_unique<ChangeCharacterOrderResponsePacket>();
		case PacketType::CreateCharacterRequest: return std::make_unique<CreateCharacterRequestPacket>();
		case PacketType::CreateCharacterResponse: return std::make_unique<CreateCharacterResponsePacket>();
		case PacketType::DeleteCharacterRequest: return std::make_unique<DeleteCharacterRequestPacket>();
		case PacketType::DeleteCharacterResponse: return std::make_unique<DeleteCharacterResponsePacket>();
		case PacketType::ConnectChannelRequest: return std::make_unique<ConnectChannelRequestPacket>();
		case PacketType::ConnectChannelResponse: return std::make_unique<ConnectChannelResponsePacket>();
		case PacketType::DisconnectChannelRequest: return std::make_unique<DisconnectChannelRequestPacket>();
		case PacketType::DisconnectChannelResponse: return std::make_unique<DisconnectChannelResponsePacket>();
        case PacketType::GetMonsterList: return std::make_unique<GetMonsterListPacket>();
        case PacketType::TakeDamageMonster: return std::make_unique<TakeDamageMonsterPacket>();
        case PacketType::GainMonsterExp: return std::make_unique<GainMonsterExpPacket>();
        case PacketType::RevivePlayerRequest: return std::make_unique<RevivePlayerRequestPacket>();
        case PacketType::RevivePlayerResponse: return std::make_unique<RevivePlayerResponsePacket>();
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