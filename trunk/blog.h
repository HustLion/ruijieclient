 /*******************************************************************************\
 * RuijieClient -- a CLI based Ruijie Client authentication modified from mystar *
 *                                                                               *
 * Copyright (C) Gong Han, Chen Tingjun                                          *
 \*******************************************************************************/
 
/*
 * This program is modified from MyStar, the original author is netxray@byhh.
 * We just add something to make it more convinence.
 *
 * Many thanks to netxray@byhh
 *
 * AUTHORS:
 *   Gong Han  <gonghan1989@gmail.com> from CSE@FJNU CN
 *   Chen Tingjun <chentingjun@gmail.com> from POET@FJNU CN
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
*/

#ifndef BLOG_H
#define BLOG_H

/* The Blog algorithm is mainly de-assembled out by SnowWings.        */
/* We should thank him very much, because the algorithm is crucial.  */

#include <sys/types.h>
#include <string.h>
#include "myerr.h"

void
InitializeBlog(const unsigned char *m_ip, const unsigned char *m_netmask,
    const unsigned char *m_netgate, const unsigned char *m_dns1);

void
FillNetParamater(unsigned char ForFill[]);

unsigned char
Alog(unsigned char BForAlog);

#endif
