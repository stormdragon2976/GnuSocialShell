/*
 * Copyright (C) 2016 Dan Rulos.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdio.h>

struct account_info {
	char name[64];
	char screen_name[64];
	char location[64];
	char description[256];
	char url[128];
	int followers;
	int friends;
	int statuses;
};

struct gss_account {
	char protocol[8];
	char user[64];
	char password[64];
	char server[32];
};

struct status {
	char text[1024];
	int id;
	char author_screen_name[64];
	int in_reply_to_id;
	char in_reply_to_user[64];
	char date[64];
};

struct group_info {
	int id;
	char url[128];
	char nickname[64];
	char fullname[64];
	/* ZERO if not, Non-ZERO if true */
	int member;
	int admins;
	int members;
	char description[256];
};

struct account_info get_my_account_info(struct gss_account account);

void send_status(struct gss_account account, char *msg);

void favorite(struct gss_account account, int id);

void unfavorite(struct gss_account account, int id);

void search_by_id(struct gss_account account, int id);

void delete_status_by_id(struct gss_account account, int id);

void answer_status_by_id(struct gss_account account, int id, char *msg);

void read_timeline(struct gss_account account, char *timeline, int n_status);

void retweet(struct gss_account account, int id, int code);

struct account_info get_user_info(struct gss_account account, char *source);

int verify_account(struct gss_account account);

struct group_info get_group_info(struct gss_account account, int id);

void join_group(struct gss_account account, int id);

void leave_group(struct gss_account account, int id);

void list_groups(struct gss_account account, int n_groups);

void print_users_array_info(struct gss_account account, char *source, int n_users);

struct status makeStatusFromRawSource(char *raw_data, int data_size);

void print_status(struct status status_);

size_t save_xml(void *ptr, size_t size, size_t nmemb, FILE *stream);

int parseXml(char *xml_data, int xml_data_size, char *tofind, int tofind_size, char *output, int output_size);
