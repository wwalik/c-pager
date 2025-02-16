#pragma once

typedef enum TOKEN_TYPE
{
	NONE,
	C_TYPE,
	C_OPERATOR,
} TOKEN_TYPE;

extern TOKEN_TYPE
find_type(const char *token);
