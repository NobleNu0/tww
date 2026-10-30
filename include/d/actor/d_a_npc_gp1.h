#ifndef D_A_NPC_GP1_H
#define D_A_NPC_GP1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Gp1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Gp1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };

    void nodeGp1Control(J3DNode*, J3DModel*);
    bool init_GP1_0();
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
    bool chk_drct(f32);
    bool chk_partsNotMove();
    bool chk_forceTlkArea();
    void lookBack();
    u16 next_msgStatus(u32*);
    u32 getMsg_GP1_0();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    bool partner_srch_sub(fpcLyIt_JudgeFunc);
    void partner_srch();
    void ctrl_WAITanm();
    int gp_movPass();
    void gp_clcMovSpd();
    void gp_nMove();
    BOOL create_rupee();
    bool charDecide(int);
    void eInit_INI_KAERE_KAERE_();
    void eInit_END_KAERE_KAERE_();
    void event_actionInit(int);
    bool event_action();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL talk_1();
    BOOL walk_1();
    BOOL hair_1();
    BOOL wait_2();
    BOOL wait_action1(void*);
    bool demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_L_jnt_num;
    /* 0x6D0 */ u32 mShadowID;
    /* 0x6D4 */ J3DModel* mpShadowModel;
    /* 0x6D8 */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6DC */ mDoExt_btpAnm mHeadBtpAnm;
    /* 0x6F0 */ u8 mBlinkFrame;
    /* 0x6F2 */ s16 mBlinkTimer;
    /* 0x6F4 */ ProcFunc mCurrProcFunc;
    /* 0x700 */ dNpc_PathRun_c mPath;
    /* 0x708 */ dNpc_EventCut_c mEventCut;
    /* 0x774 */ fpc_ProcID mPartnerProcID;
    /* 0x778 */ cXyz mInitialPos;
    /* 0x784 */ csXyz mInitialAngle;
    /* 0x78A */ csXyz m78A;
    /* 0x790 */ cXyz mTransformedEyePos;
    /* 0x79C */ cXyz m79C;
    /* 0x7A8 */ cXyz mPathPos;
    /* 0x7B4 */ u8 field_0x7B4[0x7C0 - 0x7B4];
    /* 0x7C0 */ f32 mPrevMorfFrame;
    /* 0x7C4 */ f32 mEyeOffset;
    /* 0x7C8 */ u8 field_0x7C8[0x7CC - 0x7C8];
    /* 0x7CC */ f32 mTargetSpeed;
    /* 0x7D0 */ f32 mSpeedStep;
    /* 0x7D4 */ f32 mPassDist;
    /* 0x7D8 */ s16 mJointHeadY;
    /* 0x7DA */ s16 mJointBackboneY;
    /* 0x7DC */ s16 mActorAngleY;
    /* 0x7DE */ s16 mEventIdTable[3];
    /* 0x7E4 */ s16 mEventIdx;
    /* 0x7E6 */ u8 field_0x7E6[0x7E8 - 0x7E6];
    /* 0x7E8 */ s16 mLookTimer;
    /* 0x7EA */ s16 mWalkTimer;
    /* 0x7EC */ s16 mWalkCount;
    /* 0x7EE */ s16 mLookAtMaxVel;
    /* 0x7F0 */ s16 mTargetYRot;
    /* 0x7F2 */ s16 mNecklaceNum;
    /* 0x7F4 */ s16 mRupeeNum;
    /* 0x7F6 */ s16 mWaitAnmTimer;
    /* 0x7F8 */ s8 mbMorfAnimStopped;
    /* 0x7F9 */ s8 mAnmLoopCount;
    /* 0x7FA */ s8 m7FA;
    /* 0x7FB */ u8 mItemNo;
    /* 0x7FC */ bool m7FC;
    /* 0x7FD */ bool m7FD;
    /* 0x7FE */ bool m7FE;
    /* 0x7FF */ bool m7FF;
    /* 0x800 */ bool mbPathPassed;
    /* 0x801 */ bool mbPayRupee;
    /* 0x802 */ bool mbRanExecute;
    /* 0x804 */ BOOL mbSetEyePos;
    /* 0x808 */ bool mbAttention;
    /* 0x809 */ bool m809;
    /* 0x80A */ bool mHeadOnlyFollow;
    /* 0x80B */ bool mbInDemo;
    /* 0x80C */ s8 mWalkState;
    /* 0x80D */ s8 mActionIndex;
    /* 0x80E */ s8 mActNo;
    /* 0x80F */ u8 m80F;
    /* 0x810 */ u8 mMesgAnimeTagInfo;
    /* 0x811 */ s8 mBtpNum;
    /* 0x812 */ s8 mAnmNum;
    /* 0x813 */ s8 m813;
    /* 0x814 */ s8 mStatus;
    /* 0x815 */ s8 mPrevStatus;
    /* 0x816 */ s8 mLookBackState;
    /* 0x817 */ s8 mType;
    /* 0x818 */ s8 mSpecificType;
    /* 0x819 */ s8 m819;
    /* 0x81A */ s8 m81A;
}; // Size: 0x81C

#endif /* D_A_NPC_GP1_H */
