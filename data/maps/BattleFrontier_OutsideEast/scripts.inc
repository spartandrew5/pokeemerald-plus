BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	call BattleFrontier_OutsideEast_EventScript_TryShowSky
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_FRONTIER_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "This is the BATTLE TOWER!\n"
	.string "Keep the win streak as the toughest\l"
	.string "TRAINER!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "This is the BATTLE PALACE!\n"
	.string "Keep your eyes on POKéMON battles!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "This is the BATTLE ARENA!\n"
	.string "Let the toughest teams gather!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "This is the BATTLE PYRAMID!\n"
	.string "Advance through the Battle Quest!$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "BATTLE FRONTIER RANKING HALL\n"
	.string "Set your sights on new records!$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "BATTLE POINT EXCHANGE SERVICE CORNER\n"
	.string "Exchange your Battle Points!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "Wow!\n"
	.string "It's huge!\p"
	.string "The BATTLE TOWER feels special.\n"
	.string "It's different from the others.$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "My grand ambition is to conquer both\n"
	.string "the BATTLE FRONTIER and the POKéMON\l"
	.string "LEAGUE.\p"
	.string "And if my dream comes true…\p"
	.string "I… I'm going to ask MIMI next door\n"
	.string "if she will be friends with me!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "The BATTLE PYRAMID's too harsh!\n"
	.string "I just can't make it to the top!\p"
	.string "Since I'm out of options, maybe I can\n"
	.string "climb the outside…$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "I thrive in darkness…\n"
	.string "Yes… What is worthy of me?\l"
	.string "None other than the BATTLE PYRAMID…\p"
	.string "What say you to wandering in darkness\n"
	.string "and in utter and total desperation?$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "I didn't sleep for a week, but then\n"
	.string "I put together the ultimate team!\p"
	.string "I can't see myself losing, no joke.\n"
	.string "We're storming the BATTLE ARENA!$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "Did SCOTT bring you here, too?\n"
	.string "What is it with that guy?\p"
	.string "It sounds like he really does know\n"
	.string "how to spot talented TRAINERS, but…\p"
	.string "I've never seen him battling in person\n"
	.string "ever.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "ZIGG!\n"
	.string "I believe in you, little buddy!\p"
	.string "I'll make my little ZIGG any favorite\n"
	.string "tasty treats you like if you win!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "ZIGZAGOON looks vacant…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "People call me a busybody,\n"
	.string "but I can't help it.\p"
	.string "Your hat's on crooked!\n"
	.string "Oh, no, trash on the ground!\l"
	.string "Oops, it's almost dinnertime!\p"
	.string "I don't know if I can stand to just\n"
	.string "watch at the BATTLE PALACE…$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "I may not look that impressive now,\n"
	.string "but I once beat a GYM LEADER.\p"
	.string "Who knows, maybe I should give it\n"
	.string "another shot at glory.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "I'm fast on my BIKE, and that goes for\n"
	.string "the way I battle, too.\p"
	.string "I win matches in the blink of\n"
	.string "an eye!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "I'm better than my daddy\n"
	.string "at POKéMON.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "Go on, my baby sweetie!\n"
	.string "Go rack up some wins for Daddy!\p"
	.string "You're just like your mother,\n"
	.string "so you'll be dominating!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "It wasn't easy getting here,\n"
	.string "but I'd heard about this knockout\l"
	.string "pretty girl at the BATTLE ARENA.\p"
	.string "Instead of her, do you know what\n"
	.string "I found?\p"
	.string "A whole teeming mob of sweaty,\n"
	.string "stinky, and primitive martial artists!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "I sometimes see this really important-\n"
	.string "looking old man going in there.\p"
	.string "He has these really awesome POKéMON.\n"
	.string "He seems really nice, though.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "Do you know it?\n"
	.string "The legend of the BATTLE PYRAMID?\p"
	.string "When there comes a confident TRAINER\n"
	.string "reaching for the golden pinnacle,\l"
	.string "there shall appear a man among men.\p"
	.string "Don't know that legend?\n"
	.string "Well, of course not!\l"
	.string "I just made it up!\p"
	.string "What's it supposed to mean?\n"
	.string "That, my friend, I can't say!$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "Man! Oh man!\n"
	.string "I've never lost once before!\p"
	.string "But I got wiped out with no saving\n"
	.string "grace at all!\p"
	.string "And then I'm told I don't have any\n"
	.string "talent?! Man!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "This guy ran into a horribly tough\n"
	.string "TRAINER while he was on the BATTLE\l"
	.string "TOWER challenge.\p"
	.string "Now look at him…\p"
	.string "You need to be cautious if you ever\n"
	.string "decide to go to the BATTLE TOWER.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "Yes!\n"
	.string "I've finally got enough Battle Points!\p"
	.string "I guess I'll trade for another giant\n"
	.string "plush DOLL!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "Oh, yeah, okay!\n"
	.string "So this is the RANKING HALL!\p"
	.string "I'd like to go down in history as\n"
	.string "a super champ and have my name\l"
	.string "recorded here for posterity.$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "With you by my side, I can do anything.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "Ooh, darling, you are so wonderful!\p"
	.string "Ooh, I just can't wait anymore!\p"
	.string "Let's go to a MULTI BATTLE ROOM\n"
	.string "right this instant!\p"
	.string "If we get together in the BATTLE SALON,\n"
	.string "the power of our love will overcome\l"
	.string "everyone we meet.\p"
	.string "Why, before us, darling, everything\n"
	.string "will topple like dominoes!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "The BATTLE FRONTIER isn't exclusively\n"
	.string "for tough TRAINERS.\p"
	.string "Many people with special abilities\n"
	.string "have been invited, it seems.\p"
	.string "That man SCOTT…\p"
	.string "He may have built this place to serve\n"
	.string "a bigger objective…$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "Excuse me, young one.\n"
	.string "Have you good eyesight?\p"
	.string "There is an odd tree past here, and to\n"
	.string "my tired eyes it seems to wiggle.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "Excuse me, young one.\n"
	.string "Have you a good memory?\p"
	.string "I have this feeling there once was\n"
	.string "an odd tree past here.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "I…\n"
	.string "I saw it!\p"
	.string "There was a sticky sort of a POKéMON\n"
	.string "with a long tail up ahead!\p"
	.string "It was hiding under a boulder, and\n"
	.string "it kept staring at me!$"

