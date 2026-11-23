Common_EventScript_PkmnCenterNurse::
	lock
	faceplayer
	setvar VAR_0x8004, 0
.if !IS_FRLG
	specialvar VAR_RESULT, CountPlayerTrainerStars
	goto_if_eq VAR_RESULT, 4, EventScript_PkmnCenterNurse_GoldCard
.endif
	message gText_WouldYouLikeToRestYourPkmn
	waitmessage
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, NurseTera_Str_Heal, NurseTera_Str_Tera, NurseTera_Str_Mode, NurseTera_Str_Giga, NurseTera_Str_Cancel
	switch VAR_RESULT
	case 0, EventScript_PkmnCenterNurse_HealPkmn
	case 1, EventScript_PkmnCenterNurse_ChangeTera
	case 2, NurseTera_ToggleMode
	case 3, NurseTera_Giga
	goto EventScript_PkmnCenterNurse_Goodbye
	end

EventScript_PkmnCenterNurse_Goodbye::
	message gText_WeHopeToSeeYouAgain
	return

@ VAR_0x8004 is 1 when player has Gold Card; jumps are identical
EventScript_PkmnCenterNurse_HealPkmn::
	incrementgamestat GAME_STAT_USED_POKECENTER
	call_if_eq VAR_0x8004, 0, EventScript_PkmnCenterNurse_IllTakeYourPkmn
	call_if_eq VAR_0x8004, 1, EventScript_PkmnCenterNurse_IllTakeYourPkmn2
	waitmessage
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	goto_if_unset FLAG_POKERUS_EXPLAINED, EventScript_PkmnCenterNurse_CheckPokerus
	goto EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

EventScript_PkmnCenterNurse_IllTakeYourPkmn::
	message gText_IllTakeYourPkmn
	return

EventScript_PkmnCenterNurse_IllTakeYourPkmn2::
	message gText_IllTakeYourPkmn2
	return

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	hidefollower 0
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Turn
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
.if OW_UNION_DISABLE_CHECK == FALSE && OW_FLAG_MOVE_UNION_ROOM_CHECK != 0
	setflag OW_FLAG_MOVE_UNION_ROOM_CHECK
	call CableClub_OnResume
	clearflag OW_FLAG_MOVE_UNION_ROOM_CHECK
.endif
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	return

EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom::
	specialvar VAR_RESULT, PlayerNotAtTrainerHillEntrance
	goto_if_eq VAR_RESULT, 0, EventScript_PkmnCenterNurse_ReturnPkmn
	specialvar VAR_RESULT, BufferUnionRoomPlayerName
	copyvar VAR_0x8008, VAR_RESULT
	goto_if_eq VAR_0x8008, 0, EventScript_PkmnCenterNurse_ReturnPkmn
	goto_if_eq VAR_0x8008, 1, EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom
	end

@ VAR_0x8004 is 1 when player has Gold Card
EventScript_PkmnCenterNurse_ReturnPkmn::
	goto_if_eq VAR_0x8004, 1, EventScript_PkmnCenterNurse_ReturnPkmn2
	message gText_RestoredPkmnToFullHealth
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain
	return

EventScript_PkmnCenterNurse_ReturnPkmn2::
	message gText_ThankYouForWaiting
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_PlayerWaitingInUnionRoom::
	goto_if_set FLAG_NURSE_UNION_ROOM_REMINDER, EventScript_PkmnCenterNurse_ReturnPkmn
	msgbox gText_RestoredPkmnToFullHealth, MSGBOX_DEFAULT
	setflag FLAG_NURSE_UNION_ROOM_REMINDER
	message CableClub_Text_PlayerIsWaiting
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	message gText_WeHopeToSeeYouAgain
	return

EventScript_PkmnCenterNurse_CheckPokerus::
	specialvar VAR_RESULT, IsPokerusInParty
	goto_if_eq VAR_RESULT, TRUE, EventScript_PkmnCenterNurse_ExplainPokerus
	goto_if_eq VAR_RESULT, FALSE, EventScript_PkmnCenterNurse_CheckTrainerHillAndUnionRoom
	end

