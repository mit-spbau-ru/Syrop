#include <string>
#include <vector>
#include <algorithm>

#include "fileinfo.h"
#include "system.h"

namespace utils
{

typedef std::vector<FileInfo> files_t;

struct Predicat
{
	Predicat(std::string const& s)
	: myValue(s)
	{}
	
	bool operator()(FileInfo const& info) const
	{
		return myValue == info.getName();
	}
	
	std::string myValue;
};

/**
 * Function tests that lock what placed in directory where
 *
 * @param where directory with lock
 * @param what lock name
 * @return true if lock is present and false otherwise
 * @throws std::runtime_error if an error occured
 */
bool locked(std::string const& where, std::string const& what)
{
	files_t const entries = listDirEntries(where);
	files_t::const_iterator it = find_if(entries.begin(),
						entries.end(), Predicat(what));
	
	return it != entries.end();
}

/**
 * Function tries to place lock what in the dir where
 *
 * @param what lock name
 * @return true if lock is places and false otherwise (if lock already present, for example)
 * @throws std::runtime_error if an error occured
 */
bool lock(std::string const& where, std::string const& what)
{
	if ( !locked(where, what) )
	{
		createDir(where);
		createFile(where + "/" + what);
		return true;
	}
	return false;
}

/**
 * Function tries to premove lock what from dir where
 *
 * @param what lock name
 * @return true if lock was removed and false otherwise
 * @throws std::runtime_error if an error occured
 */
bool unlock(std::string const& where, std::string const& what)
{
	if ( locked(where, what) )
	{
		removeFile(where + "/" + what);
		return true;
	}
	return false;
}

} // namespace utils
