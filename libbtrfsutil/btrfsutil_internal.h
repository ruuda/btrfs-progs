/*
 * Copyright (C) 2018 Facebook
 *
 * This file is part of libbtrfsutil.
 *
 * libbtrfsutil is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libbtrfsutil is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libbtrfsutil.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BTRFS_UTIL_INTERNAL_H
#define BTRFS_UTIL_INTERNAL_H

#include <asm/byteorder.h>

#include "btrfsutil.h"

#define BTRFS_UUID_SIZE 16

#define BTRFS_FIRST_FREE_OBJECTID 256ULL
#define BTRFS_ROOT_TREE_OBJECTID 1ULL
#define BTRFS_ORPHAN_OBJECTID -5ULL
#define BTRFS_INODE_ITEM_KEY		1
#define BTRFS_INODE_REF_KEY		12
#define BTRFS_INODE_EXTREF_KEY		13
#define BTRFS_XATTR_ITEM_KEY		24
#define BTRFS_ORPHAN_ITEM_KEY		48
#define BTRFS_DIR_LOG_ITEM_KEY  60
#define BTRFS_DIR_LOG_INDEX_KEY 72
#define BTRFS_DIR_ITEM_KEY	84
#define BTRFS_DIR_INDEX_KEY	96
#define BTRFS_EXTENT_DATA_KEY	108
#define BTRFS_CSUM_ITEM_KEY	120
#define BTRFS_EXTENT_CSUM_KEY	128
#define BTRFS_ROOT_ITEM_KEY	132
#define BTRFS_ROOT_BACKREF_KEY	144
#define BTRFS_ROOT_REF_KEY	156
#define BTRFS_EXTENT_ITEM_KEY	168
#define BTRFS_METADATA_ITEM_KEY	169
#define BTRFS_TREE_BLOCK_REF_KEY	176
#define BTRFS_EXTENT_DATA_REF_KEY	178
#define BTRFS_EXTENT_REF_V0_KEY		180
#define BTRFS_SHARED_BLOCK_REF_KEY	182
#define BTRFS_SHARED_DATA_REF_KEY	184
#define BTRFS_BLOCK_GROUP_ITEM_KEY 192
#define BTRFS_FREE_SPACE_INFO_KEY 198
#define BTRFS_FREE_SPACE_EXTENT_KEY 199
#define BTRFS_FREE_SPACE_BITMAP_KEY 200
#define BTRFS_DEV_EXTENT_KEY	204
#define BTRFS_DEV_ITEM_KEY	216
#define BTRFS_CHUNK_ITEM_KEY	228
#define BTRFS_BALANCE_ITEM_KEY	248
#define BTRFS_QGROUP_STATUS_KEY		240
#define BTRFS_QGROUP_INFO_KEY		242
#define BTRFS_QGROUP_LIMIT_KEY		244
#define BTRFS_QGROUP_RELATION_KEY	246
#define BTRFS_BALANCE_ITEM_KEY	248
#define BTRFS_TEMPORARY_ITEM_KEY	248
#define BTRFS_DEV_STATS_KEY		249
#define BTRFS_PERSISTENT_ITEM_KEY	249
#define BTRFS_DEV_REPLACE_KEY	250
#if BTRFS_UUID_SIZE != 16
#error "UUID items require BTRFS_UUID_SIZE == 16!"
#endif
#define BTRFS_UUID_KEY_SUBVOL	251	/* for UUIDs assigned to subvols */
#define BTRFS_UUID_KEY_RECEIVED_SUBVOL	252	/* for UUIDs assigned to
						 * received subvols */

