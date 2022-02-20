#ifndef DUSKCOMET_SYSTEM_FILESYSTEMOBJECTINFO__HPP
#define DUSKCOMET_SYSTEM_FILESYSTEMOBJECTINFO__HPP

#include <cstdint>

namespace dc
{
	struct FileSystemObjectInfo
	{
	public:
		uint64_t CreationUnixTime;
		uint64_t LastModifiedUnixTime;
	};
}
#endif // !DUSKCOMET_SYSTEM_FILESYSTEMOBJECTINFO__HPP
