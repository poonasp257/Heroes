#ifndef PACKET_TYPE_H
#define PACKET_TYPE_H

enum class PacketType : UInt32 {
	ExitRequest,
	ExitResponse,
	AuthLoginRequest,
	AuthLoginResponse,
	AuthRegisterRequest,
	AuthRegisterResponse,
	ChanelStatusRequest,
	ChanelStatusResponse,
	AccountInfoRequest,
	AccountInfoResponse,
	CreateCharacterRequest,
	CreateCharacterResponse,
	DeleteCharacterRequest,
	DeleteCharacterResponse,
	ConnectChanelRequest,
	ConnectChanelResponse,
	DisconnectChanelRequest,
	DisconnectChanelResponse,
	NotifyNewConnect,
	ChattingRequest,
	ChattingResponse,
	CharacterInfoRequest,
	CharacterInfoResponse,
	NotifyCharacterMovement,
	NotifyCharacterAction,
	ApplyCharacterStatRequest,
	ApplyCharacterStatResponse,
	ResetCharacterStatRequest,
	ResetCharacterStatResponse,
	ApplyCharacterSkillRequest,
	ApplyCharacterSkillResponse,
	ResetCharacterSkillRequest,
	ResetCharacterSkillResponse,
	EquipItemRequest,
	EquipItemResponse,
	DeleteItemRequest,
	DeleteItemResponse,
	TradeItemRequest,
	TradeItemResponse,
	EchantItemRequest,
	EchantItemResponse,
	MonsterItemDropRequest,
	MonsterItemDropResponse,
	BuyItemAtMarketRequest,
	BuyItemAtMarketResponse,
	SellItemAtMarketRequest,
	SellItemAtMarketResponse,
	LogoutRequest,
	LogoutResponse
};

#endif