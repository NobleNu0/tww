/**
 * d_a_npc_gk1.cpp
 * NPC - Mila's Father (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_gk1.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_lib.h"
#include "res/Object/Gk.h"

class daNpc_Gk1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        s16 mMaxHeadX;
        s16 mMaxHeadY;
        s16 mMinHeadX;
        s16 mMinHeadY;
        s16 mMaxBackboneX;
        s16 mMaxBackboneY;
        s16 mMinBackboneX;
        s16 mMinBackboneY;
        s16 mMaxTurnStep;
        s16 field_12;
        f32 mAttentionYOffset;
        f32 field_18;
    };  // Size: 0x1C

    daNpc_Gk1_HIO_c();
    virtual ~daNpc_Gk1_HIO_c() {};

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

static daNpc_Gk1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000150       .text __ct__15daNpc_Gk1_HIO_cFv */
daNpc_Gk1_HIO_c::daNpc_Gk1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x2000,
        /* mMaxHeadY         */ 0x0FA0,
        /* mMinHeadX         */ 0xEE6C,
        /* mMinHeadY         */ 0xF060,
        /* mMaxBackboneX     */ 0x0000,
        /* mMaxBackboneY     */ 0x0DAC,
        /* mMinBackboneX     */ 0xFC18,
        /* mMinBackboneY     */ 0xF254,
        /* mMaxTurnStep      */ 0x0578,
        /* field_12          */ 0x03E8,
        /* mAttentionYOffset */ 200.0f,
        /* field_18          */ 0.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static const char* l_evn_tbl[1] = {
    "dummy"
};

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Gk1_c* actor = (daNpc_Gk1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_Head(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {
    static cXyz a_eye_pos_off(30.0f, 30.0f, 0.0f);

    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));

    mDoMtx_stack_c::multVecZero(&field_0x758);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &field_0x734);
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000314-00000360       .text nodeCB_Neck__FP7J3DNodei */
static BOOL nodeCB_Neck(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Gk1_c* actor = (daNpc_Gk1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_Neck(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_Neck(J3DNode* i_node, J3DModel* i_pModel) {
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000400-0000044C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Gk1_c* actor = (daNpc_Gk1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_BackBone(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 000004EC-0000050C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* ac) {
    return ((daNpc_Gk1_c*)ac)->CreateHeap();
}

/* 0000050C-0000058C       .text init_GK1_0__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::init_GK1_0() {
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
        set_action(&daNpc_Gk1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* 0000058C-00000720       .text createInit__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::createInit() {
    bool ret;
    for(int i = 0; i < ARRAY_SSIZE(l_evn_tbl); i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    mEventCut.setActorInfo2("Gk1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    fopAcM_setCullSizeFar(this, 12000.0f / mDoLib_clipper::getFar());

    switch(field_0x7B3) {
        case 0:
            break;
    }

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;

    gravity = -4.5f;
    field_0x7AD = 5;

    switch(field_0x7B3) {
        case 0:
            ret = init_GK1_0();
            break;
        default:
            ret = false;
    }
    if(!ret) {
        return false;
    }

    field_0x726 = current.angle;
    shape_angle = field_0x726;
    mStts.Init(0xff, 0xff, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    play_animation();
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 00000720-000007C8       .text play_animation__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::play_animation() {
    u32 mtrlSndId = 0;
    play_btp_anm();
    if(mObjAcch.ChkGroundHit()) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    field_0x79C = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    if(mpMorf->getFrame() < mFrame) {
        field_0x79C = 1;
    }
    mFrame = mpMorf->getFrame();
}

/* 000007C8-00000930       .text setMtx__11daNpc_Gk1_cFb */
void daNpc_Gk1_c::setMtx(bool param_1) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(field_0x726);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    if(mpHairModel != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mpHairModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpHairModel->calc();
    }

    if(mpHatModel != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mpHatModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpHatModel->calc();
    }

    setAttention(param_1);
}

/* 00000930-00000944       .text bckResID__11daNpc_Gk1_cFi */
int daNpc_Gk1_c::bckResID(int idx) {
    static const int a_resID_tbl[] = {
        dRes_ID_GK_BCK_GK_WAIT01_e,
        dRes_ID_GK_BCK_GK_WALK_e,
        dRes_ID_GK_BCK_GK_TALK01_e,
        dRes_ID_GK_BCK_GK_TALK02_e,
        dRes_ID_GK_BCK_GK_TALK03_e,
    };
    return a_resID_tbl[idx];
}

/* 00000944-00000958       .text btpResID__11daNpc_Gk1_cFi */
int daNpc_Gk1_c::btpResID(int idx) {
    static const int a_resID_tbl[] = {
        dRes_ID_GK_BTP_GK_e,
    };
    return a_resID_tbl[idx];
}

/* 00000958-00000A5C       .text setBtp__11daNpc_Gk1_cFScb */
bool daNpc_Gk1_c::setBtp(s8 param_1, bool param_2) {
    J3DModel* model = mpMorf->getModel();
    if(param_1 < 0) {
        return false;
    }
    int resID = btpResID(param_1);
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern *)dComIfG_getObjectIDRes(mArcName, resID);
    JUT_ASSERT(0x1C3, a_btp != NULL);
    field_0x7AC = param_1;
    mBtpAnmFrame = 0;
    mTimer1 = 0;

    return mBtpAnm.init(model->getModelData(), a_btp, J3DFrameCtrl::EMode_RESET, 0, 1.0f, 0, -1, param_2, 0) != 0;
}

/* 00000A5C-00000A7C       .text init_texPttrnAnm__11daNpc_Gk1_cFScb */
bool daNpc_Gk1_c::init_texPttrnAnm(s8 param_1, bool param_2) {
    return setBtp(param_1, param_2);
}

/* 00000A7C-00000B18       .text play_btp_anm__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::play_btp_anm() {
    u16 frame = mBtpAnm.getBtpAnm()->getFrameMax() & 0xff;
    if(field_0x7AC != 0 || cLib_calcTimer(&mTimer1) == 0) {
        mBtpAnmFrame++;
        if((u16)mBtpAnmFrame >= frame) {
            if(field_0x7AC != 0) {
                mBtpAnmFrame = frame;
            } else {
                mTimer1 = cLib_getRndValue(0x3c, 0x5a);
                mBtpAnmFrame = 0;
            }
        }
    }
}

/* 00000B18-00000BB4       .text setAnm_anm__11daNpc_Gk1_cFPQ211daNpc_Gk1_c9anm_prm_c */
void daNpc_Gk1_c::setAnm_anm(daNpc_Gk1_c::anm_prm_c* param_1) {
    s8 temp = param_1->field_0x0;
    if(temp < 0 || field_0x7AD == temp) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf,
        param_1->field_0xC,
        param_1->field_0x4,
        param_1->field_0x8,
        bckResID(temp),
        -1,
        mArcName
    );
    field_0x7AD = param_1->field_0x0;
    field_0x79C = 0;
    field_0x79D = 0;
    mFrame = 0.0f;
}

/* 00000BB4-00000C20       .text setAnm__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::setAnm() {
    static daNpc_Gk1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0.0f, 0.0f, -1},
        {0, 0, 8.0f, 1.0f, 2},
        {-1, -1, 0.0f, 0.0f, -1},
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7AF].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7AF]);
}

/* 00000C20-00000C24       .text chngAnmTag__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::chngAnmTag() {
}

/* 00000C24-00000C28       .text ctrlAnmTag__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::ctrlAnmTag() {
}

/* 00000C28-00000C68       .text chngAnmAtr__11daNpc_Gk1_cFUc */
void daNpc_Gk1_c::chngAnmAtr(u8 param_1) {
    if(param_1 == field_0x7AA || param_1 > 5) {
        return;
    }
    field_0x7AA = param_1;
    setAnm_ATR();
}

/* 00000C68-00000C74       .text ctrlAnmAtr__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::ctrlAnmAtr() {
    if(field_0x7AA == (s8)5) {
        return;
    }
}

/* 00000C74-00000CD8       .text setAnm_ATR__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::setAnm_ATR() {
    static daNpc_Gk1_c::anm_prm_c a_anm_prm_tbl[5] = {
        {0, 0, 8.0f, 1.0f, 2},
        {1, 0, 8.0f, 1.0f, 2},
        {2, 0, 8.0f, 1.0f, 2},
        {3, 0, 8.0f, 1.0f, 2},
        {4, 0, 8.0f, 1.0f, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7AA].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7AA]);
}

/* 00000CD8-00000D94       .text anmAtr__11daNpc_Gk1_cFUs */
void daNpc_Gk1_c::anmAtr(u16 i_msgStatus) {
    switch (i_msgStatus) {
        case fopMsgStts_MSG_TYPING_e: {
            if(field_0x7B5 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x7B5++;
            }
            u8 tagInfo = dComIfGp_getMesgAnimeTagInfo();
            if(tagInfo != 0xFF && tagInfo != field_0x7AB) {
                dComIfGp_clearMesgAnimeTagInfo();
                field_0x7AB = tagInfo;
                chngAnmTag();
            }
            break;
        }
        case fopMsgStts_MSG_DISPLAYED_e:
            field_0x7B5 = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000D94-00000EAC       .text next_msgStatus__11daNpc_Gk1_cFPUl */
u16 daNpc_Gk1_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;

    switch(*pMsgNo) {
        case 0x28A1:
            *pMsgNo = 0x28A2;
            break;
        case 0x28A2:
            *pMsgNo = 0x28A3;
            break;
        case 0x28A3:
            *pMsgNo = 0x28A4;
            break;
        case 0x28A4:
            *pMsgNo = 0x28A5;
            break;
        case 0x28A6:
            *pMsgNo = 0x28A7;
            break;
        case 0x28A7:
            *pMsgNo = 0x28A8;
            break;
        case 0x28A8:
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1640)) {
                status = fopMsgStts_MSG_ENDS_e;
            } else {
                *pMsgNo = 0x28A9;
            }
            break;
        case 0x28A9:
            *pMsgNo = 0x28AA;
            break;
        case 0x28AB:
            *pMsgNo = 0x28AC;
            break;
        case 0x28AC:
            *pMsgNo = 0x28AD;
            break;
        case 0x28AD:
            *pMsgNo = 0x28AE;
            break;
        case 0x28AF:
            *pMsgNo = 0x28B0;
            break;
        default:
            status = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return status;
}

/* 00000EAC-00000F50       .text getMsg_GK1_0__11daNpc_Gk1_cFv */
u32 daNpc_Gk1_c::getMsg_GK1_0() {
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B02) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1680)) {
        return 0x28A1;
    }
    if(!dKy_daynight_check()) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1640) ? 0x28A7 : 0x28A6;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E08) ? 0x28AF : 0x28AB;
}