#define BTRFS_ROOT_TREE_OBJECTID 1ULL
#define BTRFS_EXTENT_TREE_OBJECTID 2ULL
#define BTRFS_CHUNK_TREE_OBJECTID 3ULL
#define BTRFS_DEV_TREE_OBJECTID 4ULL
#define BTRFS_FS_TREE_OBJECTID 5ULL
#define BTRFS_ROOT_TREE_DIR_OBJECTID 6ULL
#define BTRFS_CSUM_TREE_OBJECTID 7ULL
#define BTRFS_QUOTA_TREE_OBJECTID 8ULL
#define BTRFS_UUID_TREE_OBJECTID 9ULL
#define BTRFS_FREE_SPACE_TREE_OBJECTID 10ULL
#define BTRFS_DEV_STATS_OBJECTID 0ULL
#define BTRFS_BALANCE_OBJECTID -4ULL
#define BTRFS_ORPHAN_OBJECTID -5ULL
#define BTRFS_TREE_LOG_OBJECTID -6ULL
#define BTRFS_TREE_LOG_FIXUP_OBJECTID -7ULL
#define BTRFS_TREE_RELOC_OBJECTID -8ULL
#define BTRFS_DATA_RELOC_TREE_OBJECTID -9ULL
#define BTRFS_EXTENT_CSUM_OBJECTID -10ULL
#define BTRFS_FREE_SPACE_OBJECTID -11ULL
#define BTRFS_FREE_INO_OBJECTID -12ULL
#define BTRFS_MULTIPLE_OBJECTIDS -255ULL
#define BTRFS_FIRST_FREE_OBJECTID 256ULL
#define BTRFS_LAST_FREE_OBJECTID -256ULL
#define BTRFS_FIRST_CHUNK_TREE_OBJECTID 256ULL
#define BTRFS_DEV_ITEMS_OBJECTID 1ULL
#define BTRFS_EMPTY_SUBVOL_DIR_OBJECTID 2ULL
#define BTRFS_STRING_ITEM_KEY	253

struct btrfs_disk_key {
	__le64 objectid;
	__u8 type;
	__le64 offset;
} __attribute__ ((__packed__));

struct btrfs_dir_item {
	struct btrfs_disk_key location;
	__le64 transid;
	__le16 data_len;
	__le16 name_len;
	__u8 type;
} __attribute__ ((__packed__));

struct btrfs_root_ref {
	__le64 dirid;
	__le64 sequence;
	__le16 name_len;
} __attribute__ ((__packed__));

struct btrfs_timespec {
	__le64 sec;
	__le32 nsec;
} __attribute__ ((__packed__));

struct btrfs_inode_item {
	/* nfs style generation number */
	__le64 generation;
	/* transid that last touched this inode */
	__le64 transid;
	__le64 size;
	__le64 nbytes;
	__le64 block_group;
	__le32 nlink;
	__le32 uid;
	__le32 gid;
	__le32 mode;
	__le64 rdev;
	__le64 flags;

	/* modification sequence number for NFS */
	__le64 sequence;

	/*
	 * a little future expansion, for more than this we can
	 * just grow the inode item and version it
	 */
	__le64 reserved[4];
	struct btrfs_timespec atime;
	struct btrfs_timespec ctime;
	struct btrfs_timespec mtime;
	struct btrfs_timespec otime;
} __attribute__ ((__packed__));

struct btrfs_root_item {
	struct btrfs_inode_item inode;
	__le64 generation;
	__le64 root_dirid;
	__le64 bytenr;
	__le64 byte_limit;
	__le64 bytes_used;
	__le64 last_snapshot;
	__le64 flags;
	__le32 refs;
	struct btrfs_disk_key drop_progress;
	__u8 drop_level;
	__u8 level;

	/*
	 * The following fields appear after subvol_uuids+subvol_times
	 * were introduced.
	 */

	/*
	 * This generation number is used to test if the new fields are valid
	 * and up to date while reading the root item. Every time the root item
	 * is written out, the "generation" field is copied into this field. If
	 * anyone ever mounted the fs with an older kernel, we will have
	 * mismatching generation values here and thus must invalidate the
	 * new fields. See btrfs_update_root and btrfs_find_last_root for
	 * details.
	 * the offset of generation_v2 is also used as the start for the memset
	 * when invalidating the fields.
	 */
	__le64 generation_v2;
	__u8 uuid[BTRFS_UUID_SIZE];
	__u8 parent_uuid[BTRFS_UUID_SIZE];
	__u8 received_uuid[BTRFS_UUID_SIZE];
	__le64 ctransid; /* updated when an inode changes */
	__le64 otransid; /* trans when created */
	__le64 stransid; /* trans when sent. non-zero for received subvol */
	__le64 rtransid; /* trans when received. non-zero for received subvol */
	struct btrfs_timespec ctime;
	struct btrfs_timespec otime;
	struct btrfs_timespec stime;
	struct btrfs_timespec rtime;
        __le64 reserved[8]; /* for future */
} __attribute__ ((__packed__));


#define PUBLIC __attribute__((visibility("default")))

#define le16_to_cpu __le16_to_cpu
#define le32_to_cpu __le32_to_cpu
#define le64_to_cpu __le64_to_cpu

#define SAVE_ERRNO_AND_CLOSE(fd) {	\
	int saved_errno = errno;	\
					\
	close(fd);			\
	errno = saved_errno;		\
}

#endif /* BTRFS_UTIL_INTERNAL_H */
