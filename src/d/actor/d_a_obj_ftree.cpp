/**
 * d_a_obj_ftree.cpp
 * Object - Forest Trees
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ftree.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_kankyo.h"
#include "d/d_particle_name.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_lib.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"
#include "res/Object/Vmr.h"

namespace daObjFtree {

namespace {
struct Attr_c {
    /* 0x00 */ f32 mCylWRadius;
    /* 0x04 */ f32 mCylWHeight;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 mCylLRadius;
    /* 0x14 */ f32 mCylLHeight;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ s16 field_0x24;
    /* 0x28 */ f32 mScaleS;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 mCylWOffsetY;
    /* 0x38 */ f32 mWaterDist;
    /* 0x3C */ s16 mEventTimer;
    /* 0x40 */ f32 mTalkDist;
    /* 0x44 */ f32 mHeartSpeedF;
    /* 0x48 */ f32 mHeartSpeedY;
    /* 0x4C */ s16 mHeartAngleOffset;
    /* 0x50 */ f32 mHeartOffsetY;
    /* 0x54 */ f32 mHeartGravity;
    /* 0x58 */ s16 mLaunchTimer;
    /* 0x5A */ s16 field_0x5A;
    /* 0x5C */ s16 mChangeTimer;
}; // Size: 0x60

static const Attr_c L_attr = {
    61.0f, 96.0f, 25.0f, 52.0f, 132.0f, 950.0f, 72.0f, 37.0f, -37.0f, 20, 0.2f, 0.2f, 0.02f,
    50.0f, 20.0f, 140, 130.0f, 1.75f, 30.0f, 9000, 860.0f, -2.1f, 47, 0, 30,
};
} // namespace

static const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};

static const dCcD_SrcCyl M_cyl_srcW = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WATER,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};

u32 message_table[] = {
    0, 0x149F, 0x14A0, 0x14A1, 0, 0, 0, 0, 0, 0, 0x149F, 0x14A0, 0x14A1,
};

}; // namespace daObjFtree

/* 00000078-000000DC       .text search_heart_part__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::search_heart_part() {
    if (mHeartPartId != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* heart_part;
        if (!fopAcM_SearchByID(mHeartPartId, &heart_part)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2E20);
            mHeartPartId = fpcM_ERROR_PROCESS_ID_e;
        }
    }
}

/* 000000DC-000001F0       .text launch_heart_part__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::launch_heart_part() {
    csXyz angle = shape_angle;
    cXyz scale(1.0f, 1.0f, 1.0f);
    cXyz pos = current.pos;
    angle.y += 9000;
    pos.y += 860.0f;
    fopAc_ac_c* heart_part = (fopAc_ac_c*)fopAcM_fastCreateItem(&pos, dItemNo_HEART_PIECE_e, fopAcM_GetRoomNo(this), &angle, &scale,
                                                                1.75f, 30.0f, -2.1f, -1, NULL);
    if (heart_part != NULL) {
        mHeartPartId = fopAcM_GetID(heart_part);
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_9B07, param_get_tree_idx());
        heart_part->actor_status = 0x4040;
        mHeartPlaced = 1;
        return TRUE;
    }
    return FALSE;
}

/* 000001F0-00000394       .text place_heart_part__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::place_heart_part() {
    if (mXyEventIdx == -1 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_0102) == TRUE &&
        !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E20) &&
        param_get_tree_idx() == dComIfGs_getEventReg(dSv_event_flag_c::UNK_9B07))
    {
        cXyz offset(0.0f, 1.0f, 310.0f);
        s16 angle_y = shape_angle.y + 9000;
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(angle_y);
        Mtx mtx;
        MTXCopy(mDoMtx_stack_c::get(), mtx);
        cXyz pos;
        MTXMultVec(mtx, &offset, &pos);
        cXyz scale(1.0f, 1.0f, 1.0f);
        csXyz angle(0, 0, 0);
        fopAc_ac_c* heart_part = (fopAc_ac_c*)fopAcM_fastCreateItem(&pos, dItemNo_HEART_PIECE_e, fopAcM_GetRoomNo(this), &angle, &scale,
                                                                    0.0f, 0.0f, -2.1f, -1, NULL);
        if (heart_part != NULL) {
            mHeartPartId = fopAcM_GetID(heart_part);
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_9B07, param_get_tree_idx());
            return TRUE;
        }
    }
    return FALSE;
}

/* 00000394-00000454       .text Ftree_get_water_pos__10daObjFtreeFP4cXyzP4cXyz */
void daObjFtree::Ftree_get_water_pos(cXyz* o_pos, cXyz* i_pos) {
    cXyz offset(0.0f, 0.0f, 50.0f);
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    s16 angle = cM_atan2s(i_pos->x - player->current.pos.x, i_pos->z - player->current.pos.z);
    mDoMtx_stack_c::transS(player->current.pos);
    mDoMtx_stack_c::YrotM(angle);
    Mtx mtx;
    MTXCopy(mDoMtx_stack_c::get(), mtx);
    MTXMultVec(mtx, &offset, o_pos);
}

/* 00000454-000004B8       .text estimate_water__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::estimate_water() {
    cXyz water_pos;
    Ftree_get_water_pos(&water_pos, &current.pos);
    return water_pos.abs2(current.pos) <= (20.0f + mCylR) * (20.0f + mCylR);
}

/* 000004B8-000004DC       .text Ftree_checkXyEventCallBack__10daObjFtreeFPvi */
s16 daObjFtree::Ftree_checkXyEventCallBack(void*, int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == dItemNo_FOREST_WATER_e ? TRUE : FALSE;
}

