//******************************************************************************
/*
 * @file    Matrix_KeyBoard_4x4.h
 * @author  ������ �����
 * @version 1.0
 * @date    28.07.2017
 * @brief   header ���� ��� ������ ��������� ��������� ����������         
 */
//******************************************************************************


/* 
 * MKB4x4 -- ���������� �� "MATRIX_KEYBOARD_4X4". ������ �������� ��������� ��� 
 * �������� ����, ��� ���������� ���������, ���������� � ������ ������, ����� ���������
 */

#ifndef MATRIX_KEYBOARD_4X4_H
#define	MATRIX_KEYBOARD_4X4_H

//******************************************************************************
// ������ include (���������� ������������ ����� ������������ �������)
#include <stdint.h>
//******************************************************************************


//******************************************************************************
// ������ ����������� ��������
// ���������� ����������� ���������� ����������� �������� (����������� 
// ������������ ��������� �� ����� ���� ������ ���������� ����������� ��������)
#define MAX_VIRT_TMR_MKB4x4                 8    
#define MK_TEST_CONST                       2


//==============================================================================
// ����������� ������� �������
#define MS_MKB4x4                           1
#define SEC_MKB4x4                          (MS_MKB4x4 * 1000)
#define DEBOUNCE_MKB4x4                     (MS_MKB4x4 * 50)
#define FIRST_DELAY_MKB4x4                  (MS_MKB4x4 * 500)
#define AUTO_REPEAT_MKB4x4                  (MS_MKB4x4 * 200)
//==============================================================================
//******************************************************************************


//******************************************************************************
// ������ ����������� �����

typedef enum {
    NOT_PRESS = 0,
    PRESS = 2,
    DEBONCE = 1,
    FIRST_DELAY = 3,
    AUTO_REPEAT = 4
} FSM_State_MKB4x4; //  ��������� �������� ��������� ��������� ����������

typedef enum {
    STOP = 0,
    RUNNING = 1,
    PAUSE = 2
} vTMRState_MKB4x4; //  ��������� � ������� ����� ��������� ����������� �������

typedef struct {
    // ������ � ������� ��������� � ��������� ��� ���� ����� ������� ������ ����������
    // ���������� ����� � ���� �����, ��� ���� ���������� ������� ������� � ���������� 
    // ������ ������� (�� ������������)
    uint16_t rows;
    uint16_t cols;

    unsigned char keyCode; //               ��� ������� �������
    unsigned char _keyCode; //              ��� ������� ������� � ���������� ������
    uint16_t id_TMR; //                     ����� ������������ ������� (�� ������ 
    //                                      ��������� �������� #define MAX_VIRT_TMR_MKB4x4)

    // ������ ����������� �� �������, ������������ ��� void
    void (*pOutSet[4])(void); //             ������ ���������� �� �������, ��������������� "HIGH" �� ������� 0-3
    void (*pOutReSet[4])(void); //           ������ ���������� �� �������, ��������������� "LOW" �� ������� 0-3

    // ������ ���������� �� �������, ������������ ��� uint16_t
    uint16_t(*pIn[4])(void); //              ��������� �� �������, ����������� ��������� ������� � 4-7

    //--------------------------------------------------------------------------
    // ������ �������� ��������� ����������
    unsigned char keyCodeArr[4][4];

    /* ������ (��������� ���, ��� ���������������� ������ ���������):
         unsigned char KeyCode [4][4] = {
            {'1', '2', '3', 'A'},
            {'4', '5', '6', 'B'},
            {'7', '8', '9', 'C'},
            {'*', '0', '#', 'D'}
        };
     */
    //--------------------------------------------------------------------------

    FSM_State_MKB4x4 status; //             ������ ����������� ������� ������ ����������

    //==========================================================================
    // ��������� � ���������� �������, ������� ����������������
    //    vTMRState_MKB4x4 gTMRState[MAX_VIRT_TMR_MKB4x4]; // ������ ��������� 
    //    //                                                  ����������� ��������
    //==========================================================================
} MKB4x4_Typedef;

//******************************************************************************


//******************************************************************************
// ������ ����������� ���������� ����������
//extern FSM_State_MKB4x4_TypeDef State_MKB4x4;
//extern uint16_t gTMR_MKB4x4[MAX_VIRT_TMR_MKB4x4];
//extern vTMRState_MKB4x4_TypeDef gTMRState_MKB4x4[MAX_VIRT_TMR_MKB4x4];
//******************************************************************************


//******************************************************************************
// ������ ���������� ���������� �������
//==============================================================================
// ���������� ����������� ��������
extern void IntProcess_vTMR_MKB4x4(void);
//==============================================================================


//==============================================================================
//extern unsigned char KeyPressDetect_MKB4x4(InOut_MKB4x4_Typedef *PORT);
extern unsigned char ProcessKeyFSM_MKB4x4(MKB4x4_Typedef *MKB);
//==============================================================================
//******************************************************************************


//******************************************************************************
// ������ ����������� ��������
//******************************************************************************

#endif	/* MATRIX_KEYBOARD_4X4_H */

////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
