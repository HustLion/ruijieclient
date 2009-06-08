/*******************************************************************************\
 * RuijieClient -- a CLI based Ruijie Client authentication modified from mystar *
 *                                                                               *
 * Copyright (C) Gong Han, Chen Tingjun                                          *
 \*******************************************************************************/

/*
 * This program is modified from MyStar, the original author is netxray@byhh.
 *
 * Many thanks to netxray@byhh
 *
 * AUTHORS:
 *   Gong Han  <gong AT fedoraproject.org> from CSE@FJNU CN
 *   Chen Tingjun <chentingjun AT gmail.com> from POET@FJNU CN
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

/*  mystar.h & mystar.c are writton by NetXRay */

#ifndef RUIJIECLIENT_H
#define RUIJIECLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <pcap.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include "global.h"

#define FILTER_STR "ether[12:2]=0x888e and ether dst %02x:%02x:%02x:%02x:%02x:%02x"

#define MAX_MSG_LEN 1024
#define MAX_U_MSG_LEN MAX_MSG_LEN*2

#define C_VERSION "0.1.1"
#define CONF_NAME "ruijie.conf"
#define CONF_PATH "/etc/ruijie.conf"
#define TMP_FILE "/tmp/ruijieclient_tmp"

#endif /* RUIJIECLIENT_H */