/* 000004DC-000004FC       .text Ftree_XyEventCallBack__10daObjFtreeFPvi */
s16 daObjFtree::Ftree_XyEventCallBack(void* i_this, int i_itemBtn) {
    return ((Act_c*)i_this)->XyEventCallBack(i_itemBtn);
}

/* 000004FC-000005E4       .text XyEventCallBack__Q210daObjFtree5Act_cFi */
s16 daObjFtree::Act_c::XyEventCallBack(int i_itemBtn) {
    if (dComIfGp_getSelectItem(i_itemBtn) == dItemNo_FOREST_WATER_e && !is_brought() && estimate_water()) {
        if (!iam_last()) {
            if (XyEvent_set(mEventCam1Idx)) {
                mEventTimer = 140;
                return mEventCam1Idx;
            }
        } else {
            if (XyEvent_set(mEventCam2Idx)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0102);
                mEventTimer = 140;
                return mEventCam2Idx;
            }
        }
    }

    if (XyEvent_set(mEventCam0Idx)) {
        return mEventCam0Idx;
    }
    return -1;
}

/* 000005E4-000005F8       .text XyEvent_init__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::XyEvent_init() {
    mXyEventIdx = -1;
    mXyEventState = 0;
}

/* 000005F8-0000062C       .text XyEvent_set__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::XyEvent_set(s16 i_eventIdx) {
    if (mXyEventState == 0 && i_eventIdx != -1) {
        mXyEventIdx = i_eventIdx;
        mXyEventState = 1;
        return TRUE;
    }
    return FALSE;
}

/* 0000062C-00000764       .text XyEvent_exe__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::XyEvent_exe() {
    switch (mXyEventState) {
    case 1:
        if (eventInfo.checkCommandTalk()) {
            mXyEventState = 2;
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            cXyz offset(0.0f, 1.0f, 108.0f);
            s16 angle_y = shape_angle.y + 9000;
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(angle_y);
            Mtx mtx;
            MTXCopy(mDoMtx_stack_c::get(), mtx);
            cXyz pos;
            MTXMultVec(mtx, &offset, &pos);
            player->setPlayerPosAndAngle(&pos, angle_y + 0x8000);
        }
        break;
    case 2:
        if (dComIfGp_evmng_endCheck(mXyEventIdx)) {
            dComIfGp_event_reset();
            XyEvent_init();
        }
        break;
    }
}

namespace daObjFtree {
static const u8 ret_tree_no[] = {
    15, 0, 1, 2, 3, 4, 5, 15, 6, 7,
};
}; // namespace daObjFtree

/* 00000764-000007A8       .text param_get_tree_idx__Q210daObjFtree5Act_cCFv */
inline int daObjFtree::Act_c::param_get_tree_idx() const {
    static const u8 ret_num = ARRAY_SIZE(ret_tree_no);
    int idx = daObj::PrmAbstract(this, 4, 0);
    if (idx < ret_num) {
        return ret_tree_no[idx];
    }
    return 15;
}

/* 000007A8-000008D8       .text SetJointAnimation__Q210daObjFtree5Act_cFiffi */
BOOL daObjFtree::Act_c::SetJointAnimation(int i_bckIdx, f32 i_speed, f32 i_morf, int i_endOffset) {
    J3DAnmTransform* bck = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, i_bckIdx);
    int end_offset = i_endOffset > 0 ? 0 : i_endOffset;
    if (bck != NULL) {
        if (end_offset == 0) {
            mpMorf->setAnm(bck, J3DFrameCtrl::EMode_NONE, i_morf, i_speed, 0.0f, -1.0f, NULL);
        } else {
            mpMorf->setAnm(bck, J3DFrameCtrl::EMode_NONE, i_morf, i_speed, 0.0f, (f32)end_offset + (f32)bck->getFrameMax(), NULL);
        }
        return TRUE;
    }
    return FALSE;
}

