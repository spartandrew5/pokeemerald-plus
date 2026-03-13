Route104_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route104_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_OnTransition
	.byte 0

Route104_OnFrame:
	map_script_2 VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_StartSailToDewford
	.2byte 0

Route104_EventScript_StartSailToDewford::
	lockall
	goto Route104_EventScript_SailToDewford
	end

Route104_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call Route104_EventScript_TrySetRivalPos
	call Route104_EventScript_ShowOrHideWhiteHerbFlorist
	call Route104_EventScript_TryShowSky
	end

Route104_EventScript_ShowOrHideWhiteHerbFlorist::
	goto_if_unset FLAG_MET_PRETTY_PETAL_SHOP_OWNER, Route104_EventScript_HideWhiteHerbFlorist
	goto_if_unset FLAG_BADGE03_GET, Route104_EventScript_HideWhiteHerbFlorist
	clearflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_HideWhiteHerbFlorist::
	setflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_TrySetRivalPos::
	goto_if_ge VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_DontSetRivalPos
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, Route104_EventScript_DontSetRivalPos
	goto_if_unset FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_DontSetRivalPos
	setobjectxyperm LOCALID_ROUTE104_RIVAL, 17, 52
	return

Route104_EventScript_DontSetRivalPos::
	return

Route104_EventScript_Rival::
	lockall
	setvar VAR_0x8008, 1
	applymovement LOCALID_ROUTE104_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

Route104_EventScript_RivalTrigger::
	lockall
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 10
	addobject LOCALID_ROUTE104_RIVAL
	clearflag FLAG_HIDE_ROUTE_104_RIVAL
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerBackUp
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalExitBrineysCottage
	waitmovement 0
	delay 20
	setvar VAR_0x8008, 0
	call RustboroCity_EventScript_PlayRivalMusic
	playse SE_PIN
	applymovement LOCALID_ROUTE104_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Common_Movement_Delay48
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

@ Unused, shares script with Rustboro encounter instead
Route104_EventScript_PlayRivalMusic::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_PlayMayMusic
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_PlayBrendanMusic
	return

Route104_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

Route104_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

Route104_EventScript_RivalEncounter::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_MayEncounter
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_BrendanEncounter
	end

Route104_EventScript_MayEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_MayDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_MayAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_MayWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_MayHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_ROUTE104_RIVAL
	msgbox Route104_Text_MayMinesDecentLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_Movement_RivalWalkSlowLeft:
	walk_slow_left
	step_end

Route104_Movement_RivalApproachPlayer:
	walk_down
	face_right
	step_end

Route104_Movement_PlayerFaceRival:
	delay_4
	walk_in_place_faster_left
	step_end

Route104_EventScript_MayAskToBattle::
	msgbox Route104_Text_MayLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleMay::
	msgbox Route104_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleMayTreecko
	case 1, Route104_EventScript_BattleMayTorchic
	case 2, Route104_EventScript_BattleMayMudkip
	end

Route104_EventScript_MayDefeated::
	msgbox Route104_Text_MayPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_RestoreMusic::
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

Route104_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BrendanEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_BrendanDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_BrendanAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_BrendanWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredBrendan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_BrendanHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_ROUTE104_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_ROUTE104_RIVAL
	msgbox Route104_Text_BrendanDoingGreatLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BrendanAskToBattle::
	msgbox Route104_Text_BrendanLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleBrendan::
	msgbox Route104_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleBrendanTreecko
	case 1, Route104_EventScript_BattleBrendanTorchic
	case 2, Route104_EventScript_BattleBrendanMudkip
	end

Route104_EventScript_BrendanDefeated::
	msgbox Route104_Text_BrendanPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_Movement_PlayerBackUp:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Route104_Movement_RivalExitBrineysCottage:
	walk_down
	step_end

Route104_EventScript_ExpertF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104, Route104_EventScript_ReceivedBerry
	msgbox Route104_Text_PlantBerriesInSoilTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_CHESTO_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_ReceivedBerry::
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_WhiteHerbFlorist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WHITE_HERB, Route104_EventScript_ReceivedWhiteHerb
	msgbox Route104_Text_DontNeedThisTakeIt, MSGBOX_DEFAULT
	giveitem ITEM_WHITE_HERB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WHITE_HERB
	release
	end

Route104_EventScript_ReceivedWhiteHerb::
	msgbox Route104_Text_FlowerShopSellingSaplings, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl1::
	msgbox Route104_Text_BrineyLivesInSeasideCottage, MSGBOX_NPC
	end

Route104_EventScript_BugCatcher::
	msgbox Route104_Text_WhatsItLikeAtBottomOfSea, MSGBOX_SIGN
	end

Route104_EventScript_BrineysCottageSign::
	msgbox Route104_Text_MrBrineysCottage, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignPetalburg::
	msgbox Route104_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignRustboro::
	msgbox Route104_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route104_EventScript_FlowerShopSign::
	msgbox Route104_Text_PrettyPetalFlowShop, MSGBOX_SIGN
	end

