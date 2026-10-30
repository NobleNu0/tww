/**
 * d_a_obj_balancelift.cpp
 * Object - Tower of the Gods - Pair of scales
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_balancelift.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_chain.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Hten1.h"

class daBalancelift_HIO_c : public JORReflexible {
public:
    daBalancelift_HIO_c();
    virtual ~daBalancelift_HIO_c() {}

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ cXyz mScale;
}; // size = 0x38

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
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
        /* Radius */ 30.0f,
        /* Height */ 200.0f,
    }},
};

static daBalancelift_HIO_c l_HIO;

/* 000000EC-00000160       .text __ct__19daBalancelift_HIO_cFv */
daBalancelift_HIO_c::daBalancelift_HIO_c() {
    mNo = -1;
    m08 = 45.0f;
    m0C = 0.05f;
    m10 = 0.005f;
    m14 = 0.9f;
    m18 = 25.0f;
    m1C = 0.65f;
    m20 = 0.9f;
    m24 = 440.0f;
    m28 = 1800.0f;
    mScale.setall(2.0f);
}

const char daBalancelift_c::M_arcname[6] = "Hten1";

/* 0000019C-00000264       .text daObjBlift_ride_actor_check__FP10fopAc_ac_c */
static int daObjBlift_ride_actor_check(fopAc_ac_c* i_actor) {
    int weight = 0;
    if (fopAc_IsActor(i_actor)) {
        s16 name = fopAcM_GetName(i_actor);
        if (name == fpcNm_Obj_Try_e) {
            weight = 1;
        } else if (name == fpcNm_PLAYER_e) {
            weight++;
            fpc_ProcID grab_id = ((daPy_py_c*)i_actor)->getGrabActorID();
            if (grab_id != fpcM_ERROR_PROCESS_ID_e) {
                fopAc_ac_c* grab_actor = fopAcM_SearchByID(grab_id);
                if (grab_actor != NULL) {
                    weight += daObjBlift_ride_actor_check(grab_actor);
                }
            }
        } else if (name == fpcNm_AM2_e || name == fpcNm_NPC_OS_e || name == fpcNm_NPC_CB1_e) {
            weight = 1;
        }
    }
    return weight;
}

/* 00000264-0000033C       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
static void ride_call_back(dBgW*, fopAc_ac_c* i_this, fopAc_ac_c* i_rider) {
    daBalancelift_c* a_this = (daBalancelift_c*)i_this;
    int weight = daObjBlift_ride_actor_check(i_rider);
    cXyz pos = i_rider->current.pos;
    cXyz delta = pos - a_this->m2EC;
    delta *= l_HIO.m10;
    a_this->m2F8 += delta;
    if (a_this->m31C == 0) {
        *a_this->m318 += weight;
    } else {
        *a_this->m318 -= weight;
    }
}

/* 0000033C-00000510       .text calc_quat__15daBalancelift_cFv */
void daBalancelift_c::calc_quat() {
    cXyz pos = current.pos;
    pos.y -= m310;
    cXyz delta = pos - m2EC;
    delta *= l_HIO.m0C;
    m2F8 += delta;
    m2F8 *= l_HIO.m14;
    m2EC += m2F8;

    cXyz top = m290;
    cXyz center = current.pos;
    top -= m2EC;
    center -= m2EC;

    Quaternion rot;
    Quaternion slerp;
    daObj::quat_rotBaseY2(&rot, center);
    QUATInverse(&rot, &rot);
    C_QUATSlerp(&m2CC, &rot, &slerp, 0.1f + REG10_F(23));
    m2CC = slerp;

    daObj::quat_rotBaseY2(&rot, top);
    QUATInverse(&rot, &rot);
    C_QUATSlerp(&m2DC, &rot, &slerp, 0.15f + REG10_F(24));
    m2DC = slerp;
}

/* 00000510-00000670       .text set_mtx__15daBalancelift_cFv */
void daBalancelift_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::quatM(&m2CC);
    mDoMtx_stack_c::transM(0.0f, -m310, 0.0f);

    cXyz top_offset(0.0f, 300.0f, 0.0f);
    mDoMtx_stack_c::multVec(&top_offset, &m290);
    mDoMtx_stack_c::multVec(&m29C, &m2C0);
    cXyz zero(0.0f, 0.0f, 0.0f);
    mDoMtx_stack_c::multVec(&zero, &m304);

    mDoMtx_stack_c::quatM(&m2DC);
    mDoMtx_stack_c::scaleM(l_HIO.mScale);
    M_mdl->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);

    cXyz* chain_pos = m_chain->mPt;
    chain_pos[0] = m304;
    chain_pos[1] = m2C0;
    chain_pos[2] = current.pos;
}