@ =============================================
@ Sky Event - Battle Frontier Post-Game
@ =============================================

BattleFrontier_OutsideEast_EventScript_TryShowSky::
	goto_if_unset FLAG_IS_CHAMPION, BattleFrontier_OutsideEast_EventScript_HideSky
	@ Only show Sky if his position is on the East map (0-3)
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 0, BattleFrontier_OutsideEast_EventScript_SkySyncPos0
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 1, BattleFrontier_OutsideEast_EventScript_SkySyncPos1
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 2, BattleFrontier_OutsideEast_EventScript_SkySyncPos2
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 3, BattleFrontier_OutsideEast_EventScript_SkySyncPos3
	@ Position 4-6 means Sky is on West map
	goto BattleFrontier_OutsideEast_EventScript_HideSky
	return

BattleFrontier_OutsideEast_EventScript_SkySyncPos0::
	setobjectxyperm LOCALID_FRONTIER_SKY, 18, 15
	setobjectmovementtype LOCALID_FRONTIER_SKY, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_SKY_BATTLE_FRONTIER
	return

BattleFrontier_OutsideEast_EventScript_SkySyncPos1::
	setobjectxyperm LOCALID_FRONTIER_SKY, 65, 25
	setobjectmovementtype LOCALID_FRONTIER_SKY, MOVEMENT_TYPE_FACE_LEFT
	clearflag FLAG_HIDE_SKY_BATTLE_FRONTIER
	return

BattleFrontier_OutsideEast_EventScript_SkySyncPos2::
	setobjectxyperm LOCALID_FRONTIER_SKY, 42, 41
	setobjectmovementtype LOCALID_FRONTIER_SKY, MOVEMENT_TYPE_FACE_RIGHT
	clearflag FLAG_HIDE_SKY_BATTLE_FRONTIER
	return

BattleFrontier_OutsideEast_EventScript_SkySyncPos3::
	setobjectxyperm LOCALID_FRONTIER_SKY, 47, 58
	setobjectmovementtype LOCALID_FRONTIER_SKY, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_SKY_BATTLE_FRONTIER
	return

