/**
 * @file    "Lib_A_VTMR_virtual_timers.c"
 * @author  Isaev Mickle;
 * @version Beta;
 * @date    19.03.2018
 * #
 * @brief   Библиотека содержит функции для работы с виртуальными таймерами.
 *          Функции в данной библиотеке делятся на 2 категории:
 *          --------------------------------------------------------------------
 *          --  Функции виртуальных таймеров, ведущие отсчет времени через
 *              программный инкремент виртуального таймера (как правило,
 *              в прерывании от аппаратного таймера);
 *      @see    void VTMR_RestartVirtTimer(VTMR_tmr_s *vTMR);
 *              void VTMR_StopVirtTimer(VTMR_tmr_s *vTMR);
 *              void VTMR_StartVirtTimer(VTMR_tmr_s *vTMR);
 *              uint32_t VTMR_GetValueVirtTimer(VTMR_tmr_s *vTMR);
 *              void VTMR_IntProcess(VTMR_tmr_s *vTMR);
 *      @note   При таком способе отсчета времени инкремент виртуального таймера
 *              выполняется при вызове функции VTMR_IntProcess();
 *      @code
 *          // Объявление глобальных переменных
 *          VTMR_tmr_s myVirtTimerStruct;
 *          uint32_t myVirtTimerValue;
 *
 *          int main(void)
 *          {
 *              ...
 *              // Разрешает инкремент виртуального таймера при вызове
 *              // функции VTMR_IntProcess();
 *              VTMR_StartVirtTimer(&myVirtTimerStruct);
 *              ...
 *              while(1)
 *              {
 *                  // Разрешает инкремент виртуального таймера при вызове
 *                  // функции VTMR_IntProcess() и сбрасывает значение
 *                  // счетчика в нуль - перезапуск виртуального таймера;
 *                  VTMR_RestartVirtTimer(&myVirtTimerStruct);
 *                  ...
 *                  // Получение количества вызова функции VTMR_IntProcess();
 *                  // (получение количества прерываний  "void TIMER_1_INTERRUPT(void)")
 *                  myVirtTimerValue = VTMR_GetValueVirtTimer(&myVirtTimerStruct);
 *
 *                  // Аналогичный результат даст такая запись;
 *                  myVirtTimerValue = myVirtTimerStruct.cnt;
 *
 *                  // Запрещает инкремент виртуального таймера при вызове
 *                  // функции VTMR_IntProcess() - остановка виртуального таймера;
 *                  VTMR_StopVirtTimer(&myVirtTimerStruct);
 *              }
 *          }
 *
 *          void TIMER_1_INTERRUPT(void)
 *          {
 *              ...
 *              VTMR_IntProcess(&myVirtTimerStruct);
 *          }
 *      @endcode
 *          --------------------------------------------------------------------
 *
 *
 *          --------------------------------------------------------------------
 *          --  функции виртуальных таймеров, ведущие отсчет времени с использованием
 *              аппаратного таймера, сконфигурированного для работы в 32-х битном режиме.
 *      @note   При таком способе отсчета времени библиотека не использует прерывания.
 *      @see    void VTMR_StartTimer(VTMR_tmr_s *pVTMR);
 *              uint32_t VTMR_GetTimerValue(VTMR_tmr_s *pVTMR);
 *              uint32_t VTMR_GetMaxTimerValue(VTMR_tmr_s *pVTMR);
 *              void VTMR_InitTimerStruct(VTMR_tmr_s *pVTMR);
 *      @code
 *          // Объявление глобальных переменных
 *          VTMR_tmr_s myVirtTimerStruct;
 *          uint32_t myVirtTimerValue;
 *
 *          int main(void)
 *          {
 *              ...
 *              // Пример для микроконтроллеров PIC:
 *              // где TMR9 - указатель на старшие 16 бит аппаратного счетчика;
 *                     TMR8 - указатель на младшие 16 бит аппаратного счетчика;
 *              VTMR_InitTimerStruct(&myVirtTimerStruct,
 *                                   (uint32_t*) &TMR9,
 *                                   (uint32_t*) &TMR8);
 *
 *              // Пример для микроконтроллеров STM32;
 *              // где TIM3->CNT - указатель на старшие 16 бит аппаратного счетчика;
 *                     TIM4->CNT - указатель на младшие 16 бит аппаратного счетчика;
 *              VTMR_InitTimerStruct(&myVirtTimerStruct,
 *                                   (uint32_t*) &TIM3->CNT,
 *                                   (uint32_t*) &TIM4->CNT);
 *              ...
 *              while(1)
 *              {
 *                  // Запись в переменную счетчика текущего значения
 *                  // аппаратного 32-х битного счетчика;
 *                  // @see VTMR_tmr_s;
 *                  VTMR_StartTimer(&myVirtTimerStruct);
 *                  ...
 *
 *                  // Определение разницы между текущим значением аппаратного
 *                  // 32-х битного счетчика и значением переменной счетчика в
 *                  // структуре myVirtTimerStruct.
 *                  // В результате имеем количество тиков аппаратного счетчика
 *                  // между вызовами функций VTMR_StartTimer() и VTMR_GetTimerValue();
 *                  // @see VTMR_tmr_s;
 *                  myVirtTimerValue = VTMR_GetTimerValue(&myVirtTimerStruct);
 *
 *                  // Причем
 *                  myVirtTimerValue == myVirtTimerStruct.timeInterval;
 *                  ...
 *              }
 *          }
 *      @endcode
 *      ------------------------------------------------------------------------
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

/* ################################################################## */
/* <Функции виртуальных таймеров, привязанных к аппаратному счетчику> */
/* ################################################################## */

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
 * @param[in,out]   *pVTMR: Указатель на структуру виртуального таймера;
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
 * @brief   Функция вычисляет временной интервал между вызовами функции
 *          "VTMR_StartTimer" и "VTMR_GetTimerValue" и возвращает наибольшее
 *          значение временного интервала;
 * @param[in,out]   *pVTMR: Указатель на структуру виртуального таймера;
 * @return  Наибольший временной интервал между вызовами функций "VTMR_StartTimer" и
 *          "VTMR_GetTimerValue" в тиках аппаратного счетчика;
 */
uint32_t VTMR_GetMaxTimerValue(
                               VTMR_tmr_s *pVTMR)
{
    uint32_t timeInterval = (uint32_t) (((uint32_t) * pVTMR->pHighCntReg << 16)
            | *pVTMR->pLowCntReg)
            - pVTMR->cnt;

    // Если новое значение временного интервала больше предыдущего:
    if (timeInterval > pVTMR->timeInterval)
    {
        pVTMR->timeInterval = timeInterval;
    }
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
                          const uint16_t * const pHighCntReg,
                          const uint16_t * const pLowCntReg)
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
