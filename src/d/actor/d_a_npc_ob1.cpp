/**
 * d_a_npc_ob1.cpp
 * NPC - Rose
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ob1.h"
#include "d/actor/d_a_kb.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_hostIO.h"
#include "res/Object/Ob.h"

class daNpc_Ob1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackboneX;
        /* 0x0A */ s16 mMaxBackboneY;
        /* 0x0C */ s16 mMinBackboneX;
        /* 0x0E */ s16 mMinBackboneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 mCalcAngleTarget;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ int m18;
        /* 0x1C */ s16 mChaseAngleStep;
        /* 0x20 */ f32 mWalkAnmSpeedRate;
        /* 0x24 */ f32 mWalkMaxSpeed;
        /* 0x28 */ f32 mWalkSpeedStep;
        /* 0x2C */ f32 mPassDist;
    };  // Size: 0x30

    daNpc_Ob1_HIO_c();
    virtual ~daNpc_Ob1_HIO_c() {};

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};  // Size: 0x3C

/* 000000EC-00000150       .text __ct__15daNpc_Ob1_HIO_cFv */
daNpc_Ob1_HIO_c::daNpc_Ob1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x2000,
        /* mMaxHeadY         */ 0x1388,
        /* mMinHeadX         */ -0x3E8,
        /* mMinHeadY         */ -0x1388,
        /* mMaxBackboneX     */ 0x05DC,
        /* mMaxBackboneY     */ 0x1F40,
        /* mMinBackboneX     */ -0x7D0,
        /* mMinBackboneY     */ -0x1F40,
        /* mMaxTurnStep      */ 0x04B0,
        /* mCalcAngleTarget  */ 0x04B0,
        /* mAttPosOffsetY    */ 170.0f,
        /* m18               */ 6,
        /* mChaseAngleStep   */ 0x0400,
        /* mWalkAnmSpeedRate */ 0.5f,
        /* mWalkMaxSpeed     */ 3.0f,
        /* mWalkSpeedStep    */ 0.1f,
        /* mPassDist         */ 40.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static daNpc_Ob1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;
static u8 l_check_flg;

/* 00000198-00000228       .text searchActor_Kb__FPvPv */
static void* searchActor_Kb(void* i_actor, void*) {
    if (l_check_wrk < 20 && fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_KB_e) {
        kb_class* pig = (kb_class*)i_actor;
        if (pig->m405 != 0) {
            l_check_flg |= pig->m405;
        }
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk++;
    }
    return NULL;
}

/* 00000228-00000274       .text nodeCallBack_Ob1__FP7J3DNodei */
static BOOL nodeCallBack_Ob1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ob1_c*>(j3dSys.getModel()->getUserArea())->nodeOb1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000274-000003C4       .text nodeOb1Control__11daNpc_Ob1_cFP7J3DNodeP8J3DModel */
void daNpc_Ob1_c::nodeOb1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(20.0f, -20.0f, 0.0f);
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    if (jointIdx == m_hed_jnt_num) {
        mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    }
    if (jointIdx == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

static char* l_evn_tbl[] = {
    "Get_Rupee",
};

/* 00000400-00000480       .text init_OB1_0__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        set_action(&daNpc_Ob1_c::wait_action1, NULL);
        return true;
    } else {
        return false;
    }
}

/* 00000480-00000518       .text init_OB1_1__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_1() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 0) {
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        set_action(&daNpc_Ob1_c::wait_action2, NULL);
        return true;
    } else {
        return false;
    }
}

/* 00000518-000005A4       .text init_OB1_2__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_2() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 1) {
        set_action(&daNpc_Ob1_c::wait_action2, NULL);
        return true;
    } else {
        return false;
    }
}

/* 000005A4-000007AC       .text createInit__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::createInit() {
    for (int i = 0; i < 1; i++) {
        mEventIdTable[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 172;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 172;
    gravity = -4.5f;
    mInitialAngle = current.angle;
    mInitialPos = current.pos;
    m79C = mInitialPos;
    int weight = 0xFF;
    u8 path_idx = fopAcM_GetParam(this) >> 16;
    if (path_idx != 0xFF) {
        mPathRun.setInf(path_idx, fopAcM_GetRoomNo(this), 1);
        if (!mPathRun.isPath()) {
            return false;
        }
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        weight = 0xD9;
    }
    mEventCut.setActorInfo2("Ob1", this);
    mAnmNum = 8;
    bool init_success;
    switch (mSpecificType) {
        case 0:
            init_success = init_OB1_0();
            break;
        case 1:
            init_success = init_OB1_1();
            break;
        case 2:
            init_success = init_OB1_2();
            break;
        default:
            init_success = false;
            break;
    }
    if (init_success) {
        m78A = current.angle;
        shape_angle = m78A;
    } else {
        return false;
    }
    mStts.Init(weight, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 000007AC-00000900       .text setMtx__11daNpc_Ob1_cFb */
void daNpc_Ob1_c::setMtx(bool i_setEyePos) {
    if (!mbInDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(m78A.y);

    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    m_hed_model->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    m_hed_model->calc();
    setAttention(i_setEyePos);
}

/* 00000900-00000914       .text anmNum_toResID__11daNpc_Ob1_cFi */
int daNpc_Ob1_c::anmNum_toResID(int i_anmNum) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_OB_BCK_WAIT_e,
        dRes_ID_OB_BCK_TALK_e,
        dRes_ID_OB_BCK_THANK_e,
        dRes_ID_OB_BCK_WALK_e,
        dRes_ID_OB_BCK_THANK02_e,
        dRes_ID_OB_BCK_LAUGH_e,
        dRes_ID_OB_BCK_SHUTUP01_e,
        dRes_ID_OB_BCK_SHUTUP02_e,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 00000914-00000928       .text btpNum_toResID__11daNpc_Ob1_cFi */
int daNpc_Ob1_c::btpNum_toResID(int i_btpNum) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_OB_BTP_MABA_A_e,
        dRes_ID_OB_BTP_MABA_A_e,
    };
    return a_btp_resID_tbl[i_btpNum];
}

