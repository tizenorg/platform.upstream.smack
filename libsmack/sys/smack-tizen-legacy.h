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
 * Smack user space library - compatibility with smack 1.0.4
 */

#ifndef _SYS_SMACK_COMPATIBILITY_1_0_4_H
#define _SYS_SMACK_COMPATIBILITY_1_0_4_H

enum smack_label_type {
	SMACK_LABEL_ACCESS,
	SMACK_LABEL_EXEC,
	SMACK_LABEL_MMAP,
	SMACK_LABEL_TRANSMUTE,
	SMACK_LABEL_IPIN,
	SMACK_LABEL_IPOUT,
};

int smack_getlabel(const char *path, char** label, enum smack_label_type type) __attribute__((deprecated));
int smack_lgetlabel(const char *path, char** label, enum smack_label_type type) __attribute__((deprecated));
int smack_fgetlabel(int fd, char** label, enum smack_label_type type) __attribute__((deprecated));
int smack_setlabel(const char *path, const char* label, enum smack_label_type type) __attribute__((deprecated));
int smack_lsetlabel(const char *path, const char* label, enum smack_label_type type) __attribute__((deprecated));
int smack_fsetlabel(int fd, const char* label, enum smack_label_type type) __attribute__((deprecated));

#endif /* _SYS_SMACK_COMPATIBILITY_1_0_4_H */

