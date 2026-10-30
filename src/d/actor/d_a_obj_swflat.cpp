/**
 * d_a_obj_swflat.cpp
 * Object - Tower of the Gods - Floor switch (requires statues to stay active)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_swflat.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "res/Object/Hfbot.h"

class daObjSwflat_HIO_c : public JORReflexible {
public:
    daObjSwflat_HIO_c();
    virtual ~daObjSwflat_HIO_c() {}

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ s32 mCount;
    /* 0x0C */ f32 mCylR;
    /* 0x10 */ f32 mCylH;
    /* 0x14 */ s16 mDemoTime;
    /* 0x16 */ s16 mLockTime;
    /* 0x18 */ u8 mUseHioCyl;
    /* 0x19 */ u8 mResetSwitch;
};  // Size: 0x1C

static daObjSwflat_HIO_c l_HIO;

Mtx daObjSwflat::Act_c::M_tmp_mtx;

namespace daObjSwflat {
static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e | cCcD_CoSPrm_NoCrr_e | cCcD_CoSPrm_NoCoHitInfSet_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 10.0f,
        /* Height */ 20.0f,
    }},
};
}


/* 000000EC-00000138       .text __ct__17daObjSwflat_HIO_cFv */
daObjSwflat_HIO_c::daObjSwflat_HIO_c() {
    mNo = -1;
    mCount = 0;
    mResetSwitch = 0;
    mUseHioCyl = 0;
    mCylR = 10.0f;
    mCylH = 20.0f;
    mDemoTime = 30;
    mLockTime = 30;
}

const char daObjSwflat::Act_c::M_arcname[] = "Hfbot";

/* 00000138-00000280       .text CreateHeap__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HFBOT_BDL_HFBOT1_e);
    if (model_data == NULL) {
        return FALSE;
    }
    mpModel = mDoExt_J3DModel__create(model_data, 0, 0x11020203);

    J3DAnmTevRegKey* pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HFBOT_BRK_HFBOT1_e);
    if (pbrk == NULL) {
        return FALSE;
    }
    mpBrk = new mDoExt_brkAnm();
    if (mpBrk == NULL) {
        return FALSE;
    }
    BOOL brk_ok = mpBrk->init(model_data, pbrk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    return mpModel != NULL && brk_ok;
}

/* 000002C8-00000630       .text Create__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeSphere(this, 0.0f, 0.0f, 0.0f, 90.0f);
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    mType = prmGetType();
    mSwNo = prmGetSwNo();
    mSwNo2 = prmGetSwNo2();
    mBrkFrame = 0;
    mBrkFrameMax = mpBrk->getEndFrame() - 5.0f;
    mEffPos = current.pos;
    mIsLocked = 0;

    if (l_HIO.mResetSwitch == 1) {
        if (mSwNo != 0xFF) {
            fopAcM_offSwitch(this, mSwNo);
        }
        if (mSwNo2 != 0xFF) {
            fopAcM_offSwitch(this, mSwNo2);
        }
    }

    u8 sw_no = mSwNo;
    if (mType == 2) {
        if (fopAcM_isSwitch(this, mSwNo2)) {
            mType = 0;
            sw_no = mSwNo2;
        } else {
            mType = 1;
        }
    }

    if (fopAcM_isSwitch(this, sw_no)) {
        mIsOn = mWasOn = 1;
        if (mType != 0) {
            mpOnEmitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONON, &mEffPos, &shape_angle);
            mOnEmitterAlpha = 250;
        } else {
            mpOnEmitter = NULL;
            mOnEmitterAlpha = 0;
            mIsLocked = 1;
            mpBrk->setFrame(mpBrk->getEndFrame());
        }
        mpOffEmitter = NULL;
        mOffEmitterAlpha = 0;
    } else {
        mIsOn = mWasOn = 0;
        mpOffEmitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONOFF, &mEffPos, &shape_angle);
        mOffEmitterAlpha = 250;
        mpOnEmitter = NULL;
        mOnEmitterAlpha = 0;
    }

    mMode = Mode_WAIT_e;
    mDemoTimer = 0;
    mOffTimer = 0;

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("フラットスイッチ", &l_HIO); // "Flat Switch"
    }
    l_HIO.mCount++;
    return TRUE;
}

/* 00000630-000007BC       .text Mthd_Create__Q211daObjSwflat5Act_cFv */
cPhs_State daObjSwflat::Act_c::Mthd_Create() {
    fopAcM_ct(this, Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, dRes_INDEX_HFBOT_DZB_HFBOT1_e, NULL, -1);
        JUT_ASSERT(385, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }

    return phase_state;
}

