#include "fsl_os_abstraction.h"
#include "fsl_os_abstraction_zephyr.h"

/*FUNCTION**********************************************************************
*
* Function Name : OSA_MutexCreate
* Description   : This function is used to create a mutex.
* Return        : Mutex handle of the new mutex, or NULL if failed.
*
* END**************************************************************************/
osa_status_t OSA_MutexCreate(osa_mutex_handle_t mutexHandle)
{
  assert(NULL != mutexHandle);
  k_mutex_init((struct k_mutex *)mutexHandle);
  return KOSA_StatusSuccess;
}

/*FUNCTION**********************************************************************
*
* Function Name : OSA_MutexLock
* Description   : This function checks the mutex's status, if it is unlocked,
* lock it and returns KOSA_StatusSuccess, otherwise, wait for the mutex.
* This function returns KOSA_StatusSuccess if the mutex is obtained, returns
* KOSA_StatusError if any errors occur during waiting. If the mutex has been
* locked, pass 0 as timeout will return KOSA_StatusTimeout immediately.
*
* END**************************************************************************/
osa_status_t OSA_MutexLock(osa_mutex_handle_t mutexHandle, uint32_t millisec)
{
  assert(mutexHandle);
  k_timeout_t timeout;
  osa_status_t status = KOSA_StatusSuccess;

  /* Convert timeout from millisecond to tick. */
  if (millisec == osaWaitForever_c) {
    timeout = K_FOREVER;
  } else {
    timeout = K_MSEC(millisec);
  }

  if (k_mutex_lock((struct k_mutex *)mutexHandle, timeout) != 0) {
    status = KOSA_StatusError;
  }
  return status;
}

/*FUNCTION**********************************************************************
*
* Function Name : OSA_MutexUnlock
* Description   : This function is used to unlock a mutex.
*
* END**************************************************************************/
osa_status_t OSA_MutexUnlock(osa_mutex_handle_t mutexHandle)
{
  assert(mutexHandle);
  osa_status_t status = KOSA_StatusSuccess;

  if (k_mutex_unlock((struct k_mutex *)mutexHandle) != 0) {
    status = KOSA_StatusError;
  }
  return status;
}

/*FUNCTION**********************************************************************
*
* Function Name : OSA_MutexDestroy
* Description   : This function is used to destroy a mutex.
* Return        : KOSA_StatusSuccess if the lock object is destroyed successfully, otherwise
*   return KOSA_StatusError.
*
* END**************************************************************************/
osa_status_t OSA_MutexDestroy(osa_mutex_handle_t mutexHandle)
{
  assert(mutexHandle);
  return KOSA_StatusSuccess;
}

/*FUNCTION**********************************************************************
*
* Function Name : OSA_TimeDelay
* Description   : This function is used to suspend the active thread for the given number of
*   milliseconds.
*
* END**************************************************************************/
void OSA_TimeDelay(uint32_t millisec)
{
  k_msleep(millisec);
}