Route104_EventScript_TrainerTipsDoubleBattles::
	msgbox Route104_Text_TrainerTipsDoubleBattles, MSGBOX_SIGN
	end

Route104_EventScript_Boy1::
	msgbox Route104_Text_ThrowBallAtWeakenedPokemon, MSGBOX_NPC
	end

Route104_EventScript_Woman::
	msgbox Route104_Text_OnlyThrowBallAtWildPokemon, MSGBOX_NPC
	end

Route104_EventScript_Boy2::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_BULLET_SEED, Route104_EventScript_ReceivedBulletSeed
	msgbox Route104_Text_LikeFillingMouthWithSeedsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_BULLET_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_BULLET_SEED
	release
	end

Route104_EventScript_ReceivedBulletSeed::
	msgbox Route104_Text_TMsAreOneTimeUse, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl2::
	msgbox Route104_Text_ImNotATrainer, MSGBOX_NPC
	end

Route104_EventScript_SailToDewford::
	setobjectsubpriority LOCALID_ROUTE104_BRINEY, MAP_ROUTE104, 0
	setobjectsubpriority LOCALID_PLAYER, MAP_ROUTE104, 0
	applymovement LOCALID_ROUTE104_BRINEY, Route104_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject LOCALID_ROUTE104_BRINEY
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat LOCALID_PLAYER, MAP_ROUTE104
	call Common_EventScript_PlayBrineysBoatMusic
	goto_if_set FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordNoCall
	goto_if_unset FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordDadCalls
	end

Route104_EventScript_SailToDewfordNoCall::
	applymovement LOCALID_ROUTE104_BOAT, Route104_Movement_SailToDewford
	applymovement LOCALID_PLAYER, Route104_Movement_SailToDewford
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_SailToDewfordDadCalls::
	applymovement LOCALID_ROUTE104_BOAT, Route104_Movement_SailToDewfordBeforeDadCalls
	applymovement LOCALID_PLAYER, Route104_Movement_SailToDewfordBeforeDadCalls
	waitmovement 0
	pokenavcall Route104_Text_DadPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredDadInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_NORMAN_MATCH_CALL
	applymovement LOCALID_PLAYER, Route104_Movement_SailToDewfordAfterDadCalls
	applymovement LOCALID_ROUTE104_BOAT, Route104_Movement_SailToDewfordAfterDadCalls, MAP_ROUTE104
	waitmovement LOCALID_ROUTE104_BOAT, MAP_ROUTE104
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_ArriveInDewford::
	delay 50
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerExitBoat
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat LOCALID_PLAYER, MAP_DEWFORD_TOWN
	applymovement LOCALID_PLAYER, Route104_Movement_PlayerMoveForBriney
	waitmovement 0
	setobjectxyperm LOCALID_DEWFORD_BRINEY, 12, 8
	addobject LOCALID_DEWFORD_BRINEY
	setobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN, 0
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	applymovement LOCALID_DEWFORD_BRINEY, Route104_Movement_BrineyExitBoat
	waitmovement 0
	addobject LOCALID_DEWFORD_BOAT
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	call Common_EventScript_StopBrineysBoatMusic
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	hideobjectat LOCALID_ROUTE104_BOAT, MAP_ROUTE104
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectsubpriority LOCALID_PLAYER, MAP_ROUTE104
	resetobjectsubpriority LOCALID_DEWFORD_BRINEY, MAP_DEWFORD_TOWN
	copyobjectxytoperm LOCALID_DEWFORD_BRINEY
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 0
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_DeliverLetterReminder
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_LandedInDewford
	end

Route104_EventScript_DeliverLetterReminder::
	msgbox Route104_Text_LandedInDewfordDeliverLetter, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_LandedInDewford::
	msgbox DewfordTown_Text_BrineyLandedInDewford, MSGBOX_DEFAULT
	releaseall
	end

Route104_Movement_SailToDewfordBeforeDadCalls:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

Route104_Movement_SailToDewfordAfterDadCalls:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_SailToDewford:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerBoardBoat:
	walk_left
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerExitBoat:
	walk_down
	step_end

Route104_Movement_PlayerMoveForBriney:
	walk_down
	walk_left
	walk_in_place_faster_right
	step_end

Route104_Movement_BrineyBoardBoat:
	walk_down
	walk_down
	step_end

Route104_Movement_BrineyExitBoat:
	walk_down
	walk_in_place_faster_left
	step_end

Route104_EventScript_Ivan::
	trainerbattle_single TRAINER_IVAN, Route104_Text_IvanIntro, Route104_Text_IvanDefeat
	msgbox Route104_Text_IvanPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY, Route104_Text_BillyIntro, Route104_Text_BillyDefeat
	msgbox Route104_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Haley::
	trainerbattle_single TRAINER_HALEY_1, Route104_Text_HaleyIntro, Route104_Text_HaleyDefeat, Route104_EventScript_TryRegisterHaleyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchHaley
	setvar VAR_0x8004, TRAINER_HALEY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterHaleyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaleyAfterBattle
	release
	end