EventScript_PkmnCenterNurse_ExplainPokerus::
	message gText_PokerusExplanation
	setflag FLAG_POKERUS_EXPLAINED
	return

EventScript_PkmnCenterNurse_GoldCard::
	goto_if_set FLAG_NURSE_MENTIONS_GOLD_CARD, EventScript_PkmnCenterNurse_AskForUsual
	setflag FLAG_NURSE_MENTIONS_GOLD_CARD
	msgbox gText_WelcomeCutShort, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x800B, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x800B, Common_Movement_Delay48
	waitmovement 0
	msgbox gText_NoticesGoldCard, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_GoldCardHealPkmn
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_AskForUsual::
	msgbox gText_YouWantTheUsual, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, EventScript_PkmnCenterNurse_GoldCardHealPkmn
	message gText_WeHopeToSeeYouAgain2
	return

EventScript_PkmnCenterNurse_GoldCardHealPkmn::
	setvar VAR_0x8004, 1
	goto EventScript_PkmnCenterNurse_HealPkmn
	end

Movement_PkmnCenterNurse_Bow:
	nurse_joy_bow
	delay_4
	step_end

Movement_PkmnCenterNurse_Turn:
	walk_in_place_faster_left
	step_end

EventScript_PkmnCenterNurse_ChangeTera::
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, EventScript_PkmnCenterNurse_Goodbye
	copyvar VAR_0x8005, VAR_0x8004
	dynmultichoice 0, 0, FALSE, 7, 0, DYN_MULTICHOICE_CB_NONE, NurseTera_Str_NORMAL, NurseTera_Str_FIGHTING, NurseTera_Str_FLYING, NurseTera_Str_POISON, NurseTera_Str_GROUND, NurseTera_Str_ROCK, NurseTera_Str_BUG, NurseTera_Str_GHOST, NurseTera_Str_STEEL, NurseTera_Str_FIRE, NurseTera_Str_WATER, NurseTera_Str_GRASS, NurseTera_Str_ELECTRIC, NurseTera_Str_PSYCHIC, NurseTera_Str_ICE, NurseTera_Str_DRAGON, NurseTera_Str_DARK, NurseTera_Str_FAIRY
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, EventScript_PkmnCenterNurse_Goodbye
	switch VAR_RESULT
	case 0, NurseTera_Set_NORMAL
	case 1, NurseTera_Set_FIGHTING
	case 2, NurseTera_Set_FLYING
	case 3, NurseTera_Set_POISON
	case 4, NurseTera_Set_GROUND
	case 5, NurseTera_Set_ROCK
	case 6, NurseTera_Set_BUG
	case 7, NurseTera_Set_GHOST
	case 8, NurseTera_Set_STEEL
	case 9, NurseTera_Set_FIRE
	case 10, NurseTera_Set_WATER
	case 11, NurseTera_Set_GRASS
	case 12, NurseTera_Set_ELECTRIC
	case 13, NurseTera_Set_PSYCHIC
	case 14, NurseTera_Set_ICE
	case 15, NurseTera_Set_DRAGON
	case 16, NurseTera_Set_DARK
	case 17, NurseTera_Set_FAIRY
	goto EventScript_PkmnCenterNurse_Goodbye

NurseTera_Set_NORMAL::
	setteratype TYPE_NORMAL, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_FIGHTING::
	setteratype TYPE_FIGHTING, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_FLYING::
	setteratype TYPE_FLYING, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_POISON::
	setteratype TYPE_POISON, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_GROUND::
	setteratype TYPE_GROUND, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_ROCK::
	setteratype TYPE_ROCK, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_BUG::
	setteratype TYPE_BUG, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_GHOST::
	setteratype TYPE_GHOST, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_STEEL::
	setteratype TYPE_STEEL, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_FIRE::
	setteratype TYPE_FIRE, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_WATER::
	setteratype TYPE_WATER, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_GRASS::
	setteratype TYPE_GRASS, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_ELECTRIC::
	setteratype TYPE_ELECTRIC, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_PSYCHIC::
	setteratype TYPE_PSYCHIC, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_ICE::
	setteratype TYPE_ICE, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_DRAGON::
	setteratype TYPE_DRAGON, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_DARK::
	setteratype TYPE_DARK, VAR_0x8005
	goto NurseTera_Done

