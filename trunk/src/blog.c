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

#include "blog.h"

static int blogIsInitialized = 0;
static unsigned char m_IP[4];
static unsigned char m_NetMask[4];
static unsigned char m_NetGate[4];
static unsigned char m_DNS1[4];
static unsigned char circleCheck[2]; //那两个鬼值

static unsigned char Table[]={
  0x00,0x00,0x21,0x10,0x42,0x20,0x63,0x30,0x84,0x40,0xA5,0x50,0xC6,0x60,0xE7,0x70,
  0x08,0x81,0x29,0x91,0x4A,0xA1,0x6B,0xB1,0x8C,0xC1,0xAD,0xD1,0xCE,0xE1,0xEF,0xF1,
  0x31,0x12,0x10,0x02,0x73,0x32,0x52,0x22,0xB5,0x52,0x94,0x42,0xF7,0x72,0xD6,0x62,
  0x39,0x93,0x18,0x83,0x7B,0xB3,0x5A,0xA3,0xBD,0xD3,0x9C,0xC3,0xFF,0xF3,0xDE,0xE3,
  0x62,0x24,0x43,0x34,0x20,0x04,0x01,0x14,0xE6,0x64,0xC7,0x74,0xA4,0x44,0x85,0x54,
  0x6A,0xA5,0x4B,0xB5,0x28,0x85,0x09,0x95,0xEE,0xE5,0xCF,0xF5,0xAC,0xC5,0x8D,0xD5,
  0x53,0x36,0x72,0x26,0x11,0x16,0x30,0x06,0xD7,0x76,0xF6,0x66,0x95,0x56,0xB4,0x46,
  0x5B,0xB7,0x7A,0xA7,0x19,0x97,0x38,0x87,0xDF,0xF7,0xFE,0xE7,0x9D,0xD7,0xBC,0xC7,
  0xC4,0x48,0xE5,0x58,0x86,0x68,0xA7,0x78,0x40,0x08,0x61,0x18,0x02,0x28,0x23,0x38,
  0xCC,0xC9,0xED,0xD9,0x8E,0xE9,0xAF,0xF9,0x48,0x89,0x69,0x99,0x0A,0xA9,0x2B,0xB9,
  0xF5,0x5A,0xD4,0x4A,0xB7,0x7A,0x96,0x6A,0x71,0x1A,0x50,0x0A,0x33,0x3A,0x12,0x2A,
  0xFD,0xDB,0xDC,0xCB,0xBF,0xFB,0x9E,0xEB,0x79,0x9B,0x58,0x8B,0x3B,0xBB,0x1A,0xAB,
  0xA6,0x6C,0x87,0x7C,0xE4,0x4C,0xC5,0x5C,0x22,0x2C,0x03,0x3C,0x60,0x0C,0x41,0x1C,
  0xAE,0xED,0x8F,0xFD,0xEC,0xCD,0xCD,0xDD,0x2A,0xAD,0x0B,0xBD,0x68,0x8D,0x49,0x9D,
  0x97,0x7E,0xB6,0x6E,0xD5,0x5E,0xF4,0x4E,0x13,0x3E,0x32,0x2E,0x51,0x1E,0x70,0x0E,
  0x9F,0xFF,0xBE,0xEF,0xDD,0xDF,0xFC,0xCF,0x1B,0xBF,0x3A,0xAF,0x59,0x9F,0x78,0x8F,
  0x88,0x91,0xA9,0x81,0xCA,0xB1,0xEB,0xA1,0x0C,0xD1,0x2D,0xC1,0x4E,0xF1,0x6F,0xE1,
  0x80,0x10,0xA1,0x00,0xC2,0x30,0xE3,0x20,0x04,0x50,0x25,0x40,0x46,0x70,0x67,0x60,
  0xB9,0x83,0x98,0x93,0xFB,0xA3,0xDA,0xB3,0x3D,0xC3,0x1C,0xD3,0x7F,0xE3,0x5E,0xF3,
  0xB1,0x02,0x90,0x12,0xF3,0x22,0xD2,0x32,0x35,0x42,0x14,0x52,0x77,0x62,0x56,0x72,
  0xEA,0xB5,0xCB,0xA5,0xA8,0x95,0x89,0x85,0x6E,0xF5,0x4F,0xE5,0x2C,0xD5,0x0D,0xC5,
  0xE2,0x34,0xC3,0x24,0xA0,0x14,0x81,0x04,0x66,0x74,0x47,0x64,0x24,0x54,0x05,0x44,
  0xDB,0xA7,0xFA,0xB7,0x99,0x87,0xB8,0x97,0x5F,0xE7,0x7E,0xF7,0x1D,0xC7,0x3C,0xD7,
  0xD3,0x26,0xF2,0x36,0x91,0x06,0xB0,0x16,0x57,0x66,0x76,0x76,0x15,0x46,0x34,0x56,
  0x4C,0xD9,0x6D,0xC9,0x0E,0xF9,0x2F,0xE9,0xC8,0x99,0xE9,0x89,0x8A,0xB9,0xAB,0xA9,
  0x44,0x58,0x65,0x48,0x06,0x78,0x27,0x68,0xC0,0x18,0xE1,0x08,0x82,0x38,0xA3,0x28,
  0x7D,0xCB,0x5C,0xDB,0x3F,0xEB,0x1E,0xFB,0xF9,0x8B,0xD8,0x9B,0xBB,0xAB,0x9A,0xBB,
  0x75,0x4A,0x54,0x5A,0x37,0x6A,0x16,0x7A,0xF1,0x0A,0xD0,0x1A,0xB3,0x2A,0x92,0x3A,
  0x2E,0xFD,0x0F,0xED,0x6C,0xDD,0x4D,0xCD,0xAA,0xBD,0x8B,0xAD,0xE8,0x9D,0xC9,0x8D,
  0x26,0x7C,0x07,0x6C,0x64,0x5C,0x45,0x4C,0xA2,0x3C,0x83,0x2C,0xE0,0x1C,0xC1,0x0C,
  0x1F,0xEF,0x3E,0xFF,0x5D,0xCF,0x7C,0xDF,0x9B,0xAF,0xBA,0xBF,0xD9,0x8F,0xF8,0x9F,
  0x17,0x6E,0x36,0x7E,0x55,0x4E,0x74,0x5E,0x93,0x2E,0xB2,0x3E,0xD1,0x0E,0xF0,0x1E};