Route104_EventScript_RegisterHaleyAfterBattle::
	msgbox Route104_Text_HaleyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_TryRegisterHaley::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterHaley::
	msgbox Route104_Text_HaleyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_RematchHaley::
	trainerbattle_rematch TRAINER_HALEY_1, Route104_Text_HaleyRematchIntro, Route104_Text_HaleyRematchDefeat
	msgbox Route104_Text_HaleyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Winston::
	trainerbattle_single TRAINER_WINSTON_1, Route104_Text_WinstonIntro, Route104_Text_WinstonDefeat, Route104_EventScript_TryRegisterWinstonAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchWinston
	setvar VAR_0x8004, TRAINER_WINSTON_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterWinstonAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinstonAfterBattle
	release
	end

Route104_EventScript_RegisterWinstonAfterBattle::
	msgbox Route104_Text_WinstonRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_TryRegisterWinston::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterWinston::
	msgbox Route104_Text_WinstonRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_RematchWinston::
	trainerbattle_rematch TRAINER_WINSTON_1, Route104_Text_WinstonRematchIntro, Route104_Text_WinstonRematchDefeat
	msgbox Route104_Text_WinstonPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Cindy::
	trainerbattle_single TRAINER_CINDY_1, Route104_Text_CindyIntro, Route104_Text_CindyDefeat, Route104_EventScript_TryRegisterCindyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchCindy
	setvar VAR_0x8004, TRAINER_CINDY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterCindyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindyAfterBattle
	release
	end

Route104_EventScript_RegisterCindyAfterBattle::
	msgbox Route104_Text_CindyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_TryRegisterCindy::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterCindy::
	msgbox Route104_Text_CindyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_RematchCindy::
	trainerbattle_rematch TRAINER_CINDY_1, Route104_Text_CindyRematchIntro, Route104_Text_CindyRematchDefeat
	msgbox Route104_Text_CindyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Gina::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_GinaIntro, Route104_Text_GinaDefeat, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_GinaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Mia::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_MiaIntro, Route104_Text_MiaDefeat, Route104_Text_MiaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_MiaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Darian::
	trainerbattle_single TRAINER_DARIAN, Route104_Text_DarianIntro, Route104_Text_DarianDefeat
	msgbox Route104_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_Text_BrineyLivesInSeasideCottage:
	.string "That seaside cottage is where\n"
	.string "MR. BRINEY lives.\p"
	.string "He was once a mighty sailor who never\n"
	.string "feared the sea, however stormy.$"

Route104_Text_WhatsItLikeAtBottomOfSea:
	.string "The sea, huh?\p"
	.string "I wonder what it's like at the bottom\n"
	.string "of the sea?$"

Route104_Text_ThrowBallAtWeakenedPokemon:
	.string "If you're going to throw a POKé BALL,\n"
	.string "weaken the wild POKéMON first.\p"
	.string "It will be easier to catch if it's been\n"
	.string "poisoned, burned, or lulled to sleep.$"

Route104_Text_OnlyThrowBallAtWildPokemon:
	.string "You're a thief if you try to steal\n"
	.string "someone else's POKéMON.\p"
	.string "You should throw POKé BALLS only at\n"
	.string "wild POKéMON.$"

Route104_Text_ImNotATrainer:
	.string "Oh, no, I'm not a TRAINER.\p"
	.string "But that's right, if TRAINERS lock eyes,\n"
	.string "it's a challenge to battle.\p"
	.string "If you don't want to battle, stay out\n"
	.string "of their sight.$"

Route104_Text_LikeFillingMouthWithSeedsTakeThis:
	.string "I like filling my mouth with seeds,\n"
	.string "then spitting them out fast!\p"
	.string "You can have this, so you try it out!\p"
	.string "Use it on a POKéMON, and it will learn\n"
	.string "a move for firing seeds rapidly.$"

Route104_Text_TMsAreOneTimeUse:
	.string "A word of advice!\p"
	.string "A TM, TECHNICAL MACHINE, is good only\n"
	.string "for one-time use.\p"
	.string "Once you use it, it's gone.\n"
	.string "Think twice before using it!$"

Route104_Text_DontNeedThisTakeIt:
	.string "This FLOWER SHOP started selling\n"
	.string "saplings recently.\p"
	.string "It made me so happy, I went overboard\n"
	.string "shopping.\p"
	.string "I don't need this WHITE HERB anymore.\n"
	.string "Would you take it, please?$"

Route104_Text_FlowerShopSellingSaplings:
	.string "This FLOWER SHOP started selling\n"
	.string "saplings recently.\p"
	.string "It made me so happy, I went overboard\n"
	.string "shopping. Where should I put them?$"

Route104_Text_MrBrineysCottage:
	.string "MR. BRINEY'S COTTAGE$"

