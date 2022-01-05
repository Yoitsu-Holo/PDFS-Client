#include <map>
#include <vector>
#include <string>
#include <cstring>

#include "protocol.h"

namespace file_inner_struct
{
    using namespace std;
    class PDFS_File
    {
    private:
        string filename;
        string filetype;
        size_t filesize;
        char sha[32];

    public:
        PDFS_File() : filename(""), filetype(""), filesize(0), sha()
        {
            memset(sha, 0x0, sizeof(sha));
        }

        PDFS_File(string RawFileName, size_t FileSize, char *SHA)
        {
            int pos = RawFileName.length();
            for (pos--; pos >= 0; pos--)
                if (RawFileName[pos] == '.')
                    break;

            filename = "";
            filetype = "";

            if (pos == -1)
                filename = RawFileName,
                filetype = "unknow";
            else
                for (int i = 0; i < (int)RawFileName.length(); i++)
                    if (i < pos)
                        filename += RawFileName[i];
                    else if (i > pos)
                        filetype += RawFileName[i];

            filesize = FileSize;
            memcpy(sha, SHA, 32);
        }

        void setFileName(string FileName) { filename = FileName; }
        void setFileType(string FileType) { filetype = FileType; }
        void setFileSize(size_t FileSize) { filesize = FileSize; }
        void setSHAcode(char *SHA) { memcpy(sha, SHA, 32); }
        void setFileInfo(string RawFileName, size_t FileSize, char *SHA)
        {
            PDFS_File tempFile(RawFileName, FileSize, SHA);
            *this = tempFile;
        }

        string getFileName() { return filename; }
        string getFileType() { return filetype; }
        size_t getFileSize() { return filesize; }
        const char *getSHA() { return sha; }
    };

    class PDFS_Dir
    {
    private:
        map<string, PDFS_Dir *> ListDir;
        map<string, PDFS_File *> ListFile;
        string dirname;
        PDFS_Dir *prePath;
        char sha[32];

    public:
        PDFS_Dir() : ListDir(), ListFile(), dirname(""), prePath(NULL), sha() {}
        PDFS_Dir(string DirName, char *SHA, PDFS_Dir *PrePath)
        {
            dirname = DirName;
            prePath = PrePath;
            memcpy(sha, SHA, 32);
        }

        void setDirName(string DirName) { dirname = DirName; }
        void setSHA(char *SHA) { memcpy(sha, SHA, 32); }
        void setPrePath(PDFS_Dir *PrePath) { prePath = PrePath; }
        PDFS_Dir *getPrePath() { return prePath; }
        string getDirName() { return dirname; }
        const char *getSHA() { return sha; }
        map<string, PDFS_Dir *> getDirInfo() { return ListDir; }
        map<string, PDFS_File *> getFileInfo() { return ListFile; }

        RSC addFile(PDFS_File *File)
        {
            if (ListFile.find(File->getFileName()) != ListFile.end())
                return run_FileExist;
            ListFile[File->getFileName()] = File;
            return run_NoError;
        }

        RSC addDir(PDFS_Dir *Dir)
        {
            if (ListDir.find(Dir->getDirName()) != ListDir.end())
                return run_DirExist;
            ListDir[Dir->getDirName()] = Dir;
            return run_NoError;
        }

        RSC delFile(PDFS_File *File)
        {
            if (ListFile.find(File->getFileName()) == ListFile.end())
                return run_FileUnexist;
            ListFile.erase(ListFile.find(File->getFileName()));
            return run_NoError;
        }

        RSC delDir(PDFS_Dir *Dir)
        {
            if (ListDir.find(Dir->getDirName()) == ListDir.end())
                return run_DirUnexist;
            ListDir.erase(ListDir.find(Dir->getDirName()));
            return run_NoError;
        }

        RSC delFile(string FileName)
        {
            if (ListFile.find(FileName) == ListFile.end())
                return run_FileUnexist;
            ListFile.erase(ListFile.find(FileName));
            return run_NoError;
        }

        RSC delDir(string DirName)
        {
            if (ListDir.find(DirName) == ListDir.end())
                return run_DirUnexist;
            ListDir.erase(ListDir.find(DirName));
            return run_NoError;
        }
    };
};

class PDFS_FileSystem
{
#define FIS file_inner_struct

private:
    FIS::PDFS_Dir *root;
    FIS::PDFS_Dir *now;

    std::vector<std::string> path;

public:
    PDFS_FileSystem() : root(new FIS::PDFS_Dir()) { now = root; };
    std::string getPath()
    {
        std::string fullPath;
        for (auto &&dir : path)
            fullPath.append("\\").append(dir);
        return fullPath;
    }
    std::vector<std::vector<std::string>> getFileTree()
    {
        std::vector<std::vector<std::string>> FileTree;
        std::vector<std::string> FileInfo;
        for (auto &&Ele : now->getDirInfo())
        {
            FileInfo.clear();
            FileInfo.push_back(Ele.second->getDirName());
            FileInfo.push_back("<DIR>");
            FileInfo.push_back("-----");
            FileTree.push_back(FileInfo);
        }
        for (auto &&Ele : now->getFileInfo())
        {
            FileInfo.clear();
            FileInfo.push_back(Ele.second->getFileName());
            FileInfo.push_back(Ele.second->getFileType());
            FileInfo.push_back(std::to_string(Ele.second->getFileSize()));
            FileTree.push_back(FileInfo);
        }
        return FileTree;
    }
    int addFile(std::string RawFileName, size_t FileSize, char *SHA)
    {
        FIS::PDFS_File *File = new FIS::PDFS_File(RawFileName, FileSize, SHA);
        return now->addFile(File);
    }

    int addDir(std::string DirName, char *SHA)
    {
        FIS::PDFS_Dir *Dir = new FIS::PDFS_Dir(DirName, SHA, now);
        return now->addDir(Dir);
    }

    int delFile(FIS::PDFS_File *File) { return now->delFile(File); }
    int delDir(FIS::PDFS_Dir *Dir) { return now->delDir(Dir); }
    int delFile(std::string FileName) { return now->delFile(FileName); }
    int delDir(std::string DirName) { return now->delDir(DirName); }
    int inPath(std::string DirName)
    {
        if (now->getDirInfo().find(DirName) == now->getDirInfo().end())
            return run_DirUnexist;
        now = now->getDirInfo()[DirName];
        return run_NoError;
    }
    void outPath() { now = now->getPrePath(); }
};