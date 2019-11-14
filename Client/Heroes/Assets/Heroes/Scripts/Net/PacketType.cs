﻿using System;

namespace Heroes {
	public enum PacketType : UInt32 {
		AuthLoginRequest,
		AuthLoginResponse,
		AuthRegisterRequest,
		AuthRegisterResponse,
		AccountInfoRequest,
		AccountInfoResponse,
		CreateCharacterRequest,
		CreateCharacterResponse,
		ConnectChanelRequest,
		ConnectChanelResponse,
		DisConnectChanelRequest,
		DisConnectChanelResponse,
		ChattingRequest,
		ChattingResponse,
		CharacterInfoRequest,
		CharacterInfoResponse,
		CharacterMoveRequest,
		CharacterMoveResponse,
		CharacterAttackRequest,
		CharacterAttackResponse,
		CharacterActionRequest,
		CharacterActionResponse,
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
		LogoutResponse,
		ExitRequest,
		ExitResponse
	}
}