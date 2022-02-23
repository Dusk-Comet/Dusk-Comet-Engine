#ifndef DUSKCOMET_SYSTEM_PAK__HPP
#define DUSKCOMET_SYSTEM_PAK__HPP

#include <vector>
#include <string>
#include <map>

namespace dc
{
	
	class Pak; //Forward declare to allow us to make as a friend class
	class PakDirectory; //Forward declare so we can use it as pointer

	class PakFileEntry
	{
	protected:
		Pak* _pakFile = nullptr;
		PakDirectory* _parent = nullptr;

		std::string _fileName = "";

	public:

		Pak* getParentPakFile();
		PakDirectory* getParentDirectory();

		std::string getFilePath();

		friend class Pak;
	};

	class PakFile : public PakFileEntry
	{
	private:
		std::string _fileExtension = "";

	public:

		friend class Pak;
	};

	class PakDirectory : public PakFileEntry
	{
	private:
		std::map<std::string, PakFile> _files;
		std::map<std::string, PakDirectory> _directories;

	public:

		std::vector<std::string> getFileSystemEntries();


		PakDirectory* getDirectory(std::string name);
		PakFile* getFile(std::string name);

		friend class Pak;
	};

	class Pak
	{
	private:
		PakDirectory _rootDirectory = PakDirectory();

	public:
		Pak();
		PakDirectory* getRoot();

	};
}

#endif // !DUSKCOMET_SYSTEM_PAK__HPP