/* 000008D8-00000910       .text PlayStopJointAnimation__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::PlayStopJointAnimation() {
    return mpMorf->play(NULL, 0, 0) ? TRUE : FALSE;
}

/* 00000910-0000093C       .text PlayStopColorAnimation__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::PlayStopColorAnimation() {
    return mBrkAnm.play() ? TRUE : FALSE;
}

/* 0000093C-00000A1C       .text set_first_stat__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_first_stat() {
    if (dComIfGs_isSymbol(dSymbol_FARORE_e)) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0102)) {
            process_init(MODE_WAIT_L_e, 0);
            mScaleL = 1.0f;
        } else if (!is_brought()) {
            process_init(MODE_WAIT_S_e, 0);
            mScaleL = 0.2f;
        } else {
            process_init(MODE_WAIT_M_e, 0);
            mScaleL = 0.2f;
        }
    } else {
        process_init(MODE_NONE_e, 0);
    }
}

/* 00000A1C-00000C1C       .text set_collision__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_collision() {
    if (mDrawS == 1 || mDrawL == 1) {
        if (mCyl.ChkTgHit()) {
            if (mDrawS == 1) {
                daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), &mCyl, 8);
            } else {
                daObj::HitSeStart(&current.pos, fopAcM_GetRoomNo(this), &mCyl, 7);
                daObj::HitEff_kikuzu(this, &mCyl);
            }
            dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
            mCyl.ClrTgHit();
        } else if (mDrawS == 1) {
            cXyz pos = current.pos;
            pos.y -= 50.0f;
            mCylW.SetR(61.0f);
            mCylW.SetH(96.0f);
            mCylW.SetC(pos);
            dComIfG_Ccsp()->Set(&mCylW);
            mCylR = 61.0f;
            mCyl.SetR(61.0f);
            mCyl.SetH(96.0f);
            mCyl.SetC(current.pos);
            dComIfG_Ccsp()->Set(&mCyl);
        } else if (mDrawL == 1) {
            mCylR = 132.0f * mScaleL;
            mCyl.SetR(mCylR);
            mCyl.SetH(950.0f * mScaleL);
            mCyl.SetC(current.pos);
            dComIfG_Ccsp()->Set(&mCyl);
        }
    }
}

/* 00000C1C-00000D50       .text talk_ct__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::talk_ct() {
    mMsgId = fpcM_ERROR_PROCESS_ID_e;
    mpMsg = NULL;
    cXyz attn_pos = current.pos;
    cXyz eye_pos = current.pos;
    if (mMode >= 0 && mMode < (int)ARRAY_SIZE(message_table)) {
        switch (message_table[mMode]) {
        case 0x149F:
            eye_pos.y += 80.0f;
            attn_pos.y += 105.0f;
            attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_TALKFLAG_LOOK_e;
            break;
        case 0x14A0:
            eye_pos.y += 90.0f;
            attn_pos.y += 195.0f;
            attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_TALKFLAG_LOOK_e;
            break;
        case 0x14A1:
            eye_pos.y += 250.0f;
            attn_pos.y += 200.0f;
            attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_TALKFLAG_LOOK_e;
            break;
        }
    }
    attention_info.position = attn_pos;
    eyePos = eye_pos;
}

/* 00000D50-00000F14       .text talk_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::talk_main() {
    if (mXyEventIdx == -1 && eventInfo.checkCommandTalk()) {
        if (mMsgId == fpcM_ERROR_PROCESS_ID_e) {
            mMsgId = fopMsgM_messageSet(message_table[mMode], this);
            mpMsg = NULL;
        } else if (mpMsg == NULL) {
            mpMsg = fopMsgM_SearchByID(mMsgId);
        } else {
            switch (mpMsg->mStatus) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpMsg->mStatus = fopMsgStts_MSG_ENDS_e;
                break;
            case fopMsgStts_BOX_CLOSED_e:
                mpMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                dComIfGp_event_reset();
                talk_ct();
                break;
            }
        }
    } else if (mMode >= 0 && mMode < (int)ARRAY_SIZE(message_table) && message_table[mMode] != 0) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        if (current.pos.abs2(player->current.pos) <= (130.0f + mCylR) * (130.0f + mCylR)) {
            talk_ct();
            player = dComIfGp_getPlayer(0);
            if (player != NULL) {
                cXyz diff = current.pos - player->current.pos;
                s16 angle = cM_atan2s(diff.x, diff.z) - player->shape_angle.y;
                if ((angle <= 0 ? -angle : angle) <= 0x4000) {
                    eventInfo.onCondition(dEvtCnd_CANTALK_e);
                }
            }
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        }
    }
}

/* 00000F14-00000FC4       .text get_tev_material0_color__Q210daObjFtree5Act_cFP12J3DModelDataUlPsPsPs */
void daObjFtree::Act_c::get_tev_material0_color(J3DModelData* i_modelData, u32 i_no, s16* o_r, s16* o_g, s16* o_b) {
    J3DMaterial* material = i_modelData->getJointNodePointer(0)->getMesh();
    if (material != NULL) {
        *o_r = material->getTevColor(i_no)->mColor.r;
        *o_g = material->getTevColor(i_no)->mColor.g;
        *o_b = material->getTevColor(i_no)->mColor.b;
    }
}

/* 00000FC4-00001070       .text set_tev_color__Q210daObjFtree5Act_cFP12J3DModelDataUlsss */
void daObjFtree::Act_c::set_tev_color(J3DModelData* i_modelData, u32 i_no, s16 i_r, s16 i_g, s16 i_b) {
    for (J3DMaterial* material = i_modelData->getJointNodePointer(0)->getMesh(); material != NULL; material = material->getNext()) {
        material->getTevColor(i_no)->mColor.r = i_r;
        material->getTevColor(i_no)->mColor.g = i_g;
        material->getTevColor(i_no)->mColor.b = i_b;
    }
}

/* 00001070-000010F0       .text is_broughtID__10daObjFtreeFi */
BOOL daObjFtree::is_broughtID(int i_id) {
    return ((dComIfGs_getEventReg(dSv_event_flag_c::UNK_9EFF) >> (i_id & 7)) & 1) || dComIfGs_isEventBit(dSv_event_flag_c::UNK_0102);
}

/* 000010F0-00001138       .text is_brought__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::is_brought() {
    return is_broughtID(param_get_tree_idx());
}

/* 00001138-000011FC       .text set_broughtID__Q210daObjFtree5Act_cFi */
void daObjFtree::Act_c::set_broughtID(int i_id) {
    u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_9EFF);
    reg |= 1 << (i_id & 7);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_9EFF, reg);
    reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_9AFF);
    reg |= 1 << (i_id & 7);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_9AFF, reg);
    _ftree_seach_info_ info;
    get_ftree_info(&info);
    if (info.mBroughtNum == info.mTotal) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0102);
    }
}

/* 000011FC-00001260       .text set_brought__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_brought() {
    set_broughtID(param_get_tree_idx());
    mBrought = TRUE;
}

/* 00001260-000012D0       .text unset_broughtID__Q210daObjFtree5Act_cFi */
void daObjFtree::Act_c::unset_broughtID(int i_id) {
    u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_9EFF);
    reg &= ~(1 << (i_id & 7));
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_9EFF, reg);
}