/* 00000F50-00000F8C       .text getMsg__11daNpc_Gk1_cFv */
u32 daNpc_Gk1_c::getMsg() {
    u32 msgNo = 0;

    switch(field_0x7B3) {
        case 0:
            msgNo = getMsg_GK1_0();
            break;
        default:
            break;
    }
    return msgNo;
}

/* 00000F8C-00001018       .text eventOrder__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::eventOrder() {
    if(field_0x7AE == 1 || field_0x7AE == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);

        if(field_0x7AE == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if(field_0x7AE >= 3) {
        field_0x786 = field_0x7AE - 3;
        fopAcM_orderOtherEventId(this, mEventIdx[field_0x786]);
    }
}

/* 00001018-000010CC       .text checkOrder__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mEventIdx[field_0x786]) && field_0x7AE >= 3) {
            field_0x7AE = 0;
            field_0x7AA = 0xff;
            field_0x7AB = 0xff;
        }
    } else if(eventInfo.checkCommandTalk() && (field_0x7AE == 1 || field_0x7AE == 2)) {
        field_0x7AE = 0;
        field_0x7A5 = true;
    }
}

/* 000010CC-00001164       .text chk_talk__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chk_talk() {
    if(dComIfGp_event_chkTalkXY()) {
        if(dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            return true;
        }
        return false;
    }

    mItemNo = 0xff;
    return true;
}

/* 00001164-000011A4       .text chk_parts_notMov__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chk_parts_notMov() {
    return field_0x778.y != m_jnt.getHead_y() ||
        field_0x778.z != m_jnt.getBackbone_y() ||
        field_0x778.x != current.angle.y;
}

/* 000011A4-000011F8       .text searchByID__11daNpc_Gk1_cFUiPi */
fopAc_ac_c* daNpc_Gk1_c::searchByID(fpc_ProcID pid, int* param_2) {
    fopAc_ac_c* actor = NULL;
    *param_2 = 0;

    int temp = fopAcM_SearchByID(pid, &actor);
    if(temp == 0) {
        *param_2 = 1;
    }
    return actor;
}

