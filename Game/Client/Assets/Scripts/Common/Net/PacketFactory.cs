using System;
using System.Diagnostics;

namespace Heroes {
	public static class PacketFactory {
		public static Packet CreatePacket(UInt32 type) {
			switch((PacketType)type) {
				case PacketType.NotifyConnectPlayer: return new NotifyConnectPlayerPacket();
				case PacketType.NotifyDisconnectPlayer: return new NotifyDisconnectPlayerPacket();
				case PacketType.NotifyChat: return new NotifyChatPacket();
				case PacketType.NotifyPlayerMovement: return new NotifyPlayerMovementPacket();
				case PacketType.NotifyPlayerAction: return new NotifyPlayerActionPacket();
				case PacketType.NotifyTakeDamagePlayer: return new NotifyTakeDamagePlayerPacket();
				case PacketType.NotifyPlayerRevive: return new NotifyPlayerRevivePacket();
				case PacketType.NotifyPlayerDead: return new NotifyPlayerDeadPacket();
				case PacketType.NotifyLevelUpPlayer: return new NotifyLevelUpPlayerPacket();
				case PacketType.NotifyMonsterMovement: return new NotifyMonsterMovementPacket();
				case PacketType.NotifyMonsterAction: return new NotifyMonsterActionPacket();
				case PacketType.NotifyTakeDamageMonster: return new NotifyTakeDamageMonsterPacket();
				case PacketType.NotifyRespawnMonster: return new NotifyRespawnMonsterPacket();
				case PacketType.NotifyLoseAggressionMonster: return new NotifyLoseAggressionMonsterPacket();

				case PacketType.ExitRequest: return new ExitRequestPacket();
				case PacketType.ExitResponse: return new ExitResponsePacket();
				case PacketType.GetChannelListRequest: return new GetChannelListRequestPacket();
				case PacketType.GetChannelListResponse: return new GetChannelListResponsePacket();
				case PacketType.SearchAccountRequest: return new SearchAccountRequestPacket();
				case PacketType.SearchAccountResponse: return new SearchAccountResponsePacket();
				case PacketType.CreateAccountRequest: return new CreateAccountRequestPacket();
				case PacketType.CreateAccountResponse: return new CreateAccountResponsePacket();
				case PacketType.GetCharacterListRequest: return new GetCharacterListRequestPacket();
				case PacketType.GetCharacterListResponse: return new GetCharacterListResponsePacket();
				case PacketType.ChangeCharacterOrderRequest: return new ChangeCharacterOrderRequestPacket();
				case PacketType.ChangeCharacterOrderResponse: return new ChangeCharacterOrderResponsePacket();
				case PacketType.CreateCharacterRequest: return new CreateCharacterRequestPacket();
				case PacketType.CreateCharacterResponse: return new CreateCharacterResponsePacket();
				case PacketType.DeleteCharacterRequest: return new DeleteCharacterRequestPacket();
				case PacketType.DeleteCharacterResponse: return new DeleteCharacterResponsePacket();
				case PacketType.ConnectChannelRequest: return new ConnectChannelRequestPacket();
				case PacketType.ConnectChannelResponse: return new ConnectChannelResponsePacket();
				case PacketType.DisconnectChannelRequest: return new DisconnectChannelRequestPacket();
				case PacketType.DisconnectChannelResponse: return new DisconnectChannelResponsePacket();
				case PacketType.GetMonsterList: return new GetMonsterListPacket();
				case PacketType.TakeDamageMonster: return new TakeDamageMonsterPacket();
				case PacketType.GainMonsterExp: return new GainMonsterExpPacket();
				case PacketType.RevivePlayerRequest: return new RevivePlayerRequestPacket();
				case PacketType.RevivePlayerResponse: return new RevivePlayerResponsePacket();
			}

			return null;
		}
	}
}