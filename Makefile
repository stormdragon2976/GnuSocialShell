CC = gcc
OBJ_NAME = gss
OBJS = Main.c loadConfig.c lib/get_account_info.c lib/gnusocial.c gnusocialshell.c lib/send_status.c lib/favorite.c lib/search_by_id.c lib/delete_status_by_id.c lib/answer_status_by_id.c lib/read_timeline.c lib/retweet_by_id.c lib/get_user_info_by_id.c lib/print_users_array_info.c lib/verify_account.c lib/get_group_info.c lib/join_group.c lib/leave_group.c lib/list_groups.c
FLAGS = -Wall -lcurl

all:
	$(CC) $(FLAGS) $(OBJS) -o $(OBJ_NAME) $$(pkg-config libcurl --cflags --libs)
clean:
	rm $(OBJ_NAME)

