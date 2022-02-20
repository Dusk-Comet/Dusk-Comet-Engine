#include "Pak.hpp"



namespace dc
{

	Pak* PakFileEntry::getParentPakFile()
	{
		return this->_pakFile;
	}

	PakDirectory* PakFileEntry::getParentDirectory()
	{
		return this->_parent;
	}


	std::vector<std::string> PakDirectory::getFileSystemEntries()
	{
		return std::vector<std::string>();
	}
	PakDirectory* PakDirectory::getDirectory(std::string name)
	{
		return nullptr;
	}
	PakFile* PakDirectory::getFile(std::string name)
	{
		return nullptr;
	}


	Pak::Pak()
	{
		this->_rootDirectory._pakFile = this;
	}

	PakDirectory* Pak::getRoot()
	{
		return &_rootDirectory;
	}


}