Route104_Text_RouteSignPetalburg:
	.string "ROUTE 1O4\n"
	.string "{RIGHT_ARROW} PETALBURG CITY$"

Route104_Text_RouteSignRustboro:
	.string "ROUTE 1O4\n"
	.string "{UP_ARROW} RUSTBORO CITY$"

Route104_Text_PrettyPetalFlowShop:
	.string "PRETTY PETAL FLOWER SHOP$"

Route104_Text_TrainerTipsDoubleBattles:
	.string "TRAINER TIPS\p"
	.string "In the HOENN region there are pairs\n"
	.string "of TRAINERS who challenge others\l"
	.string "for 2-on-2 POKéMON battles called\l"
	.string "DOUBLE BATTLES.\p"
	.string "In a DOUBLE BATTLE, the TRAINER must\n"
	.string "send out two POKéMON, the one at the\l"
	.string "left of the list and the top one.\l"
	.string "Watch how POKéMON are lined up.$"

Route104_Text_MayWeShouldRegister:
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\p"
	.string "DEVON upgraded your POKéNAV with\n"
	.string "the MATCH CALL system, huh?\p"
	.string "We should register each other so we\n"
	.string "can get in contact anytime.$"

Route104_Text_RegisteredMay:
	.string "{PLAYER} registered MAY\n"
	.string "in the POKéNAV.$"

Route104_Text_MayHowsYourPokedex:
	.string "MAY: Oh, by the way, {PLAYER}{KUN},\n"
	.string "how's your POKéDEX coming along?$"

Route104_Text_MayMinesDecentLetsBattle:
	.string "Mine's looking pretty decent.\n"
	.string "So…\l"
	.string "How about a little battle?$"

Route104_Text_MayHaventRaisedPokemon:
	.string "MAY: Oh, what's the matter?\p"
	.string "Haven't you caught or raised your\n"
	.string "POKéMON very much?\p"
	.string "That's not very good for a TRAINER!$"

Route104_Text_MayLetsBattle:
	.string "MAY: So, what do you think?\n"
	.string "How about a little battle here?$"

Route104_Text_MayIntro:
	.string "MAY: You just became a TRAINER,\n"
	.string "{PLAYER}{KUN}. I'm not going to lose!$"

Route104_Text_MayDefeat:
	.string "Yikes!\n"
	.string "You're better than I expected!$"

Route104_Text_MayPostBattle:
	.string "MAY: I can tell you've gotten pretty\n"
	.string "good with the way you handle POKéMON.\p"
	.string "But instead of only making them\n"
	.string "battle, you should be like MR. BRINEY.\p"
	.string "It's important to become friends with\n"
	.string "POKéMON, too.$"

Route104_Text_BrendanWeShouldRegister:
	.string "BRENDAN: Oh, hey, {PLAYER}!\p"
	.string "Cool, you had DEVON install the MATCH\n"
	.string "CALL system on your POKéNAV!\p"
	.string "Let's register each other in our\n"
	.string "POKéNAVS so we can keep in touch.$"

Route104_Text_RegisteredBrendan:
	.string "{PLAYER} registered BRENDAN\n"
	.string "in the POKéNAV.$"

Route104_Text_BrendanHowsYourPokedex:
	.string "BRENDAN: {PLAYER}, how's your POKéDEX?\n"
	.string "Have you filled in any pages yet?$"

Route104_Text_BrendanDoingGreatLetsBattle:
	.string "Me, I'm doing great!\p"
	.string "Want to check out how good I am with\n"
	.string "a battle?$"

Route104_Text_BrendanNoConfidence:
	.string "BRENDAN: What's the matter? Don't have\n"
	.string "any confidence in your POKéMON?$"

Route104_Text_BrendanLetsBattle:
	.string "BRENDAN: What's up?\n"
	.string "Want to have a battle with me?$"

Route104_Text_BrendanIntro:
	.string "BRENDAN: I know you just became\n"
	.string "a TRAINER, but I won't go easy!$"

Route104_Text_BrendanDefeat:
	.string "Hmm…\n"
	.string "You're pretty good.$"

Route104_Text_BrendanPostBattle:
	.string "BRENDAN: You've gotten pretty decent\n"
	.string "at handling POKéMON.\p"
	.string "But, you know, you shouldn't just be\n"
	.string "making POKéMON battle.\p"
	.string "Like MR. BRINEY, it's important to\n"
	.string "become friends with your POKéMON.$"

@ =============================================
@ Sky Event - Route 104 South
@ =============================================

Route104_EventScript_TryShowSky::
	goto_if_unset FLAG_DEFEATED_RIVAL_ROUTE103, Route104_EventScript_HideSky
	goto_if_set FLAG_DEFEATED_SKY_ROUTE_104, Route104_EventScript_HideSky
	clearflag FLAG_HIDE_SKY_ROUTE_104
	return

Route104_EventScript_HideSky::
	setflag FLAG_HIDE_SKY_ROUTE_104
	return