/* 000012D0-00001334       .text unset_brought__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::unset_brought() {
    unset_broughtID(param_get_tree_idx());
    mBrought = FALSE;
}

/* 00001334-000013A0       .text get_ftree_info__Q210daObjFtree5Act_cFPQ210daObjFtree18_ftree_seach_info_ */
void daObjFtree::Act_c::get_ftree_info(daObjFtree::_ftree_seach_info_* o_info) {
    o_info->mTotal = 8;
    o_info->mBroughtNum = 0;
    for (u32 i = 0; i < 8; i++) {
        if (is_broughtID(i)) {
            o_info->mBroughtNum++;
        }
    }
}

/* 000013A0-00001400       .text iam_last__Q210daObjFtree5Act_cFv */
BOOL daObjFtree::Act_c::iam_last() {
    _ftree_seach_info_ info;
    get_ftree_info(&info);
    if (!is_brought() && info.mBroughtNum >= info.mTotal - 1) {
        return TRUE;
    }
    return FALSE;
}

/* 00001400-00001414       .text action_none_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_none_init(s16) {
    mDrawS = 0;
    mDrawL = 0;
    return TRUE;
}

/* 00001414-00001418       .text action_none_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_none_main() {
}

/* 00001418-000014E8       .text action_waitS_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_waitS_init(s16) {
    mDrawS = 1;
    mDrawL = 0;
    unset_brought();
    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e);
    if (brk != NULL && mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE)) {
        return SetJointAnimation(dRes_INDEX_VMR_BCK_VMRTY_e, 1.0f, 0.0f, 0);
    }
    return FALSE;
}

/* 000014E8-00001608       .text action_waitS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitS_main() {
    if (mEventTimer == 1) {
        BOOL ret;
        if (mXyEventIdx == mEventCam2Idx) {
            ret = process_init(MODE_CHANGE_SL_e, 0);
        } else {
            ret = process_init(MODE_CHANGE_SM_e, 0);
        }
        if (ret) {
            mEventTimer = 0;
            return;
        }
    }

    int co_hit = mCyl.ChkCoHit();
    if (mPrevCoHit == 0 && co_hit == 1 && process_init(MODE_PIKUPIKU_S_e, 1)) {
        co_hit = 0;
    } else if ((int)cM_rndF(100.0f) == 0 && mMode == MODE_WAIT_S_e) {
        process_init(MODE_PIKUPIKU_S_e, 1.0f + 4.0f * cM_rndF(1.0f));
    }
    mPrevCoHit = co_hit;
}

/* 00001608-0000173C       .text action_waitM_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_waitM_init(s16) {
    set_brought();
    mDrawS = 1;
    mDrawL = 0;
    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e);
    if (brk != NULL && mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_NONE, -1.0f, 0, -1, true, FALSE) &&
        SetJointAnimation(dRes_INDEX_VMR_BCK_VMRMZ_e, -1.0f, 0.0f, 0))
    {
        mpMorf->setFrame(mpMorf->getEndFrame() - 1.0f);
        return TRUE;
    }
    return FALSE;
}

/* 0000173C-00001878       .text action_waitM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitM_main() {
    if (dComIfGs_getFwaterTimer() == 0) {
        _ftree_seach_info_ info;
        get_ftree_info(&info);
        if (info.mTotal != info.mBroughtNum) {
            process_init(MODE_CHANGE_MS_e, 0);
            return;
        }
    }

    if (mMode == MODE_WAIT_M_e) {
        int co_hit = mCyl.ChkCoHit();
        if (dKy_rain_check()) {
            process_init(MODE_PIKUPIKU_M_e, -1);
        } else if (mPrevCoHit == 0 && co_hit == 1 && process_init(MODE_PIKUPIKU_M_e, 120)) {
            co_hit = 0;
        } else if ((int)cM_rndF(90.0f) == 0) {
            process_init(MODE_PIKUPIKU_M_e, 30.0f + 90.0f * cM_rndF(1.0f));
        }
        mPrevCoHit = co_hit;
    }
}

/* 00001878-000018AC       .text action_waitL_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_waitL_init(s16) {
    mDrawL = 1;
    mDrawS = 0;
    set_brought();
    return TRUE;
}

/* 000018AC-000019BC       .text action_waitL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_waitL_main() {
    if (mMode == MODE_WAIT_L_e) {
        if (dKy_rain_check()) {
            process_init(MODE_PIKUPIKU_L_e, -1);
        } else if ((int)cM_rndF(30.0f) == 0) {
            process_init(MODE_PIKUPIKU_L_e, 100.0f + 80.0f * cM_rndF(1.0f));
        } else if (mXyEventIdx != -1) {
            process_init(MODE_PIKUPIKU_L_e, -1);
        }
    } else if (mMode == MODE_PIKUPIKU_L_e) {
        if (!dKy_rain_check() && mPikuNumL == -1 && mXyEventIdx == -1) {
            process_init(MODE_WAIT_L_e, 0);
        }
    }
}

/* 000019BC-00001A4C       .text action_pikupikuS_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_pikupikuS_init(s16 i_num) {
    i_num = i_num > 0 ? i_num : 1;
    mDrawS = 1;
    mDrawL = 0;
    mPikuNumS = i_num;
    mPikuCntS = 0;
    return SetJointAnimation(dRes_INDEX_VMR_BCK_VMRTY_e, 0.7f + (1.2f - 0.7f) * cM_rndF(1.0f), 10.0f, 0);
}

/* 00001A4C-00001AF4       .text action_pikupikuS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuS_main() {
    if (PlayStopJointAnimation()) {
        if (mPikuCntS < mPikuNumS) {
            SetJointAnimation(dRes_INDEX_VMR_BCK_VMRTY_e, 0.7f + 0.3f * cM_rndF(1.0f), 10.0f, 0);
        } else {
            process_init(MODE_WAIT_S_e, 0);
        }
        mPikuCntS++;
    }
    action_waitS_main();
}

/* 00001AF4-00001B4C       .text action_pikupikuM_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_pikupikuM_init(s16 i_num) {
    set_brought();
    mPikuNumM = i_num;
    mPikuCntM = 0;
    mPikuPhaseM = 0;
    mDrawS = 1;
    mDrawL = 0;
    return TRUE;
}

/* 00001B4C-00001C44       .text action_pikupikuM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuM_main() {
    if (mPikuCntM < mPikuNumM || mPikuNumM == -1) {
        mTargetAngleMX = 100.0f * cM_ssin(mPikuPhaseM);
        mTargetAngleMY = 300.0f * cM_ssin(mPikuPhaseM);
        mPikuPhaseM += 4000;
    } else if (mPikuCntM >= mPikuNumM) {
        process_init(MODE_WAIT_M_e, 0);
    }
    mPikuCntM++;
    action_waitM_main();
}

/* 00001C44-00001C9C       .text action_pikupikuL_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_pikupikuL_init(s16 i_num) {
    set_brought();
    mPikuNumL = i_num;
    mPikuCntL = 0;
    mPikuPhaseL = 0;
    mDrawS = 0;
    mDrawL = 1;
    return TRUE;
}

/* 00001C9C-00001D94       .text action_pikupikuL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_pikupikuL_main() {
    if (mPikuCntL < mPikuNumL || mPikuNumL == -1) {
        mTargetAngleLY = 30.0f * cM_ssin(mPikuPhaseL);
        mTargetAngleLZ = 36.0f * cM_ssin(mPikuPhaseL);
        mPikuPhaseL += 3000;
    } else if (mPikuCntL >= mPikuNumL) {
        process_init(MODE_WAIT_L_e, 0);
    }
    mPikuCntL++;
    action_waitL_main();
}

/* 00001D94-00001EAC       .text action_changeSL_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_changeSL_init(s16) {
    mDrawS = 1;
    mDrawL = 0;
    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e));
    if (brk != NULL && mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE) &&
        SetJointAnimation(dRes_INDEX_VMR_BCK_VMRMZ_e, 1.0f, 10.0f, 0))
    {
        set_brought();
        mDoAud_seStart(JA_SE_OBJ_DK_TREE_RECOVER, &current.pos, 0, 0);
        return TRUE;
    }
    return FALSE;
}

/* 00001EAC-00001F0C       .text action_changeSL_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSL_main() {
    BOOL joint_end = PlayStopJointAnimation();
    BOOL color_end = PlayStopColorAnimation();
    if (joint_end == TRUE && color_end == TRUE) {
        process_init(MODE_CHANGE_SL2_e, 0);
    }
}

/* 00001F0C-00001FB4       .text action_changeSL2_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_changeSL2_init(s16) {
    mDrawS = 1;
    mDrawL = 0;
    mEffectFlag = 1;
    mColorRateS = 0.0f;
    mChangeTimer = 30;
    mScaleL = 0.2f;
    get_tev_material0_color(mpMorf->getModel()->getModelData(), 2, &mStartColorS.r, &mStartColorS.g, &mStartColorS.b);
    mCurColorS = mStartColorS;
    mPikuPhaseL = 0;
    return TRUE;
}

/* 00001FB4-00002300       .text action_changeSL2_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSL2_main() {
    if (mDrawS) {
        cLib_addCalc(&mColorRateS, 1.0f, 0.2f, 1.0f, 0.007f);
        mCurColorS.r = mStartColorS.r + (255.0f - mStartColorS.r) * mColorRateS;
        mCurColorS.g = mStartColorS.g + (255.0f - mStartColorS.g) * mColorRateS;
        mCurColorS.b = mStartColorS.b + (255.0f - mStartColorS.b) * mColorRateS;
        if (1.0f == mColorRateS) {
            if (mChangeTimer > 0) {
                mChangeTimer--;
            }
            if (mChangeTimer == 0) {
                mDrawS = 0;
                mDrawL = 1;
            }
        }
    }

    if (mDrawL) {
        f32 rate = GetRate(mScaleL, 0.2f, 1.0f);
        cLib_addCalc(&mScaleL, 1.0f, 0.02f, 1.0f, 0.005f);
        mCurColorL.r = 255.0f + (mColorL.r - 255.0f) * rate;
        mCurColorL.g = 255.0f + (mColorL.g - 255.0f) * rate;
        mCurColorL.b = 255.0f + (mColorL.b - 255.0f) * rate;
        if (1.0f == mScaleL && process_init(MODE_WAIT_L_e, 0)) {
            mLaunchTimer = 47;
        }
        mTargetAngleLY = 30.0f * cM_ssin(mPikuPhaseL);
        mTargetAngleLZ = 36.0f * cM_ssin(mPikuPhaseL);
        mPikuPhaseL += 3000;
    }
}

/* 00002300-00002344       .text action_changeLS_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_changeLS_init(s16) {
    mDrawS = 0;
    mDrawL = 1;
    mColorRateS = 1.0f;
    mScaleL = 1.0f;
    unset_brought();
    return TRUE;
}

/* 00002344-000025DC       .text action_changeLS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeLS_main() {
    if (mDrawL) {
        f32 rate = GetRate(mScaleL, 0.2f, 1.0f);
        cLib_addCalc(&mScaleL, 0.2f, 0.02f, 1.0f, 0.005f);
        mCurColorL.r = 255.0f + (mColorL.r - 255.0f) * rate;
        mCurColorL.g = 255.0f + (mColorL.g - 255.0f) * rate;
        mCurColorL.b = 255.0f + (mColorL.b - 255.0f) * rate;
        if (0.2f == mScaleL) {
            mDrawS = 1;
            mDrawL = 0;
        }
    }

    if (mDrawS) {
        cLib_addCalc(&mColorRateS, 0.0f, 0.2f, 1.0f, 0.007f);
        mCurColorS.r = mStartColorS.r + (255.0f - mStartColorS.r) * mColorRateS;
        mCurColorS.g = mStartColorS.g + (255.0f - mStartColorS.g) * mColorRateS;
        mCurColorS.b = mStartColorS.b + (255.0f - mStartColorS.b) * mColorRateS;
        if (0.0f == mColorRateS) {
            process_init(MODE_CHANGE_LS2_e, 0);
        }
    }
}

/* 000025DC-000026AC       .text action_changeLS2_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_changeLS2_init(s16) {
    mDrawS = 1;
    mDrawL = 0;
    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e);
    if (brk != NULL && mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_NONE, -1.0f, 0, -1, true, FALSE)) {
        return SetJointAnimation(dRes_INDEX_VMR_BCK_VMRMZ_e, -0.7f, 10.0f, -20);
    }
    return FALSE;
}

/* 000026AC-0000270C       .text action_changeLS2_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeLS2_main() {
    BOOL joint_end = PlayStopJointAnimation();
    BOOL color_end = PlayStopColorAnimation();
    if (joint_end == TRUE && color_end == TRUE) {
        process_init(MODE_WAIT_S_e, 0);
    }
}

/* 0000270C-00002794       .text action_changeSM_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_changeSM_init(s16) {
    set_brought();
    if (action_changeSL_init(0) == TRUE) {
        mDoAud_seStart(JA_SE_OBJ_DK_TREE_RECOVER, &current.pos, 0, 0);
        return TRUE;
    }
    return FALSE;
}

/* 00002794-000027F4       .text action_changeSM_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeSM_main() {
    BOOL joint_end = PlayStopJointAnimation();
    BOOL color_end = PlayStopColorAnimation();
    if (joint_end == TRUE && color_end == TRUE) {
        process_init(MODE_WAIT_M_e, 0);
    }
}

/* 000027F4-00002840       .text action_changeMS_init__Q210daObjFtree5Act_cFs */
BOOL daObjFtree::Act_c::action_changeMS_init(s16) {
    if (action_changeLS2_init(0)) {
        unset_brought();
        return TRUE;
    }
    return FALSE;
}

