/**
 * @file charset.h
 * @author Hightman Mar
 * @editor set number ; syntax on ; set autoindent ; set tabstop=4 (vim)
 * $Id: charset.h,v 1.2 2009/05/26 02:44:08 hightman Exp $
 */

#ifndef	_SCWS_CHARSET_20070528_H_
#define	_SCWS_CHARSET_20070528_H_

#ifdef WIN32
#	include "config_win32.h"
#endif

/* api used to change the charset assocted */
unsigned char *charset_table_get(const char *cs);

#endif
