#ifndef D_A_OBJ_BALANCELIFT_H
#define D_A_OBJ_BALANCELIFT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"

class dBgW;
class dChain_packet_c;
struct dPath;

class daBalancelift_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();

    void calc_quat();
    void set_mtx();
    void calc_weight();
    BOOL CreateHeap();
    cPhs_State CreateInit();

    static const char M_arcname[6];

public:
    /* 0x290 */ cXyz m290;
    /* 0x29C */ cXyz m29C;
    /* 0x2A8 */ cXyz m2A8;
    /* 0x2B4 */ cXyz m2B4;
    /* 0x2C0 */ cXyz m2C0;
    /* 0x2CC */ Quaternion m2CC;
    /* 0x2DC */ Quaternion m2DC;
    /* 0x2EC */ cXyz m2EC;
    /* 0x2F8 */ cXyz m2F8;
    /* 0x304 */ cXyz m304;
    /* 0x310 */ f32 m310;
    /* 0x314 */ s16 m314;
    /* 0x318 */ s16* m318;
    /* 0x31C */ s16 m31C;
    /* 0x31E */ s16 m31E;
    /* 0x320 */ s16* m320;
    /* 0x324 */ request_of_phase_process_class mPhase;
    /* 0x32C */ J3DModel* M_mdl;
    /* 0x330 */ Mtx mMtx;
    /* 0x360 */ dPath* mpPath;
    /* 0x364 */ dBgW* pm_bgw;
    /* 0x368 */ f32 m368;
    /* 0x36C */ cXyz m36C[4];
    /* 0x39C */ mDoExt_3DlineMat0_c mLineMat;
    /* 0x3B8 */ dChain_packet_c* m_chain;
    /* 0x3BC */ dCcD_Stts mStts;
    /* 0x3F8 */ dCcD_Cyl mCyl;
}; // size = 0x528

#endif /* D_A_OBJ_BALANCELIFT_H */
