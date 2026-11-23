#include "global.h"
#include "string_util.h"
#include "pokemon.h"
#include "event_data.h"

void BuildIvEvText(void);

static u8 *St(u8 *d, const u8 *l, u32 v)
{
    d = StringCopy(d, l);
    return ConvertIntToDecimalStringN(d, v, 0, 3);
}

void BuildIvEvText(void)
{
    struct Pokemon *m = &gPlayerParty[gSpecialVar_0x8004];
    u8 *d;
    GetMonData(m, MON_DATA_NICKNAME, gStringVar1);
    d = StringCopy(gStringVar4, gStringVar1);
    d = StringCopy(d, COMPOUND_STRING(" IV\nHP "));
    d = St(d, COMPOUND_STRING(""), GetMonData(m, MON_DATA_HP_IV));
    d = St(d, COMPOUND_STRING("  ATK "), GetMonData(m, MON_DATA_ATK_IV));
    d = St(d, COMPOUND_STRING("  DEF "), GetMonData(m, MON_DATA_DEF_IV));
    d = St(d, COMPOUND_STRING("\pSPA "), GetMonData(m, MON_DATA_SPATK_IV));
    d = St(d, COMPOUND_STRING("  SPD "), GetMonData(m, MON_DATA_SPDEF_IV));
    d = St(d, COMPOUND_STRING("  SPE "), GetMonData(m, MON_DATA_SPEED_IV));
    d = StringCopy(d, COMPOUND_STRING("\pEV\nHP "));
    d = St(d, COMPOUND_STRING(""), GetMonData(m, MON_DATA_HP_EV));
    d = St(d, COMPOUND_STRING("  ATK "), GetMonData(m, MON_DATA_ATK_EV));
    d = St(d, COMPOUND_STRING("  DEF "), GetMonData(m, MON_DATA_DEF_EV));
    d = St(d, COMPOUND_STRING("\pSPA "), GetMonData(m, MON_DATA_SPATK_EV));
    d = St(d, COMPOUND_STRING("  SPD "), GetMonData(m, MON_DATA_SPDEF_EV));
    d = St(d, COMPOUND_STRING("  SPE "), GetMonData(m, MON_DATA_SPEED_EV));
}