/* 000011F8-000013BC       .text lookBack__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::lookBack() {
    int temp3;
    field_0x778.y = m_jnt.getHead_y();
    field_0x778.z = m_jnt.getBackbone_y();
    field_0x778.x = current.angle.y;
    cXyz temp5;
    cXyz temp(current.pos);
    temp.y = eyePos.y;
    temp5.set(0.0f, 0.0f, 0.0f);
    cXyz* temp2 = NULL;
    s16 targetY = current.angle.y;
    bool temp4 = field_0x7A6;

    switch(field_0x7B1) {
        case 1:
            field_0x740.set(dNpc_playerEyePos(-20.0f));
            temp5 = field_0x740;
            temp2 = &temp5;
            break;
        case 2:
            temp5.set(field_0x740);
            temp2 = &temp5;
            break;
        case 3:
            targetY = field_0x79A;
            break;
        case 4:
            fopAc_ac_c* actor = searchByID(mPId, &temp3);
            if(actor != NULL && temp3 == 0) {
                field_0x740.set(actor->current.pos);
                field_0x740.y = actor->eyePos.y;
                temp5.set(field_0x740);
                temp2 = &temp5;
            }
            break;
    }

    m_jnt.lookAtTarget_2(&current.angle.y, temp2, temp, targetY, l_HIO.mPrmTbl.field_12, temp4);
}

/* 000013BC-0000143C       .text chkAttention__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();

    if(attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }

    return this == attention.ActionTarget(0);
}

/* 0000143C-00001494       .text setAttention__11daNpc_Gk1_cFb */
void daNpc_Gk1_c::setAttention(bool param_1) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrmTbl.mAttentionYOffset, current.pos.z);
    if(field_0x780 == 0 && !param_1) {
        return;
    }
    eyePos.set(field_0x734.x, field_0x734.y, field_0x734.z);
}

