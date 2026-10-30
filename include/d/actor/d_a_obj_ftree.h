#ifndef D_A_OBJ_FTREE_H
#define D_A_OBJ_FTREE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_gnd_chk.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class J3DNode;
class msg_class;

namespace daObjFtree {
    struct _ftree_seach_info_ {
        /* 0x00 */ int mTotal;
        /* 0x04 */ int mBroughtNum;
    };

    static void Ftree_get_water_pos(cXyz*, cXyz*);
    static s16 Ftree_checkXyEventCallBack(void*, int);
    static s16 Ftree_XyEventCallBack(void*, int);
    static BOOL is_broughtID(int);
    static BOOL Ftree_NodeCallBack_Effect(J3DNode*, int);
    static BOOL Ftree_NodeCallBack_M(J3DNode*, int);
    static BOOL Ftree_NodeCallBack_L(J3DNode*, int);

    class Act_c : public fopAc_ac_c {
    public:
        enum Mode_e {
            MODE_NONE_e,
            MODE_WAIT_S_e,
            MODE_WAIT_M_e,
            MODE_WAIT_L_e,
            MODE_CHANGE_SL_e,
            MODE_CHANGE_SL2_e,
            MODE_CHANGE_LS_e,
            MODE_CHANGE_LS2_e,
            MODE_CHANGE_SM_e,
            MODE_CHANGE_MS_e,
            MODE_PIKUPIKU_S_e,
            MODE_PIKUPIKU_M_e,
            MODE_PIKUPIKU_L_e,
            MODE_MAX_e,
        };

        virtual ~Act_c() {}

        f32 GetRate(f32 i_value, f32 i_min, f32 i_max) {
            if (i_value <= i_min) {
                return 0.0f;
            }
            if (i_value >= i_max) {
                return 1.0f;
            }
            return (i_value - i_min) / (i_max - i_min);
        }
        void brought() {}
        void check_heart() {}
        void check_water() {}
        void init_water() {}
        int param_get_tree_idx() const;
        void set_heart(short) {}
        void set_water(short) {}
        void tree_brouht(int) {}

        void search_heart_part();
        BOOL launch_heart_part();
        BOOL place_heart_part();
        BOOL estimate_water();
        s16 XyEventCallBack(int);
        void XyEvent_init();
        BOOL XyEvent_set(s16);
        void XyEvent_exe();
        BOOL SetJointAnimation(int, f32, f32, int);
        BOOL PlayStopJointAnimation();
        BOOL PlayStopColorAnimation();
        void set_first_stat();
        void set_collision();
        void talk_ct();
        void talk_main();
        void get_tev_material0_color(J3DModelData*, u32, s16*, s16*, s16*);
        void set_tev_color(J3DModelData*, u32, s16, s16, s16);
        BOOL is_brought();
        void set_broughtID(int);
        void set_brought();
        void unset_broughtID(int);
        void unset_brought();
        void get_ftree_info(_ftree_seach_info_*);
        BOOL iam_last();
        BOOL action_none_init(s16);
        void action_none_main();
        BOOL action_waitS_init(s16);
        void action_waitS_main();
        BOOL action_waitM_init(s16);
        void action_waitM_main();
        BOOL action_waitL_init(s16);
        void action_waitL_main();
        BOOL action_pikupikuS_init(s16);
        void action_pikupikuS_main();
        BOOL action_pikupikuM_init(s16);
        void action_pikupikuM_main();
        BOOL action_pikupikuL_init(s16);
        void action_pikupikuL_main();
        BOOL action_changeSL_init(s16);
        void action_changeSL_main();
        BOOL action_changeSL2_init(s16);
        void action_changeSL2_main();
        BOOL action_changeLS_init(s16);
        void action_changeLS_main();
        BOOL action_changeLS2_init(s16);
        void action_changeLS2_main();
        BOOL action_changeSM_init(s16);
        void action_changeSM_main();
        BOOL action_changeMS_init(s16);
        void action_changeMS_main();
        BOOL process_init(int, s16);
        void process_main();
        static BOOL solidHeapCB(fopAc_ac_c*);
        BOOL NodeCallBack_Effect(J3DNode*, int);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();

        static char M_arcname[];

    public:
        /* 0x294 */ s16 mAngleMX;
        /* 0x296 */ s16 mAngleMY;
        /* 0x298 */ s16 mAngleLY;
        /* 0x29A */ s16 mAngleLZ;
        /* 0x29C */ request_of_phase_process_class mPhs;
        /* 0x2A4 */ s16 mEffectFlag;
        /* 0x2A6 */ u8 mDrawS;
        /* 0x2A7 */ u8 mDrawL;
        /* 0x2A8 */ Mtx mMtx;
        /* 0x2D8 */ mDoExt_McaMorf* mpMorf;
        /* 0x2DC */ J3DModel* mpModelL;
        /* 0x2E0 */ mDoExt_brkAnm mBrkAnm;
        /* 0x2F8 */ dBgS_ObjGndChk mGndChk;
        /* 0x34C */ f32 mGroundY;
        /* 0x350 */ s16 mEventCam0Idx;
        /* 0x352 */ s16 mEventCam1Idx;
        /* 0x354 */ s16 mEventCam2Idx;
        /* 0x356 */ s16 mXyEventIdx;
        /* 0x358 */ s16 mXyEventState;
        /* 0x35C */ dCcD_Stts mStatusW;
        /* 0x398 */ dCcD_Cyl mCylW;
        /* 0x4C8 */ f32 mCylR;
        /* 0x4CC */ dCcD_Stts mStatus;
        /* 0x508 */ dCcD_Cyl mCyl;
        /* 0x638 */ BOOL mBrought;
        /* 0x63C */ f32 mScaleL;
        /* 0x640 */ f32 mColorRateS;
        /* 0x644 */ int mTreeIdx;
        /* 0x648 */ s16 mHeartPlaced;
        /* 0x64C */ fpc_ProcID mHeartPartId;
        /* 0x650 */ s16 mLaunchTimer;
        /* 0x652 */ s16 mEventTimer;
        /* 0x654 */ GXColorS10 mColorS;
        /* 0x65C */ GXColorS10 mStartColorS;
        /* 0x664 */ GXColorS10 mColorL;
        /* 0x66C */ GXColorS10 mCurColorS;
        /* 0x674 */ GXColorS10 mCurColorL;
        /* 0x67C */ int mPrevCoHit;
        /* 0x680 */ int mMode;
        /* 0x684 */ s16 mChangeTimer;
        /* 0x688 */ int mPikuNumS;
        /* 0x68C */ int mPikuCntS;
        /* 0x690 */ s16 mPikuNumM;
        /* 0x692 */ s16 mPikuCntM;
        /* 0x694 */ s16 mPikuPhaseM;
        /* 0x696 */ s16 mTargetAngleMX;
        /* 0x698 */ s16 mTargetAngleMY;
        /* 0x69A */ s16 mPikuNumL;
        /* 0x69C */ s16 mPikuCntL;
        /* 0x69E */ s16 mPikuPhaseL;
        /* 0x6A0 */ s16 mTargetAngleLY;
        /* 0x6A2 */ s16 mTargetAngleLZ;
        /* 0x6A4 */ fpc_ProcID mMsgId;
        /* 0x6A8 */ msg_class* mpMsg;
        /* 0x6AC */ u8 m6AC[0x6B0 - 0x6AC];
    }; // Size: 0x6B0
};

#endif /* D_A_OBJ_FTREE_H */