Route104_EventScript_Sky::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SKY_ROUTE_104, Route104_EventScript_SkyPostBattle
	msgbox Route104_Text_SkyIntro, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	delay 20
	msgbox Route104_Text_SkyChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SKY_ROUTE_104, Route104_Text_SkyDefeat
	setflag FLAG_DEFEATED_SKY_ROUTE_104
	msgbox Route104_Text_SkyAfterBattle, MSGBOX_DEFAULT
	goto Route104_EventScript_SkyGiveStarter
	end

Route104_EventScript_SkyPostBattle::
	goto_if_unset FLAG_RECEIVED_SKY_TREECKO_EGG, Route104_EventScript_SkyGiveStarter
	msgbox Route104_Text_SkyReminder, MSGBOX_DEFAULT
	release
	end

@ --- Starter Gift Flow ---

Route104_EventScript_SkyGiveStarter::
	msgbox Route104_Text_SkyStarterOffer, MSGBOX_DEFAULT
Route104_EventScript_SkyRegionSelect::
	msgbox Route104_Text_SkyPickRegion, MSGBOX_DEFAULT
	dynmultipush Route104_Text_RegionKanto, 0
	dynmultipush Route104_Text_RegionJohto, 1
	dynmultipush Route104_Text_RegionHoenn, 2
	dynmultipush Route104_Text_RegionSinnoh, 3
	dynmultipush Route104_Text_RegionUnova, 4
	dynmultipush Route104_Text_RegionKalos, 5
	dynmultipush Route104_Text_RegionAlola, 6
	dynmultipush Route104_Text_RegionGalar, 7
	dynmultipush Route104_Text_RegionPaldea, 8
	dynmultistack 1, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, Route104_EventScript_SkyStarter_Kanto
	case 1, Route104_EventScript_SkyStarter_Johto
	case 2, Route104_EventScript_SkyStarter_Hoenn
	case 3, Route104_EventScript_SkyStarter_Sinnoh
	case 4, Route104_EventScript_SkyStarter_Unova
	case 5, Route104_EventScript_SkyStarter_Kalos
	case 6, Route104_EventScript_SkyStarter_Alola
	case 7, Route104_EventScript_SkyStarter_Galar
	case 8, Route104_EventScript_SkyStarter_Paldea
	end

@ --- Kanto ---
Route104_EventScript_SkyStarter_Kanto::
	msgbox Route104_Text_SkyKantoComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Bulbasaur, Route104_Text_Charmander, Route104_Text_Squirtle
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Bulbasaur
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Charmander
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Squirtle
	end

@ --- Johto ---
Route104_EventScript_SkyStarter_Johto::
	msgbox Route104_Text_SkyJohtoComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Chikorita, Route104_Text_Cyndaquil, Route104_Text_Totodile
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Chikorita
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Cyndaquil
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Totodile
	end

@ --- Hoenn ---
Route104_EventScript_SkyStarter_Hoenn::
	msgbox Route104_Text_SkyHoennComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Treecko, Route104_Text_Torchic, Route104_Text_Mudkip
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Treecko
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Torchic
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Mudkip
	end

@ --- Sinnoh ---
Route104_EventScript_SkyStarter_Sinnoh::
	msgbox Route104_Text_SkySinnohComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Turtwig, Route104_Text_Chimchar, Route104_Text_Piplup
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Turtwig
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Chimchar
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Piplup
	end

@ --- Unova ---
Route104_EventScript_SkyStarter_Unova::
	msgbox Route104_Text_SkyUnovaComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Snivy, Route104_Text_Tepig, Route104_Text_Oshawott
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Snivy
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Tepig
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Oshawott
	end

@ --- Kalos ---
Route104_EventScript_SkyStarter_Kalos::
	msgbox Route104_Text_SkyKalosComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Chespin, Route104_Text_Fennekin, Route104_Text_Froakie
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Chespin
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Fennekin
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Froakie
	end

@ --- Alola ---
Route104_EventScript_SkyStarter_Alola::
	msgbox Route104_Text_SkyAlolaComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Rowlet, Route104_Text_Litten, Route104_Text_Popplio
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Rowlet
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Litten
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Popplio
	end

@ --- Galar ---
Route104_EventScript_SkyStarter_Galar::
	msgbox Route104_Text_SkyGalarComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Grookey, Route104_Text_Scorbunny, Route104_Text_Sobble
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Grookey
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Scorbunny
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Sobble
	end

@ --- Paldea ---
Route104_EventScript_SkyStarter_Paldea::
	msgbox Route104_Text_SkyPaldeaComment, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route104_Text_Sprigatito, Route104_Text_Fuecoco, Route104_Text_Quaxly
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route104_EventScript_SkyRegionSelect
	goto_if_eq VAR_RESULT, 0, Route104_EventScript_SkyGive_Sprigatito
	goto_if_eq VAR_RESULT, 1, Route104_EventScript_SkyGive_Fuecoco
	goto_if_eq VAR_RESULT, 2, Route104_EventScript_SkyGive_Quaxly
	end