/* 00001494-0000151C       .text decideType__11daNpc_Gk1_cFi */
bool daNpc_Gk1_c::decideType(int param_1) {
    bool temp;
    if(field_0x7B2 > 0) {
        temp = true;
    } else {
        field_0x7B2 = 1;
        field_0x7B3 = 0;
        strcpy(mArcName, "Gk");
        temp = false;
        if((field_0x7B2 != -1) && (field_0x7B3 != -1)) {
            temp = true;
        }
    }
    return temp;
}

/* 0000151C-000015BC       .text privateCut__11daNpc_Gk1_cFi */
void daNpc_Gk1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "dummy"
    };

    if(i_staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);

        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        } else {
            dComIfGp_evmng_getIsAddvance(i_staffIdx);
            dComIfGp_evmng_cutEnd(i_staffIdx);
        }
    }
}

/* 000015BC-000015E0       .text endEvent__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::endEvent() {
    dComIfGp_event_reset();
    field_0x7AA = 0xff;
    field_0x7AB = 0xff;
}

/* 000015E0-00001618       .text isEventEntry__11daNpc_Gk1_cFv */
int daNpc_Gk1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00001618-0000169C       .text event_proc__11daNpc_Gk1_cFi */
void daNpc_Gk1_c::event_proc(int i_staffIdx) {
    if(dComIfGp_evmng_endCheck(mEventIdx[field_0x786])) {
        endEvent();
    } else {
        if(!mEventCut.cutProc()) {
            privateCut(i_staffIdx);
        }
    }
}

/* 0000169C-00001748       .text set_action__11daNpc_Gk1_cFM11daNpc_Gk1_cFPCvPvPv_iPv */
bool daNpc_Gk1_c::set_action(ActionFunc i_action, void* param_2) {
    if(mCurrActionFunc != i_action) {
        if(mCurrActionFunc != 0) {
            field_0x7B4 = 9;
            (this->*mCurrActionFunc)(param_2);
        }
        mCurrActionFunc = i_action;
        field_0x7B4 = 0;
        (this->*mCurrActionFunc)(param_2);
    }
    return true;
}

/* 00001748-000017C8       .text setStt__11daNpc_Gk1_cFSc */
void daNpc_Gk1_c::setStt(s8 param_1) {
    s8 temp = field_0x7AF;
    field_0x7AF = param_1;

    switch(field_0x7AF) {
        case 0:
            break;
        case 1:
            field_0x7AE = 0;
            speedF = 0.0f;
            break;
        case 2:
            field_0x7AE = 0;
            field_0x7AA = 0xff;
            field_0x7AB = 0xff;
            field_0x7B5 = 0;
            field_0x7B0 = temp;
            break;
    }
    setAnm();
}

static inline bool chkAttnArea(f32 dist, s16 angle, f32 diffY, f32 maxAngle) {
    bool ret = false;
    bool inRange = false;
    if(dist < 200.0f && abs(angle) / DEG2S_CONSTANT < maxAngle) {
        inRange = true;
    }
    if(inRange && std::fabsf(diffY) < 300.0f) {
        ret = true;
    }
    return ret;
}