/* 00000974-0000097C       .text Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Delete() {
    return TRUE;
}

/* 0000097C-00000A64       .text Mthd_Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Mthd_Delete() {
    if (heap != NULL) {
        if (mpOffEmitter != NULL) {
            mpOffEmitter->becomeInvalidEmitter();
            mpOffEmitter = NULL;
        }
        if (mpOnEmitter != NULL) {
            mpOnEmitter->becomeInvalidEmitter();
            mpOnEmitter = NULL;
        }
    }

    if (l_HIO.mNo >= 0 && --l_HIO.mCount == 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }

    BOOL ret = MoveBGDelete();
    dComIfG_resDelete(&mPhs, M_arcname);
    return ret;
}

/* 00000A64-00000AE4       .text set_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000AE4-00000B20       .text init_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000B20-0000121C       .text Execute__Q211daObjSwflat5Act_cFPPA3_A4_f */
BOOL daObjSwflat::Act_c::Execute(Mtx** mtx) {
    bool player_on = false;

    mCyl.SetC(current.pos);
    if (l_HIO.mUseHioCyl) {
        mCyl.SetR(l_HIO.mCylR);
        mCyl.SetH(l_HIO.mCylH);
    }
    dComIfG_Ccsp()->Set(&mCyl);

    bool pressed = false;
    if (mCyl.ChkCoHit()) {
        fopAc_ac_c* hit_actor = mCyl.GetCoHitAc();
        if (hit_actor != NULL && fopAcM_CheckStatus(hit_actor, fopAcStts_FREEZE_e)) {
            pressed = true;
            if (fopAcM_GetProfName(hit_actor) == fpcNm_PLAYER_e) {
                player_on = true;
            }
        }
    }

    if (mDemoTimer == 0) {
        if (pressed) {
            mIsOn = 1;
            mCyl.SetR(15.0f);
        } else if (mType == 1) {
            mIsOn = 0;
            mCyl.SetR(10.0f);
        }
    }

    if (prmGetType() == 2 && fopAcM_isSwitch(this, mSwNo2)) {
        mType = 0;
        if (mIsLocked == 0) {
            mOffTimer = l_HIO.mLockTime;
            mIsLocked = 1;
        }
    }

    bool turned_on = false;
    if (mIsOn == 1) {
        if (mWasOn == 0) {
            mDoAud_seStart(JA_SE_OBJ_FLAT_SW_ON, &current.pos, 0, 0);
        }
        if (mIsLocked == 0) {
            mDoAud_seStart(JA_SE_OBJ_FLAT_SW_LIGHT, &current.pos, 0, 0);
        }
        if (mBrkFrame < mBrkFrameMax) {
            mBrkFrame++;
            mpBrk->setFrame(mBrkFrame);
        }
        if (!player_on) {
            fopAcM_onSwitch(this, mSwNo);
        }
        if (mIsLocked == 0) {
            if (mpOnEmitter == NULL) {
                mpOnEmitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONON, &mEffPos, &shape_angle);
                mOnEmitterAlpha = 250;
                turned_on = true;
                if (prmGetType() == 0) {
                    mOffTimer = l_HIO.mLockTime;
                    mIsLocked = 1;
                }
            } else if (mOnEmitterAlpha < 250) {
                mOnEmitterAlpha += 25;
                mpOnEmitter->setGlobalAlpha(mOnEmitterAlpha);
                fopAcM_onSwitch(this, mSwNo);
            }
        }
        if (mpOffEmitter != NULL) {
            mOffEmitterAlpha -= 25;
            mpOffEmitter->setGlobalAlpha(mOffEmitterAlpha);
            if (mOffEmitterAlpha == 0) {
                mpOffEmitter->becomeInvalidEmitter();
                mpOffEmitter = NULL;
            }
        }
    } else {
        if (mBrkFrame > 0) {
            mBrkFrame--;
            mpBrk->setFrame(mBrkFrame);
        }
        fopAcM_offSwitch(this, mSwNo);
        if (mpOffEmitter == NULL) {
            mpOffEmitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONOFF, &mEffPos, &shape_angle);
            mOffEmitterAlpha = 250;
        } else if (mOffEmitterAlpha < 250) {
            mOffEmitterAlpha += 25;
            mpOffEmitter->setGlobalAlpha(mOffEmitterAlpha);
        }
        if (mpOnEmitter != NULL) {
            mOnEmitterAlpha -= 25;
            mpOnEmitter->setGlobalAlpha(mOnEmitterAlpha);
            if (mOnEmitterAlpha == 0) {
                mpOnEmitter->becomeInvalidEmitter();
                mpOnEmitter = NULL;
            }
        }
    }

    switch (mMode) {
    case Mode_WAIT_e:
        mDemoTimer = 0;
        if (turned_on && player_on) {
            mMode = Mode_DEMO_WAIT_e;
            mDemoTimer = 30;
        }
        break;
    case Mode_DEMO_WAIT_e:
        if (eventInfo.checkCommandDemoAccrpt()) {
            mMode = Mode_DEMO_e;
            if (l_HIO.mUseHioCyl) {
                mDemoTimer = l_HIO.mDemoTime;
            }
        } else {
            fopAcM_orderPotentialEvent(this, 1, 0, 0);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
        break;
    case Mode_DEMO_e:
        mDemoTimer--;
        if (mDemoTimer <= 1) {
            dComIfGp_event_reset();
            mMode = Mode_WAIT_e;
            fopAcM_onSwitch(this, mSwNo);
        }
        break;
    }

    if (mIsLocked) {
        mIsOn = 1;
        if (mOffTimer != 0) {
            mOffTimer--;
        } else {
            if (mpOnEmitter != NULL) {
                mOnEmitterAlpha -= 25;
                mpOnEmitter->setGlobalAlpha(mOnEmitterAlpha);
                if (mOnEmitterAlpha == 0) {
                    mpOnEmitter->becomeInvalidEmitter();
                    mpOnEmitter = NULL;
                }
            }
            if (mpOffEmitter != NULL) {
                mOffEmitterAlpha -= 25;
                mpOffEmitter->setGlobalAlpha(mOffEmitterAlpha);
                if (mOffEmitterAlpha == 0) {
                    mpOffEmitter->becomeInvalidEmitter();
                    mpOffEmitter = NULL;
                }
            }
            if (mBrkFrame < mBrkFrameMax + 5) {
                mBrkFrame++;
                mpBrk->setFrame(mBrkFrame);
            }
        }
    }

    set_mtx();
    *mtx = &M_tmp_mtx;
    mWasOn = mIsOn;
    return TRUE;
}

/* 0000121C-000012D4       .text Draw__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpBrk->entry(mpModel->getModelData());

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

/* 000012D4-000012DC       .text IsDelete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::IsDelete() {
    return TRUE;
}

namespace daObjSwflat {
namespace {
/* 000012DC-000012FC       .text Mthd_Create__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Mthd_Create();
}

/* 000012FC-0000131C       .text Mthd_Delete__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Mthd_Delete();
}

/* 0000131C-0000133C       .text Mthd_Execute__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->MoveBGExecute();
}

/* 0000133C-00001368       .text Mthd_Draw__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Draw();
}

/* 00001368-00001394       .text Mthd_IsDelete__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjSwflat

actor_process_profile_definition g_profile_Obj_Swflat = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0002,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Swflat_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSwflat::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Swflat_e,
    /* Actor SubMtd */ &daObjSwflat::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLSPHERE_CUSTOM_e,
};
