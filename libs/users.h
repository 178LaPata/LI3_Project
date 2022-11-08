#pragma once

typedef struct xd_users *XD_USERS;

typedef struct xd_users_array *XD_USERS_ARRAY;

int users_array_max_size (XD_USERS_ARRAY array);

int users_array_size (XD_USERS_ARRAY array);

XD_USERS* users_array (XD_USERS_ARRAY array);



