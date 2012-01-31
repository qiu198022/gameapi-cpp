#OBJ=CData.o CGameVars.o CGeoIp.o CLeaderboard.o CLevel.o CLink.o CLog.o CLogRequest.o CPlayerLevels.o CPlaytomic.o CScore.o \
#../Tools/MD5.o ../Tools/timer.o ../Tools/StringHelper.o \
#../CurlWrap/CConnectionInterface.o ../CurlWrap/CPlaytomicResponse.o ../CurlWrap/CPost.o ../CurlWrap/CRequest.o \
#../json/src/json_reader.o ../json/src/json_value.o ../json/src/json_writer.o

MY_FILES = $(wildcard *.cpp)
MY_FILES += $(wildcard Unix/*.cpp)
MY_FILES += $(wildcard ../CurlWrap/*.cpp)
MY_FILES += $(wildcard ../json/src/*.cpp)
MY_FILES += $(wildcard ../Tools/*.cpp)
MY_FILES += $(wildcard Linux/*.cpp)
LOCAL_SRC_FILES = $(MY_FILES:%.cpp=%.o) 

OBJ = ${LOCAL_SRC_FILES}