/* 00002840-00002860       .text action_changeMS_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::action_changeMS_main() {
    action_changeLS2_main();
}

/* 00002860-00002A4C       .text process_init__Q210daObjFtree5Act_cFis */
BOOL daObjFtree::Act_c::process_init(int i_mode, s16 i_prm) {
    typedef BOOL (daObjFtree::Act_c::*initProc)(s16);
    static initProc init_table[] = {
        &daObjFtree::Act_c::action_none_init,
        &daObjFtree::Act_c::action_waitS_init,
        &daObjFtree::Act_c::action_waitM_init,
        &daObjFtree::Act_c::action_waitL_init,
        &daObjFtree::Act_c::action_changeSL_init,
        &daObjFtree::Act_c::action_changeSL2_init,
        &daObjFtree::Act_c::action_changeLS_init,
        &daObjFtree::Act_c::action_changeLS2_init,
        &daObjFtree::Act_c::action_changeSM_init,
        &daObjFtree::Act_c::action_changeMS_init,
        &daObjFtree::Act_c::action_pikupikuS_init,
        &daObjFtree::Act_c::action_pikupikuM_init,
        &daObjFtree::Act_c::action_pikupikuL_init,
    };

    if (i_mode >= 0 && i_mode < MODE_MAX_e && (this->*init_table[i_mode])(i_prm)) {
        mTargetAngleMX = 0;
        mTargetAngleMY = 0;
        mTargetAngleLY = 0;
        mTargetAngleLZ = 0;
        mMode = i_mode;
        return TRUE;
    }
    return FALSE;
}