/* 00000670-00000984       .text calc_weight__15daBalancelift_cFv */
void daBalancelift_c::calc_weight() {
    f32 target;
    if (m31C == 0) {
        if (*m318 == 0) {
            target = l_HIO.m28 - 0.5f * l_HIO.m24;
        } else if (*m318 > 0) {
            target = l_HIO.m28;
        } else {
            target = l_HIO.m28 - l_HIO.m24;
        }
        *m320 |= 1;
    } else {
        if (*m318 == 0) {
            target = l_HIO.m28 - 0.5f * l_HIO.m24;
        } else if (*m318 > 0) {
            target = l_HIO.m28 - l_HIO.m24;
        } else {
            target = l_HIO.m28;
        }
        *m320 |= 2;
    }

    if (*m320 == 3) {
        *m318 = 0;
        *m320 = 0;
    }

    f32 height = std::sqrtf(target * target - m29C.abs2XZ());
    m368 += 0.005f * (height - m310);
    m368 *= 0.92f;
    m310 += m368;

    cXyz delta = m2A8 - m29C;
    delta *= l_HIO.m20;
    m2B4 += delta;
    m2B4 *= l_HIO.m1C;
    m29C += m2B4;

    if (std::fabsf(m368 > 1.0f)) {
        mDoAud_seStart(JA_SE_OBJ_TENBIN_LIFT_MOVE, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
}

/* 00000984-000009A4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daBalancelift_c*)i_this)->CreateHeap();
}

/* 000009A4-00000BA0       .text CreateHeap__15daBalancelift_cFv */
BOOL daBalancelift_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTEN1_BDL_HTEN1_e);
    JUT_ASSERT(419, modelData != NULL);
    M_mdl = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    JUT_ASSERT(421, M_mdl != NULL);
    m_chain = dChain_packet_create(3, &tevStr, 2.0f);
    JUT_ASSERT(423, m_chain != NULL);
    pm_bgw = new dBgW();
    pm_bgw->Set((cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTEN1_DZB_HTEN1_e), cBgW::MOVE_BG_e, &mMtx);
    pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
    JUT_ASSERT(432, pm_bgw != NULL);
    return M_mdl != NULL && m_chain != NULL && pm_bgw != NULL;
}

/* 00000BA0-00000F34       .text CreateInit__15daBalancelift_cFv */
cPhs_State daBalancelift_c::CreateInit() {
    u8 path_id = fopAcM_GetParam(this) >> 16;
    if (path_id != 0xFF) {
        mpPath = dPath_GetRoomPath(path_id, fopAcM_GetRoomNo(this));
        if (mpPath != NULL && mpPath->m_num != 0) {
            current.pos = mpPath->m_points[0].m_position;
            home.pos = current.pos;
            if (mpPath->m_num > 1) {
                cXyz pos = mpPath->m_points[1].m_position;
                parentActorID = fopAcM_createChild(
                    fpcNm_Balancelift_e, fopAcM_GetID(this), -1, &pos, tevStr.mRoomNo, NULL, NULL, -1, NULL
                );
            }
        }
        m314 = 0;
        m31C = 0;
        m318 = &m314;
        m31E = 0;
        m320 = &m31E;
        m310 = l_HIO.m28 - 0.5f * l_HIO.m24;
    } else {
        m314 = 0;
        m31E = 0;
        if (parentActorID != fpcM_ERROR_PROCESS_ID_e) {
            daBalancelift_c* parent = (daBalancelift_c*)fopAcM_SearchByID(parentActorID);
            if (parent != NULL) {
                m31C = 1;
                m318 = &parent->m314;
                m320 = &parent->m31E;
            } else {
                m31C = 0;
                m318 = &m314;
                m320 = &m31E;
            }
        } else {
            m31C = 0;
            m318 = &m314;
            m320 = &m31E;
        }
        m310 = l_HIO.m28 - 0.5f * l_HIO.m24;
    }

    m368 = 0.0f;
    dComIfG_Bgsp()->Regist(pm_bgw, this);
    m2EC = current.pos;
    m2EC.y -= m310;
    m2F8 = cXyz::Zero;
    m2B4 = cXyz::Zero;
    m29C = cXyz::Zero;
    m2A8 = cXyz::Zero;
    m2CC = ZeroQuat;
    m2DC = ZeroQuat;
    scale.setall(2.0f);
    set_mtx();
    pm_bgw->SetRideCallback(ride_call_back);

    mStts.Init(0xC0, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.OnTgShield();
    mCyl.OnTgNoConHit();

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("天秤リフト", &l_HIO);
    }
    return cPhs_COMPLEATE_e;
}

