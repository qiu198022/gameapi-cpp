//
//  File.cpp
//  Playtomic
//
//  Created by matias on 12/15/11.
//  Copyright 2011 __Playtomic__. All rights reserved.
//
//  Documentation is available at:
//  http://playtomic.com/api/cpp
//
// PLEASE NOTE:
// You may modify this SDK if you wish but be kind to our servers.  Be
// careful about modifying the analytics stuff as it may give you
// borked reports.
//
// If you make any awesome improvements feel free to let us know!
//
// -------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY PLAYTOMIC, LLC "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "File.h"

#ifdef __ANDROID__
#include <android/log.h>
#define  LOG_TAG    "playtomicTest"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif

bool CFile::Exist(const std::string& fileName)
{
    return   Exist(fileName.c_str());
}

bool CFile::Exist(const char *pFileName)
{
    FILE* file = fopen(pFileName, "r");
    return (file != NULL);
}

bool CFile::Remove(const std::string& fileName)
{
    return   Exist(fileName.c_str());
}

bool CFile::Remove(const char *pFileName)
{
    return ( remove(pFileName) );
}

CFile::CFile()
{
    mFile = NULL;
}

CFile::CFile(const char* pFileName)
{
    mFile = NULL;
    Open(pFileName);
}

CFile::CFile(const std::string& fileName)
{
    mFile = NULL;
    Open(fileName.c_str());
}

CFile::~CFile()
{
    Close();
}

void CFile::Close()
{
    if(mFile)
    {
        fclose(mFile);
        mFile = NULL;
    }
}

bool CFile::Open(const std::string &fileName)
{
    return Open(fileName.c_str());
}

bool CFile::Open(const char *pFileName)
{
    if (mFile)
    {
        fclose(mFile);
    }
    mFile = fopen(pFileName, "a+");
    if(mFile == NULL)
    {
#if defined(__ANDROID__)
        LOGI("failed to open %s", pFileName);
#endif
        perror(" ");
        return false;
    }
    return true;
}


bool CFile::Write(const std::string &data)
{
    return Write(data.c_str());
}

bool CFile::Write(const char* data)
{
    if(mFile == NULL)
    {
        return false;
    }
    size_t ret = fwrite(data, strlen(data), sizeof(char), mFile);
    
    return ret==0;
}

bool CFile::WriteLine(const std::string &data)
{
    return WriteLine(data.c_str());
}

bool CFile::WriteLine(const char* data)
{
    if(mFile == NULL)
    {
        return false;
    }
    std::string line(data);
    line += '\n';
    size_t ret = fputs(line.c_str(), mFile);
    
    return ret==0;
}

void CFile::Rewind()
{
    rewind(mFile);
}
void CFile::Read(std::string &dest)
{
    fseek (mFile, 0, SEEK_END);
    long size = ftell (mFile);
    
    char* buff = new char[size];
    
    rewind(mFile);
    fread(buff, size, sizeof(char), mFile);
    
    dest = buff;
}

bool CFile::ReadLine(std::string &dest)
{
    if( mFile == NULL)
    {
        return false;
    }
    char buff[600];
    char* ret = fgets(buff,600,mFile);
    if(ret == NULL)
    {
        return false;
    }
    dest = buff;
    dest.erase(dest.length()-1,1);
    return ret != NULL;
}

size_t CFile::GetSize()
{
    if(mFile == NULL)
    {
        return 0;
    }
    size_t currPos = ftell(mFile);
    
    fseek(mFile, 0, SEEK_END);
    size_t ret = ftell(mFile);
    fseek(mFile, currPos, SEEK_SET);
    return ret;
}