/* 00002A4C-00002BF0       .text process_main__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::process_main() {
    typedef void (daObjFtree::Act_c::*mainProc)();
    static mainProc main_table[] = {
        &daObjFtree::Act_c::action_none_main,
        &daObjFtree::Act_c::action_waitS_main,
        &daObjFtree::Act_c::action_waitM_main,
        &daObjFtree::Act_c::action_waitL_main,
        &daObjFtree::Act_c::action_changeSL_main,
        &daObjFtree::Act_c::action_changeSL2_main,
        &daObjFtree::Act_c::action_changeLS_main,
        &daObjFtree::Act_c::action_changeLS2_main,
        &daObjFtree::Act_c::action_changeSM_main,
        &daObjFtree::Act_c::action_changeMS_main,
        &daObjFtree::Act_c::action_pikupikuS_main,
        &daObjFtree::Act_c::action_pikupikuM_main,
        &daObjFtree::Act_c::action_pikupikuL_main,
    };

    if (mMode >= 0 && mMode < MODE_MAX_e) {
        (this->*main_table[mMode])();
    }
}

char daObjFtree::Act_c::M_arcname[] = "Vmr";

/* 00002BF0-00002C14       .text solidHeapCB__Q210daObjFtree5Act_cFP10fopAc_ac_c */
BOOL daObjFtree::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 00002C14-00002D94       .text NodeCallBack_Effect__Q210daObjFtree5Act_cFP7J3DNodei */
BOOL daObjFtree::Act_c::NodeCallBack_Effect(J3DNode* i_node, int i_calcTiming) {
    if (mEffectFlag == 1 && i_calcTiming == J3DNodeCBCalcTiming_In) {
        cXyz offset(0.0f, 0.0f, 0.0f);
        cXyz pos;
        mDoMtx_stack_c::copy(j3dSys.getModel()->getAnmMtx(((J3DJoint*)i_node)->getJntNo()));
        Mtx mtx;
        MTXCopy(mDoMtx_stack_c::get(), mtx);
        MTXMultVec(mtx, &offset, &pos);
        mDoAud_seStart(JA_SE_OBJ_DK_TREE_GROW_UP, &current.pos, 0, 0);
        JPABaseEmitter* emitter0 = dComIfGp_particle_set(dPa_name::ID_AK_SN_HANASAKAFLASH00, &pos);
        JPABaseEmitter* emitter1 = dComIfGp_particle_set(dPa_name::ID_AK_SN_HANASAKAFLASH01, &pos);
        if (emitter0 != NULL && emitter1 != NULL) {
            mEffectFlag = 0;
        }
    }
    return TRUE;
}

