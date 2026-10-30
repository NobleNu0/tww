#ifndef D_A_NPC_GK1_H
#define D_A_NPC_GK1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

class J3DNode;

class daNpc_Gk1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Gk1_c::*ActionFunc)(void*);

    struct anm_prm_c {
        s8 field_0x0;
        s8 field_0x1;
        f32 field_0x4;
        f32 field_0x8;
        int field_0xC;
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_GK1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool setBtp(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_GK1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    bool set_action(ActionFunc, void*);
    void setStt(s8);
    bool chk_attn();
    BOOL wait_1();
    BOOL talk_1();
    int wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL itemCreateHeap();
    BOOL hat_CreateHeap();
    BOOL CreateHeap();

private:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_nck_jnt_num;
    /* 0x6D0 */ J3DModel* mpHairModel;
    /* 0x6D4 */ J3DModel* mpHatModel;
    /* 0x6D8 */ char mArcName[4];
    /* 0x6DC */ u32 mShadowId;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u8 mBtpAnmFrame;
    /* 0x6F6 */ s16 mTimer1;
    /* 0x6F8 */ ActionFunc mCurrActionFunc;
    /* 0x704 */ u8 field_0x704[0x708 - 0x704];
    /* 0x708 */ fpc_ProcID mPId;
    /* 0x70C */ u8 field_0x70C[0x714 - 0x70C];
    /* 0x714 */ cXyz field_0x714;
    /* 0x720 */ csXyz field_0x720;
    /* 0x726 */ csXyz field_0x726;
    /* 0x72C */ u8 field_0x72C[0x734 - 0x72C];
    /* 0x734 */ cXyz field_0x734;
    /* 0x740 */ cXyz field_0x740;
    /* 0x74C */ u8 field_0x74C[0x758 - 0x74C];
    /* 0x758 */ cXyz field_0x758;
    /* 0x764 */ u8 field_0x764[0x770 - 0x764];
    /* 0x770 */ f32 mFrame;
    /* 0x774 */ u8 field_0x774[0x778 - 0x774];
    /* 0x778 */ csXyz field_0x778;
    /* 0x780 */ int field_0x780;
    /* 0x784 */ s16 mEventIdx[1];
    /* 0x786 */ s16 field_0x786;
    /* 0x788 */ u8 field_0x788[0x790 - 0x788];
    /* 0x790 */ s16 mTimer2;
    /* 0x792 */ u8 field_0x792[0x79A - 0x792];
    /* 0x79A */ s16 field_0x79A;
    /* 0x79C */ s8 field_0x79C;
    /* 0x79D */ u8 field_0x79D;
    /* 0x79E */ u8 mItemNo;
    /* 0x79F */ bool mStateIsComplaete;
    /* 0x7A0 */ bool field_0x7A0;
    /* 0x7A1 */ bool field_0x7A1;
    /* 0x7A2 */ bool field_0x7A2;
    /* 0x7A3 */ bool field_0x7A3;
    /* 0x7A4 */ bool mHasAttention;
    /* 0x7A5 */ bool field_0x7A5;
    /* 0x7A6 */ bool field_0x7A6;
    /* 0x7A7 */ bool field_0x7A7;
    /* 0x7A8 */ bool field_0x7A8;
    /* 0x7A9 */ s8 mActIdx;
    /* 0x7AA */ u8 field_0x7AA;
    /* 0x7AB */ u8 field_0x7AB;
    /* 0x7AC */ s8 field_0x7AC;
    /* 0x7AD */ s8 field_0x7AD;
    /* 0x7AE */ s8 field_0x7AE;
    /* 0x7AF */ s8 field_0x7AF;
    /* 0x7B0 */ s8 field_0x7B0;
    /* 0x7B1 */ s8 field_0x7B1;
    /* 0x7B2 */ s8 field_0x7B2;
    /* 0x7B3 */ s8 field_0x7B3;
    /* 0x7B4 */ s8 field_0x7B4;
    /* 0x7B5 */ s8 field_0x7B5;
};  // Size: 0x7B8

#endif /* D_A_NPC_GK1_H */
