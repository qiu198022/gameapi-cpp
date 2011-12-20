//
//  File.h
//  Playtomic
//
//  Created by matias on 12/15/11.
//  Copyright 2011 Playtomic. All rights reserved.
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

#ifndef __Playtomic_FILE_H__
#define __Playtomic_FILE_H__

#include <stdio.h>
#include <string>

class CFile
{
public:
    CFile();
    CFile(const char* pFileName);
    CFile(const std::string& fileName);
    ~CFile();
    
    static bool Exist(const char* pFileName);
    static bool Exist(const std::string& fileName);
    
    static bool Remove(const char* pFileName);
    static bool Remove(const std::string& fileName);
    
    bool Open(const char* pFileName);
    bool Open(const std::string& fileName);
    void Close();
    
    bool Write(const char* data);
    bool Write(const std::string& data);
    
    bool WriteLine(const char* data);
    bool WriteLine(const std::string& data);
    
    void Rewind(void);
    
    void Read(std::string& dest);
    bool ReadLine(std::string& dest);
    
    size_t GetSize();
private:
    FILE*   mFile;
};
#endif