static unsigned char sCircleBase[0x15]=
{
  0x00,0x00,0x13,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00
};

static void
Blog(void);

//configure the 4 parameters Blog() and FillNetParameter() need.
void
InitializeBlog(const unsigned char *m_ip, const unsigned char *m_netmask,
    const unsigned char *m_netgate, const unsigned char *m_dns1, const int m_dhcpmode)
{
  memcpy(m_IP, m_ip, 4);
  memcpy(m_NetMask, m_netmask, 4);
  memcpy(m_NetGate, m_netgate, 4);
  memcpy(m_DNS1, m_dns1, 4);

  if (m_dhcpmode > 0)//Dhcp Enabled
    sCircleBase[0x04] = 0x01;

  Blog();

  blogIsInitialized = 1;
}

//Fill in some additional information  Ruijie Corp. required.
//You should call InitializeBlog() before calling this function.
void
FillNetParamater(unsigned char ForFill[])
{
  if (blogIsInitialized == 0)
    err_quit("Blog algorithm not initialied yet \n");

  ForFill[0] = Alog(m_IP[0]);
  ForFill[1] = Alog(m_IP[1]);
  ForFill[2] = Alog(m_IP[2]);
  ForFill[3] = Alog(m_IP[3]);
  ForFill[4] = Alog(m_NetMask[0]);
  ForFill[5] = Alog(m_NetMask[1]);
  ForFill[6] = Alog(m_NetMask[2]);
  ForFill[7] = Alog(m_NetMask[3]);
  ForFill[8] = Alog(m_NetGate[0]);
  ForFill[9] = Alog(m_NetGate[1]);
  ForFill[10] = Alog(m_NetGate[2]);
  ForFill[11] = Alog(m_NetGate[3]);
  ForFill[12] = Alog(m_DNS1[0]);
  ForFill[13] = Alog(m_DNS1[1]);
  ForFill[14] = Alog(m_DNS1[2]);
  ForFill[15] = Alog(m_DNS1[3]);
  ForFill[16] = Alog(circleCheck[0]);
  ForFill[17] = Alog(circleCheck[1]);
}

//A transformation of one-byte-for-one-byte
unsigned char
Alog(unsigned char BForAlog)
{
  int a = 0, b = 0, c = 0, d = 0, iRt;

  a = BForAlog;
  c = a;
  d = a;
  c &= 0x40;
  b = a;
  d >>= 2;
  c |= d;
  d = a;
  c >>= 2;
  d &= 0x20;
  c |= d;
  d = a;
  c >>= 2;
  d &= 0x10;
  c |= d;

  d = a;
  d &= 2;
  b <<= 2;
  d |= b;
  b = a;
  d <<= 2;
  b &= 4;
  a &= 8;
  d |= b;
  d <<= 2;
  d |= a;

  c >>= 1;
  d <<= 1;
  c |= d;
  iRt = (~c) & 0xff;
  return iRt;
}

//那帮家伙们，单靠这个算法就想区别实达客户端和非实达客户端 -_- !!
//The only use of function Blog() is to work out circleCheck[2],
//with and only with the help of 4 parameters----m_IP, m_NetMask, m_NetGate, m_DNS1
static void
Blog(void)
{
  int iCircle = 0x15;
  int i, ax = 0, bx = 0, dx = 0;

  sCircleBase[0x05] = m_IP[0];
  sCircleBase[0x06] = m_IP[1];
  sCircleBase[0x07] = m_IP[2];
  sCircleBase[0x08] = m_IP[3];
  sCircleBase[0x09] = m_NetMask[0];
  sCircleBase[0x0a] = m_NetMask[1];
  sCircleBase[0x0b] = m_NetMask[2];
  sCircleBase[0x0c] = m_NetMask[3];
  sCircleBase[0x0d] = m_NetGate[0];
  sCircleBase[0x0e] = m_NetGate[1];
  sCircleBase[0x0f] = m_NetGate[2];
  sCircleBase[0x10] = m_NetGate[3];
  sCircleBase[0x11] = m_DNS1[0];
  sCircleBase[0x12] = m_DNS1[1];
  sCircleBase[0x13] = m_DNS1[2];
  sCircleBase[0x14] = m_DNS1[3];

  for (i = 0; i < iCircle; i++)
    {
      dx = ax;
      bx = 0;
      bx = (bx & 0xff00) | sCircleBase[i]; // add "( )" by cdx
      dx &= 0xffff;
      dx >>= 8;
      dx ^= bx;
      bx = 0;
      bx &= 0x00ff;
      bx |= (ax & 0xff) << 8;

      ax = Table[dx * 2] | Table[dx * 2 + 1] << 8;
      ax ^= bx;
    }
  circleCheck[0] = (unsigned char) ((ax & 0xff00) >> 8);
  circleCheck[1] = (unsigned char) (ax & 0x00ff);
}
