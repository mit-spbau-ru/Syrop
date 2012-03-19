#ifndef _CORE_SYROP_H_
#define _CORE_SYROP_H_

#include <cstdlib>
#include <unistd.h>
#include <getopt.h>

#include <map>
#include <string>

struct SyropControlArgs
{
	bool apply;
	bool rollback;
	bool create;
	bool help;
	std::string network;
};

static char const *argsDecsripton = "ca:rh";

static const struct option longOps[] = 
{
	{"create",    no_argument,       NULL, 'c'},
	{"apply",     required_argument, NULL, 'a'},
	{"roll_back", no_argument,       NULL, 'r'},
	{"help",      no_argument,       NULL, 'h'},
	{NULL,        no_argument,       NULL, 0}
};

typedef std::map<std::string, std::string> plugins_t;

#endif // _CORE_SYROP_H_