/* 00002D94-00002DDC       .text Ftree_NodeCallBack_Effect__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_Effect(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        return ((Act_c*)j3dSys.getModel()->getUserArea())->NodeCallBack_Effect(i_node, i_calcTiming);
    }
    return TRUE;
}

/* 00002DDC-00002E9C       .text Ftree_NodeCallBack_M__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_M(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        Act_c* i_this = (Act_c*)model->getUserArea();
        if (i_this != NULL) {
            csXyz angle(i_this->mAngleMX, i_this->mAngleMY, 0);
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::ZXYrotM(angle);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
            MTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00002E9C-00002F5C       .text Ftree_NodeCallBack_L__10daObjFtreeFP7J3DNodei */
BOOL daObjFtree::Ftree_NodeCallBack_L(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        Act_c* i_this = (Act_c*)model->getUserArea();
        if (i_this != NULL) {
            csXyz angle(0, i_this->mAngleLY, i_this->mAngleLZ);
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::ZXYrotM(angle);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
            MTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00002F5C-00003354       .text create_heap__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::create_heap() {
    J3DAnmTransform* tmp_bck_data = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BCK_VMRTY_e);
    JUT_ASSERT(2102, tmp_bck_data != NULL);

    J3DModelData* mdl_dataS = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BDL_VMRTY_e);
    JUT_ASSERT(2108, mdl_dataS != NULL);
    if (mdl_dataS == NULL) {
        return false;
    }

    mpMorf = new mDoExt_McaMorf(mdl_dataS, NULL, NULL, tmp_bck_data, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);
    if (mpMorf == NULL) {
        return false;
    }
    mpMorf->getModel()->setUserArea((uintptr_t)this);
    mdl_dataS->getJointNodePointer(2)->setCallBack(Ftree_NodeCallBack_Effect);
    mdl_dataS->getJointNodePointer(3)->setCallBack(Ftree_NodeCallBack_M);
    mdl_dataS->getJointNodePointer(4)->setCallBack(Ftree_NodeCallBack_M);
    mdl_dataS->getJointNodePointer(5)->setCallBack(Ftree_NodeCallBack_M);

    J3DModelData* mdl_dataL = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BDL_VMRTO_e);
    JUT_ASSERT(2139, mdl_dataL != NULL);
    if (mdl_dataL == NULL) {
        return false;
    }

    mpModelL = mDoExt_J3DModel__create(mdl_dataL, 0, 0x11020203);
    if (mpModelL == NULL) {
        return false;
    }
    mpModelL->setUserArea((uintptr_t)this);
    mdl_dataL->getJointNodePointer(1)->setCallBack(Ftree_NodeCallBack_L);

    J3DAnmTevRegKey* brk_data = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VMR_BRK_VMRMZ_e);
    JUT_ASSERT(2155, brk_data != NULL);
    if (brk_data == NULL) {
        return false;
    }

    int brk_ret = mBrkAnm.init(mdl_dataS, brk_data, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE);

    get_tev_material0_color(mpMorf->getModel()->getModelData(), 2, &mColorS.r, &mColorS.g, &mColorS.b);
    mCurColorS = mColorS;
    get_tev_material0_color(mpModelL->getModelData(), 2, &mColorL.r, &mColorL.g, &mColorL.b);
    mCurColorL = mColorL;

    return mdl_dataS != NULL && mpMorf != NULL && mpMorf->getModel() != NULL && mdl_dataL != NULL && brk_data != NULL && brk_ret;
}