cPhs_State daBalancelift_c::_create() {
    fopAcM_ct(this, daBalancelift_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xE40)) {
            phase_state = CreateInit();
        } else {
            return cPhs_ERROR_e;
        }
        fopAcM_SetMtx(this, M_mdl->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -150.0f, -150.0f, -150.0f, 150.0f, 1000.0f, 150.0f);
        cMtx_copy(M_mdl->getBaseTRMtx(), mMtx);
    }
    return phase_state;
}

/* 00000F34-000010E0       .text daBalanceliftCreate__FPv */
static cPhs_State daBalanceliftCreate(void* i_this) {
    return ((daBalancelift_c*)i_this)->_create();
}

bool daBalancelift_c::_delete() {
    dComIfG_Bgsp()->Release(pm_bgw);
    dComIfG_resDelete(&mPhase, M_arcname);
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return true;
}

/* 0000129C-00001318       .text daBalanceliftDelete__FPv */
static BOOL daBalanceliftDelete(void* i_this) {
    return ((daBalancelift_c*)i_this)->_delete();
}

/* 00001318-0000133C       .text daBalanceliftExecute__FPv */
static BOOL daBalanceliftExecute(void* i_this) {
    return ((daBalancelift_c*)i_this)->_execute();
}

/* 0000133C-000016F0       .text _execute__15daBalancelift_cFv */
bool daBalancelift_c::_execute() {
    calc_weight();
    calc_quat();
    set_mtx();
    pm_bgw->Move();
    mStts.Move();

    if (mCyl.ChkTgHit()) {
        fopAc_ac_c* hit_actor = mCyl.GetTgHitAc();
        cCcD_Obj* hit_obj = mCyl.GetTgHitObj();
        if (fopAc_IsActor(hit_actor) && fopAcM_GetProfName(hit_actor) == fpcNm_BOMB_e) {
            cXyz pos = m304;
            pos.y -= 50.0f;
            cXyz dir = pos - hit_actor->current.pos;
            if (!dir.normalizeRS()) {
                dir.set(0.0f, 0.0f, 1.0f);
            }
            m2F8 += dir * -20.0f;
            m368 += 2.0f * -dir.y;
        } else if (hit_obj != NULL) {
            cXyz dir = *mCyl.GetTgRVecP();
            if (!dir.normalizeRS()) {
                dir.set(0.0f, 0.0f, 1.0f);
            }
            if (hit_obj->ChkAtType(AT_TYPE_WIND)) {
                m2F8 += dir * -12.0f;
                m368 += 2.0f * -dir.y;
            } else if (hit_obj->ChkAtType(AT_TYPE_SWORD)) {
                m2F8 += dir * -8.0f;
                m368 += 2.0f * -dir.y;
                cXyz* hit_pos = mCyl.GetTgHitPosP();
                if (hit_pos != NULL) {
                    cXyz diff = *hit_pos - m304;
                    f32 dist = diff.abs();
                    m2B4 += dir * l_HIO.m18;
                    m2A8.y = dist;
                    m29C.y = dist;
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, hit_pos);
                }
                mDoAud_seStart(JA_SE_OBJ_COL_SWS_NMTLP, &eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            }
        }
    }

    mCyl.SetC(m304);
    dComIfG_Ccsp()->Set(&mCyl);
    return false;
}

bool daBalancelift_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(M_mdl, &tevStr);
    mDoExt_modelUpdateDL(M_mdl);
    j3dSys.getDrawBuffer(J3DSysDrawBuf_Opa)->entryImm(m_chain, 0);
    return true;
}

/* 000016F0-00001774       .text daBalanceliftDraw__FPv */
static BOOL daBalanceliftDraw(void* i_this) {
    return ((daBalancelift_c*)i_this)->_draw();
}

/* 00001774-0000177C       .text daBalanceliftIsDelete__FPv */
static BOOL daBalanceliftIsDelete(void*) {
    return TRUE;
}

static actor_method_class daBalanceliftMethodTable = {
    (process_method_func)daBalanceliftCreate,
    (process_method_func)daBalanceliftDelete,
    (process_method_func)daBalanceliftExecute,
    (process_method_func)daBalanceliftIsDelete,
    (process_method_func)daBalanceliftDraw,
};

actor_process_profile_definition g_profile_Balancelift = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Balancelift_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBalancelift_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Balancelift_e,
    /* Actor SubMtd */ &daBalanceliftMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