NurseTera_Set_FAIRY::
	setteratype TYPE_FAIRY, VAR_0x8005
	goto NurseTera_Done

NurseTera_Done::
	msgbox NurseTera_Text_Done, MSGBOX_DEFAULT
	goto EventScript_PkmnCenterNurse_Goodbye

NurseTera_Text_Done:
	.string "The Tera Type was changed!$"

NurseTera_Str_Heal:
	.string "Heal$"
NurseTera_Str_Tera:
	.string "Change Tera Type$"
NurseTera_Str_Cancel:
	.string "Cancel$"
NurseTera_Str_NORMAL:
	.string "Normal$"
NurseTera_Str_FIGHTING:
	.string "Fighting$"
NurseTera_Str_FLYING:
	.string "Flying$"
NurseTera_Str_POISON:
	.string "Poison$"
NurseTera_Str_GROUND:
	.string "Ground$"
NurseTera_Str_ROCK:
	.string "Rock$"
NurseTera_Str_BUG:
	.string "Bug$"
NurseTera_Str_GHOST:
	.string "Ghost$"
NurseTera_Str_STEEL:
	.string "Steel$"
NurseTera_Str_FIRE:
	.string "Fire$"
NurseTera_Str_WATER:
	.string "Water$"
NurseTera_Str_GRASS:
	.string "Grass$"
NurseTera_Str_ELECTRIC:
	.string "Electric$"
NurseTera_Str_PSYCHIC:
	.string "Psychic$"
NurseTera_Str_ICE:
	.string "Ice$"
NurseTera_Str_DRAGON:
	.string "Dragon$"
NurseTera_Str_DARK:
	.string "Dark$"
NurseTera_Str_FAIRY:
	.string "Fairy$"

NurseTera_ToggleMode::
	goto_if_set FLAG_UNUSED_0x020, NurseTera_ModeToDynamax
	setflag FLAG_UNUSED_0x020
	msgbox NurseTera_Text_ModeTera, MSGBOX_DEFAULT
	goto EventScript_PkmnCenterNurse_Goodbye

NurseTera_ModeToDynamax::
	clearflag FLAG_UNUSED_0x020
	msgbox NurseTera_Text_ModeDynamax, MSGBOX_DEFAULT
	goto EventScript_PkmnCenterNurse_Goodbye

NurseTera_Giga::
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, EventScript_PkmnCenterNurse_Goodbye
	togglegigantamaxfactor VAR_0x8004
	hasgigantamaxfactor VAR_0x8004
	goto_if_eq VAR_RESULT, TRUE, NurseTera_GigaOn
	msgbox NurseTera_Text_GigaOff, MSGBOX_DEFAULT
	goto EventScript_PkmnCenterNurse_Goodbye

NurseTera_GigaOn::
	msgbox NurseTera_Text_GigaOn, MSGBOX_DEFAULT
	goto EventScript_PkmnCenterNurse_Goodbye

NurseTera_Text_ModeTera:
	.string "Mode set: TERA!$"
NurseTera_Text_ModeDynamax:
	.string "Mode set: DYNAMAX!$"
NurseTera_Text_GigaOn:
	.string "Gigantamax Factor: ON!$"
NurseTera_Text_GigaOff:
	.string "Gigantamax Factor: OFF!$"
NurseTera_Str_Mode:
	.string "Dynamax/Tera Mode$"
NurseTera_Str_Giga:
	.string "Gigantamax Factor$"