/* 00000928-00000A34       .text setBtp__11daNpc_Ob1_cFbi */
bool daNpc_Ob1_c::setBtp(bool i_modify, int i_btpNum) {
    J3DModelData* model_data = m_hed_model->getModelData();
    m_hed_tex_pttrn = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Ob", btpNum_toResID(i_btpNum));
    JUT_ASSERT(511, m_hed_tex_pttrn != NULL);

    if (mHeadBtpAnm.init(model_data, m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        mBlinkFrame = 0;
        mBlinkTimer = 0;
        return true;
    }
    return false;
}

/* 00000A34-00000A5C       .text iniTexPttrnAnm__11daNpc_Ob1_cFb */
bool daNpc_Ob1_c::iniTexPttrnAnm(bool i_modify) {
    return setBtp(i_modify, mBtpNum);
}

/* 00000A5C-00000B08       .text plyTexPttrnAnm__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::plyTexPttrnAnm() {
    if (mBtpNum != 0 || !cLib_calcTimer(&mBlinkTimer)) {
        mBlinkFrame++;
        if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
            if (mBtpNum != 0) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            } else {
                mBlinkTimer = cM_rndF(60.0f) + 30.0f;
                mBlinkFrame = 0;
            }
        }
    }
}

/* 00000B08-00000B44       .text setAnm_tex__11daNpc_Ob1_cFSc */
void daNpc_Ob1_c::setAnm_tex(s8 i_btpNum) {
    if (mBtpNum != i_btpNum) {
        mBtpNum = i_btpNum;
        iniTexPttrnAnm(true);
    }
}

/* 00000B44-00000C04       .text setAnm_anm__11daNpc_Ob1_cFPQ211daNpc_Ob1_c9anm_prm_c */
BOOL daNpc_Ob1_c::setAnm_anm(daNpc_Ob1_c::anm_prm_c* i_anmPrm) {
    if (mAnmNum == i_anmPrm->mAnmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrm->mAnmNum;
    dNpc_setAnmIDRes(mpMorf, i_anmPrm->mLoopMode, i_anmPrm->mMorf, i_anmPrm->mSpeed, anmNum_toResID(mAnmNum), -1, "Ob");
    mPrevMorfFrame = mAnmLoopCnt = mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00000C04-00000C70       .text setAnm_NUM__11daNpc_Ob1_cFii */
void daNpc_Ob1_c::setAnm_NUM(int i_anmIdx, int i_setTex) {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {2, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {4, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {6, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {7, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
    };
    if (i_setTex != 0) {
        setAnm_tex(a_anm_prm_tbl[i_anmIdx].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmIdx]);
}

/* 00000C70-00000CF0       .text setAnm__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {-1, -1, 0.0f, 0.0f, -1, 0},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {-1, -1, 0.0f, 0.0f, -1, 0},
        {3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {-1, -1, 0.0f, 0.0f, -1, 0},
    };
    if (a_anm_prm_tbl[mStatus].mBtpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStatus].mBtpNum);
    }
    if (a_anm_prm_tbl[mStatus].mAnmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStatus]);
    }
    return true;
}

/* 00000CF0-00000CFC       .text chg_anmTag__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::chg_anmTag() {
    switch (mMesgAnimeTagInfo) {
        case 0xFF:
            break;
    }
}

/* 00000CFC-00000D08       .text control_anmTag__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::control_anmTag() {
    switch (mMesgAnimeTagInfo) {
        case 0xFF:
            break;
    }
}

/* 00000D08-00000E00       .text chg_anmAtr__11daNpc_Ob1_cFUc */
void daNpc_Ob1_c::chg_anmAtr(u8 i_anmAtr) {
    if (mAtrMsgNo != -1) {
        switch (mAtrMsgNo) {
            case 0xAFC:
            case 0xAFD:
            case 0xAFF:
            case 0xB02:
            case 0xB05:
            case 0xB06:
            case 0xB09:
            case 0xB0C:
            case 0xB0D:
            case 0xB5D:
            case 0xB61:
            case 0xB64:
            case 0xB65:
                mLookBackState = 1;
                mHeadOnlyFollow = false;
                m_jnt.setTrn();
                break;
        }
    }
    if (i_anmAtr >= 7 || i_anmAtr == m800) {
        return;
    }
    m800 = i_anmAtr;
    setAnm_ATR(1);
}

/* 00000E00-00000E8C       .text control_anmAtr__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::control_anmAtr() {
    switch (m800) {
        case 3:
            if (mbMorfAnimStopped) {
                setAnm_NUM(4, 1);
                m800 = 7;
            }
            break;
        case 6:
            if (mbMorfAnimStopped) {
                setAnm_NUM(7, 1);
                m800 = 7;
            }
            break;
        case 2:
            break;
    }
}

/* 00000E8C-00000EF4       .text setAnm_ATR__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::setAnm_ATR(int i_setTex) {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {2, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {2, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {4, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {6, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
    };
    if (i_setTex != 0) {
        setAnm_tex(a_anm_prm_tbl[m800].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[m800]);
}

/* 00000EF4-00000FFC       .text anmAtr__11daNpc_Ob1_cFUs */
void daNpc_Ob1_c::anmAtr(u16 i_msgStatus) {
    dComIfG_MesgCamInfo_c* caminfo = dComIfGp_getMesgCameraInfo();
    if (field_0x6bc[0] == 2 && this != caminfo->mActor[caminfo->mBasicID - 1]) {
        control_anmTag();
        control_anmAtr();
        return;
    }

    switch (i_msgStatus) {
        case fopMsgStts_MSG_TYPING_e: {
            if (m80B == 0) {
                m800 = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m80B++;
            }
            u32 tag_info = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if (tag_info != 0xFF && mMesgAnimeTagInfo != tag_info) {
                mMesgAnimeTagInfo = tag_info;
                chg_anmTag();
            }
            break;
        }
        case fopMsgStts_MSG_DISPLAYED_e:
            m80B = 0;
            break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00000FFC-00001088       .text eventOrder__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::eventOrder() {
    s8 condition = m804;
    if (condition == 1 || condition == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m804 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (condition >= 3) {
        mEventIdx = condition - 3;
        fopAcM_orderOtherEventId(this, mEventIdTable[mEventIdx]);
    }
}

/* 00001088-00001120       .text checkOrder__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdTable[mEventIdx])) {
            m804 = 0;
        }
    } else if (eventInfo.checkCommandTalk() && (m804 == 1 || m804 == 2)) {
        m804 = 0;
        m7F9 = true;
    }
}

/* 00001120-000011C0       .text chk_talk__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::chk_talk() {
    bool ret = false;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            ret = true;
        }
    } else {
        mItemNo = 0xFF;
        ret = true;
    }
    return ret;
}

/* 000011C0-00001200       .text chk_partsNotMove__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::chk_partsNotMove() {
    return mJointHeadY == m_jnt.getHead_y() &&
        mJointBackboneY == m_jnt.getBackbone_y() &&
        mActorAngleY == current.angle.y;
}

/* 00001200-000013A0       .text lookBack__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = mHeadOnlyFollow;

    switch (mLookBackState) {
        case 1:
            dstPos = dNpc_playerEyePos(-20.0f);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 2:
            dstPos.set(m79C);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 3:
            desiredYrot = mTargetYRot;
            break;
    }
    cLib_addCalcAngleS2(&mLookAtMaxVel, l_HIO.mPrmTbl.mCalcAngleTarget, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, mLookAtMaxVel, headOnlyFollow);
}

/* 000013A0-000014CC       .text next_msgStatus__11daNpc_Ob1_cFPUl */
u16 daNpc_Ob1_c::next_msgStatus(u32* i_msgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*i_msgNo) {
        case 0xA8D:
            *i_msgNo = 0xA8E;
            break;
        case 0xA90:
            *i_msgNo = 0xA91;
            break;
        case 0xA93:
            *i_msgNo = 0xA94;
            break;
        case 0xA97:
            *i_msgNo = 0xA98;
            break;
        case 0xA92:
        case 0xA96:
        case 0xA9B:
        case 0xA9D:
        case 0xAA0:
        case 0xAA2:
        case 0xAA3:
        case 0xAA4:
        case 0xAA5:
        case 0xAA6:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0308)) {
                *i_msgNo = 0xAA7;
                break;
            }
            goto msg_end;
        case 0xAA8:
            if (dKy_daynight_check() == 0) {
                *i_msgNo = 0xAA9;
            } else {
                *i_msgNo = 0xAAA;
            }
            break;
        case 0xAAD:
        case 0xAAE:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0304)) {
                *i_msgNo = 0xA8F;
            } else {
                *i_msgNo = 0xA8D;
            }
            break;
        default:
        msg_end:
            ret = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return ret;
}

/* 000014CC-000017F0       .text getMsg_OB1_0__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_0() {
    u32 msgNo = 0;
    if (mNearPigCnt != 0 || mPigCnt != 0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0302)) {
            if (mNewPigCnt != 0) {
                if (mPigCnt == 2) {
                    if (mMsgCycle != 0) {
                        msgNo = 0xAA2;
                        mMsgCycle = 0;
                    } else {
                        msgNo = 0xAA1;
                        mMsgCycle = 1;
                    }
                } else {
                    switch (mNewPigCnt) {
                        case 1:
                            if (mMsgCycle == 1) {
                                msgNo = 0xA9D;
                                mMsgCycle = 0;
                            } else {
                                msgNo = 0xA9C;
                                mMsgCycle = 1;
                            }
                            break;
                        case 2:
                            if (mMsgCycle == 2) {
                                msgNo = 0xA9F;
                                mMsgCycle = 1;
                            } else if (mMsgCycle == 1) {
                                msgNo = 0xAA0;
                                mMsgCycle = 0;
                            } else {
                                msgNo = 0xA9E;
                                mMsgCycle = 2;
                            }
                            break;
                    }
                }
            } else if (mPigCnt > mNearPigCnt) {
                msgNo = 0xAA3;
            } else {
                switch (mNearPigCnt) {
                    case 1:
                        msgNo = 0xAA4;
                        break;
                    case 2:
                        msgNo = 0xAA5;
                        break;
                    default:
                        msgNo = 0xAA6;
                        break;
                }
            }
        } else {
            switch (mNewPigCnt) {
                case 1:
                    if (mMsgCycle == 1) {
                        msgNo = 0xA92;
                        mMsgCycle = 0;
                    } else {
                        msgNo = 0xA90;
                        mMsgCycle = 1;
                    }
                    break;
                case 2:
                    if (mMsgCycle == 2) {
                        msgNo = 0xA95;
                        mMsgCycle = 1;
                    } else if (mMsgCycle == 1) {
                        msgNo = 0xA96;
                        mMsgCycle = 0;
                    } else {
                        msgNo = 0xA93;
                        mMsgCycle = 2;
                    }
                    break;
                case 3:
                    if (mMsgCycle == 3) {
                        msgNo = 0xA99;
                        mMsgCycle = 2;
                    } else if (mMsgCycle == 2) {
                        msgNo = 0xA9A;
                        mMsgCycle = 1;
                    } else if (mMsgCycle == 1) {
                        msgNo = 0xA9B;
                        mMsgCycle = 0;
                    } else {
                        msgNo = 0xA97;
                        mMsgCycle = 3;
                    }
                    break;
            }
            m7EC = true;
        }
        return msgNo;
    }

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C40)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C40);
            return 0xAAD;
        }
    } else if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C80)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C80);
        return 0xAAE;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0304) ? 0xA8F : 0xA8D;
}

/* 000017F0-0000185C       .text getMsg_OB1_1__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_1() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C20)) {
        return 0xAA8;
    }
    return dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF) != 0 ? 0xAAB : 0xAAC;
}

/* 0000185C-0000187C       .text getMsg_OB1_2__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_2() {
    return getMsg_OB1_1();
}

/* 0000187C-000018EC       .text getMsg__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg() {
    u32 msgNo = 0;
    switch (mSpecificType) {
        case 0:
            msgNo = getMsg_OB1_0();
            break;
        case 1:
            msgNo = getMsg_OB1_1();
            break;
        case 2:
            msgNo = getMsg_OB1_2();
            break;
    }
    return msgNo;
}

/* 000018EC-0000196C       .text chkAttention__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 0000196C-000019C4       .text setAttention__11daNpc_Ob1_cFb */
void daNpc_Ob1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY, current.pos.z);
    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }
    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 000019C4-000019F8       .text searchByID__11daNpc_Ob1_cFUi */
fopAc_ac_c* daNpc_Ob1_c::searchByID(fpc_ProcID i_procID) {
    fopAc_ac_c* actor = NULL;
    fopAcM_SearchByID(i_procID, &actor);
    return actor;
}

/* 000019F8-00001A04       .text partner_srch__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::partner_srch() {
    switch (m80A) {
        case 1:
            break;
    }
}

/* 00001A04-00001A34       .text bitCount__11daNpc_Ob1_cFUc */
s8 daNpc_Ob1_c::bitCount(u8 i_bits) {
    s8 count = 0;
    for (int i = 0; i < 8; i++) {
        if (i_bits & 1) {
            count++;
        }
        i_bits = i_bits >> 1;
    }
    return count;
}

/* 00001A34-00001B14       .text set_pigCnt__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::set_pigCnt() {
    mPigCnt = bitCount(dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF));
    l_check_wrk = 0;
    l_check_flg = 0;
    for (int i = 0; i < 20; i++) {
        l_check_inf[i] = NULL;
    }
    fpcM_Search(searchActor_Kb, this);
    mNearPigCnt = bitCount(l_check_flg);
    mNewPigCnt = bitCount(l_check_flg & ~dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF));
    mMsgCycle = 0;
}

/* 00001B14-00001BB0       .text ob_setPthPos__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_setPthPos() {
    if (mPathRun.isPath()) {
        current.pos = mPathRun.getPoint(mPathRun.getIdx());
        mPathRun.nextIdxAuto();
        cXyz next_pos = mPathRun.getPoint(mPathRun.getIdx());
        current.angle.y = cLib_targetAngleY(&current.pos, &next_pos);
    }
}

/* 00001BB0-00001C50       .text get_attPos__11daNpc_Ob1_cFv */
cXyz daNpc_Ob1_c::get_attPos() {
    cXyz pos;
    dPath* path = mPathRun.nextPath(fopAcM_GetRoomNo(this));
    if (path != NULL) {
        u8 idx = mPathRun.getIdx();
        if (idx == 0) {
            idx = mPathRun.maxPoint();
        }
        dPnt* pnt = &path->m_points[(u8)(idx - 1)];
        pos.set(pnt->m_position.x, pnt->m_position.y, pnt->m_position.z);
    }
    return pos;
}

/* 00001C50-00001DC0       .text ob_movPass__11daNpc_Ob1_cFv */
int daNpc_Ob1_c::ob_movPass() {
    int ret = 0;
    if (mPathRun.isPath() && dPath_ChkClose(mPathRun.getPath())) {
        if (mPathRun.chkPointPass(current.pos, mPathRun.getDir())) {
            mPathRun.nextIdxAuto();
            ret = 1;
        }
        return ret;
    }

    f32 dist = (mTargetPos - current.pos).absXZ();
    if (dist <= mPassDist) {
        ret = 1;
        if (mPathRun.isPath() && !mPathRun.nextIdxAuto()) {
            ret = 2;
        }
    }
    return ret;
}

/* 00001DC0-00001E50       .text ob_clcMovSpd__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_clcMovSpd() {
    (mTargetPos - current.pos).abs2XZ();
    cLib_chaseAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &mTargetPos), l_HIO.mPrmTbl.mChaseAngleStep);
    cLib_chaseF(&speedF, mMaxSpeed, mSpeedStep);
}

/* 00001E50-00001F28       .text ob_nMove__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_nMove() {
    f32 anm_speed;
    switch (mMoveMode) {
        case 1:
            ob_clcMovSpd();
            if (mMoveMode == 1) {
                anm_speed = speedF * l_HIO.mPrmTbl.mWalkAnmSpeedRate;
            }
            if (anm_speed < 0.5f) {
                anm_speed = 0.5f;
            }
            mpMorf->setPlaySpeed(anm_speed);
            switch (ob_movPass()) {
                case 1:
                    mbPointPassed = true;
                    break;
                case 2:
                    mbPointPassed = true;
                    mMoveMode = 0;
                    break;
            }
            break;
    }
    if (mbPointPassed) {
        m7F0 = true;
    }
}

/* 00001F28-00001F78       .text charDecide__11daNpc_Ob1_cFi */
bool daNpc_Ob1_c::charDecide(int i_type) {
    mType = 0;
    mSpecificType = -1;
    switch (i_type) {
        case 1:
            mSpecificType = 1;
            break;
        case 2:
            mSpecificType = 2;
            break;
        default:
            mSpecificType = 0;
            break;
    }
    return true;
}

/* 00001F78-00001FD0       .text event_actionInit__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::event_actionInit(int i_staffIdx) {
    int* act_no_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    if (act_no_p != NULL) {
        mActNo = *act_no_p;
    }
}

/* 00001FD0-00001FE0       .text event_action__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::event_action() {
    switch (mActNo) {
        case 0:
            break;
    }
    return true;
}

/* 00001FE0-000020CC       .text privateCut__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "ACTION",
    };
    enum {
        ACT_ACTION,
    };

    if (i_staffIdx == -1) {
        return;
    }

    mActionIndex = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);
    if (mActionIndex == -1) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    } else {
        if (dComIfGp_evmng_getIsAddvance(i_staffIdx)) {
            switch (mActionIndex) {
                case ACT_ACTION:
                    event_actionInit(i_staffIdx);
                    break;
            }
        }
        bool endCut;
        switch (mActionIndex) {
            case ACT_ACTION:
                endCut = event_action();
                break;
            default:
                endCut = true;
                break;
        }
        if (endCut) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        }
    }
}

/* 000020CC-000020EC       .text endEvent__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::endEvent() {
    dComIfGp_event_reset();
    m800 = 0xFF;
}

/* 000020EC-00002124       .text isEventEntry__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 00002124-000021B8       .text event_proc__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIdTable[mEventIdx])) {
        m804 = 1;
        endEvent();
    } else {
        if (!mEventCut.cutProc()) {
            privateCut(i_staffIdx);
        }
        lookBack();
    }
}

/* 000021B8-00002264       .text set_action__11daNpc_Ob1_cFM11daNpc_Ob1_cFPCvPvPv_iPv */
BOOL daNpc_Ob1_c::set_action(ProcFunc i_procFunc, void* i_arg) {
    if (mCurrProcFunc != i_procFunc) {
        if (mCurrProcFunc) {
            m80A = 0;
            (this->*mCurrProcFunc)(i_arg);
        }
        mCurrProcFunc = i_procFunc;
        m80A = 0;
        (this->*mCurrProcFunc)(i_arg);
    }
    return TRUE;
}

/* 00002264-00002288       .text clrSpd__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::clrSpd() {
    mMaxSpeed = 0.0f;
    mSpeedStep = 0.0f;
    speedF = 0.0f;
    gravity = -4.5f;
}

/* 00002288-00002488       .text setStt__11daNpc_Ob1_cFSc */
void daNpc_Ob1_c::setStt(s8 i_status) {
    searchByID(mPartnerProcID);
    s8 prev_status = mStatus;
    mEvTimer = 0;
    mStatus = i_status;
    switch (mStatus) {
        case 4:
            mLookTimer = cLib_getRndValue(90, 180);
            // fallthrough
        case 1:
        case 5:
            if (prev_status != 2) {
                switch (mStatus) {
                    case 1:
                        mLookBackState = 3;
                        mTargetYRot = mInitialAngle.y;
                        break;
                    case 4:
                        mLookBackState = 2;
                        m79C = get_attPos();
                        break;
                    case 5:
                        mLookBackState = 1;
                        break;
                }
                m_jnt.setTrn();
                mHeadOnlyFollow = false;
            }
            m804 = 0;
            mMoveMode = 0;
            clrSpd();
            break;
        case 2:
            mLookBackState = 1;
            m_jnt.setTrn();
            mHeadOnlyFollow = false;
            m804 = 0;
            mMoveMode = 0;
            clrSpd();
            m800 = 0xFF;
            if (prev_status != 5) {
                mPrevStatus = prev_status;
            }
            set_pigCnt();
            break;
        case 3:
            mTargetPos = mPathRun.getPoint(mPathRun.getIdx());
            mLookBackState = 0;
            mHeadOnlyFollow = true;
            m804 = 0;
            mMoveMode = 1;
            mbPointPassed = false;
            gravity = -4.5f;
            mMaxSpeed = l_HIO.mPrmTbl.mWalkMaxSpeed;
            mSpeedStep = l_HIO.mPrmTbl.mWalkSpeedStep;
            mPassDist = l_HIO.mPrmTbl.mPassDist;
            break;
        case 6:
            m800 = 0xFF;
            mPrevStatus = prev_status;
            return;
        case 0:
            break;
    }
    setAnm();
}

/* 00002488-00002564       .text wait_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_1() {
    if (m7F9) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    if (field_0x6bc[0] == 1) {
        field_0x6bc[0] = 2;
        setStt(6);
        mLookBackState = 3;
        mTargetYRot = mInitialAngle.y;
        return TRUE;
    }
    m804 = 2;
    if (mbAttention) {
        mEvTimer = 60;
    }
    if (cLib_calcTimer(&mEvTimer)) {
        mLookBackState = 1;
    } else {
        mLookBackState = 3;
        mTargetYRot = mInitialAngle.y;
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 00002564-0000264C       .text wait_2__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_2() {
    if (m7F9) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    m804 = 2;
    if (mbAttention) {
        mEvTimer = 60;
    }
    if (cLib_calcTimer(&mEvTimer)) {
        mLookBackState = 1;
    } else {
        if (!cLib_calcTimer(&mLookTimer)) {
            setStt(3);
            return TRUE;
        }
        mLookBackState = 2;
        m79C = get_attPos();
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 0000264C-000026F0       .text wait_3__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_3() {
    if (m7F9) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    if (mbMorfAnimStopped) {
        mAnmLoopCnt++;
        if (mAnmLoopCnt > 3) {
            setStt(mPrevStatus);
            return TRUE;
        }
    }
    m804 = 2;
    mLookBackState = 1;
    m_jnt.setTrn();
    return TRUE;
}

/* 000026F0-00002808       .text walk_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::walk_1() {
    if (m7F9) {
        setAnm_NUM(0, 1);
        speedF = 0.0f;
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    m804 = 2;
    if (mbAttention) {
        mEvTimer = 20;
    }
    if (cLib_calcTimer(&mEvTimer)) {
        mLookBackState = 1;
    } else {
        mLookBackState = 0;
    }
    if (mbPointPassed) {
        if (mPathRun.getIdx() == 0) {
            mPathRun.nextIdxAuto();
        }
        setStt(4);
        return TRUE;
    }
    mbPointPassed = false;
    mTargetPos = mPathRun.getPoint(mPathRun.getIdx());
    return TRUE;
}

/* 00002808-00002A58       .text talk_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::talk_1() {
    u8 ret = chk_partsNotMove();
    if (m804 == 1 || m804 >= 3) {
        return TRUE;
    }
    if (mpCurrMsg != NULL) {
        mOldMsgStat = mpCurrMsg->mStatus;
    } else {
        mOldMsgStat = 0;
    }
    if (m7ED && mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        mCurrMsgNo = getMsg();
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, dComIfGp_getMesgCameraInfo()->mActor[0]);
        mpCurrMsg = NULL;
    } else {
        mAtrMsgNo = -1;
        talk(1);
    }
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
            case fopMsgStts_MSG_TYPING_e:
            case fopMsgStts_BOX_OPENING_e:
                break;
            case fopMsgStts_MSG_DESTROYED_e:
                if (mMsgCycle != 0) {
                    m804 = 3;
                    setAnm_NUM(0, 1);
                    endEvent();
                    return ret;
                }
                l_check_flg |= dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF);
                dComIfGs_setEventReg(dSv_event_flag_c::UNK_B6FF, l_check_flg);
                switch (mCurrMsgNo) {
                    case 0xA8E:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0304);
                        break;
                    case 0xAA7:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0308);
                        break;
                    case 0xAA9:
                    case 0xAAA:
                    case 0xAAB:
                    case 0xAAC:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C20);
                        break;
                }
                if (m7EC) {
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_0302);
                }
                mItemNo = 0xFF;
                m7F9 = false;
                switch (mSpecificType) {
                    case 0:
                        setStt(5);
                        break;
                    default:
                        setStt(mPrevStatus);
                        mEvTimer = 60;
                        break;
                }
                endEvent();
        }
    }
    return ret;
}

/* 00002A58-00002B60       .text manzai__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::manzai() {
    dComIfG_MesgCamInfo_c* caminfo = dComIfGp_getMesgCameraInfo();
    switch (field_0x6bc[0]) {
        case 2: {
            fopNpc_npc_c* partner = (fopNpc_npc_c*)searchByID(*(fpc_ProcID*)field_0x6b4);
            if (this != caminfo->mActor[caminfo->mBasicID - 1]) {
                if (m800 != 0xFF) {
                    mLookBackState = 3;
                    mTargetYRot = mInitialAngle.y;
                    m_jnt.setTrn();
                    mStatus = mPrevStatus;
                    setAnm();
                    mStatus = 6;
                    m800 = 0xFF;
                }
            } else {
                mAtrMsgNo = partner->mCurrMsgNo;
                anmAtr(*(u16*)&partner->field_0x6b4[4]);
            }
            break;
        }
        case 3:
            fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
            setStt(mPrevStatus);
            field_0x6bc[0] = 0;
            break;
    }
    return TRUE;
}

/* 00002B60-00002C54       .text wait_action1__11daNpc_Ob1_cFPv */
BOOL daNpc_Ob1_c::wait_action1(void*) {
    switch (m80A) {
        case 0:
            ob_setPthPos();
            setStt(3);
            m80A++;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch (mStatus) {
                case 4:
                    mbSetEyePos = wait_2();
                    break;
                case 5:
                    mbSetEyePos = wait_3();
                    break;
                case 3:
                    mbSetEyePos = walk_1();
                    break;
                case 2:
                    mbSetEyePos = talk_1();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00002C54-00002D2C       .text wait_action2__11daNpc_Ob1_cFPv */
BOOL daNpc_Ob1_c::wait_action2(void*) {
    switch (m80A) {
        case 0:
            setStt(1);
            m80A++;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch (mStatus) {
                case 1:
                    mbSetEyePos = wait_1();
                    break;
                case 2:
                    mbSetEyePos = talk_1();
                    break;
                case 6:
                    mbSetEyePos = manzai();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00002D2C-00002E68       .text demo__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::demo() {
    if (demoActorID == 0) {
        if (mbInDemo) {
            mbInDemo = false;
        }
    } else {
        mbInDemo = true;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if (m_hed_tex_pttrn) {
            mBlinkFrame++;
            if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demo_btp = demo_actor->getP_BtpData("Ob");
        if (demo_btp) {
            m_hed_tex_pttrn = demo_btp;
            if (mHeadBtpAnm.init(m_hed_model->getModelData(), m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE)) {
                mBtpNum = 2;
                mBlinkFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Ob");
    }
    return mbInDemo;
}

/* 00002E68-00002F18       .text shadowDraw__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowID = dComIfGd_setShadow(
        mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr,
        0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
    if (mShadowID != 0) {
        dComIfGd_addRealShadow(mShadowID, m_hed_model);
    }
}

static void dummy() {
    const GXColor dummy1 = { 0xFF, 0x00, 0x00, 0x80 };
    const GXColor dummy2 = { 0x00, 0x00, 0xFF, 0x80 };
    const GXColor dummy3 = { 0x00, 0xFF, 0x00, 0x80 };
}

/* 00002F18-0000300C       .text _draw__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_draw() {
    J3DModel* hed_model = m_hed_model;
    J3DModelData* hed_model_data = hed_model->getModelData();
    J3DModel* morf_model = mpMorf->getModel();

    if (m7EE || m7F1) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model, &tevStr);
    mpMorf->entryDL();
    mHeadBtpAnm.entry(hed_model_data, mBlinkFrame);
    mDoExt_modelEntryDL(hed_model);
    mHeadBtpAnm.remove(hed_model_data);
    g_env_light.setLightTevColorType(hed_model, &tevStr);
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK4F, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 0000300C-000031F0       .text _execute__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_execute() {
    if (!mbRanExecute) {
        mInitialPos = current.pos;
        mInitialAngle = current.angle;
        mbRanExecute = true;
    }
    m_jnt.setParam(
        l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY,
        l_HIO.mPrmTbl.mMinBackboneX, l_HIO.mPrmTbl.mMinBackboneY,
        l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY,
        l_HIO.mPrmTbl.mMaxTurnStep
    );
    if (m7EE && demoActorID == 0) {
        return TRUE;
    }
    m7F0 = false;
    m7EE = false;
    partner_srch();
    checkOrder();
    if (!demo()) {
        int staff_idx = -1;
        if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            staff_idx = isEventEntry();
        }
        if (staff_idx >= 0) {
            event_proc(staff_idx);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }
        if (!m7F0) {
            ob_nMove();
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if (!m7EF) {
            m78A = current.angle;
            shape_angle = m78A;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbInDemo) {
        setCollision(80.0f, 160.0f);
    }
    return TRUE;
}

/* 000031F0-0000324C       .text _delete__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Ob");
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 0000324C-0000326C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ob1_c*>(i_this)->CreateHeap();
}

/* 0000326C-0000338C       .text _create__11daNpc_Ob1_cFv */
cPhs_State daNpc_Ob1_c::_create() {
    static int a_size_tbl[] = {
        0x272E0,
    };

    fopAcM_ct(this, daNpc_Ob1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Ob");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    if (!charDecide(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mType])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -60.0f, -20.0f, -60.0f, 60.0f, 170.0f, 60.0f);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 000037BC-000039D0       .text create_Anm__11daNpc_Ob1_cFv */
J3DModelData* daNpc_Ob1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ob", dRes_ID_OB_BDL_OB_e);
    JUT_ASSERT(2423, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Ob", dRes_ID_OB_BCK_WAIT_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11020022
    );
    if (mpMorf == NULL) {
        return NULL;
    }
    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(2443, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(2446, m_bbone_jnt_num >= 0);

    return a_mdl_dat;
}

/* 000039D0-00003A9C       .text create_hed_Mdl__11daNpc_Ob1_cFv */
J3DModelData* daNpc_Ob1_c::create_hed_Mdl() {
    static int a_hed_mdl_resID_tbl[] = {
        dRes_ID_OB_BDL_OBA_HEAD_e,
    };
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ob", a_hed_mdl_resID_tbl[mType]);
    JUT_ASSERT(2465, a_mdl_dat != NULL);
    m_hed_model = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11020022);
    return a_mdl_dat;
}

/* 00003A9C-00003BE8       .text CreateHeap__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::CreateHeap() {
    J3DModelData* model_data = create_Anm();
    if (!model_data) {
        return FALSE;
    }
    if (!create_hed_Mdl()) {
        mpMorf = NULL;
        return FALSE;
    }
    s8 a_btp_num_tbl[] = {0};
    mBtpNum = a_btp_num_tbl[0];
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    for (u16 i = 0; i < model_data->getJointNum(); i++) {
        if (i == m_hed_jnt_num || i == m_bbone_jnt_num) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ob1);
        }
    }
    mpMorf->getModel()->setUserArea((uintptr_t)this);
    mAcchCir.SetWall(30.0f, 80.0f);
    mObjAcch.Set(
        fopAcM_GetPosition_p(this),
        fopAcM_GetOldPosition_p(this),
        this,
        1,
        &mAcchCir,
        fopAcM_GetSpeed_p(this),
        NULL,
        NULL
    );
    return TRUE;
}

/* 00003BE8-00003C08       .text daNpc_Ob1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ob1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_create();
}

/* 00003C08-00003C28       .text daNpc_Ob1_Delete__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_Delete(daNpc_Ob1_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_delete();
}

/* 00003C28-00003C48       .text daNpc_Ob1_Execute__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_Execute(daNpc_Ob1_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_execute();
}

/* 00003C48-00003C68       .text daNpc_Ob1_Draw__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_Draw(daNpc_Ob1_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_draw();
}

/* 00003C68-00003C70       .text daNpc_Ob1_IsDelete__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_IsDelete(daNpc_Ob1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ob1_Method = {
    (process_method_func)daNpc_Ob1_Create,
    (process_method_func)daNpc_Ob1_Delete,
    (process_method_func)daNpc_Ob1_Execute,
    (process_method_func)daNpc_Ob1_IsDelete,
    (process_method_func)daNpc_Ob1_Draw,
};

actor_process_profile_definition g_profile_NPC_OB1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_OB1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ob1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_OB1_e,
    /* Actor SubMtd */ &l_daNpc_Ob1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
