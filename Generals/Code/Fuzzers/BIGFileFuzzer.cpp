/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																			  //
//  (c) 2025 Electronic Arts Inc.											  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

// BIGFileFuzzer.cpp - Fuzzer for BIG file parsing
// This fuzzer tests the BIG file parser for potential vulnerabilities

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <string>
#include <memory>

#include "Common/LocalFileSystem.h"
#include "Common/RAMFile.h"
#include "Win32Device/Common/Win32BIGFileSystem.h"
#include "Win32Device/Common/Win32BIGFile.h"

// Mock implementation of required globals
LocalFileSystem* TheLocalFileSystem = nullptr;
GameAudio* TheAudio = nullptr;

// Create a temporary file with the fuzzer-provided data
class FuzzerFile : public File {
public:
    FuzzerFile(const uint8_t* data, size_t size) 
        : m_data(data), m_size(size), m_position(0) {}

    virtual ~FuzzerFile() {}

    virtual Bool open(const Char* filename, Int access) override { return TRUE; }
    virtual void close() override {}
    virtual Bool isOpen() const override { return TRUE; }
    virtual Int read(void* buffer, Int size) override {
        if (m_position >= m_size) return 0;
        
        Int bytesToRead = (m_position + size > m_size) ? (m_size - m_position) : size;
        memcpy(buffer, m_data + m_position, bytesToRead);
        m_position += bytesToRead;
        return bytesToRead;
    }
    virtual Int write(const void* buffer, Int size) override { return 0; }
    virtual Int seek(Int offset, Int origin) override {
        switch (origin) {
            case START:
                m_position = offset;
                break;
            case CURRENT:
                m_position += offset;
                break;
            case END:
                m_position = m_size + offset;
                break;
        }
        if (m_position < 0) m_position = 0;
        if (m_position > m_size) m_position = m_size;
        return m_position;
    }
    virtual Int tell() const override { return m_position; }
    virtual Int getSize() const override { return m_size; }
    virtual const Char* getName() const override { return "fuzzer.big"; }
    virtual Bool deleteOnClose() override { return FALSE; }
    virtual void deleteOnClose(Bool) override {}

private:
    const uint8_t* m_data;
    size_t m_size;
    Int m_position;
};

// Mock LocalFileSystem implementation
class MockLocalFileSystem : public LocalFileSystem {
public:
    MockLocalFileSystem() {}
    virtual ~MockLocalFileSystem() {}

    void setFuzzerData(const uint8_t* data, size_t size) {
        m_data = data;
        m_size = size;
    }

    virtual File* openFile(const Char* filename, Int access) override {
        return new FuzzerFile(m_data, m_size);
    }

    virtual Bool getFileInfo(const AsciiString& filename, FileInfo* fileInfo) const override {
        if (fileInfo) {
            fileInfo->sizeHigh = 0;
            fileInfo->sizeLow = m_size;
            fileInfo->attributes = 0;
            fileInfo->createTime = 0;
            fileInfo->accessTime = 0;
            fileInfo->writeTime = 0;
        }
        return TRUE;
    }

private:
    const uint8_t* m_data = nullptr;
    size_t m_size = 0;
};

// Mock GameAudio implementation
class MockGameAudio : public GameAudio {
public:
    MockGameAudio() {}
    virtual ~MockGameAudio() {}

    virtual void stopAudio(AudioAffect) override {}
    // Add other required overrides as needed
};

// The fuzzer entry point
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
    // Skip very small inputs
    if (Size < 16) {
        return 0;
    }

    // Initialize mocks
    MockLocalFileSystem mockFileSystem;
    MockGameAudio mockAudio;
    TheLocalFileSystem = &mockFileSystem;
    TheAudio = &mockAudio;

    // Set up the fuzzer data
    mockFileSystem.setFuzzerData(Data, Size);

    // Create a BIG file system
    Win32BIGFileSystem bigFileSystem;

    // Try to open and parse the BIG file
    try {
        ArchiveFile* archiveFile = bigFileSystem.openArchiveFile("fuzzer.big");
        
        // If successful, try to access some files in the archive
        if (archiveFile) {
            // Get the list of files in the archive
            List<AsciiString> fileList;
            archiveFile->getFileList(fileList);

            // Try to open some files from the archive
            for (List<AsciiString>::iterator it = fileList.begin(); it != fileList.end(); ++it) {
                File* file = archiveFile->openFile(it->str());
                if (file) {
                    // Read some data from the file
                    char buffer[1024];
                    file->read(buffer, sizeof(buffer));
                    file->close();
                }
            }

            // Clean up
            delete archiveFile;
        }
    }
    catch (...) {
        // Catch any exceptions to continue fuzzing
    }

    // Clean up
    TheLocalFileSystem = nullptr;
    TheAudio = nullptr;

    return 0;
}