/* 00003354-000035F4       .text _create__Q210daObjFtree5Act_cFv */
cPhs_State daObjFtree::Act_c::_create() {
    fopAcM_ct(this, daObjFtree::Act_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            mTreeIdx = param_get_tree_idx();
            mHeartPlaced = 0;
            mHeartPartId = fpcM_ERROR_PROCESS_ID_e;
            set_first_stat();
            talk_ct();

            cXyz pos(current.pos.x, current.pos.y + 100.0f, current.pos.z);
            mGndChk.SetPos(&pos);
            mGndChk.SetActorPid(fopAcM_GetID(this));
            mGroundY = dComIfG_Bgsp()->GroundCross(&mGndChk);

            set_mtx();
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -300.0f, 0.0f, -300.0f, 300.0f, 1000.0f, 300.0f);

            mStatusW.Init(0xFF, 0xFF, this);
            mCylW.Set(M_cyl_srcW);
            mCylW.SetStts(&mStatusW);
            mCylW.SetTgVec((cXyz&)cXyz::Zero);
            mCylW.OnTgNoHitMark();

            mStatus.Init(0xFF, 0xFF, this);
            mCyl.Set(M_cyl_src);
            mCyl.SetStts(&mStatus);
            mCyl.SetTgVec((cXyz&)cXyz::Zero);
            mCyl.OnTgNoHitMark();

            XyEvent_init();
            eventInfo.setXyCheckCB(Ftree_checkXyEventCallBack);
            eventInfo.setXyEventCB(Ftree_XyEventCallBack);
            mEventCam0Idx = dComIfGp_evmng_getEventIdx("morinoki_camera0");
            mEventCam1Idx = dComIfGp_evmng_getEventIdx("morinoki_camera1");
            mEventCam2Idx = dComIfGp_evmng_getEventIdx("morinoki_camera2");
        } else {
            ret = cPhs_ERROR_e;
        }
    }
    return ret;
}

/* 00003FB8-00004004       .text _delete__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_delete() {
    if (mBrought) {
        set_brought();
    }
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00004004-00004144       .text set_mtx__Q210daObjFtree5Act_cFv */
void daObjFtree::Act_c::set_mtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);

    cXyz scale_l(scale.x * mScaleL, scale.y * mScaleL, scale.z * mScaleL);
    mpModelL->setBaseScale(scale_l);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModelL->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
    mpModelL->calc();
}

/* 00004144-000042C4       .text _execute__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_execute() {
    if (mMode == MODE_NONE_e) {
        return true;
    }

    search_heart_part();
    talk_main();
    set_mtx();
    process_main();
    set_collision();
    fopAcM_rollPlayerCrash(this, mCylR, 7);

    s16 step_m = mMode == MODE_PIKUPIKU_M_e ? 1 : 30;
    cLib_addCalcAngleS2(&mAngleMX, mTargetAngleMX, step_m, 0x1000);
    cLib_addCalcAngleS2(&mAngleMY, mTargetAngleMY, step_m, 0x1000);

    s16 step_l = mMode == MODE_PIKUPIKU_L_e || mMode == MODE_CHANGE_SL2_e ? 1 : 10;
    cLib_addCalcAngleS2(&mAngleLY, mTargetAngleLY, step_l, 0x1000);
    cLib_addCalcAngleS2(&mAngleLZ, mTargetAngleLZ, step_l, 0x1000);

    XyEvent_exe();

    if (mHeartPlaced == 0) {
        mHeartPlaced = place_heart_part();
    }
    if (mLaunchTimer == 1 && launch_heart_part()) {
        mLaunchTimer = 0;
    }
    if (mEventTimer > 1) {
        mEventTimer--;
    }
    if (mLaunchTimer > 1) {
        mLaunchTimer--;
    }
    return true;
}

/* 000042C4-0000455C       .text _draw__Q210daObjFtree5Act_cFv */
bool daObjFtree::Act_c::_draw() {
    if (mMode == MODE_NONE_e) {
        return true;
    }

    if (mDrawS == 1) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
        dComIfGd_setListBG();
        if (mMode == MODE_CHANGE_SL2_e || mMode == MODE_CHANGE_LS_e) {
            mBrkAnm.remove(mpMorf->getModel()->getModelData());
            set_tev_color(mpMorf->getModel()->getModelData(), 2, mCurColorS.r, mCurColorS.g, mCurColorS.b);
        } else {
            mBrkAnm.entry(mpMorf->getModel()->getModelData());
        }
        mpMorf->updateDL();
        dComIfGd_setList();
        cXyz pos(current.pos.x, current.pos.y, current.pos.z);
        dComIfGd_setSimpleShadow2(&pos, mGroundY, 75.0f, mGndChk, shape_angle.y, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }

    if (mDrawL == 1) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModelL, &tevStr);
        dComIfGd_setListBG();
        set_tev_color(mpModelL->getModelData(), 2, mCurColorL.r, mCurColorL.g, mCurColorL.b);
        mDoExt_modelUpdateDL(mpModelL);
        dComIfGd_setList();
        f32 rate = GetRate(mScaleL, 0.2f, 1.0f);
        cXyz pos(current.pos.x, current.pos.y, current.pos.z);
        dComIfGd_setSimpleShadow2(&pos, mGroundY, 75.0f * (1.0f + 2.5f * rate), mGndChk, shape_angle.y, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }
    return true;
}

namespace daObjFtree {
namespace {
/* 0000455C-0000457C       .text Mthd_Create__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_create();
}

/* 0000457C-000045A0       .text Mthd_Delete__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_delete();
}

/* 000045A0-000045C4       .text Mthd_Execute__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_execute();
}

/* 000045C4-000045E8       .text Mthd_Draw__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjFtree::Act_c*)i_this)->_draw();
}

/* 000045E8-000045F0       .text Mthd_IsDelete__Q210daObjFtree27@unnamed@d_a_obj_ftree_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjFtree

actor_process_profile_definition g_profile_Obj_Ftree = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Ftree_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjFtree::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Ftree_e,
    /* Actor SubMtd */ &daObjFtree::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
