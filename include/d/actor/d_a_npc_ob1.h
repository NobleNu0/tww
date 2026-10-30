#ifndef D_A_NPC_OB1_H
#define D_A_NPC_OB1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class J3DNode;

class daNpc_Ob1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Ob1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
        /* 0x10 */ int field_0x10;
    };  // Size: 0x14

    void nodeOb1Control(J3DNode*, J3DModel*);
    bool init_OB1_0();
    bool init_OB1_1();
    bool init_OB1_2();
    bool createInit();
    void setMtx(bool);
    int anmNum_toResID(int);
    int btpNum_toResID(int);
    bool setBtp(bool, int);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    bool setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(u32*);
    u32 getMsg_OB1_0();
    u32 getMsg_OB1_1();
    u32 getMsg_OB1_2();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    void partner_srch();
    s8 bitCount(u8);
    void set_pigCnt();
    void ob_setPthPos();
    cXyz get_attPos();
    int ob_movPass();
    void ob_clcMovSpd();
    void ob_nMove();
    bool charDecide(int);
    void event_actionInit(int);
    bool event_action();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(int (daNpc_Ob1_c::*)(void*), void*);
    void clrSpd();
    void setStt(s8);
    BOOL wait_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL walk_1();
    BOOL talk_1();
    BOOL manzai();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_hed_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6D0 */ u32 mShadowID;
    /* 0x6D4 */ J3DModel* m_hed_model;
    /* 0x6D8 */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6DC */ mDoExt_btpAnm mHeadBtpAnm;
    /* 0x6F0 */ u8 mBlinkFrame;
    /* 0x6F2 */ s16 mBlinkTimer;
    /* 0x6F4 */ ProcFunc mCurrProcFunc;
    /* 0x700 */ dNpc_PathRun_c mPathRun;
    /* 0x708 */ dNpc_EventCut_c mEventCut;
    /* 0x774 */ fpc_ProcID mPartnerProcID;
    /* 0x778 */ cXyz mInitialPos;
    /* 0x784 */ csXyz mInitialAngle;
    /* 0x78A */ csXyz m78A;
    /* 0x790 */ cXyz mTransformedEyePos;
    /* 0x79C */ cXyz m79C;
    /* 0x7A8 */ cXyz mTargetPos;
    /* 0x7B4 */ f32 mPrevMorfFrame;
    /* 0x7B8 */ f32 mMaxSpeed;
    /* 0x7BC */ f32 mSpeedStep;
    /* 0x7C0 */ f32 mPassDist;
    /* 0x7C4 */ s16 mJointHeadY;
    /* 0x7C6 */ s16 mJointBackboneY;
    /* 0x7C8 */ s16 mActorAngleY;
    /* 0x7CC */ u32 mAtrMsgNo;
    /* 0x7D0 */ s16 mEventIdTable[1];
    /* 0x7D2 */ s16 mEventIdx;
    /* 0x7D4 */ u8 field_0x7D4[0x7D6 - 0x7D4];
    /* 0x7D6 */ s16 mEvTimer;
    /* 0x7D8 */ u8 field_0x7D8[0x7DA - 0x7D8];
    /* 0x7DA */ s16 mLookTimer;
    /* 0x7DC */ u8 field_0x7DC[0x7DE - 0x7DC];
    /* 0x7DE */ s16 mLookAtMaxVel;
    /* 0x7E0 */ s16 mTargetYRot;
    /* 0x7E2 */ u16 mOldMsgStat;
    /* 0x7E4 */ s8 mbMorfAnimStopped;
    /* 0x7E5 */ s8 mAnmLoopCnt;
    /* 0x7E6 */ u8 field_0x7E6;
    /* 0x7E7 */ s8 mPigCnt;
    /* 0x7E8 */ s8 mNearPigCnt;
    /* 0x7E9 */ s8 mNewPigCnt;
    /* 0x7EA */ s8 mMsgCycle;
    /* 0x7EB */ u8 mItemNo;
    /* 0x7EC */ bool m7EC;
    /* 0x7ED */ bool m7ED;
    /* 0x7EE */ bool m7EE;
    /* 0x7EF */ bool m7EF;
    /* 0x7F0 */ bool m7F0;
    /* 0x7F1 */ bool m7F1;
    /* 0x7F2 */ bool mbPointPassed;
    /* 0x7F3 */ bool mbRanExecute;
    /* 0x7F4 */ BOOL mbSetEyePos;
    /* 0x7F8 */ bool mbAttention;
    /* 0x7F9 */ bool m7F9;
    /* 0x7FA */ bool mHeadOnlyFollow;
    /* 0x7FB */ bool mbInDemo;
    /* 0x7FC */ s8 mMoveMode;
    /* 0x7FD */ u8 field_0x7FD;
    /* 0x7FE */ s8 mActionIndex;
    /* 0x7FF */ s8 mActNo;
    /* 0x800 */ u8 m800;
    /* 0x801 */ u8 mMesgAnimeTagInfo;
    /* 0x802 */ s8 mBtpNum;
    /* 0x803 */ s8 mAnmNum;
    /* 0x804 */ s8 m804;
    /* 0x805 */ s8 mStatus;
    /* 0x806 */ s8 mPrevStatus;
    /* 0x807 */ s8 mLookBackState;
    /* 0x808 */ s8 mType;
    /* 0x809 */ s8 mSpecificType;
    /* 0x80A */ s8 m80A;
    /* 0x80B */ s8 m80B;
};  // Size: 0x80C

#endif /* D_A_NPC_OB1_H */