@ --- Give Pokémon Scripts ---
@ Sky's picks: Charmander, Cyndaquil, Treecko, Chimchar, Oshawott, Froakie, Rowlet, Grookey, Fuecoco

Route104_EventScript_SkyGive_Bulbasaur::
	bufferspeciesname STR_VAR_1, SPECIES_BULBASAUR
	givemon SPECIES_BULBASAUR, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Charmander::
	bufferspeciesname STR_VAR_1, SPECIES_CHARMANDER
	givemon SPECIES_CHARMANDER, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Squirtle::
	bufferspeciesname STR_VAR_1, SPECIES_SQUIRTLE
	givemon SPECIES_SQUIRTLE, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Chikorita::
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	givemon SPECIES_CHIKORITA, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Cyndaquil::
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	givemon SPECIES_CYNDAQUIL, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Totodile::
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	givemon SPECIES_TOTODILE, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Treecko::
	bufferspeciesname STR_VAR_1, SPECIES_TREECKO
	givemon SPECIES_TREECKO, 5, gender=MON_MALE, atkIv=31, speedIv=31, hpIv=28, defIv=25, spAtkIv=25, spDefIv=25
	setvar VAR_0x8009, 2
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Torchic::
	bufferspeciesname STR_VAR_1, SPECIES_TORCHIC
	givemon SPECIES_TORCHIC, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Mudkip::
	bufferspeciesname STR_VAR_1, SPECIES_MUDKIP
	givemon SPECIES_MUDKIP, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Turtwig::
	bufferspeciesname STR_VAR_1, SPECIES_TURTWIG
	givemon SPECIES_TURTWIG, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Chimchar::
	bufferspeciesname STR_VAR_1, SPECIES_CHIMCHAR
	givemon SPECIES_CHIMCHAR, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Piplup::
	bufferspeciesname STR_VAR_1, SPECIES_PIPLUP
	givemon SPECIES_PIPLUP, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Snivy::
	bufferspeciesname STR_VAR_1, SPECIES_SNIVY
	givemon SPECIES_SNIVY, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Tepig::
	bufferspeciesname STR_VAR_1, SPECIES_TEPIG
	givemon SPECIES_TEPIG, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Oshawott::
	bufferspeciesname STR_VAR_1, SPECIES_OSHAWOTT
	givemon SPECIES_OSHAWOTT, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Chespin::
	bufferspeciesname STR_VAR_1, SPECIES_CHESPIN
	givemon SPECIES_CHESPIN, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Fennekin::
	bufferspeciesname STR_VAR_1, SPECIES_FENNEKIN
	givemon SPECIES_FENNEKIN, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Froakie::
	bufferspeciesname STR_VAR_1, SPECIES_FROAKIE
	givemon SPECIES_FROAKIE, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Rowlet::
	bufferspeciesname STR_VAR_1, SPECIES_ROWLET
	givemon SPECIES_ROWLET, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Litten::
	bufferspeciesname STR_VAR_1, SPECIES_LITTEN
	givemon SPECIES_LITTEN, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Popplio::
	bufferspeciesname STR_VAR_1, SPECIES_POPPLIO
	givemon SPECIES_POPPLIO, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Grookey::
	bufferspeciesname STR_VAR_1, SPECIES_GROOKEY
	givemon SPECIES_GROOKEY, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Scorbunny::
	bufferspeciesname STR_VAR_1, SPECIES_SCORBUNNY
	givemon SPECIES_SCORBUNNY, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Sobble::
	bufferspeciesname STR_VAR_1, SPECIES_SOBBLE
	givemon SPECIES_SOBBLE, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Sprigatito::
	bufferspeciesname STR_VAR_1, SPECIES_SPRIGATITO
	givemon SPECIES_SPRIGATITO, 5
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Fuecoco::
	bufferspeciesname STR_VAR_1, SPECIES_FUECOCO
	givemon SPECIES_FUECOCO, 5
	setvar VAR_0x8009, 1
	goto Route104_EventScript_SkyStarterReceived
	end

Route104_EventScript_SkyGive_Quaxly::
	bufferspeciesname STR_VAR_1, SPECIES_QUAXLY
	givemon SPECIES_QUAXLY, 5
	goto Route104_EventScript_SkyStarterReceived
	end

@ --- Received Logic ---

Route104_EventScript_SkyStarterReceived::
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Route104_EventScript_SkyStarterReceivedParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Route104_EventScript_SkyStarterReceivedPC
	goto Route104_EventScript_SkyStarterNoRoom
	end

Route104_EventScript_SkyStarterReceivedParty::
	setflag FLAG_RECEIVED_SKY_TREECKO_EGG
	playfanfare MUS_OBTAIN_ITEM
	msgbox Route104_Text_SkyStarterReceived, MSGBOX_DEFAULT
	waitfanfare
	goto Route104_EventScript_SkyStarterCheckSpecial
	end