BattleFrontier_OutsideEast_EventScript_HideSky::
	setflag FLAG_HIDE_SKY_BATTLE_FRONTIER
	return

BattleFrontier_OutsideEast_EventScript_Sky::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SKY_BATTLE_FRONTIER, BattleFrontier_OutsideEast_EventScript_SkyRematch
	@ --- First Battle ---
	msgbox BattleFrontier_OutsideEast_Text_SkyIntro, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	delay 20
	msgbox BattleFrontier_OutsideEast_Text_SkyChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SKY_BATTLE_FRONTIER, BattleFrontier_OutsideEast_Text_SkyDefeat
	setflag FLAG_DEFEATED_SKY_BATTLE_FRONTIER
	msgbox BattleFrontier_OutsideEast_Text_SkyAfterFirstBattle, MSGBOX_DEFAULT
	closemessage
	@ After first battle, move Sky to position 1 for the next visit
	setvar VAR_SKY_BATTLE_FRONTIER_POSITION, 1
	@ Walk off screen
	goto BattleFrontier_EventScript_SkyWalkOff_East
	end

@ --- Rematch Logic ---
BattleFrontier_OutsideEast_EventScript_SkyRematch::
	msgbox BattleFrontier_OutsideEast_Text_SkyRematchIntro, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	delay 20
	msgbox BattleFrontier_OutsideEast_Text_SkyRematchChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SKY_BATTLE_FRONTIER_REMATCH, BattleFrontier_OutsideEast_Text_SkyRematchDefeat
	@ Location-specific post-battle dialogue
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 0, BattleFrontier_EventScript_SkyPostBattle_Tower
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 1, BattleFrontier_EventScript_SkyPostBattle_Pyramid
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 2, BattleFrontier_EventScript_SkyPostBattle_Arena
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 3, BattleFrontier_EventScript_SkyPostBattle_Palace
	@ Fallback
	msgbox BattleFrontier_OutsideEast_Text_SkyRematchAfterBattle, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_SKY_BATTLE_FRONTIER_POSITION, 6, BattleFrontier_EventScript_SkyCycleToPos0_East
	addvar VAR_SKY_BATTLE_FRONTIER_POSITION, 1
	goto BattleFrontier_EventScript_SkyWalkOff_East
	end

@ --- Post-battle dialogue per East location ---
BattleFrontier_EventScript_SkyPostBattle_Tower::
	msgbox BattleFrontier_Text_SkyPostBattle_Tower, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SKY_BATTLE_FRONTIER_POSITION, 1
	goto BattleFrontier_EventScript_SkyWalkOff_East
	end

BattleFrontier_EventScript_SkyPostBattle_Pyramid::
	msgbox BattleFrontier_Text_SkyPostBattle_Pyramid, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SKY_BATTLE_FRONTIER_POSITION, 1
	goto BattleFrontier_EventScript_SkyWalkOff_East
	end

BattleFrontier_EventScript_SkyPostBattle_Arena::
	msgbox BattleFrontier_Text_SkyPostBattle_Arena, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SKY_BATTLE_FRONTIER_POSITION, 1
	goto BattleFrontier_EventScript_SkyWalkOff_East
	end

BattleFrontier_EventScript_SkyPostBattle_Palace::
	msgbox BattleFrontier_Text_SkyPostBattle_Palace, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SKY_BATTLE_FRONTIER_POSITION, 1
	goto BattleFrontier_EventScript_SkyWalkOff_East
	end

BattleFrontier_EventScript_SkyCycleToPos0_East::
	setvar VAR_SKY_BATTLE_FRONTIER_POSITION, 0
	goto BattleFrontier_EventScript_SkyWalkOff_East
	end

@ --- Sky flies off screen (East map) ---
BattleFrontier_EventScript_SkyWalkOff_East::
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_FRONTIER_SKY
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setflag FLAG_HIDE_SKY_BATTLE_FRONTIER
	release
	end

@ ----- Sky Dialogue Text (Battle Frontier) -----

BattleFrontier_OutsideEast_Text_SkyIntro:
	.string "SKY: Well, well…\p"
	.string "If it isn't {PLAYER}! I had a\n"
	.string "feeling I'd run into you here.\p"
	.string "You've become the CHAMPION, huh?\n"
	.string "I'm not surprised one bit.\p"
	.string "I saw that fire in your eyes back\n"
	.string "when we first met…$"

