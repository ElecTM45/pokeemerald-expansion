EventScript_StartMenuPC::
lockall
special ShowPokemonStorageSystemPC
waitstate
releaseall
end

EventScript_StartMenuIvEv::
lockall
special ChoosePartyMon
waitstate
goto_if_ge VAR_0x8004, PARTY_SIZE, EventScript_StartMenuIvEv_End
special BuildIvEvText
msgbox gStringVar4, MSGBOX_DEFAULT
EventScript_StartMenuIvEv_End::
releaseall
end