Route104_EventScript_SkyStarterReceivedPC::
	setflag FLAG_RECEIVED_SKY_TREECKO_EGG
	playfanfare MUS_OBTAIN_ITEM
	msgbox Route104_Text_SkyStarterReceivedPC, MSGBOX_DEFAULT
	waitfanfare
	goto Route104_EventScript_SkyStarterCheckSpecial
	end

Route104_EventScript_SkyStarterNoRoom::
	msgbox Route104_Text_SkyStarterNoRoom, MSGBOX_DEFAULT
	setvar VAR_0x8009, 0
	release
	end

Route104_EventScript_SkyStarterCheckSpecial::
	goto_if_eq VAR_0x8009, 2, Route104_EventScript_SkyStarterTreecko
	goto_if_eq VAR_0x8009, 1, Route104_EventScript_SkyStarterSameRegion
	msgbox Route104_Text_SkyFarewell, MSGBOX_DEFAULT
	closemessage
	goto Route104_EventScript_SkyWalkAway
	end

Route104_EventScript_SkyStarterTreecko::
	setvar VAR_0x8009, 0
	msgbox Route104_Text_SkyTreeckoPick, MSGBOX_DEFAULT
	msgbox Route104_Text_SkyFarewellTreecko, MSGBOX_DEFAULT
	closemessage
	goto Route104_EventScript_SkyWalkAway
	end

Route104_EventScript_SkyStarterSameRegion::
	setvar VAR_0x8009, 0
	msgbox Route104_Text_SkySameRegionChoice, MSGBOX_DEFAULT
	msgbox Route104_Text_SkyFarewellSpecial, MSGBOX_DEFAULT
	closemessage
	goto Route104_EventScript_SkyWalkAway
	end

Route104_EventScript_SkyWalkAway::
	setflag FLAG_HIDE_SKY_ROUTE_104
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_ROUTE104_SKY
	waitfieldeffect FLDEFF_NPCFLY_OUT
	release
	end

@ ----- Sky Dialogue Text -----

Route104_Text_SkyIntro:
	.string "???: Hey! You there!\p"
	.string "You look like you just started your\n"
	.string "journey, am I right?\p"
	.string "The name's SKY. I've been traveling\n"
	.string "across all kinds of regions.\p"
	.string "I started my adventure right here\n"
	.string "in HOENN a long time ago…$"

Route104_Text_SkyChallenge:
	.string "SKY: You've got that look in your\n"
	.string "eyes. The look of a real TRAINER.\p"
	.string "How about a quick battle? I want\n"
	.string "to see what you've got!$"

Route104_Text_SkyDefeat:
	.string "Ha! Not bad at all!\n"
	.string "You remind me of myself.$"

Route104_Text_SkyAfterBattle:
	.string "SKY: Wow, you really are something.\p"
	.string "That battle reminded me of when\n"
	.string "I first started out…\p"
	.string "All those journeys across different\n"
	.string "regions, meeting all kinds of\l"
	.string "POKéMON…$"

Route104_Text_SkyStarterOffer:
	.string "SKY: Listen, I've collected starters\n"
	.string "from every region I've visited.\p"
	.string "I want you to have one of them.\n"
	.string "Think of it as a gift from one\l"
	.string "TRAINER to another.$"

Route104_Text_SkyPickRegion:
	.string "SKY: So, which region's starter\n"
	.string "catches your eye?$"

@ Region menu labels
Route104_Text_RegionKanto:
	.string "KANTO$"
Route104_Text_RegionJohto:
	.string "JOHTO$"
Route104_Text_RegionHoenn:
	.string "HOENN$"
Route104_Text_RegionSinnoh:
	.string "SINNOH$"
Route104_Text_RegionUnova:
	.string "UNOVA$"
Route104_Text_RegionKalos:
	.string "KALOS$"
Route104_Text_RegionAlola:
	.string "ALOLA$"
Route104_Text_RegionGalar:
	.string "GALAR$"
Route104_Text_RegionPaldea:
	.string "PALDEA$"

@ Region comments
Route104_Text_SkyKantoComment:
	.string "SKY: Ah, KANTO! Home of\n"
	.string "some legendary TRAINERS.$"

Route104_Text_SkyJohtoComment:
	.string "SKY: JOHTO… A beautiful region.\n"
	.string "I have fond memories there.$"

Route104_Text_SkyHoennComment:
	.string "SKY: HOENN is where I started\n"
	.string "my very first journey. Good taste!$"

Route104_Text_SkySinnohComment:
	.string "SKY: SINNOH! The cold air, the\n"
	.string "legends… What a place.$"

Route104_Text_SkyUnovaComment:
	.string "SKY: UNOVA is huge. So much\n"
	.string "to explore out there.$"

Route104_Text_SkyKalosComment:
	.string "SKY: KALOS… That's where I\n"
	.string "learned about MEGA EVOLUTION.$"