/* 000017C8-000019E0       .text chk_attn__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chk_attn() {
    f32 dist = (current.pos - dComIfGp_getPlayer(0)->current.pos).absXZ();
    f32 diffY = current.pos.y - dComIfGp_getPlayer(0)->current.pos.y;
    s16 angle = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos) - current.angle.y;

    if(field_0x7B1 == 1) {
        return chkAttnArea(dist, angle, diffY, 90.0f);
    } else {
        return chkAttnArea(dist, angle, diffY, 60.0f);
    }
}

/* 000019E0-00001B74       .text wait_1__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::wait_1() {
    field_0x7A7 = (current.pos - dComIfGp_getPlayer(0)->current.pos).absXZ() > 300.0f;
    if(field_0x7A7) {
        cLib_addCalcAngleS(&current.angle.y, field_0x720.y, 4, 0x800, 0x80);
    }

    if(field_0x7A5) {
        if(chk_talk()) {
            setStt(2);
            field_0x7B1 = 1;
            field_0x7A6 = false;
            field_0x7A7 = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }
    field_0x7AE = 2;
    field_0x7A6 = true;

    if(chk_attn()) {
        field_0x7B1 = 1;
        return TRUE;
    }
    field_0x7B1 = 0;
    return TRUE;
}

/* 00001B74-00001C74       .text talk_1__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::talk_1() {
    BOOL ret = chk_parts_notMov();
    talk(1);
    if(mpCurrMsg == NULL) {
        return TRUE;
    }
    switch(mpCurrMsg->mStatus) {
        case 6:
        case 2:
            break;
        case 19:
            switch(mCurrMsgNo) {
                case 0x28A5:
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_1680);
                    break;
                case 0x28AA:
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_1640);
                    break;
            }
            mItemNo = 0xFF;
            field_0x7A5 = false;
            setStt(field_0x7B0);
            mTimer2 = cLib_getRndValue(0xf, 0x1e);
            endEvent();
            break;
    }
    return ret;
}

/* 00001C74-00001D30       .text wait_action1__11daNpc_Gk1_cFPv */
int daNpc_Gk1_c::wait_action1(void*) {
    switch (field_0x7B4) {
        case 0:
            setStt(1);
            field_0x7A7 = true;
            field_0x7B4++;
            break;
        case 1:
        case 2:
        case 3:
            mHasAttention = chkAttention();
            switch (field_0x7AF) {
            case 1:
                field_0x780 = wait_1();
                break;
            case 2:
                field_0x780 = talk_1();
                break;
            }
        case 9:
            break;
    }
    return 1;
}

/* 00001D30-00001E70       .text demo__11daNpc_Gk1_cFv */
u8 daNpc_Gk1_c::demo() {
    if(demoActorID == 0) {
        if(field_0x7A8) {
            field_0x7A8 = false;
        }
    } else {
        if(!field_0x7A8) {
            field_0x7A8 = true;
            field_0x7A1 = false;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }

        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);

        J3DAnmTexPattern* btp = mBtpAnm.getBtpAnm();
        if(btp != NULL) {
            s16 frame = btp->getFrameMax() & 0xff;
            mBtpAnmFrame++;
            if((u16)mBtpAnmFrame >= (u16)frame) {
                mBtpAnmFrame = frame;
            }
        }

        btp = demo_actor->getP_BtpData(mArcName);
        if(btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, 1, 0, 1.0f, 0, -1, true, 0);
            field_0x7AC = 1;
            mBtpAnmFrame = 0;
        }
        dDemo_setDemoData(this, dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e, mpMorf, mArcName);
    }
    return field_0x7A8;
}

