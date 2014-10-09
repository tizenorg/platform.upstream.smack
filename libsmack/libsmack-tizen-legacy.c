/*
 * This file is part of libsmack
 *
 * Copyright (C) 2010, 2011 Nokia Corporation
 * Copyright (C) 2011, 2012, 2013 Intel Corporation
 * Copyright (C) 2012, 2013 Samsung Electronics Co.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

/*!
 * Smack user space library - tizen legacy functions
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/smack.h>
#include <linux/xattr.h>

static inline const char *xattr_name(enum smack_label_type type)
{
	switch(type) {
	case SMACK_LABEL_ACCESS: return XATTR_NAME_SMACK;
	case SMACK_LABEL_EXEC: return XATTR_NAME_SMACKEXEC;
	case SMACK_LABEL_MMAP: return XATTR_NAME_SMACKMMAP;
	case SMACK_LABEL_TRANSMUTE: return XATTR_NAME_SMACKTRANSMUTE;
	case SMACK_LABEL_IPIN: return XATTR_NAME_SMACKIPIN;
	case SMACK_LABEL_IPOUT: return XATTR_NAME_SMACKIPOUT;
	}
	return NULL;
}

static inline int getresult(char** label, int status)
{
   if (status >= 0)
      return 0;
   if (errno == ENODATA)
      *label = NULL;
   return -1;
}

static inline int setlabel(const char** label, enum smack_label_type type)
{
   if (!*label)
      return 1;
   if (type == SMACK_LABEL_TRANSMUTE) {
      if (!strcmp(*label, "0") || !strcmp(*label, "FALSE")) {
         *label = NULL;
         return 1;
      } else if (!strcmp(*label, "1") || !strcmp(*label, "TRUE")) {
         *label = "TRUE";
         return 1;
      }
      return 0;
   }
   if (!**label)
      *label = NULL;
   return 1;
}

int smack_getlabel(const char *path, char** label, enum smack_label_type type)
{
   return getresult(label, smack_new_label_from_path(path, xattr_name(type), 1, label));
}

int smack_lgetlabel(const char *path, char** label, enum smack_label_type type)
{
   return getresult(label, smack_new_label_from_path(path, xattr_name(type), 0, label));
}

int smack_fgetlabel(int fd, char** label, enum smack_label_type type)
{
   return getresult(label, smack_new_label_from_file(fd, xattr_name(type), label));
}

int smack_setlabel(const char *path, const char* label, enum smack_label_type type)
{
   if (!setlabel(&label, type))
      return -1;
   return label ? smack_set_label_for_path(path, xattr_name(type), 1, label)
                : smack_remove_label_for_path(path, xattr_name(type), 1);
}

int smack_lsetlabel(const char *path, const char* label, enum smack_label_type type)
{
   if (!setlabel(&label, type))
      return -1;
   return label ? smack_set_label_for_path(path, xattr_name(type), 0, label)
                : smack_remove_label_for_path(path, xattr_name(type), 0);
}

int smack_fsetlabel(int fd, const char* label, enum smack_label_type type)
{
   if (!setlabel(&label, type))
      return -1;
   return label ? smack_set_label_for_file(fd, xattr_name(type), label)
                : smack_remove_label_for_file(fd, xattr_name(type));
}