Route104_Text_SkyAlolaComment:
	.string "SKY: ALOLA! Island hopping with\n"
	.string "POKéMON is the best.$"

Route104_Text_SkyGalarComment:
	.string "SKY: GALAR! The stadiums, the\n"
	.string "crowds… Nothing like it.$"

Route104_Text_SkyPaldeaComment:
	.string "SKY: PALDEA! Wide open spaces\n"
	.string "as far as the eye can see.$"

@ Starter name labels
Route104_Text_Bulbasaur:
	.string "BULBASAUR$"
Route104_Text_Charmander:
	.string "CHARMANDER$"
Route104_Text_Squirtle:
	.string "SQUIRTLE$"
Route104_Text_Chikorita:
	.string "CHIKORITA$"
Route104_Text_Cyndaquil:
	.string "CYNDAQUIL$"
Route104_Text_Totodile:
	.string "TOTODILE$"
Route104_Text_Treecko:
	.string "TREECKO$"
Route104_Text_Torchic:
	.string "TORCHIC$"
Route104_Text_Mudkip:
	.string "MUDKIP$"
Route104_Text_Turtwig:
	.string "TURTWIG$"
Route104_Text_Chimchar:
	.string "CHIMCHAR$"
Route104_Text_Piplup:
	.string "PIPLUP$"
Route104_Text_Snivy:
	.string "SNIVY$"
Route104_Text_Tepig:
	.string "TEPIG$"
Route104_Text_Oshawott:
	.string "OSHAWOTT$"
Route104_Text_Chespin:
	.string "CHESPIN$"
Route104_Text_Fennekin:
	.string "FENNEKIN$"
Route104_Text_Froakie:
	.string "FROAKIE$"
Route104_Text_Rowlet:
	.string "ROWLET$"
Route104_Text_Litten:
	.string "LITTEN$"
Route104_Text_Popplio:
	.string "POPPLIO$"
Route104_Text_Grookey:
	.string "GROOKEY$"
Route104_Text_Scorbunny:
	.string "SCORBUNNY$"
Route104_Text_Sobble:
	.string "SOBBLE$"
Route104_Text_Sprigatito:
	.string "SPRIGATITO$"
Route104_Text_Fuecoco:
	.string "FUECOCO$"
Route104_Text_Quaxly:
	.string "QUAXLY$"

@ Received text
Route104_Text_SkyStarterReceived:
	.string "{PLAYER} received {STR_VAR_1}\n"
	.string "from SKY!$"

Route104_Text_SkyStarterReceivedPC:
	.string "{PLAYER} received {STR_VAR_1}\n"
	.string "from SKY!\p"
	.string "Your party is full, so {STR_VAR_1}\n"
	.string "was sent to a PC BOX.$"

Route104_Text_SkyStarterNoRoom:
	.string "SKY: Hmm, looks like you don't have\n"
	.string "room right now.\p"
	.string "Come back when you've made some\n"
	.string "space in your party or PC!$"

@ Special Treecko message (offspring of Sky's Sceptile)
Route104_Text_SkyTreeckoPick:
	.string "SKY: Wait… you want TREECKO?\p"
	.string "That one's actually special.\n"
	.string "It's the offspring of my SCEPTILE…\l"
	.string "my very first POKéMON.\p"
	.string "That little TREECKO has some of\n"
	.string "its parent's best qualities.\l"
	.string "I can already tell it's strong.$"

Route104_Text_SkyFarewellTreecko:
	.string "SKY: Take good care of that little\n"
	.string "one for me, okay?\n"
	.string "Maybe one day your SCEPTILE and\n"
	.string "mine will face off.\l"
	.string "Now THAT would be a battle.\p"
	.string "See you around, {PLAYER}!$"

@ Same region pick message (Sky chose this starter in that region)
Route104_Text_SkySameRegionChoice:
	.string "SKY: Oh, {STR_VAR_1}? Nice!\p"
	.string "You know, that's the same starter\n"
	.string "I chose when I traveled to that\l"
	.string "region.\p"
	.string "We had some great times together.\n"
	.string "I think you two are going to get\l"
	.string "along just fine.$"

Route104_Text_SkyFarewellSpecial:
	.string "SKY: Take extra good care of that\n"
	.string "{STR_VAR_1}. Trust me, it'll become\l"
	.string "a great partner.\p"
	.string "Maybe one day we'll battle again…\n"
	.string "when we're both a lot stronger.\p"
	.string "I've got a feeling about you, kid.\n"
	.string "See you around, {PLAYER}!$"

Route104_Text_SkyFarewell:
	.string "SKY: Take good care of that\n"
	.string "{STR_VAR_1}, okay?\p"
	.string "Maybe one day we'll battle again…\n"
	.string "when we're both a lot stronger.\p"
	.string "See you around, {PLAYER}!$"

Route104_Text_SkyReminder:
	.string "SKY: Hey! Good to see you again.\p"
	.string "I've gotta head out, but keep\n"
	.string "training hard, okay?$"