/* 00001E70-00001F48       .text shadowDraw__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(),
        &pos, 800.0f, 40.0f, current.pos.y,
        mObjAcch.GetGroundH(), mObjAcch.m_gnd,
        &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );

    if(mShadowId != 0) {
        if(mpHairModel != NULL) {
            dComIfGd_addRealShadow(mShadowId, mpHairModel);
        }
        if(mpHatModel != NULL) {
            dComIfGd_addRealShadow(mShadowId, mpHatModel);
        }
    }
}

const u32 unused[] = {
    0xFF000080,
    0x0000FF80,
    0xFFFF0080,
};

/* 00001F48-00002064       .text _draw__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* modelData = pModel->getModelData();

    if(field_0x7A0 || field_0x7A2) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(modelData, mBtpAnmFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(modelData);

    if(mpHairModel != NULL) {
        g_env_light.setLightTevColorType(mpHairModel, &tevStr);
        mDoExt_modelEntryDL(mpHairModel);
    }
    if(mpHatModel != NULL) {
        g_env_light.setLightTevColorType(mpHatModel, &tevStr);
        mDoExt_modelEntryDL(mpHatModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK59, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002064-00002280       .text _execute__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_execute() {
    if(!field_0x7A3) {
        field_0x714 = current.pos;
        field_0x720 = current.angle;
        field_0x7A3 = true;
    }

    m_jnt.setParam(
        l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY, l_HIO.mPrmTbl.mMinBackboneX,
        l_HIO.mPrmTbl.mMinBackboneY, l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY, l_HIO.mPrmTbl.mMaxTurnStep);

    if(field_0x7A0 && demoActorID == 0) {
        return TRUE;
    }

    checkOrder();
    if(!demo()) {
        int staffIdx = -1;

        if(dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
            staffIdx = isEventEntry();
        }

        if(staffIdx >= 0) {
            event_proc(staffIdx);
        } else {
            (this->*mCurrActionFunc)(NULL);
        }

        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        play_animation();
    } else {
        field_0x7A0 = false;
    }

    eventOrder();
    field_0x726 = current.angle;
    if(!field_0x7A1) {
        shape_angle = current.angle;
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);

    if(!field_0x7A8) {
        setCollision(90.0f, 200.0f);
    }
    return TRUE;
}

/* 00002280-000022D4       .text _delete__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_delete() {
    dComIfG_resDelete(&mPhs, mArcName);

    if(heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 000022D4-00002520       .text _create__11daNpc_Gk1_cFv */
cPhs_State daNpc_Gk1_c::_create() {
    static int a_siz_tbl[] = {
        0,
        0
    };

    cPhs_State state;
    fopAcM_ct_Retail(this, daNpc_Gk1_c);
    if(!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mStateIsComplaete = state == cPhs_COMPLEATE_e;
    if(!mStateIsComplaete) {
        return state;
    }
    fopAcM_ct_Demo(this, daNpc_Gk1_c);

    if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[field_0x7B2])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -90.0f, -20.0f, -80.0f, 90.0f, 200.0f, 80.0f);

    if(createInit() == 0) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 000027EC-00002AE8       .text bodyCreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_GK_BDL_GK_e);
    JUT_ASSERT(0x611, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL, NULL, NULL,
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020022
    );

    if(!mpMorf) {
        return FALSE;
    } else if(mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }

    if(!init_texPttrnAnm(0, false)) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x625, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x627, m_bbone_jnt_num >= 0);
    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(0x629, m_nck_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_nck_jnt_num)->setCallBack(nodeCB_Neck);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* 00002AE8-00002BA8       .text itemCreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::itemCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_GK_BDL_GK_HAIR_e);
    JUT_ASSERT(0x63E, a_mdl_dat != NULL);

    mpHairModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    if(mpHairModel == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00002BA8-00002C68       .text hat_CreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::hat_CreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_GK_BDL_GK_HAT_e);
    JUT_ASSERT(0x64E, a_mdl_dat != NULL);

    mpHatModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    if(mpHatModel == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00002C68-00002D2C       .text CreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::CreateHeap() {
    if(!bodyCreateHeap()) {
        return FALSE;
    }
    if(!itemCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }
    if(!hat_CreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }
    mAcchCir.SetWall(30.0f, 90.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    return TRUE;
}

/* 00002D2C-00002D4C       .text daNpc_Gk1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Gk1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_create();
}

/* 00002D4C-00002D6C       .text daNpc_Gk1_Delete__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Delete(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_delete();
}

/* 00002D6C-00002D8C       .text daNpc_Gk1_Execute__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Execute(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_execute();
}

/* 00002D8C-00002DAC       .text daNpc_Gk1_Draw__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Draw(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_draw();
}

/* 00002DAC-00002DB4       .text daNpc_Gk1_IsDelete__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_IsDelete(daNpc_Gk1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Gk1_Method = {
    (process_method_func)daNpc_Gk1_Create,
    (process_method_func)daNpc_Gk1_Delete,
    (process_method_func)daNpc_Gk1_Execute,
    (process_method_func)daNpc_Gk1_IsDelete,
    (process_method_func)daNpc_Gk1_Draw,
};

actor_process_profile_definition g_profile_NPC_GK1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_GK1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Gk1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_GK1_e,
    /* Actor SubMtd */ &l_daNpc_Gk1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