BattleFrontier_OutsideEast_Text_SkyChallenge:
	.string "SKY: Remember when I said we'd\n"
	.string "battle again someday?\p"
	.string "Well, the time has come.\n"
	.string "This time, I'm going all out.\p"
	.string "These are some of the POKéMON I crossed every\n"
	.string "region with. My very best.\p"
	.string "Let's see if the CHAMPION of HOENN\n"
	.string "can take us on!$"

BattleFrontier_OutsideEast_Text_SkyDefeat:
	.string "…Incredible. You really are\n"
	.string "something else, {PLAYER}.$"

BattleFrontier_OutsideEast_Text_SkyAfterFirstBattle:
	.string "SKY: Ha… Haha!\p"
	.string "That was the best battle I've\n"
	.string "ever had. No question about it.\p"
	.string "You know, when I started my journey,\n"
	.string "I never imagined it would lead me\l"
	.string "back here.\p"
	.string "But meeting you, battling you…\n"
	.string "It reminds me why I fell in love\l"
	.string "with POKéMON in the first place.\p"
	.string "I'd love to battle again sometime.\n"
	.string "I'll be training at the BATTLE\l"
	.string "FRONTIER for a while.\p"
	.string "If you're ever looking for a rematch,\n"
	.string "come find me. I'll be around!$"

BattleFrontier_OutsideEast_Text_SkyRematchIntro:
	.string "SKY: Hey, {PLAYER}!\n"
	.string "I was hoping you'd show up.\p"
	.string "I've been training hard since our\n"
	.string "last battle. Picked up a few new\l"
	.string "tricks, too.\p"
	.string "Let's have another rematch!$"

BattleFrontier_OutsideEast_Text_SkyRematchChallenge:
	.string "SKY: Ready for another round?\n"
	.string "Don't expect me to go easy on you!$"

BattleFrontier_OutsideEast_Text_SkyRematchDefeat:
	.string "Beaten again!\n"
	.string "You just keep getting stronger!$"

BattleFrontier_OutsideEast_Text_SkyRematchAfterBattle:
	.string "SKY: Man, you really don't let up!\p"
	.string "That's what I love about battling\n"
	.string "you, though. You push me to be\l"
	.string "better every time.\p"
	.string "I'll keep training around the\n"
	.string "FRONTIER. Come find me anytime\l"
	.string "you want a rematch!$"

@ --- Location-specific post-battle text (East) ---

BattleFrontier_Text_SkyPostBattle_Tower:
	.string "SKY: Haha, you got me again!\p"
	.string "I've been grinding win streaks in\n"
	.string "the BATTLE TOWER, you know.\l"
	.string "Fifty straight wins… then I run\l"
	.string "into someone just as tough as you.\p"
	.string "That's what keeps it exciting.\n"
	.string "I'll be stronger next time!\p"
	.string "Later, {PLAYER}!$"

BattleFrontier_Text_SkyPostBattle_Pyramid:
	.string "SKY: Well fought, {PLAYER}!\p"
	.string "The BATTLE PYRAMID is no joke.\n"
	.string "Climbing through the darkness with\l"
	.string "limited items… it really tests your\l"
	.string "survival instincts.\p"
	.string "I picked up some new strategies\n"
	.string "in there. Maybe I'll surprise you\l"
	.string "next time!\p"
	.string "See you around!$"

BattleFrontier_Text_SkyPostBattle_Arena:
	.string "SKY: Good battle as always!\p"
	.string "The BATTLE ARENA's been teaching\n"
	.string "me a lot about aggression. You\l"
	.string "can't play it safe when the judge\l"
	.string "is watching every move.\p"
	.string "Reminds me of battling you.\n"
	.string "Gotta go all out or go home!\p"
	.string "Catch you later!$"

BattleFrontier_Text_SkyPostBattle_Palace:
	.string "SKY: Another one for you, huh?\p"
	.string "You know what I like about the\n"
	.string "BATTLE PALACE? Your POKéMON\l"
	.string "fight on their own instincts.\p"
	.string "It really shows the bond between\n"
	.string "a TRAINER and their team.\p"
	.string "My team and I are getting closer\n"
	.string "every day. We'll get you next time!$"
