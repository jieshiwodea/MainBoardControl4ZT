/*
 * user_errno.c
 *
 *  Created on: July 3, 2019
 *      Author: wt
 */

#ifndef __ERRNO_H__
#define __ERRNO_H__

#ifdef ERRNO_H_GLOBAL
  #define ERRNO_H_EXTERN 
#else
  #define ERRNO_H_EXTERN extern
#endif

#ifndef NULL
  #define NULL ((void *)0)
#endif

#ifndef RM_OK
#define  WT_OK              0
#endif

#define WT_ERROR             1
#define WT_INVAL             2  
#define WT_EXISTED           3  
#define WT_UNREGISTERED      4 
#define WT_NOSTATE           5
#define WT_USED              6
#define WT_NOMEM             7

#endif // __ERRNO_H__
