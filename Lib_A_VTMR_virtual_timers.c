/*
 * File:   Lib_A_vtmr_virtual_timers.c
 * Author: m.isaev
 *
 * Created on 4 октября 2017 г., 9:33
 */

//******************************************************************************
// Секция include: здесь подключается заголовочный файл к модулю
#include "Lib_A_VTMR_virtual_timers.h"
//******************************************************************************


//******************************************************************************
//==============================================================================
// Глобальные переменные
//==============================================================================


//==============================================================================
// Локальные переменные
//==============================================================================
//******************************************************************************


//******************************************************************************
// Секция прототипов локальных функций
//******************************************************************************


//******************************************************************************
// Секция описания функций (сначала глобальных, потом локальных)

void VTMR_RestartVirtTimer(
                           VTMR_tmr_s *vTMR)
{
	vTMR->state = VTMR_RUNNING;
    vTMR->cnt = 0;
}

void VTMR_StopVirtTimer(
                        VTMR_tmr_s *vTMR)
{
	vTMR->state = VTMR_STOP;
}

void VTMR_StartVirtTimer(
                         VTMR_tmr_s *vTMR)
{
	vTMR->state = VTMR_RUNNING;
}

uint32_t VTMR_GetValueVirtTimer(
                                VTMR_tmr_s *vTMR)
{
    return vTMR->cnt;
}

void VTMR_IntProcess(
                     VTMR_tmr_s *vTMR)
{
	if (vTMR->state == VTMR_RUNNING)
    {
        vTMR->cnt++;
    }
}

/**
 * @brief   Функция сбрасывает в нуль виртуальный таймер;
 * @param[in]   *vTMR:  Указатель на структуру виртуального таймера;
 * @return None;
 */
void VTMR_StartTimer(
                     VTMR_tmr_s *pVTMR)
{
    pVTMR->cnt = (uint32_t) (((uint32_t) * pVTMR->pHighCntReg << 16)
            | *pVTMR->pLowCntReg);
}

/**
 * @brief   Функция вычисляет временной интервал между вызовами функции
 *          "VTMR_StartTimer" и "VTMR_GetTimerValue"
 * @param[in,out]   *vTMR:  Указатель на структуру виртуального таймера;
 * @return  Временной интервал между вызовами функций "VTMR_StartTimer" и
 *          "VTMR_GetTimerValue" в тиках аппаратного счетчика;
 */
uint32_t VTMR_GetTimerValue(
                            VTMR_tmr_s *pVTMR)
{
    pVTMR->timeInterval = (uint32_t) (((uint32_t) * pVTMR->pHighCntReg << 16)
            | *pVTMR->pLowCntReg)
            - pVTMR->cnt;

    return pVTMR->timeInterval;
}

/**
 * @brief   Функция инициализирует структуру виртуального таймера;
 * @param[in]   *pVTMR: Указатель на структуру виртуального таймера;
 * @param[in]   *pHighCntReg:   Указатель на старшие 16 бит аппаратного счетчика:
 * @param[in]   *pLowCntReg:    Указатель на младшие 16 бит аппаратного счетчика:
 * @return  None;
 */
void VTMR_InitTimerStruct(
                          VTMR_tmr_s *pVTMR,
                          uint32_t *pHighCntReg,
                          uint32_t *pLowCntReg)
{
    pVTMR->pHighCntReg = pHighCntReg;
    pVTMR->pLowCntReg = pLowCntReg;
    pVTMR->cnt = 0;
    pVTMR->timeInterval = 0;
}
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
