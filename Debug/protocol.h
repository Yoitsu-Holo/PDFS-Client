#ifndef PROTOCOL_H
#define PROTOCOL_H

#endif // PROTOCOL_H

#define RunStateCode char
#define RSC RunStateCode

//word lenth
#define username_end            20
#define password_end            40
#define key_end                 20
#define keyLength               20

//run code
#define run_NoError             0
#define run_UnknowError         1
#define run_IllegalInput        2
#define run_FileExist           3
#define run_DirExist            4
#define run_FileUnexist         5
#define run_DirUnexist          6

//error code
#define noError                 0
#define error_IllegalIp         1
#define error_IllegalPort       2

//op code
#define opCode_noError          0
#define opCode_CreateUser       1
#define opCode_DeleteUser       2
#define opCode_ChangePassword   3
#define opCode_Login            4
#define opCode_WriteFile        5
#define opCode_ReadFile         6
#define opCode_deleteFile       7
#define opCode_CreatePath       8
#define opCode_DeletePath       9
#define opCode_ServerExtend     127
#define opCode_RequestDir       255

//state code
#define stCode_Seccess          0
#define stCode_UnknowError      1
#define stCode_FileUnexist      2
#define stCode_PathUnexist      3
#define stCode_ErrorPassword    4
#define stCode_UserExisted      5
#define stCode_UserUnexist      6
#define stCode_ParameterError   7
#define stCode_OpUnexist        8

//server returned code
#define svReturn_seccess        0
#define svReturn_UnknowError    1
#define svReturn_FileUnexist    2
#define svReturn_OpUnexist      3
